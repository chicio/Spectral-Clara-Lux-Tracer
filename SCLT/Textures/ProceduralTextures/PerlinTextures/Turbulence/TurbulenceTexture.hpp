//
//  MarbleTexture.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 15/08/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef TurbulenceTexture_hpp
#define TurbulenceTexture_hpp

#include "PerlinTexture.hpp"
#include "PerlinNoise.hpp"
#include "Vector3D.hpp"
#include "Point3D.hpp"

class TurbulenceTexture : public PerlinTexture {
public:
    
    /*
     Constructor.
     
     @param color1 first color.
     @param color2 second color.
     
     @returns a PerlinTexture instance.
     */
    TurbulenceTexture(Vector3D color1, Vector3D color2) : PerlinTexture(color1, color2) {};
    
    /*!
     Turbulence texture using perlin noise.
     
     @param point point to which apply texture.
     
     @return color of the texture in a Vector3D.
     */
    Vector3D readTexture(const Point3D& point);
};

#endif
