//
//  SpecularTransmission.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 13/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef SpecularTransmission_hpp
#define SpecularTransmission_hpp

#include "BRDF.hpp"

class SpecularTransmission : public BRDF {
    
    /// Reflectance spectrum.
    Spectrum<constant::spectrumSamples> reflectanceSpectrum;
    /// Refractive index.
    float refractiveIndex;
    /// Fresnel type.
    Fresnel fresnel;
    
public:

    /*!
     */
    SpecularTransmission(Spectrum<constant::spectrumSamples> reflectanceSpectrum, float refractiveIndex);;
    
    /*!
     Compute BRDF for the given direction for specular transmission model.
     
     @param wi incident direction.
     @param wo outgoing direction.
     
     @returns BRDF.
     */
    Spectrum<constant::spectrumSamples> f(const Vector3D& wi,
                                          const Vector3D& wo,
                                          const Intersection& intersection) const;
    
    /*!
     Computed BRDF and sample wi direction for specular transmission model.
     Useful on Monte carlo models (e.g. Path tracing).
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns BRDF and wi direction.
     */
    Spectrum<constant::spectrumSamples> samplef(Vector3D* wi,
                                                const Vector3D& wo,
                                                const Intersection& intersection) const;
    
    /*!
     Probability density function for specular transmission model.
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns pdf.
     */
    float pdf(const Vector3D& wi, const Vector3D& wo, const Intersection& intersection) const;
};

#endif /* SpecularTransmission_hpp */
