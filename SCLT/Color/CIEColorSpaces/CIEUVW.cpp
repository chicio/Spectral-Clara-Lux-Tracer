//
//  CIEUVW.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 25/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "CIEUCS.hpp"
#include "CIEUVW.hpp"

CIEUVWCoordinates CIEUVW::UVWValues(CIEUCSChromaticities& chromaticityObject,
                                    CIEUCSChromaticities& chromaticityReferenceWhite,
                                    Vector3D& tristimulusObject) {

    float W = 25.0f * powf(tristimulusObject.y * 100.0f, 1.0f/3.0f) - 17.0f;
    float U = 13.0f * W * (chromaticityObject.u - chromaticityReferenceWhite.u);
    float V = 13.0f * W * (chromaticityObject.v - chromaticityReferenceWhite.v);
    
    CIEUVWCoordinates coordinates(U, V, W);
    
    return coordinates;
}
