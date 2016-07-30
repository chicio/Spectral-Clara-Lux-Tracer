//
//  AxisAlignedBoundingBox.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 16/06/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#ifndef AxisAlignedBoundingBox_hpp
#define AxisAlignedBoundingBox_hpp

#include <vector>

#include "Model.hpp"
#include "Ray.hpp"

class AxisAlignedBoundingBox {
public:
    
    /// Min vertex extent of the AABB.
    Point3D min;
    /// Max vertex extent of the AABB.
    Point3D max;
    
    /*!
     AABB ray intersection.
     Test for intersection between a ray and the AABB.
     
     @see Scratchpixel 2.0 "Ray-Box Intersection".
     @see http://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
     
     @param ray the ray to be tested for intersection.
     
     @returns true if ray intersect the box, else false.
     */
    bool intersect(const Ray& ray);
};

#endif /* AxisAlignedBoundingBox_hpp */
