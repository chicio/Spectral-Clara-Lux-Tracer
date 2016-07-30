//
//  Sphere.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 05/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Sphere.hpp"

Vector3D Sphere::normal(const Point3D& pointOnSphere) const {
    
    //Normal is just a difference between the point on the sphere and the center of the sphere.
    Vector3D normal = pointOnSphere - center;
    
    return normal;
}

Intersection* Sphere::intersect(const Ray& ray) {
    
    Vector3D delta = ray.origin - center;
    
    float A = ray.direction.dot(ray.direction);
    float B = 2 * delta.dot(ray.direction);
    float C = delta.dot(delta) - radius * radius;
    
    float discr = B * B - 4 * A * C;
    
    if(discr < 0) {
        
        return nullptr;
    }
    
    float s = sqrtf(discr);
    float t0 = (-B - s) / (2 * A);
    float t1 = (-B + s) / (2 * A);
    float t = -1;
    
    if (t0 > 0 && t1 > 0) {
        
        t = std::fmin(t0, t1);
    }else if (t0 > 0 && t1 < 0) {
        
        t = t0;
    } else if (t0 < 0 && t1 > 0) {
        
        t = t1;
    } else {
        
        return nullptr;
    }
    
    //Intersection point.
    Vector3D prodvs = ray.direction * t;
    Point3D intersectionPoint = ray.origin + prodvs;
    
    //Original normal.
    Vector3D originalNormal = this->normal(intersectionPoint);

    //Normal (already normalized).
    Vector3D normal = originalNormal;
    normal.normalize();
    
    Intersection* result = new Intersection(intersectionPoint, t, normal, originalNormal, this);
        
    return result;
}

TextureCoordinate Sphere::textureCoordinate(const Point3D& intersectionPoint) const {
    
    TextureCoordinate tc;
    
    //Possible improvement: north and equator direction as parameter.
    Vector3D northDirection(0.0f, 1.0f, 0.0f);
    Vector3D equatorDirection(1.0f, 0.0f, 0.0f);
    Vector3D r = intersectionPoint - center;
    r.normalize();
    
    float phi = acosf(-1 * northDirection.dot(r));
    tc.v = phi / constant::pi;
    
    float theta = (acosf(r.dot(equatorDirection) / sinf(phi))) / (2.0f * constant::pi);

    //Check if point is on the side of the equator direction points to
    if((northDirection.cross(equatorDirection)).dot(r) > 0.0f) {
        
        tc.u = theta;
    } else {
        
        tc.u = 1.0f - theta;
    }
    
    return tc;
}
