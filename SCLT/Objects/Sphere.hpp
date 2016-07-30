//
//  Sphere.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 05/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <random>

#include "Model.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"
#include "Point3D.hpp"

class Sphere : public Model {
public:
  
    /// Center of the sphere as a Point3D.
    Point3D center;
    /// Radius of the sphere.
    float radius;

    /*!
     Default constructor.
     */
    Sphere() : center{Point3D()}, radius{0} {};
    
    /*!
     Init a sphere object.
     
     @param center center of the sphere.
     @param radius radius of the sphere.
     */
    Sphere(Point3D center, float radius) : center{center}, radius{radius} {};
    
    /*!
     Init a sphere object.
     
     @param center center of the sphere.
     @param radius radius of the sphere.
     @param isLight flag used to mark the sphere as light.
     */
    Sphere(Point3D center, float radius, bool isLight) : center{center}, radius{radius} {};
    
    /*!
     Calculate normal for a point on the sphere.
    
     @param pointOnSphere the point on the sphere for which I want to calculate the normal.
    
     @returns a Vector3D normal to the pointOnSphere.
     */
    Vector3D normal(const Point3D& pointOnSphere) const;
    
    /*!
     Calculate the intersection of the sphere with a ray.
    
     @param ray the ray used to calculate the intersection.
    
     @returns a dictionary that contains t, intersection point, normal and the sphere itself.
     */
    Intersection* intersect(const Ray& ray);
    
    /*!
     Calculate texture coordinate.
     
     @param intersectionPoint point of intersection.
     
     @returns texture coordinate.
     */
    TextureCoordinate textureCoordinate(const Point3D& intersectionPoint) const;
};

#endif /* Sphere_hpp */ 
