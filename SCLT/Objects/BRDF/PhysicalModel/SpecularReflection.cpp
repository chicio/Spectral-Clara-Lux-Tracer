//
//  Reflection.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 11/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Ray.hpp"
#include "Fresnel.hpp"
#include "SpecularReflection.hpp"

SpecularReflection::SpecularReflection(Spectrum<constant::spectrumSamples> reflectanceSpectrum,
                                       float refractiveIndex) : BRDF(Reflection),
                                                                reflectanceSpectrum{reflectanceSpectrum},
                                                                refractiveIndex{refractiveIndex},
                                                                fresnel(refractiveIndex) {}

Spectrum<constant::spectrumSamples> SpecularReflection::f(const Vector3D& wi,
                                                          const Vector3D& wo,
                                                          const Intersection& intersection) const {
 
    //Returns 0.0f
    //Specular reflection use a delta dirac function to sample brdf.
    //See samplef().
    return Spectrum<constant::spectrumSamples>();
}

Spectrum<constant::spectrumSamples> SpecularReflection::samplef(Vector3D* wi,
                                                                const Vector3D& wo,
                                                                const Intersection& intersection) const {
    
    float cosO = wo.dot(intersection.normal);

    //Wi direction is only one (delta dirac function).
    *wi =  Ray::reflectedRayDirection(intersection.normal, wo, cosO);
    
    float cosI = fabsf(intersection.normal.dot(*wi));
    
    //Avoid sampling with division by 0 on cosTheta term.
    if (cosI == 0.0f) {
        
        *wi = Vector3D(INFINITY, INFINITY, INFINITY);
        return Spectrum<constant::spectrumSamples>(0.0f);
    }
    
    float fresnelReflection = fresnel.dieletricReflectivePercentage(cosO);
    
    Spectrum<constant::spectrumSamples> reflection = reflectanceSpectrum * fresnelReflection / cosI;
    
    return reflection;
}

float SpecularReflection::pdf(const Vector3D& wi, const Vector3D& wo, const Intersection& intersection) const {
    
    //PDF is 1 for specular reflection.
    //Here there's no monte carlo sampling: delta dirac function choose the only possible wi direction.
    return 1.0f;
}
