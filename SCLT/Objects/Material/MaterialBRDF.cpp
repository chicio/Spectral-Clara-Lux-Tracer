//
//  MaterialBRDF.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 23/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "MaterialBRDF.hpp"
#include "Illuminant.hpp"

Spectrum<constant::spectrumSamples> MaterialBRDF::f(const Vector3D& wi,
                                                    const Vector3D& wo,
                                                    const Intersection& intersection) const {

    Spectrum<constant::spectrumSamples> f(0.0f);
    
    for(std::vector<BRDF *>::size_type i = 0; i != brdfs.size(); i++) {
     
        f = f + brdfs[i]->f(wi, wo, intersection);
    }
    
    return f;
}

Spectrum<constant::spectrumSamples> MaterialBRDF::samplef(Vector3D* wi,
                                                          const Vector3D& wo,
                                                          const Intersection& intersection,
                                                          const BRDFType type) const {
    
    Spectrum<constant::spectrumSamples> f(0.0f);
    
    for(std::vector<BRDF *>::size_type i = 0; i != brdfs.size(); i++) {

        if(brdfs[i]->brdfType == type) {
            
            f = f +  brdfs[i]->samplef(wi, wo, intersection);
        }
    }
        
    return f;
}

float MaterialBRDF::pdf(const Vector3D& wi,
                        const Vector3D& wo,
                        const Intersection& intersection,
                        const BRDFType type) const {
    
    for(std::vector<BRDF *>::size_type i = 0; i != brdfs.size(); i++) {
        
        if(brdfs[i]->brdfType == type) {
            
            return brdfs[i]->pdf(wi, wo, intersection);
        }
    }
    
    return 0.0F;
}

Material* MaterialBRDF::emissiveMaterial(Spectrum<constant::spectrumSamples> illuminant) {

    MaterialBRDF* emissiveMaterial = new MaterialBRDF();
    emissiveMaterial->le = illuminant;
    emissiveMaterial->brdfs.push_back(new Lambertian(Spectrum<constant::spectrumSamples>(0.0f)));

    return emissiveMaterial;
}

Material* MaterialBRDF::matteMaterial(Spectrum<constant::spectrumSamples> spectrum) {
    
    //Matte material.
    MaterialBRDF* matteMaterial = new MaterialBRDF();
    matteMaterial->brdfs.push_back(new Lambertian(spectrum));
    
    return matteMaterial;
}

Material* MaterialBRDF::matteMaterial(Spectrum<constant::spectrumSamples> spectrum, float degree) {
    
    //Matte material.
    MaterialBRDF* matteMaterial = new MaterialBRDF();
    matteMaterial->brdfs.push_back(new OrenNayar (spectrum, degree));
    
    return matteMaterial;
}

Material* MaterialBRDF::plasticMaterial(Spectrum<constant::spectrumSamples> spectrumDiffuse,
                                        Spectrum<constant::spectrumSamples> spectrumSpecular,
                                        float roughness) {
    
    //Plastic material.
    MaterialBRDF* plasticMaterial = new MaterialBRDF();
    plasticMaterial->brdfs.push_back(new Lambertian (spectrumDiffuse));
    plasticMaterial->brdfs.push_back(new TorranceSparrow(spectrumSpecular, 1.5, roughness));
    
    return plasticMaterial;
}

Material* MaterialBRDF::glassMaterial() {
    
    MaterialBRDF* mirrorMaterial = new MaterialBRDF();
    mirrorMaterial->brdfs.push_back(new SpecularReflection(Spectrum<constant::spectrumSamples>(1.0f), 1.5));
    mirrorMaterial->brdfs.push_back(new SpecularTransmission(Spectrum<constant::spectrumSamples>(1.0f), 1.5));
    
    return mirrorMaterial;
}

Material* MaterialBRDF::measuredMaterial(const char *filename, bool interpolated) {
    
    MaterialBRDF* measuredMaterial = new MaterialBRDF();
    measuredMaterial->brdfs.push_back(new Measured(filename, interpolated));

    return measuredMaterial;
}
