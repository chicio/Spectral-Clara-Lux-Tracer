//
//  TracerSpectrum.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 18/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"

#include <iostream>

#include "CIEXYZ.hpp"
#include "sRGB.hpp"
#include "PathTracer.hpp"

PathTracer::PathTracer(Scene* scene) : TracerSpectrum(scene) {

    numberOfSamples = scene->numberOfSamples;
    sampleWeight = 1.0f/((float)numberOfSamples);
};

Vector3D PathTracer::getColor(const Ray& ray, const int bounce) const {
    
    Spectrum<constant::spectrumSamples> L;
    
    for (int i = 0; i < numberOfSamples; i++) {
        
        Spectrum<constant::spectrumSamples> spectrumSample = trace(ray, bounce);
        L = L + spectrumSample;
    }
        
    //Get tristimulus values.
    Vector3D tristimulus = CIE1931XYZ::tristimulusValues(L, scene->originalLightSpectrum, colorMatchingFunction);
    
    //Convert tristimulus to sRGB.
    Vector3D color = CIE1931XYZ::tristimulusTosRGB(tristimulus);

    color = color * sampleWeight;
    
    //Apply sRGB gamma correction.
    sRGB::sRGBGammaCorrection(color, GammaCompanding);
    
    //Convert to standard 0 - 255 RGB value.
    sRGB::sRGBStandardRange(color);
        
    return color;
}
