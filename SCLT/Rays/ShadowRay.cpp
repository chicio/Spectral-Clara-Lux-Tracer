//
//  ShadowRay.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 10/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "ShadowRay.hpp"

ShadowRay::ShadowRay(const Point3D& intersectionPoint, const Point3D& lightOrigin) {
    
    Vector3D shadowRayDirection = lightOrigin - intersectionPoint;
    float magnitude = shadowRayDirection.magnitude();
    
    //Normalize the shadow ray direction.
    shadowRayDirection.normalize();
    
    //Ray origin.
    Point3D shadowRayOrigin = MathUtils::addEpsilon(intersectionPoint, shadowRayDirection);
    
    //Set shadow ray data.
    ray = new Ray(shadowRayOrigin, shadowRayDirection);;
    d = magnitude;
};

ShadowRay::~ShadowRay() {
    
    delete ray;
}
