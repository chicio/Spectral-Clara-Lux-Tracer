//
//  SCLT.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 07/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"

#include <iostream>
#include <future>

#include "SCLT.hpp"
#include "TracerModelFactory.hpp"

SCLT::SCLT(ViewPlane viewPlane, std::string sceneName, int antialiasingNOfSample) {
    
    //Init view plane and total pixel to be calculated.
    vplane = viewPlane;
    totalPixel = vplane.width * vplane.height;
    
    //Init number of sampling for antialiasing.
    antialiasingNumOfSample = antialiasingNOfSample;
    
    //Init scene.
    scene = new Scene(sceneName);
    
    //Init tracer.
    tracer = TracerModelFactory().createTracer(scene->tracerModelType, scene);
}

std::vector<Vector3D> SCLT::runSCLTRayTracer() const {
 
    //Camera setup.
    Camera camera(scene->viewReferencePoint, scene->lookAtPoint, Vector3D(0, 1, 0), vplane, scene->viewPlaneDistance);

    //Antialiasing setup.
    float antialiasingIncrementQuantity = 1.0f / (float)antialiasingNumOfSample;
    float antialiasingSampleWeight = 1.0f / powf((float)antialiasingNumOfSample, 2.0f);
    
    //Pixels array.
    std::vector<Vector3D> pixels;
    
    for (int y = 0; y < vplane.height; y++) {
        
        //Init vector of futures used for async trace operations.
        std::vector<std::future<Vector3D>> futures;

        for (int x = 0;  x < vplane.width;  x++) {

            //Each pixels is calculated async.
            futures.push_back(std::async(std::launch::async, [](Scene* scene,
                                                                Camera camera,
                                                                Tracer* tracer,
                                                                int x,
                                                                int y,
                                                                int antialiasingNumOfSample,
                                                                float antialiasingIncrementQuantity,
                                                                float antialiasingSampleWeight) {

                Vector3D color(0, 0, 0);
                
                for (int i = 0; i < antialiasingNumOfSample; i++) {
                    for (int j = 0;  j < antialiasingNumOfSample;  j++) {
                        
                        float u = x + ((i + antialiasingIncrementQuantity) / antialiasingNumOfSample);
                        float v = y + ((j + antialiasingIncrementQuantity) / antialiasingNumOfSample);
                        
                        //Compute ray direction in camera coordinate.
                        Ray ray(scene->viewReferencePoint, camera.rayInCameraCoordinateSystem(u, v));                        
                        color = color + tracer->getColor(ray, constant::maxNumberOfBounce);                        
                    }
                }
                
                color = color * antialiasingSampleWeight;

                return color;

            }, scene,
               camera,
               tracer,
               x,
               y,
               antialiasingNumOfSample,
               antialiasingIncrementQuantity,
               antialiasingSampleWeight));

#if (defined(__APPLE__) || defined(_WIN32)) && !defined(COMMAND_LINE)
            
            progressUpdate(y * vplane.width + x);
            
#endif
        }
        
        //Get result of async trace operation.
        for(auto& color : futures) {
            
            pixels.push_back(color.get());
        }

        std::cout << "Progress: " << floor(((float)y/(float)vplane.height) * 100.0f) << "% - Rows completed: " << y << "\r" << std::flush;
    }

    std::cout << "Progress: 100% - Rows completed: " << vplane.height << "\r" << std::flush;

    return pixels;
}

bool SCLT::validScene(std::string& sceneErrorsDescription) {
    
    bool sceneValid = scene->isSceneValid();
    sceneErrorsDescription = scene->getSceneErrorsDescription();
    
    return sceneValid;
}

#if defined(__APPLE__) && !defined(COMMAND_LINE)

void SCLT::setDelegate(id<ProgressDelegate> delegate) {
    
    progressDelegate = delegate;
}

#endif

#if defined(_WIN32) && !defined(COMMAND_LINE)

void SCLT::setDelegate(MainPage^ mp) {

	mainPage = mp;
}

#endif

void SCLT::progressUpdate(int currentPixel) const {

	float progress = (float)currentPixel / (float)totalPixel;

#if defined(__APPLE__) && !defined(COMMAND_LINE)
    
	//Async update of the progress bar using delegate pattern.
    [progressDelegate rayTracerProgressUpdate:progress];
    
#endif

#if defined(_WIN32) && !defined(COMMAND_LINE)

	//Async update with delegation pattern also on 
	//Microsoft platforms. This is a fast solution
	//that use only concurrency::task (possible improvement:
	//find a way to use IAsyncInterfaceWithProgress).
	//To avoid continuos block of the UI Thread,
	//update the progress bar every 500 pixel.
	if (currentPixel % 500 == 0) {
		mainPage->update(progress);
	}

#endif
    
}

SCLT::~SCLT() {
    
    delete scene;    
    delete tracer;
}
