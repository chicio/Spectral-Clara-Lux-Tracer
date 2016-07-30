//
//  TorranceSparrow.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 27/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef TorranceSparrow_hpp
#define TorranceSparrow_hpp

#include "BRDF.hpp"

class TorranceSparrow : public BRDF {
protected:
    
    /// Reflectance spectrum.
    Spectrum<constant::spectrumSamples> reflectanceSpectrum;
    /// Refractive index.
    float refractiveIndex;
    /// Blinn exponent.
    float exponent;
    /// Fresnel type.
    Fresnel fresnel;    
    
    /*!
     Geometric attenuation term for Torrance sparrow.
     
     @param wi incident light.
     @param wo outgoing direction.
     @param wh half angle vector.
     @param normal.
     
     @returns float that correspond to the geometric attenuation term.
     */
    float G(const Vector3D& wi, const Vector3D& wo, const Vector3D& wh, const Vector3D& normal) const;
    
    /*!
     Blinn distribution term for Torrance Sparrow.
     
     @param wh half angle vector.
     @param normal.
     
     @returns float that correspond to the geometric attenuation term.
     */
    float D(const Vector3D& wh, const Vector3D& normal) const;
    
    /*!
     Calculate Torrance Sparrow.
     
     @param wi incident light.
     @param wo outgoing direction.
     @param wh half angle vector.
     @param normal.

     @returns reflectance spectrum obtained from Torrance Sparrow BRDF.
     */
    Spectrum<constant::spectrumSamples> calculateTorranceSparrow(const Vector3D& wi,
                                                                 const Vector3D& wo,
                                                                 const Vector3D& wh,
                                                                 const Vector3D& normal) const;
    
public:
    
    /*!
     Default constructor.
     
     @param reflectanceSpectrum the reflectance spectrum.
     @param refractiveIndex refractive index.
     @apram
     */
    TorranceSparrow(Spectrum<constant::spectrumSamples> reflectanceSpectrum, float refractiveIndex, float exponent);
    
    /*!
     Compute BRDF for the given direction using Torrance Sparrow model.
     
     @param wi incident direction.
     @param wo outgoing direction.
     
     @returns BRDF.
     */
    Spectrum<constant::spectrumSamples> f(const Vector3D& wi,
                                          const Vector3D& wo,
                                          const Intersection& intersection) const;
    
    /*!
     Computed BRDF and sample wi direction for Torrance Sparrow model.
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
     Probability density function for Torrance Sparrow model.
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns pdf.
     */
    float pdf(const Vector3D& wi, const Vector3D& wo, const Intersection& intersection) const;
};


#endif /* TorranceSparrow_hpp */
