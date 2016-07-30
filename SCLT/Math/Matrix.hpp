//
//  Matrix.hpp
//  Framework
//
//  Created by Fabrizio Duroni on 22/01/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include "Vector3D.hpp"
#include "Point3D.hpp"

class Matrix {
private:
    
    float m[4][4];
    
public:

    /*!
     Constructor for the matrix that take a value for each cell of the matrix.
     
     @param a00-a33 value of the matrix.
     */
    Matrix(float a00, float a01, float a02, float a03,
           float a10, float a11, float a12, float a13,
           float a20, float a21, float a22, float a23,
           float a30, float a31, float a32, float a33);
    
    /*!
     Create change of coordinate matrix from orthonormal base (linear indipendent vectors), considering
     canonical base vector.
     
     @param xAxis x axis of the new cordinate system.
     @param yAxis y axis of the new cordinate system.
     @param zAxis z axis of the new cordinate system.
     
     @returns change of coordinate matrix.
     */
    static Matrix changeOfCoordinateSystemMatrix(const Vector3D& xAxis,
                                                 const Vector3D& yAxis,
                                                 const Vector3D& zAxis);

    /*!
     Create inverse change of coordinate matrix from orthonormal base (linear indipendent vectors), considering
     canonical base vector.
     
     @param xAxis x axis of the new cordinate system.
     @param yAxis y axis of the new cordinate system.
     @param zAxis z axis of the new cordinate system.
     
     @returns change of coordinate matrix.
     */    
    static Matrix inverseChangeOfCoordinateSystemMatrix(const Vector3D& xAxis,
                                                        const Vector3D& yAxis,
                                                        const Vector3D& zAxis);
    
    /*!
     Multiply a vector with the matrix.
     
     @param vector vector used in the product.
     
     @returns a new vector.
     */
    Vector3D operator*(const Vector3D& vector) const;
    
    /*!
     Multiply a point with the matrix.
     
     @param point point used in the product.
     
     @returns a new point.
     */
    Point3D operator*(const Point3D& point) const;
};

#endif /* Matrix_hpp */
