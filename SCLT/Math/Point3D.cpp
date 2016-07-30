//
//  Point3DD.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 30/10/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Point3D.hpp"

Point3D Point3D::operator+(const Vector3D& vector) const {
    
    return Point3D(x + vector.x, y + vector.y, z + vector.z);
}

Vector3D Point3D::operator-(const Point3D& otherPoint) const {

    return Vector3D(x - otherPoint.x, y - otherPoint.y, z - otherPoint.z);
}

float Point3D::distanceSquared(const Point3D &point1, const Point3D &point2) {
    
    Vector3D vector = point1 - point2;
    
    float distanceSquared = vector.dot(vector);
    
    return distanceSquared;
}
