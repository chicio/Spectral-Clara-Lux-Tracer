//
//  CIE1960UCS.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 24/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "CIEUCS.hpp"

CIEUCSChromaticities CIEUCS::chromaticity(const Vector3D& tristimulusChromaticities) {
    
    float denominator = -2.0f * tristimulusChromaticities.x + 12.0f * tristimulusChromaticities.y + 3.0f;
    
    float u = (4.0f * (tristimulusChromaticities.x)) / denominator;
    float v = (6.0f * (tristimulusChromaticities.y)) / denominator;
    
    CIEUCSChromaticities chromaticities(u, v);
    
    return chromaticities;
}

CIEUCSChromaticities CIEUCS::chromaticityFromTristimulus(const Vector3D& tristilusValues) {
    
    float denominator = tristilusValues.x + 15.0f * tristilusValues.y + 3.0f  * tristilusValues.z;
    
    float u = (4.0f * (tristilusValues.x)) / denominator;
    float v = (6.0f * (tristilusValues.y)) / denominator;
    
    CIEUCSChromaticities chromaticities(u, v);
    
    return chromaticities;
}

CIEUCSChromaticities CIEUCS::chromaticityForBlackBodyUsingCCT(float CCT) {
    
    float uNumerator = (0.860117757f + 1.54118254f * 1e-4f * CCT + 1.28641212f * 1e-7f * powf(CCT, 2.0f));
    float uDenominator = (1.0f + 8.42420235f * 1e-4f * CCT + 7.08145163f * 1e-7f * powf(CCT, 2.0f));
    float u = uNumerator / uDenominator;
    
    float vNumerator = (0.317398726f + 4.22806245f * 1e-5f * CCT + 4.20481691f * 1e-8f *  powf(CCT, 2.0f));
    float vDenominator = (1.0f - 2.89741816f * 1e-5f * CCT + 1.61456053f * 1e-7f * powf(CCT, 2.0f));
    float v = vNumerator / vDenominator;
    
    CIEUCSChromaticities chromaticities(u, v);
    
    return chromaticities;
}
