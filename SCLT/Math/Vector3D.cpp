//
//  Vector3D.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 30/10/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Vector3D.hpp"
#include "MathUtils.hpp"

float Vector3D::dot(const Vector3D& otherVector) const {
    
    float dotResult = x * otherVector.x + y * otherVector.y + z * otherVector.z;
    
    return dotResult;
}

Vector3D Vector3D::cross(const Vector3D& otherVector) const {
    
    float xCross = y * otherVector.z - z * otherVector.y;
    float yCross = z * otherVector.x - x * otherVector.z;
    float zCross = x * otherVector.y - y * otherVector.x;
    
    return Vector3D(xCross, yCross, zCross);
}

Vector3D Vector3D::pprod(const Vector3D& otherVector) const {
    
    float xpprod = x * otherVector.x;
    float ypprod = y * otherVector.y;
    float zpprod = z * otherVector.z;
    
    return Vector3D(xpprod, ypprod, zpprod);
}

void Vector3D::normalize() {
    
    float magnitude = this->magnitude();
    
    x = x / magnitude;
    y = y / magnitude;
    z = z / magnitude;
}

float Vector3D::magnitude() {
    
    return sqrtf(this->dot(*this));
}

Vector3D Vector3D::operator*(float scalar) const {
    
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

Vector3D Vector3D::operator-(const Vector3D& otherVector) const {
    
    return Vector3D(x - otherVector.x, y - otherVector.y, z - otherVector.z);
}

Vector3D Vector3D::operator+(const Vector3D& otherVector) const {
    
    return Vector3D(x + otherVector.x, y + otherVector.y, z + otherVector.z);
}
