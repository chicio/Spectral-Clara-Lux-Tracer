//
//  BRDF.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 24/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef BRDF_hpp
#define BRDF_hpp

#include "Fresnel.hpp"
#include "MathUtils.hpp"
#include "Intersection.hpp"
#include "Vector3D.hpp"
#include "Spectrum.hpp"
#include "Matrix.hpp"
#include "RandomNumberGenerator.hpp"

typedef enum BRDFType {
    Diffuse,
    Specular,
    Reflection,
    Transmission
} BRDFType;

class BRDF {
public:
    
    /// Flag used to specify the type of brdf.
    BRDFType brdfType;
    
    /*!
     Contructor.
     
     @param brdfType the type of brdf.
     */
    BRDF(BRDFType brdfType) : brdfType{brdfType} {};
    
    /*!
     Cosine weighted hemisphere sample for standard importance sampling.
     Used in samplef method of all diffuse BRDF, and in general where as specific distribution is used.
     
     @param intersection intersection data.
     
     @return sample direction in world coordinates from cosine weighted distribution.
     */
    Vector3D cosineWeightedHemisphereBRDFDirectionSampling(const Intersection& intersection) const;
    
    /*!
     Compute BRDF for the given direction.
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns BRDF.
    */
    virtual Spectrum<constant::spectrumSamples> f(const Vector3D& wi,
                                                  const Vector3D& wo,
                                                  const Intersection& intersection) const = 0;
    
    /*!
     Computed BRDF and sample wi direction.
     Useful on Monte carlo models (e.g. Path tracing).
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns BRDF and wi.
     */
    virtual Spectrum<constant::spectrumSamples> samplef(Vector3D* wi,
                                                        const Vector3D& wo,
                                                        const Intersection& intersection) const = 0;
    
    /*!
     Calculate the probability density function for the sampled direction of BRDF.
     Useful on Monte carlo models (e.g. Path tracing).
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns pdf.
     */
    virtual float pdf(const Vector3D& wi, const Vector3D& wo, const Intersection& intersection) const = 0;
};

#endif /* BRDF_hpp */
