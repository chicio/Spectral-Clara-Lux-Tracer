//
//  Lambertian.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 24/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Matrix.hpp"
#include "Lambertian.hpp"

Lambertian::Lambertian(Spectrum<constant::spectrumSamples> objectReflectanceSpectrum) : BRDF(Diffuse) {
    
    reflectanceSpectrum = objectReflectanceSpectrum;
    reflectanceSpectrumWeightWithPi = objectReflectanceSpectrum / constant::pi;
};

Spectrum<constant::spectrumSamples> Lambertian::f(const Vector3D& wi,
                                                  const Vector3D& wo,
                                                  const Intersection& intersection) const {
    
    //Lambertian scatters incident light equally in all direction.
    Spectrum<constant::spectrumSamples> lambertian = reflectanceSpectrum;
    
    return lambertian;
}

Spectrum<constant::spectrumSamples> Lambertian::samplef(Vector3D* wi,
                                                        const Vector3D& wo,
                                                        const Intersection& intersection) const {

    *wi = cosineWeightedHemisphereBRDFDirectionSampling(intersection);
        
    return reflectanceSpectrumWeightWithPi;
}

float Lambertian::pdf(const Vector3D& wi, const Vector3D& wo, const Intersection& intersection) const {
        
    float pdf = (fabsf(wi.dot(intersection.normal))/constant::pi);
    
    return pdf;
}
