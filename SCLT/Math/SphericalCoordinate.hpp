//
//  SphericalCoordinate.hpp
//  Framework
//
//  Created by Fabrizio Duroni on 26/01/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#ifndef SphericalCoordinate_hpp
#define SphericalCoordinate_hpp

#include "MathUtils.hpp"
#include "Vector3D.hpp"

class SphericalCoordinate {
public:
    
    /*!
     Calculate phi for spherical coordinate of a vector. We adapt phi to be in range 2M_PI (using
     atan2f to check the sign of phi and so the know the quarter of the cartesian plane).
     
     @param w vector to be converted.
     
     @returns phi
     */
    static float phi(const Vector3D& w);
    
    /*!
     Calculate theta for spherical coordinate of a vector.
     
     @param w vector to be converted.
     
     @returns theta.
     */
    static float theta(const Vector3D& w);
    
    /*!
     Calculate cosine of theta in tangent space using spherical coordinate.
     Tangent space allow a semplification. Cosine of theta is simply the y coordinate (y axis is the vertical one
     and tangent space is aligned with the normal of the object).
     
     @param w vector to be converted.
     
     @returns cosine of theta in tangent space.
     */
    static float cosThetaInTangentSpace(const Vector3D &w);
    
    /*!
     Calculate sine of theta in tangent space using spherical coordinate.
     Tangent space allow a semplification described above for cosine of theta.
     Also use fundamental trigonometry identity.
     
     @param w vector to be converted.
     
     @returns cosine of theta in tangent space.
     */
    static float sinThetaInTangentSpace(const Vector3D &w);
};

#endif /* SphericalCoordinate_hpp */
