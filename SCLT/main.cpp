//
//  main.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 24/06/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include <chrono>
#include <iostream>

#include "pch.h"
#include "lodepng.h"
#include "SCLT.hpp"

/*!
 Rasterization for command line version of SCLT.
 Save result of rendering as an image on this in the executable folder.

 @param vplane the view plane.
 @param pixels array of pixels generated from SCLT rendering.

 @returns rasterization.
 */
unsigned rasterize(const ViewPlane& vplane, const std::vector<Vector3D>& pixels, const char* imageName) {

    const int bytesPerPixel = 4;
    std::vector<unsigned char> image(bytesPerPixel * vplane.width * vplane.height);
    int rowPosition = 0;

    for (unsigned int k = 0; k < vplane.height; k++) {

        for (unsigned int i = 0; i < (vplane.width * bytesPerPixel); i += bytesPerPixel) {

            Vector3D pixelColor = pixels[(vplane.height - k - 1) * vplane.width + rowPosition];

            int pos = k * (vplane.width * bytesPerPixel) + (i);
            image[pos] = (unsigned char)pixelColor.x;
            image[pos + 1] = (unsigned char)pixelColor.y;
            image[pos + 2] = (unsigned char)pixelColor.z;
            image[pos + 3] = 255;

            rowPosition++;
        }

        //Reset row position.
        rowPosition = 0;
    }

    //Raster to image using lodepng.
    unsigned rasterizeError = lodepng::encode(imageName, image, vplane.width, vplane.height);

    //Return eventually errors.
    return rasterizeError;
}

/*!
 SCLT command line version entry point.

 @param argc arguments count.
 @param argv arguments vector.

 @returns 0.
 */
int main(int argc, char* argv[]) {

	if(argc < 6) {
		
		//No scene name received, stop execution.		
        std::cout << "Usage: "<< argv[0] << "<scene filename path> "
                                            "<number of antialiasing sample> "
                                            "<width> "
                                            "<height> "
                                            "<result image name>" << std::endl;
		return 0;
	}

	std::cout << "Scene selected: " << argv[1] << std::endl;
	
	//Ray tracing parameter.
    int antialiasingNumOfSample = atoi(argv[2]);
	ViewPlane vplane = ViewPlane(atoi(argv[3]), atoi(argv[4]));

	SCLT scltRayTracer(vplane, argv[1], antialiasingNumOfSample);
	
	//Validate scene.
	std::string sceneErrorsDescription;
	bool isSceneValid = scltRayTracer.validScene(sceneErrorsDescription);
	
    if(!isSceneValid) {
        
        std::cout << sceneErrorsDescription << std::endl;
        return 0;
    }
    
    //Start count time.
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    
    //Render scene.
    std::vector<Vector3D> pixels = scltRayTracer.runSCLTRayTracer();

    //Rasterize.
    unsigned rasterizationError = rasterize(vplane, pixels, argv[5]);

    if(rasterizationError != 0) {

        ///Debug lodepng error.
        std::cout << "Error lodepng: " << rasterizationError << std::endl;
    }
    
    //Calculate rendering time and show to the user.
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    long renderingSeconds = std::chrono::duration_cast<std::chrono::seconds>( t2 - t1 ).count();

    long hour = lround(floor(renderingSeconds / 3600)) % 100;
    long minute = lround(floor(renderingSeconds / 60)) % 60;
    long seconds = lround(floor(renderingSeconds)) % 60;

    std::cout << "Completed!" << std::endl;
    std::cout << "Rendering time: " << hour << " hours - " << minute << " minutes - " << seconds << " seconds" << std::endl;
    
    return 0;
}
