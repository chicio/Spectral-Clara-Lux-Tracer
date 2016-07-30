//
//  PerlinTexture.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 15/08/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef PerlinTexture_hpp
#define PerlinTexture_hpp

#include "Vector3D.hpp"
#include "Point3D.hpp"

class PerlinTexture {
public:

    /// First color used in texture.
    Vector3D color1;
    /// Second color used in texture.
    Vector3D color2;

    /*!
     Constructor.
    
     @param color1 first color.
     @param color2 second color.
    
     @returns a PerlinTexture instance.
     */
    PerlinTexture(Vector3D color1, Vector3D color2) : color1{color1}, color2{color2} {};
    
    /*!
     Method used to get the color of a texture in a specific point.
     
     @param point coordinate point.
    
     @returns a texel color.
     */
    virtual Vector3D readTexture(const Point3D& point) = 0;
    
    /*!
     Destructor.
     */
    virtual ~PerlinTexture() = 0;
};

#endif
