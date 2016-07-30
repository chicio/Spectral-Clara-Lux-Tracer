//
//  MarbleTexture.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 15/08/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "TurbulenceTexture.hpp"

Vector3D TurbulenceTexture::readTexture(const Point3D& point) {

    //I scale coordinate to zoom in/out
    //on the texture. Change value of scale
    //to obtain different result.
    float x = point.x/16;
    float y = point.y/16;
    float z = point.z/16;
    
    float turbulence = 0.0f;
    float amplitude = 1.0f;
    float frequency = 1.0f;
    
    //Standard implementation of turbulence.
    //Change the number of octaves to change
    //the details of the texture (usually
    //0 - 8 range).
    for (int numberOctaves = 0; numberOctaves < 8; numberOctaves++) {

        float noise = PerlinNoise::getInstance().noise(frequency * x, frequency * y, frequency * z);
        turbulence += amplitude * fabs(noise);
        
        amplitude *= 0.5;
        frequency *= 2;
    }
    
    Vector3D newColor1 = color1 * turbulence;
    Vector3D newColor2 = color2 * (1.0f - turbulence);
    
    return newColor1 + newColor2;
}
