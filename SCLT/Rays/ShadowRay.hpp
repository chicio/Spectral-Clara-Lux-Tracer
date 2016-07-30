//
//  ShadowRay.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 04/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef ShadowRay_hpp
#define ShadowRay_hpp

#include "Ray.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"

class ShadowRay : public Ray {
public:
    
    /// Ray instance.
    Ray *ray;
    /// Magnitude of the shadow ray.
    float d;

    /*!
     Constructor.
     
     @param intersectionPoint insersection point used as origin of the ray.
     @param lightOrigin origin of light used as end of ray.
     */
    ShadowRay(const Point3D& intersectionPoint, const Point3D& lightOrigin);
    
    /*!
     Default constructor.
     */
    ~ShadowRay();
};

#endif /* ShadowRay_hpp */
