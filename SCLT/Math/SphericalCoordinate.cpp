//
//  SphericalCoordinate.cpp
//  Framework
//
//  Created by Fabrizio Duroni on 26/01/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "SphericalCoordinate.hpp"

float SphericalCoordinate::phi(const Vector3D& w) {
    
    float phi = atan2f(w.z, w.x);
    
    //Adapt phi to be in 2 pi range.
    float phiAdapted = (phi < 0.0f) ? phi + 2.0f * constant::pi : phi;
    
    return phiAdapted;
}

float SphericalCoordinate::theta(const Vector3D& w) {
    
    float theta = acosf(MathUtils::clamp(w.y, -1.0f, 1.0f));
    
    return theta;
}

float SphericalCoordinate::cosThetaInTangentSpace(const Vector3D &w) {
    
    return w.y;
}

float SphericalCoordinate::sinThetaInTangentSpace(const Vector3D &w) {
    
    float sinThetaPow2 = std::fmax(0.0f, 1.f - powf(cosThetaInTangentSpace(w), 2.0f));
    float sinTheta = sqrtf(sinThetaPow2);
    
    return sinTheta;
}
