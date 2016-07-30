//
//  OrenNayar.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 27/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef OrenNayar_hpp
#define OrenNayar_hpp

#include "MathUtils.hpp"
#include "Spectrum.hpp"
#include "BRDF.hpp"

class OrenNayar : public BRDF {
protected:
    
    /// Reflectance spectrum.
    Spectrum<constant::spectrumSamples> reflectanceSpectrum;
    /// Reflectance spectrum divide by pi. Used in samplef to return the correct spectrum after sampling.
    Spectrum<constant::spectrumSamples> reflectanceSpectrumWeightWithPi;
    /// A component in model formula.
    float A;
    /// B component in model formula.
    float B;
    
    /*!
     Calculate Oren Nayar multiplier factor.
     
     @param wi incident direction
     @param wo outgoing direction
     @param intersection intersection data

     @returns multiplier factor.
     */
    float calculateOrenNayarMultiplierFactor(const Vector3D& wi,
                                             const Vector3D& wo,
                                             const Intersection& intersection) const;
    
public:
    
    /*!
     Constructor.
     
     @param reflectanceSpectrum the reflectance spectrum.
     @param degree microfacets orientation angle degree. 
     */
    OrenNayar(Spectrum<constant::spectrumSamples> reflectanceSpectrum, float degree);
    
    /*!
     Compute BRDF for the given direction using Oren Nayar model.
     
     @param wi incident direction.
     @param w0 outgoing direction.
     
     @returns BRDF.
     */
    Spectrum<constant::spectrumSamples> f(const Vector3D& wi,
                                          const Vector3D& wo,
                                          const Intersection& intersection) const;
    
    /*!
     Computed BRDF and sample wi direction for Oren Nayar.
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
     Probability density function for Oren Nayar model.
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns pdf.
     */
    float pdf(const Vector3D& wi, const Vector3D& wo, const Intersection& intersection) const;
};

#endif /* OrenNayar_hpp */
