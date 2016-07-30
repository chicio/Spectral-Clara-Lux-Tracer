//
//  TracerSpectrum.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 18/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "sRGB.hpp"
#include "CIEXYZ.hpp"
#include "TracerSpectrum.hpp"

TracerSpectrum::TracerSpectrum(Scene* scene) : Tracer(scene) {
    
    shadingModel = ShadingModelFactory().createShadingModelSpectrum(scene->shadingModelType);
    colorMatchingFunction = new Standard2ObserverColorMatchingFunction();
};

Vector3D TracerSpectrum::getColor(const Ray& ray, const int bounce) const {
    
    Spectrum<constant::spectrumSamples> L = trace(ray, constant::maxNumberOfBounce);
    
    //Get tristimulus values.
    Vector3D tristimulus = CIE1931XYZ::tristimulusValues(L, scene->light->spectrum, colorMatchingFunction);
    
    //Convert tristimulus to sRGB.
    Vector3D color = CIE1931XYZ::tristimulusTosRGB(tristimulus);
    
    //Apply sRGB gamma correction.
    sRGB::sRGBGammaCorrection(color, sRGBCompading);
    
    //Convert to standard 0 - 255 RGB value.
    sRGB::sRGBStandardRange(color);
        
    return color;
}

Spectrum<constant::spectrumSamples> TracerSpectrum::trace(const Ray& ray, const int bounce) const {
    
    Spectrum<constant::spectrumSamples> color;
    
    Intersection* intersectionData = closestIntersection(ray);
    
    if(intersectionData != nullptr){
        
        //Apply shade on the current object.
        color = shadingModel->shade(*intersectionData, ray, bounce, *this);
        
        //Clean intersection data.
        delete intersectionData;
    }
    
    return color;
}

TracerSpectrum::~TracerSpectrum() {
    
    delete colorMatchingFunction;
};
