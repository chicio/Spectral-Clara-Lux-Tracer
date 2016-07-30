//
//  ShadingSpectrumModel.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 06/05/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#ifndef ShadingSpectrumModel_hpp
#define ShadingSpectrumModel_hpp

#include "ShadingModel.hpp"
#include "MaterialBRDF.hpp"

class TracerSpectrum;

class ShadingSpectrumModel : public ShadingModel {
protected:
    
    /*!
     Sample delta dirac BRDF to calculate SPD using the new ray obtained from sampling.
     
     @param ray The ray used in calculation.
     @param L surface total SPD.
     @param material object material.
     @param intersectionthe data of a ray intersection.
     @param tracer the tracer used.
     @param bounce current bounce.
     @param type BRDF type to be sampled.
     
     @returns color obtained from transmission.
     */
    Spectrum<constant::spectrumSamples> deltaDiracBRDFSampling(const Ray& ray,
                                                               Spectrum<constant::spectrumSamples>& L,
                                                               const MaterialBRDF& material,
                                                               const Intersection& intersection,
                                                               const TracerSpectrum& tracer,
                                                               const int bounce,
                                                               const BRDFType type) const;
    
public:
        
    /*!
     Method to be implemented by all the subclasses to apply
     a specific shading model using SPD data.
     
     @param intersection the data of a ray intersection.
     @param ray the current ray.
     @param bounce current bounce.
     @param tracer tracer user for the scene. In this case must be a child of TracerSpectrum.
     
     @returns a SPD obtained from the shade process.
     */
    virtual Spectrum<constant::spectrumSamples> shade(const Intersection& intersection,
                                                      const Ray& ray,
                                                      const int bounce,
                                                      const TracerSpectrum& tracer) const = 0;
    
    /*!
     Destructor.
     */
    virtual ~ShadingSpectrumModel() {};
};

#endif /* ShadingSpectrumModel_hpp */
