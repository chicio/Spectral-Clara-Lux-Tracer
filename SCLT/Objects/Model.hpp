//
//  Model.h
//  Spectral Clara Lux tracer
//
//  Created by Duroni Fabrizio on 09/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include "Material.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Intersection.hpp"
#include "Texture.hpp"

class Ray;

class Model {
public:
    
    /// Material assigned to the object.
    Material *material;
    /// Flag used to check if the object is used as a light.
    bool isLight;
    
    /*!
     Default constructor.
     */
    Model() : isLight{false}, material{nullptr} {};

    /*!
     All objects must be able to test if they intersect with a ray.
    
     @param ray the ray to be tested.
    
     @results intersection data: intersection point, t, normal, object
     */
    virtual Intersection* intersect(const Ray& ray) = 0;
    
    /*!
     Calculate texture coordinate for a specific object.
     
     @param intersectionPoint point of intersection.
     
     @return texture coordinate.
     */
    virtual TextureCoordinate textureCoordinate(const Point3D& intersectionPoint) const = 0;
    
    /*!
     Destructor.
     */
    virtual ~Model() = 0;
};

#endif /* Model_h */
