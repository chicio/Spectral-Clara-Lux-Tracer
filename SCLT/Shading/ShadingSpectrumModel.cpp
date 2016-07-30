//
//  ShadingSpectrumModel.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 06/05/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "ShadingSpectrumModel.hpp"
#include "TracerSpectrum.hpp"

Spectrum<constant::spectrumSamples> ShadingSpectrumModel::deltaDiracBRDFSampling(const Ray& ray,
                                                                                 Spectrum<constant::spectrumSamples>& L,
                                                                                 const MaterialBRDF& material,
                                                                                 const Intersection& intersection,
                                                                                 const TracerSpectrum& tracer,
                                                                                 const int bounce,
                                                                                 const BRDFType type) const {
    
    //Type of delta dirac BRDF:
    // - specular reflection
    // - transmission
    // See BRDF implementation for details (SpecularTransmission and SpecularReflection).
    if(type != Reflection && type != Transmission) {
        
        return L;
    }
    
    //Sample delta dirac BRDF
    Vector3D wi(INFINITY, INFINITY, INFINITY);
    Spectrum<constant::spectrumSamples> f = material.samplef(&wi, ray.direction, intersection, type);
    
    if(wi.x != INFINITY && wi.y != INFINITY && wi.z != INFINITY) {
        
        //Normalize.
        wi.normalize();
        
        //If object is reflective ray trace the reflective ray.
        Ray sampledRay(MathUtils::addEpsilon(intersection.point, wi), wi);
        Spectrum<constant::spectrumSamples> Li = tracer.trace(sampledRay, bounce - 1);
        
        //Apply rendering equation (summing it up to previously accumulated L).
        //In any of the BRDF model descrined by delta dirac BRDF doesn't need
        //PDF in any case. This is way this method is common to all the shading models.
        L = L + f * Li * fabsf(wi.dot(intersection.normal));
    }
    
    return L;
}
