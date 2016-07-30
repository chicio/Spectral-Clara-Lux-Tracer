//
//  ChromaticAdaptationTransform.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 26/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef ChromaticAdaptationTransform_hpp
#define ChromaticAdaptationTransform_hpp

#include "Constants.hpp"
#include "CIEUCS.hpp"

class ChromaticAdaptationTransform {
public:

    /*!
     Apply von kries transform.
     
     @param chromaticityTestLight chromaticity 1960 ucs of the test light
     @param chromaticityRefLight chromaticity 1960 ucs of the reference light
     @param chromaticitySampleTestLight chromaticity 1960 ucs of the color sample under test light
     
     @returns adapted chromaticity values.
     */
    static CIEUCSChromaticities vonKries(const CIEUCSChromaticities& chromaticityTestLight,
                                         const CIEUCSChromaticities& chromaticityRefLight,
                                         const CIEUCSChromaticities& chromaticitySampleTestLight);
    
    /*!
     Apply ciecat94 transform.
     
     @param tristimulus tristimulus to be adapted.
     @param chromaticityTestLight chromaticity of the test light.
     @param chromaticityRefLight chromaticiy of the reference light.
     @param tristimulusTestLight tristimulus values.
     
     @returns tristimulus adapted.
     */
    static Vector3D ciecat94(const Vector3D& tristimulus,
                             const Vector3D& chromaticityTestLight,
                             const Vector3D& chromaticityRefLight,
                             const Vector3D& tristimulusTestLight);
};

#endif /* ChromaticAdaptationTransform_hpp */
