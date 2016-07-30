//
//  BRDF.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 08/04/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "BRDF.hpp"

Vector3D BRDF::cosineWeightedHemisphereBRDFDirectionSampling(const Intersection& intersection) const {
    
    float u1 = RandomNumberGenerator::instance().generateRandomFloat();
    float u2 = RandomNumberGenerator::instance().generateRandomFloat();
    
    //Sample uniform disk.
    float r = sqrtf(u1);
    float theta = 2.0f * constant::pi * u2;
    float x = r * cosf(theta);
    float z = r * sinf(theta);
    
    //Sample cosine weighted hemisphere sample.
    float y = sqrtf(std::fmax(0.0f, 1.0f - u1));
    
    //Setup obtained sample.
    Vector3D vectorSampleFromHemisphere(x, y, z);
    
    //Generate tangent space (local coordinates) using normal.
    Vector3D tangent;
    Vector3D bitangent;
    
    MathUtils::generateCoodinateSystem(intersection.normal, tangent, bitangent);
    
    //Convert sample in world coordinate, considering canonical base.
    Matrix m = Matrix::inverseChangeOfCoordinateSystemMatrix(bitangent, intersection.normal, tangent);
    Vector3D sampleInWorldCoordinate = m * vectorSampleFromHemisphere;
    
    return sampleInWorldCoordinate;
}
