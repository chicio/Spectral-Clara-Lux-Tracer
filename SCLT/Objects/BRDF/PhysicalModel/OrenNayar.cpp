//
//  OrenNayar.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 27/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "OrenNayar.hpp"

OrenNayar::OrenNayar(Spectrum<constant::spectrumSamples> reflectanceSpectrum,
                     float degree) : BRDF(Diffuse), reflectanceSpectrum{reflectanceSpectrum} {

    float sigma = MathUtils::degreeToRadian(degree);
    float sigmaPowerTwo = sigma * sigma;
    
    A = 1.0f - (sigmaPowerTwo / 2.0f * (sigmaPowerTwo + 0.33f));
    B = 0.45f * sigmaPowerTwo / (sigmaPowerTwo + 0.09f);
    
    reflectanceSpectrumWeightWithPi = reflectanceSpectrum / constant::pi;
};

float OrenNayar::calculateOrenNayarMultiplierFactor(const Vector3D& wi,
                                                    const Vector3D& wo,
                                                    const Intersection& intersection) const {
    
    float cosI = wi.dot(intersection.normal);
    float cosO = wo.dot(intersection.normal);
    
    float thetaI = acosf(cosI);
    float thetaO = acosf(cosO);
    
    float cosPhiDiff = (wi - intersection.normal * cosI).magnitude() * (wo - intersection.normal * cosO).magnitude();
    
    float alpha = std::fmaxf(thetaI, thetaO);
    float beta = std::fminf(thetaI, thetaO);
    
    float multiplierFactor = (A + B * std::fmaxf(0, cosPhiDiff * sinf(alpha) * tanf(beta)));

    return multiplierFactor;
}

Spectrum<constant::spectrumSamples> OrenNayar::f(const Vector3D& wi,
                                                 const Vector3D& wo,
                                                 const Intersection& intersection) const {

    float multiplierFactor = calculateOrenNayarMultiplierFactor(wi, wo, intersection);
    Spectrum<constant::spectrumSamples> orenNayar = reflectanceSpectrum * multiplierFactor;
    
    return orenNayar;
}

Spectrum<constant::spectrumSamples> OrenNayar::samplef(Vector3D* wi,
                                                       const Vector3D& wo,
                                                       const Intersection& intersection) const {

    *wi = cosineWeightedHemisphereBRDFDirectionSampling(intersection);
    
    float multiplierFactor = calculateOrenNayarMultiplierFactor(*wi, wo, intersection);
    
    Spectrum<constant::spectrumSamples> orenNayar = reflectanceSpectrumWeightWithPi * multiplierFactor;
    
    return orenNayar;
}

float OrenNayar::pdf(const Vector3D& wi, const Vector3D& wo, const Intersection& intersection) const {
    
    float pdf = (fabsf(wi.dot(intersection.normal))/constant::pi);
    
    return pdf;
}
