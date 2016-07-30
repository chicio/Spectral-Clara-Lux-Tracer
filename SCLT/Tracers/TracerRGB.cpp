//
//  TracerRGB.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 18/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "TracerRGB.hpp"

TracerRGB::TracerRGB(Scene* scene) : Tracer(scene) {
    
    shadingModel = ShadingModelFactory().createShadingModelRGB(scene->shadingModelType);
};

Vector3D TracerRGB::getColor(const Ray& ray, const int bounce) const {
    
    Vector3D color = trace(ray, bounce);
    
    color.x = MathUtils::clamp(color.x, 0.0f, 255.0f);
    color.y = MathUtils::clamp(color.y, 0.0f, 255.0f);
    color.z = MathUtils::clamp(color.z, 0.0f, 255.0f);
    
    return color;
}

Vector3D TracerRGB::trace(const Ray& ray, const int bounce) const {
    
    Vector3D color;
    
    Intersection* intersectionData = Tracer::closestIntersection(ray);
    
    if(intersectionData == nullptr){
        
        if(scene->cubeMappingSkybox != nullptr) {
            
            //Read CUBE MAPPING SKYBOX with the appropriate method.
            //Not all scene have a cube mapping, so there's fallback to black color.
            color = scene->cubeMappingSkybox->readSkyboxTexture(ray);
        }
    } else {
        
        //Apply shade on the current object.
        color = shadingModel->shade(*intersectionData, ray, bounce, *this);
    }
    
    //Clean intersection data.
    delete intersectionData;
        
    return color;
}
