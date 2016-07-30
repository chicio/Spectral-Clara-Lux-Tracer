//
//  CIEUVW.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 25/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef CIEUVW_hpp
#define CIEUVW_hpp

#include "Vector3D.hpp"

struct CIEUVWCoordinates {
    
    /// U coordinate.
    float U;
    /// V coorinate.
    float V;
    /// W coordinate.
    float W;
    
    /*!
     Default Constructor.
     */
    CIEUVWCoordinates() : U{0.0f}, V{0.0f}, W{0.0f} {}
    
    /*!
     Constructor used to init the struct with
     values calculated.
     
     @param U.
     @param V.
     @param W.
     */
    CIEUVWCoordinates(float U, float V, float W) : U{U}, V{V}, W{W} {};
};

class CIEUVW {
public:
    
    /*!
     Calculate uvw values.
     
     @param chromaticityObject CIE 1960 chromaticity values.
     @param chromaticityReferenceWhite CIE 1960 reference white.
     @param tristimulusObject tristimulus values of the objects.
     
     @return CIEUVWCoordinates.
     */
    static CIEUVWCoordinates UVWValues(CIEUCSChromaticities& chromaticityObject,
                                       CIEUCSChromaticities& chromaticityReferenceWhite,
                                       Vector3D& tristimulusObject);
};

#endif /* CIEUVW_hpp */
