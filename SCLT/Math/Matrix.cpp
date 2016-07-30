//
//  Matrix.cpp
//  Framework
//
//  Created by Fabrizio Duroni on 22/01/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Matrix.hpp"

Matrix::Matrix(float a00, float a01, float a02, float a03,
               float a10, float a11, float a12, float a13,
               float a20, float a21, float a22, float a23,
               float a30, float a31, float a32, float a33) {
    
    m[0][0] = a00; m[0][1] = a01; m[0][2] = a02; m[0][3] = a03;
    m[1][0] = a10; m[1][1] = a11; m[1][2] = a12; m[1][3] = a13;
    m[2][0] = a20; m[2][1] = a21; m[2][2] = a22; m[2][3] = a23;
    m[3][0] = a30; m[3][1] = a31; m[3][2] = a32; m[3][3] = a33;
}

Matrix Matrix::changeOfCoordinateSystemMatrix(const Vector3D& xAxis,
                                              const Vector3D& yAxis,
                                              const Vector3D& zAxis) {
    
    Matrix m(xAxis.x, xAxis.y, xAxis.z, 0,
             yAxis.x, yAxis.y, yAxis.z, 0,
             zAxis.x, zAxis.y, zAxis.z, 0,
                   0,       0,       0, 1);
    
    return m;
}

Matrix Matrix::inverseChangeOfCoordinateSystemMatrix(const Vector3D& xAxis,
                                                     const Vector3D& yAxis,
                                                     const Vector3D& zAxis) {
    
    Matrix m(xAxis.x, yAxis.x, zAxis.x, 0,
             xAxis.y, yAxis.y, zAxis.y, 0,
             xAxis.z, yAxis.z, zAxis.z, 0,
             0,       0,           0,   1);
    
    return m;
}

Vector3D Matrix::operator*(const Vector3D& vector) const {
    
    Vector3D transformedVector;
    
    transformedVector.x = m[0][0] * vector.x + m[0][1] * vector.y + m[0][2] * vector.z + m[0][3] * vector.w;
    transformedVector.y = m[1][0] * vector.x + m[1][1] * vector.y + m[1][2] * vector.z + m[1][3] * vector.w;
    transformedVector.z = m[2][0] * vector.x + m[2][1] * vector.y + m[2][2] * vector.z + m[2][3] * vector.w;
    transformedVector.w = m[3][0] * vector.x + m[3][1] * vector.y + m[3][2] * vector.z + m[3][3] * vector.w;
    
    return transformedVector;
}

Point3D Matrix::operator*(const Point3D& point) const {
    
    Point3D transformedPoint;
    
    transformedPoint.x = m[0][0] * point.x + m[0][1] * point.y + m[0][2] * point.z + m[0][3] * point.h;
    transformedPoint.y = m[1][0] * point.x + m[1][1] * point.y + m[1][2] * point.z + m[1][3] * point.h;
    transformedPoint.z = m[2][0] * point.x + m[2][1] * point.y + m[2][2] * point.z + m[2][3] * point.h;
    transformedPoint.h = m[3][0] * point.x + m[3][1] * point.y + m[3][2] * point.z + m[3][3] * point.h;
    
    return transformedPoint;
}
