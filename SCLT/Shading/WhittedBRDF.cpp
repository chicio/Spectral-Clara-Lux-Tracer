//
//  WhittedBRDF.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 24/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "WhittedBRDF.hpp"

Spectrum<constant::spectrumSamples> WhittedBRDF::shade(const Intersection& intersection,
                                                       const Ray& ray,
                                                       const int bounce,
                                                       const TracerSpectrum& tracer) const {
    
    Model* object = intersection.object;
    MaterialBRDF* material = static_cast<MaterialBRDF*>(object->material);
    
    //Calculate light direction.
    Vector3D wi = tracer.scene->light->origin - intersection.point;
    wi.normalize();
    
    //Viewer point direction.
    Vector3D wo = ray.origin - intersection.point;
    wo.normalize();
    
    //Shadow.
    float shadowPercentage = tracer.shadowCalculator->visiblePercentage(intersection.point);

    //Light.
    Spectrum<constant::spectrumSamples> Li = tracer.scene->light->spectrum;
    
    //BRDFs.
    Spectrum<constant::spectrumSamples> f = material->f(wi, wo, intersection);
    
    //SCLT doesn't use any change of coordinate system on
    //whitted model. For this reason we can't take the absolute value
    //of cosTetha attenuation factor: it must be setted to 0 if the
    //dot product is negative (point of surface not seen by the light
    //source).
    float cosI = wi.dot(intersection.normal);
    
    if(cosI <= 0.0f) {
        
        cosI = 0.0f;
    }
    
    //Rendering equation.
    Spectrum<constant::spectrumSamples> L = f * Li * cosI * shadowPercentage;
    
    //Limit bounce ray.
    if(bounce == 0) {
        
        return L;
    }
    
    deltaDiracBRDFSampling(ray, L, *material, intersection, tracer, bounce, Reflection);
    deltaDiracBRDFSampling(ray, L, *material, intersection, tracer, bounce, Transmission);
    
    return L;
}
