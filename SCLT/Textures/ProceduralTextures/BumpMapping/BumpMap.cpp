//
//  BumpMap.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 14/08/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "BumpMap.hpp"

Vector3D BumpMap::bumpMapTexture(const Point3D& point, const Vector3D& normal) const {
    
    float x = point.x / scale;
    float y = point.y / scale;
    float z = point.z / scale;
    
    float noiseCoefx = PerlinNoise::getInstance().noise(x, y, z) * 15.0f;
    float noiseCoefy = PerlinNoise::getInstance().noise(y, z, x) * 15.0f;
    float noiseCoefz = PerlinNoise::getInstance().noise(z, x, y) * 15.0f;
    
    Vector3D newNormal = normal + Vector3D(noiseCoefx, noiseCoefy, noiseCoefz);
    
    return newNormal;
}
