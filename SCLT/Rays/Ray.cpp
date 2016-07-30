//
//  Ray.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 06/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Ray.hpp"

Vector3D Ray::reflectedRayDirection(const Vector3D& normal,
                                    const Vector3D& rayToBeReflectedDirection,
                                    float cosI) {
    
    float cosINegative = -1.0f * cosI;
    Vector3D reflectedRayDirection = rayToBeReflectedDirection + ((normal * cosINegative) * 2.0f);
    
    return reflectedRayDirection;
}

Vector3D* Ray::refractedRayDirection(const Vector3D& normal,
                                     const Vector3D& rayToBeRefractedDirection,
                                     const float refractiveIndexObject,
                                     float cosI,
                                     float& n) {
    
    Vector3D norm = normal;
    
    //The default refractive index for n1 is 1 (vacuum).
    if(cosI < 0.0f) {
        
        //I am going from vacuum inside our transmissive material.
        n = 1.0f / refractiveIndexObject;
        cosI = -1.0f * cosI;
    } else {
        
        //I am going from inside our transmissive material to vacuum.
        n = refractiveIndexObject;
        norm = norm * -1.0f;
    }
    
    float cosThetaT = fmaxf(0.0f, sqrtf(1.0f - powf(n, 2.0f) * (1.0f - (powf(cosI, 2.0f)))));
    
    if (cosThetaT == 0.0f) {
        
        //Total internal reflection.
        return nullptr;
    }
    
    //Ray direction.
    Vector3D temp1 = rayToBeRefractedDirection * n;
    Vector3D temp2 = norm * (n * cosI - cosThetaT);
    Vector3D refractedRayDirection = (temp1 + temp2);
    
    return new Vector3D(refractedRayDirection.x, refractedRayDirection.y, refractedRayDirection.z);
}
