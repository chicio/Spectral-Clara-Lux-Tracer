//
//  Lambertian.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 24/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Lambertian_hpp
#define Lambertian_hpp

#include "Spectrum.hpp"
#include "BRDF.hpp"

class Lambertian : public BRDF {
    
    /// Reflectance spectrum.
    Spectrum<constant::spectrumSamples> reflectanceSpectrum;
    /// Reflectance spectrum divide by pi. Used in samplef to return the correct spectrum after sampling.
    Spectrum<constant::spectrumSamples> reflectanceSpectrumWeightWithPi;
    
public:
    
    /*!
     Constructor.
     
     @param reflectanceSpectrum the reflectance spectrum.
     */
    Lambertian(Spectrum<constant::spectrumSamples> reflectanceSpectrum);
    
    /*!
     Compute BRDF for the given direction using Lambertian model.
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns BRDF.
     */
    Spectrum<constant::spectrumSamples> f(const Vector3D& wi,
                                          const Vector3D& wo,
                                          const Intersection& intersection) const;
    
    /*!
     Computed BRDF and sample wi direction for Lambertian model.
     Useful on Monte carlo models (e.g. Path tracing).
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns BRDF and wi.
     */
    Spectrum<constant::spectrumSamples> samplef(Vector3D* wi,
                                                const Vector3D& wo,
                                                const Intersection& intersection) const;
    
    /*!
     Probability density function for lambertian model.
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns pdf.
     */
    float pdf(const Vector3D& wi, const Vector3D& wo, const Intersection& intersection) const;
};


#endif /* Lambertian_hpp */
