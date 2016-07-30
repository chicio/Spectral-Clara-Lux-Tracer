//
//  PathBRDF.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 09/02/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#ifndef PathBRDF_hpp
#define PathBRDF_hpp

#include "BRDF.hpp"
#include "Spectrum.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"
#include "TracerSpectrum.hpp"

class PathBRDF : public ShadingSpectrumModel {
private:
    
    /*!
     Sample random BRDF to calculate SPD using the new ray obtained from sampling.
     
     @param randomBRDFsampled flag used to check if BRDF has been sampled.
     @param L surface total SPD.
     @param wo outgoing direction.
     @param material object material.
     @param intersection the data of a ray intersection.
     @param tracer the path tracer.
     @param bounce current bounce.
     @param type BRDF type to be sampled.
     
     @returns color obtained from transmission.
     */
    Spectrum<constant::spectrumSamples> randomBRDFSampling(bool& randomBRDFsampled,
                                                           Spectrum<constant::spectrumSamples>& L,
                                                           const Vector3D& wo,
                                                           const MaterialBRDF& material,
                                                           const Intersection& intersection,
                                                           const TracerSpectrum& pathTracer,
                                                           const int bounce,
                                                           const BRDFType type) const;
public:
    
    /*
     Shading operation.
     
     @param intersection intersection data.
     @param ray current ray.
     @param bounce current bounce.
     @param pathtracer path tracer.
     
     @returns SPD color using path tracing.
     */
    Spectrum<constant::spectrumSamples> shade(const Intersection& intersection,
                                              const Ray& ray,
                                              const int bounce,
                                              const TracerSpectrum& pathTracer) const;
};

#endif /* PathBRDF_hpp */
