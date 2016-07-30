//
//  CIE1960UCS.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 24/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef CIE1960UCS_hpp
#define CIE1960UCS_hpp

#include "Vector3D.hpp"

struct CIEUCSChromaticities {
    
    /// u coordinate.
    float u;
    /// v coordinate
    float v;
    
    /*!
     Constructor that init a CIE1960UCSChromaticities object.
     
     @param u u coordinate.
     @param v v coordinate.
     */
    CIEUCSChromaticities(float u, float v) : u{u}, v{v} {};
};

class CIEUCS {
public:

    /*!
     Convert CIE XYZ chromaticity values to CIE UCS 1960 chromaticity values.
     
     @param tristimulusChromaticity CIE XYZ tristimulus chromaticity coordinate.

     @returns CIE 1960 chromaticity values.
     */
    static CIEUCSChromaticities chromaticity(const Vector3D& tristimulusChromaticity);
    
    /*!
     Convert CIE XYZ tristimulus values to CIE UCS 1960 chromaticity values.
     
     @param tristilusValues CIE XYZ tristimulus values.
     
     @returns CIE 1960 chromaticity values.
     */
    static CIEUCSChromaticities chromaticityFromTristimulus(const Vector3D& tristimulusValues);
    
    /*!
     Calculate CIE 1960 chromaticity values using color correleated temperature (CCT).
     Useful for black body chromaticity calculation.
     
     @param CCT black body temperature.
     
     @returns
     */
    static CIEUCSChromaticities chromaticityForBlackBodyUsingCCT(float CCT);
};

#endif /* CIEUCS_hpp */
