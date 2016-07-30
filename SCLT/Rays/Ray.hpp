//
//  Ray.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 06/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Ray_hpp
#define Ray_hpp

#include "MathUtils.hpp"
#include "Constants.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Model.hpp"
#include "Sphere.hpp"
#include "Polygon.hpp"

class Ray {
public:
    
    /// Origin of the ray.
    Point3D origin;
    /// Direction vector of the ray.
    Vector3D direction;
    
    /*!
     Default constructor.
     */
    Ray() : origin{Point3D(0, 0, 0)}, direction{Vector3D(0, 0, 0)} {};
    
    /*!
     Constructor.
     
     @param origin the origin.
     @param distanceVector the distance vector.
     
     @returns a Ray instance.
     */
    Ray(Point3D origin, Vector3D directionVector) : origin{origin}, direction{directionVector} {};
  
    /*!
     Calculate the reflective ray direction.
     
     @see Prof. Ciocca/Bianco slides for the process of calculation.
     @see https://www.cs.unc.edu/~rademach/xroads-RT/RTarticle.html
     @param normal normal of the reflective object.
     @param rayToBeReflectedDirection direction of the ray to be reflected.
     @param cosI dot product between ray and normal.
    
     @returns the direction of the reflected ray as Vector3D.
     */
    static Vector3D reflectedRayDirection(const Vector3D& normal,
                                          const Vector3D& rayToBeReflectedDirection,
                                          float cosI);
    

    /*!
     Calculate a refractive ray direction.
    
     @see Prof. Ciocca/Bianco slides fot the formula.
     @see List of refractive index https://en.wikipedia.org/wiki/List_of_refractive_indices
     @see https://www.cs.unc.edu/~rademach/xroads-RT/RTarticle.html
    
     @param normal object normal.
     @param rayToBeRefractedDirection direction of the ray to be refracted.
     @param refractiveIndexObject refractive index of the object in which we are going.
     @param cosI dot product between ray and normal.
     @param n refractive indexes ratio.
    
     @returns a Refract ray.
     */
    static Vector3D* refractedRayDirection(const Vector3D& normal,
                                           const Vector3D& rayToBeRefractedDirection,
                                           const float refractiveIndexObject,
                                           const float cosI,
                                           float& n);
};

#endif
