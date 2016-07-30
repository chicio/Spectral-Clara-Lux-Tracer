//
//  SpecularTransmission.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 13/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Ray.hpp"
#include "SpecularTransmission.hpp"

SpecularTransmission::SpecularTransmission(Spectrum<constant::spectrumSamples> reflectanceSpectrum,
                                           float refractiveIndex) : BRDF(Transmission),
                                                                    reflectanceSpectrum{reflectanceSpectrum},
                                                                    refractiveIndex{refractiveIndex},
                                                                    fresnel(refractiveIndex) {}

Spectrum<constant::spectrumSamples> SpecularTransmission::f(const Vector3D& wi,
                                                            const Vector3D& wo,
                                                            const Intersection& intersection) const {
    
    //Returns 0.0f
    //Specular reflection use a delta dirac function to sample brdf.
    //See samplef().
    return Spectrum<constant::spectrumSamples>();
}

Spectrum<constant::spectrumSamples> SpecularTransmission::samplef(Vector3D* wi,
                                                                  const Vector3D& wo,
                                                                  const Intersection& intersection) const {
    
    float n = 0.0f;
    float cosO = wo.dot(intersection.normal);
    
    //As for reflection, a delta dirac function specify the unique refraction direction.
    Vector3D* refractedDirection = Ray::refractedRayDirection(intersection.normal, wo, refractiveIndex, cosO, n);
    
    if(refractedDirection == nullptr) {
        
        return Spectrum<constant::spectrumSamples>(0.0f);
    }
    
    *wi = Vector3D(refractedDirection->x, refractedDirection->y,refractedDirection->z);
    
    delete refractedDirection;
    
    float cosI = fabsf(intersection.normal.dot(*wi));
    
    //Avoid sampling with division by 0 on cosTheta term.
    if (cosI == 0.0f) {
        
        *wi = Vector3D(INFINITY, INFINITY, INFINITY);
        return Spectrum<constant::spectrumSamples>(0.0f);
    }
    
    float fresnelTransmissive = 1.0f - fresnel.dieletricReflectivePercentage(cosO);
    
    Spectrum<constant::spectrumSamples> transmission = reflectanceSpectrum * powf(n, 2.0f) * fresnelTransmissive / cosI;
    
    return transmission;
}

float SpecularTransmission::pdf(const Vector3D& wi, const Vector3D& wo, const Intersection& intersection) const {
    
    //PDF is 1 for specular transmission.
    //Here there's no monte carlo sampling: delta dirac function choose the only possible wi direction.
    return 1.0f;
}
