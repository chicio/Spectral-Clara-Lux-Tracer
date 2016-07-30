//
//  Vector3D.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 30/10/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Vector3D_hpp
#define Vector3D_hpp

#include <math.h>

class Vector3D {
public:
    
    /// x component of the Vector3D.
    float x;
    /// y component of the Vector3D.
    float y;
    /// z component of the Vector3D.
    float z;
    /// w component of the Vector3D.
    float w;

    /*!
     Default constructor.
     
     @returns a Vector3D.
     */
    Vector3D() : x{0.0f}, y{0.0f}, z{0.0f}, w{0.0f} {}

    /*!
     Initialize a vector with each component.
     
     @param x x component.
     @param y y component.
     @param z z component.
     
     @returns a Vector3D.
     */
    Vector3D(float x, float y, float z) : x{x}, y{y}, z{z}, w{0.0f} {}

    /*!
     Initialize a vector with each component.
     This constructor is useful if we need to construct 
     it using a w homogeneous component or when we need
     to store alpha component on colors.
     
     @param x x component.
     @param y y component.
     @param z z component.
     @param w w component.
     
     @returns a Vector3D.
     */
    Vector3D(float x, float y, float z, float w) : x{x}, y{y}, z{z}, w{w} {}
    
    /*!
     Dot product bewtween vectors.
     
     @param otherVector the other vector used in multiplication.
     
     @returns a float as result of the dot product.
     */
    float dot(const Vector3D& otherVector) const;
    
    /*!
     Cross product between vectors.
     
     @param otherVector the other vector used in the cross product.
     
     @returns a Vector3D
     */
    Vector3D cross(const Vector3D& otherVector) const;
    
    /*!
     Product component * component Vector.
     
     @param otherVector the other vector used in the product.
     
     @returns a Vector with each component is the product of the components of the two vector.
     */
    Vector3D pprod(const Vector3D& otherVector) const;
    
    /*!
     Normalize the Vector.
     */
    void normalize();
    
    /*!
     Magnitude of the vector.
     */
    float magnitude();
    
    /*!
     Product Vector * Scalar
     
     @param scalar the scalar used in the product.
     
     @returns a Vector multiplied with the scalar received as parameter.
     */
    Vector3D operator*(float scalar) const;
    
    /*!
     Difference between vector.
     
     @param otherVector the other vector used in the difference.
     
     @returns a difference Vector.
     */
    Vector3D operator-(const Vector3D& otherVector) const;
    
    /*!
     Sum between vector.
     
     @param otherVector the other vector used in the sum.
     
     @returns a sum Vector.
     */
    Vector3D operator+(const Vector3D& otherVector) const;
};

#endif /* Vector3D_hpp */
