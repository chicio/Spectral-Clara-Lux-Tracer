//
//  Intersection.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 05/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Intersection_hpp
#define Intersection_hpp

#include "Point3D.hpp"
#include "Vector3D.hpp"

class Model;

class Intersection {
public:
    
    /// Normal of the surface of the closest object.
    Vector3D normal;
    /// Point of intersection.
    Point3D point;
    /// ClosectObject intersected with the ray.
    Model* object;
    /// Distance.
    float t;
    /// Normal not normalized.
    Vector3D originalNormal;
    
    /*!
     Constructor.
     
     @param point point of intersection.
     @param t distance.
     @param normal normal of the surface.
     @param originalNormal original normal vector. 
     @param object closest object.
     */
    Intersection(Point3D point,
                 float t,
                 Vector3D normal,
                 Vector3D originalNormal,
                 Model* object) : point{point},
                                  t{t},
                                  normal{normal},
                                  originalNormal(originalNormal),
                                  object{object} {};
};

#endif /* Intersection_hpp */
