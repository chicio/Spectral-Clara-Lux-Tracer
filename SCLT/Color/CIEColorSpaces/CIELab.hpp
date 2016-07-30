//
//  CIELab.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 01/01/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#ifndef CIELab_hpp
#define CIELab_hpp

#include "Vector3D.hpp"

struct CIELabCoordinate {
    
    /// L coordinate.
    float L;
    /// a coordinate.
    float a;
    /// b coordinate.
    float b;
    
    /*!
     Default constructor.
     */
    CIELabCoordinate() : L{0.0f}, a{0.0f}, b{0.0f} {}
    
    /*!
     Constructor that init a CIE1960UCSChromaticities object.
     
     @param u u coordinate.
     @param v v coordinate.
     */
    CIELabCoordinate(float L, float a, float b) : L{L}, a{a}, b{b} {};
};

class CIELab {
public:
    
    /// Epsilon used to evaluate f().
    static constexpr float epsilon = 0.008856f;
    /// K used to evaluate f().
    static constexpr float kappa = 903.3f;
    
    /*!
     Evaluate f() function for a t.
     
     @param t parameter on which f function must be evaluated.
     
     @returns f() values.
     */
    static float f(float t);
    
    /*!
     Convert CIEXYZ to CIELab.
     
     @see http://www.brucelindbloom.com/Eqn_XYZ_to_Lab.html
     @see https://en.wikipedia.org/wiki/Lab_color_space#CIELAB-CIEXYZ_conversions
     
     @param tristimulusValues values to be converted.
     @param tristimulusReferenceWhite values to be used as reference white.
     
     @returns CIE L* a* b* coordinate.
     */
    static CIELabCoordinate LabValues(const Vector3D& tristimulusValues, const Vector3D& tristimulusReferenceWhite);
};

#endif /* CIELab_hpp */
