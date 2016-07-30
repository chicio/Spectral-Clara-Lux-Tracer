//
//  Reflection.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 11/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef SpecularReflection_hpp
#define SpecularReflection_hpp

#include "BRDF.hpp"

class SpecularReflection : public BRDF {
protected:
    
    /// Reflectance spectrum.
    Spectrum<constant::spectrumSamples> reflectanceSpectrum;
    /// Refractive index.
    float refractiveIndex;
    /// Fresnel type.
    Fresnel fresnel;
    
public:
    
    /*!
     Constructor.
     
     @param reflectanceSpectrum 
     @param refractiveIndex refractive index.
     */
    SpecularReflection(Spectrum<constant::spectrumSamples> reflectanceSpectrum, float refractiveIndex);
  
    /*!
     Compute BRDF for the given direction using specular reflection model.
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns BRDF.
     */
    Spectrum<constant::spectrumSamples> f(const Vector3D& wi,
                                          const Vector3D& wo,
                                          const Intersection& intersection) const;

    /*!
     Computed BRDF and sample wi direction for specular reflection model.
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
     Probability density function for specular reflection model.
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns pdf.
     */
    float pdf(const Vector3D& wi, const Vector3D& wo, const Intersection& intersection) const;
};

#endif /* Reflection_hpp */
