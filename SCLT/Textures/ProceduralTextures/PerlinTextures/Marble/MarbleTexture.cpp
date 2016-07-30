//
//  MarbleTexture.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 15/08/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "MarbleTexture.hpp"

Vector3D MarbleTexture::readTexture(const Point3D& point) {
    
    float x = point.x;
    float y = point.y;
    float z = point.z;
    
    float turbulence = 0.0f;
    float amplitude = 0.0f;
    float frequency = 0.0f;

    for (int numberOctaves = 1; numberOctaves < 10; numberOctaves++) {
        
        amplitude = 1.0f / numberOctaves; //x^-1
        frequency = numberOctaves * 0.05f; //linear

        float noise = PerlinNoise::getInstance().noise(frequency * x, frequency * y, frequency * z);
        turbulence += amplitude * fabs(noise);
    }

    //Marble is obtained as a phase shift of turbulence.
    float marble = 0.5f * sinf((x + y) * 0.05f + turbulence) + 0.5f;
    
    Vector3D newColor1 = color1 * marble;
    Vector3D newColor2 = color2 * (1.0f - marble);
    
    return newColor1 + newColor2;
}
