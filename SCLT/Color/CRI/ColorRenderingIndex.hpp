//
//  ColorRenderingIndex.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 21/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef ColorRenderingIndex_hpp
#define ColorRenderingIndex_hpp

#include "Spectrum.hpp"
#include "Constants.hpp"

class ColorRenderingIndex {
private:
    
    /*!
     Calculate black body spectrum from CCT.
     
     @param CCT color correleated temperature.
     
     @returns the spectrum of the black body.
     */
    Spectrum<constant::spectrumSamples> blackBodySpectrum(float CCT) const;
    
    /*!
     Calculate Color Correlated Temperature (CCT) from
     CIE XYZ chromaticity values using McCamy algorithm.
     
     @param chromaticityValuesLight Light CIE XYZ chromaticity values.
     
     @returns CCT temperature as float.
     */
    float calculateCCTUsingMcCamyAlgorithm(Vector3D chromaticityValuesLight) const;
    
public:

    /*!
     CRI calculate using classic standard test sample method.
     8 Munsell sample evenly distribute over the complete range of hues are used.
     
     @param spectrumTestLight spectrum of the light to be tested.
     
     @returns CRI.
     */
    float testSampleMethod(Spectrum<constant::spectrumSamples>& spectrumTestLight) const;
    
    /*!
     CRI calculate using r96a method.
     10 Macbeth color samples are used instead of the classical samples.
     
     @param spectrumTestLight spectrum of the light to be tested.
     
     @returns CRI r96a.
     */
    float r96aMethod(Spectrum<constant::spectrumSamples>& spectrumTestLight) const;
};

#endif /* ColorRenderingIndex_hpp */
