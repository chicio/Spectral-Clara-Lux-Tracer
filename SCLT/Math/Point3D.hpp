//
//  Point3DD.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 30/10/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Point3D_hpp
#define Point3D_hpp

#include "Vector3D.hpp"

class Point3D {
public:
    
    /// x component of the Point3D.
    float x;
    /// y component of the Point3D.
    float y;
    /// z component of the Point3D.
    float z;
    /// h component of the Point3D.
    float h;

    /*!
     Default constructor.
     
     @returns a Point3D.
     */
    Point3D() : x{0}, y{0}, z{0}, h{1} {}
    
    /*!
     Initialize a Point3D with each component.
     
     @param x x component.
     @param y y component.
     @param z z component.
     
     @returns a Point3D.
     */
    Point3D(float x, float y, float z) : x{x}, y{y}, z{z}, h{1} {}
    
    /*!
     Sum a point with a Vector3D. Return a Point3D.
     
     @param vector the vector used in the calculation.
     
     @returns a Point3D as a result of the operation.
     */
    Point3D operator+(const Vector3D& vector) const;
    
    /*!
     Difference between Point3D. Return a Vector3D.
     
     @param otherPoint a Point3D to be subtracted.
     
     @returns a Point3D as a result of the operation.
     */
    Vector3D operator-(const Point3D& otherPoint) const;
    
    /*!
     Squared distance between point.
     
     @param point1 first point.
     @param point2 second point.
     
     @return distance squared.
     */
    static float distanceSquared(const Point3D &point1, const Point3D &point2);
};

#endif /* Point3D_hpp */
