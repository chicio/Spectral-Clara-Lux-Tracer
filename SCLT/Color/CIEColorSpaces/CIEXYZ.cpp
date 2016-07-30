//
//  CIEXYZ.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 14/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "CIEXYZ.hpp"

Vector3D CIE1931XYZ::tristimulusValues(Spectrum<constant::spectrumSamples>& objectProductIlluminantSpectrum,
                                       Spectrum<constant::spectrumSamples>& illuminantSpectrum,
                                       const ColorMatchingFunction* colorMatchingFunction) {
    
    //Tristimulus values.
    float X = 0.0f;
    float Y = 0.0f;
    float Z = 0.0f;
    
    //Normalizing constant.
    float luminanceSum = 0.0f;
    
    //Integration approximation.
    for (int i = 0; i < constant::spectrumSamples; i++) {
        
        X += objectProductIlluminantSpectrum[i] * colorMatchingFunction->x[i];
        Y += objectProductIlluminantSpectrum[i] * colorMatchingFunction->y[i];
        Z += objectProductIlluminantSpectrum[i] * colorMatchingFunction->z[i];
        luminanceSum += illuminantSpectrum[i] * colorMatchingFunction->y[i];
    }

    //Scale to Y.
    //Usually k is chosen to give a value of 100 for luminance Y of samples with a unit reflectance spectrum.
    float k = 1.0f/luminanceSum;
        
    X = X * k;
    Y = Y * k;
    Z = Z * k;
    
    Vector3D tristimulus(X, Y, Z);
    
    return tristimulus;
}

Vector3D CIE1931XYZ::tristimulusValuesForEmissiveSource(Spectrum<constant::spectrumSamples>& illuminantSpectrum,
                                                        const ColorMatchingFunction* colorMatchingFunction) {
 
    //Tristimulus values.
    float X = 0.0f;
    float Y = 0.0f;
    float Z = 0.0f;
    
    //Normalizing constant.
    float luminanceSum = 0;
    
    //Integration approximation.
    for (int i = 0; i < constant::spectrumSamples; i++) {
        
        X += illuminantSpectrum[i] * colorMatchingFunction->x[i];
        Y += illuminantSpectrum[i] * colorMatchingFunction->y[i];
        Z += illuminantSpectrum[i] * colorMatchingFunction->z[i];
        luminanceSum += illuminantSpectrum[i] * colorMatchingFunction->y[i];
    }
    
    float k = 1.0f/luminanceSum;
    
    X = X * k;
    Y = Y * k;
    Z = Z * k;
    
    Vector3D tristimulus(X, Y, Z);
    
    return tristimulus;
}

Vector3D CIE1931XYZ::tristimulusValues(Vector3D chromaticityValues, float Y) {
    
    float X = (chromaticityValues.x * Y) / chromaticityValues.y;
    float Z = ((1.0f - chromaticityValues.x - chromaticityValues.y) * Y) / chromaticityValues.y;
    
    Vector3D tristimulus = Vector3D(X, Y, Z);
    
    return tristimulus;
}

Vector3D CIE1931XYZ::tristimulusTosRGB(const Vector3D& tristimulus) {
    
    //Conversion to sRGB using matrix.
    float r =  3.240479f * tristimulus.x - 1.537150f * tristimulus.y - 0.498535f * tristimulus.z;
    float g = -0.969256f * tristimulus.x + 1.875991f * tristimulus.y + 0.041556f * tristimulus.z;
    float b =  0.055648f * tristimulus.x - 0.204043f * tristimulus.y + 1.057311f * tristimulus.z;
    
    Vector3D rgbColor(r, g, b);
    
    return rgbColor;
}

Vector3D CIE1931XYZ::chromaticityValues(Vector3D tristimulus) {
    
    float tristimulusSum = tristimulus.x + tristimulus.y + tristimulus.z;
    
    Vector3D chromaticityValues(tristimulus.x / tristimulusSum,
                                tristimulus.y / tristimulusSum,
                                tristimulus.z / tristimulusSum);
    
    return chromaticityValues;
}
