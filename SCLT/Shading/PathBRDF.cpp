//
//  PathBRDF.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 09/02/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "PathTracer.hpp"
#include "PathBRDF.hpp"
#include "MaterialBRDF.hpp"

Spectrum<constant::spectrumSamples> PathBRDF::shade(const Intersection& intersection,
                                                    const Ray& ray,
                                                    const int bounce,
                                                    const TracerSpectrum& pathTracer) const {
    
    //Max iteration allowed
    if(bounce == 0) {
        
        return Spectrum<constant::spectrumSamples>(0.0f);
    }

    
    Model* object = intersection.object;
    MaterialBRDF* material = static_cast<MaterialBRDF*>(object->material);
    
    if(object->isLight == true) {
        
        //Stop iteration. Light reached.
        return material->le;
    }
    
    Vector3D wo = ray.origin - intersection.point;
    wo.normalize();
    
    Spectrum<constant::spectrumSamples> L(0.0f);
    
    bool randomBRDFsampled = false;
    
    randomBRDFSampling(randomBRDFsampled, L, wo, *material, intersection, pathTracer, bounce, Diffuse);
    randomBRDFSampling(randomBRDFsampled, L, wo, *material, intersection, pathTracer, bounce, Specular);

    //If a random BRDF has been sampled return SPD L.
    //This is a consequence of the fact that random and delta dirac BRDF could not be used
    //at the same time on the same object.
    if(randomBRDFsampled == true) {
        
        return L;
    }
    
    deltaDiracBRDFSampling(ray, L, *material, intersection, pathTracer, bounce, Reflection);
    deltaDiracBRDFSampling(ray, L, *material, intersection, pathTracer, bounce, Transmission);
    
    return L;
}

Spectrum<constant::spectrumSamples> PathBRDF::randomBRDFSampling(bool& randomBRDFsampled,
                                                                 Spectrum<constant::spectrumSamples>& L,
                                                                 const Vector3D& wo,
                                                                 const MaterialBRDF& material,
                                                                 const Intersection& intersection,
                                                                 const TracerSpectrum& pathTracer,
                                                                 const int bounce,
                                                                 const BRDFType type) const {
    
    Vector3D wi(INFINITY, INFINITY, INFINITY);
    
    //Sample brdf of the give type.
    Spectrum<constant::spectrumSamples> f = material.samplef(&wi, wo, intersection, type);
    
    if(wi.x != INFINITY && wi.y != INFINITY && wi.z != INFINITY) {
        
        //BRDF has been sampled.
        randomBRDFsampled = true;
        
        //Normalize wi.
        wi.normalize();
        
        //Get pdf of wi sampled from brdf.
        float pdf = material.pdf(wi, wo, intersection, type);
        
        Spectrum<constant::spectrumSamples> weight(0.0f);
        
        //Check pdf to avoid 0/0 division (and NaN generation).
        //A spectrum composed of NaN values could bend all samples
        //during sum in Tracer classes.
        if(pdf > 0.0f) {
            
            weight = (f * fabsf(wi.dot(intersection.normal))) / pdf;
        } else {
            
            //Weight is 0, so all bounces will be useless.
            return L;
        }
        
        //Setup new ray to be traced.
        Ray newRay(MathUtils::addEpsilon(intersection.point, intersection.normal), wi);
        
        //Rendering equation with recursive path tracing calculation.
        L = L + weight * pathTracer.trace(newRay, bounce - 1);
    }
    
    return L;
}
