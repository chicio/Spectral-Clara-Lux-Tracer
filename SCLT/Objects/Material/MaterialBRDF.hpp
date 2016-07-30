//
//  MaterialBRDF.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 23/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef MaterialBRDF_hpp
#define MaterialBRDF_hpp

#include <vector>

#include "Material.hpp"
#include "BRDF.hpp"
#include "Lambertian.hpp"
#include "OrenNayar.hpp"
#include "TorranceSparrow.hpp"
#include "SpecularReflection.hpp"
#include "SpecularTransmission.hpp"
#include "Measured.hpp"

class MaterialBRDF : public Material {
public:
    
    /// Emissive component.
    Spectrum<constant::spectrumSamples> le;
    /// Array that store the BRDFs associated with an object.
    std::vector<BRDF *> brdfs;
    
    /*!
     Return evaluation of BRDF for the material.
     
     @param wi incident light direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     
     @returns the spectrum that represents the sum of the various brdf for the current object.
     */
    Spectrum<constant::spectrumSamples> f(const Vector3D& wi,
                                          const Vector3D& wo,
                                          const Intersection& intersection) const;
    
    /*!
     Sample BRDF of specific type.
     
     @param wi incident direction.
     @param wo outgoing direction.
     @param intersection intersection data.
     @param type type of brdf to be sampled.
     
     @returns the spectrum that represents the sum of the various brdf sampled.
     */
    Spectrum<constant::spectrumSamples> samplef(Vector3D* wi,
                                                const Vector3D& wo,
                                                const Intersection& intersection,
                                                const BRDFType type) const;
    
    /*!
     PDF for a specific BRDF type.
     
     @param wi incident light direction.
     @param wo outgoing direction.
     @param intersection the intersection data.     
     @param type type of brdf.
     
     @return pdf.
     */
    float pdf(const Vector3D& wi,
              const Vector3D& wo,
              const Intersection& intersection,
              const BRDFType type) const;

    /*!
     Create emissive material.
     
     @param illuminant
     
     @returns a material objetc.
     */
    static Material* emissiveMaterial(Spectrum<constant::spectrumSamples> illuminant);
    
    /*!
     Create a matte material with Lambertian BRDF.
     
     @param spectrum the diffuse spectrum  to be used.
     
     @returns a material object.
     */
    static Material* matteMaterial(Spectrum<constant::spectrumSamples> spectrum);

    /*!
     Create a matte material with Oren Nayar BRDF.
     
     @param spectrum the diffuse spectrum  to be used.
     @param degree standard deviation from the orientation angle.
     
     @returns a material object.
     */
    static Material* matteMaterial(Spectrum<constant::spectrumSamples> spectrum, float degree);
    
    /*!
     Create a plastic material.
     
     @param spectrumDiffuse spectrum used for Lambertian BRDF.
     @param spectrumSpecular spectrum used for Torrance Sparrow BRDF.
     @param roughness roughness used to define Blinn Distribution on Torrance Sparrow.
     
     @returns a material object.
     */
    static Material* plasticMaterial(Spectrum<constant::spectrumSamples> spectrumDiffuse,
                                     Spectrum<constant::spectrumSamples> spectrumSpecular,
                                     float roughness);

    /*!
     Create a glass material.
     
     @returns a material object.
     */
    static Material* glassMaterial();
    
    /*!
     Create a material from measure BRDF data.
     Cornell reflectance data must be used.
     
     @param file name that contains brdf data
     @param interpolated if true spectrum samples will be interpolated.
     
     @returns a material object.
     */
    static Material* measuredMaterial(const char *filename, bool interpolated);
};

#endif /* MaterialBRDF_hpp */
