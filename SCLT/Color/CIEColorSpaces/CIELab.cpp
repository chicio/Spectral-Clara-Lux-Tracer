//
//  CIELab.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 01/01/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"

#include "CIEXYZ.hpp"
#include "CIELab.hpp"

CIELabCoordinate CIELab::LabValues(const Vector3D& tristimulusValues, const Vector3D& tristimulusReferenceWhite) {

    float xr = tristimulusValues.x / tristimulusReferenceWhite.x;
    float yr = tristimulusValues.y / tristimulusReferenceWhite.y;
    float zr = tristimulusValues.z / tristimulusReferenceWhite.z;
    
    float fx = CIELab::f(xr);
    float fy = CIELab::f(yr);
    float fz = CIELab::f(zr);
    
    float L = 116.0f * fy - 16.0f;
    float a = 500.0f * (fx - fy);
    float b = 200.0f * (fy - fz);
    
    CIELabCoordinate coordinate(L, a, b);
    
    return coordinate;
}

float CIELab::f(float t) {

    float fEvaluation = 0.0f;
    
    if (t > CIELab::epsilon) {
        
        fEvaluation = powf(t, 1.0f/3.0f);
    } else {
        
        fEvaluation = (CIELab::kappa * t + 16.0f) / 116.0f;
    }
    
    return fEvaluation;
}
