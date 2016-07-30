//
//  WhittedBRDF.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 24/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef WhittedBRDF_hpp
#define WhittedBRDF_hpp

#include "ShadingSpectrumModel.hpp"
#include "Spectrum.hpp"
#include "MaterialBRDF.hpp"
#include "TracerSpectrum.hpp"

class WhittedBRDF : public ShadingSpectrumModel {
public:
    
    /*
     Shading operation.
     
     @param intersection intersection data.
     @param ray current ray.
     @param bounce current bounce.
     @param tracer current tracer.
     
     @returns SPD using Whitted BRDF model.
     */
    Spectrum<constant::spectrumSamples> shade(const Intersection& intersection,
                                              const Ray& ray,
                                              const int bounce,
                                              const TracerSpectrum& tracer) const;
};

#endif /* WhittedBRDF_hpp */
