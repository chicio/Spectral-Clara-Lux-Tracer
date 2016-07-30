//
//  AxisAlignedBoundingBox.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 16/06/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "AxisAlignedBoundingBox.hpp"

bool AxisAlignedBoundingBox::intersect(const Ray& ray) {

    float tmin = (min.x - ray.origin.x) / ray.direction.x;
    float tmax = (max.x - ray.origin.x) / ray.direction.x;
    
    if (tmin > tmax) {

        std::swap(tmin, tmax);
    }
    
    float tymin = (min.y - ray.origin.y) / ray.direction.y;
    float tymax = (max.y - ray.origin.y) / ray.direction.y;
    
    if (tymin > tymax) {
        
        std::swap(tymin, tymax);
    }
    
    if ((tmin > tymax) || (tymin > tmax)) {
        
        return false;
    }
    
    if (tymin > tmin) {

        tmin = tymin;
    }
    
    if (tymax < tmax) {
        
        tmax = tymax;
    }
    
    float tzmin = (min.z - ray.origin.z) / ray.direction.z;
    float tzmax = (max.z - ray.origin.z) / ray.direction.z;
    
    if (tzmin > tzmax) {

        std::swap(tzmin, tzmax);
    }
    
    if ((tmin > tzmax) || (tzmin > tmax)) {
        
        return false;
    }
    
    return true;
}
