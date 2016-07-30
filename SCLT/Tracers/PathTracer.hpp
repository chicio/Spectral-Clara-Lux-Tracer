//
//  TracerSpectrum.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 18/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef PathTracer_hpp
#define PathTracer_hpp

#include "TracerSpectrum.hpp"
#include "PathBRDF.hpp"

class PathTracer : public TracerSpectrum {
private:
    
    /// Number of sample to be taken.
    int numberOfSamples;
    /// Sample weight: the result spectrum is a mean with respect to the total samples.
    float sampleWeight;
    
public:
    
    /*!
     Constructor.
     
     @param scene pointer to the scene.
     */
    PathTracer(Scene* scene);
    
    /*!
     Get color given for the current pixel or subpixel (if using antialiasing).
     
     @param ray the current ray.
     
     @returns color as Vector3D.
     */
    Vector3D getColor(const Ray& ray, const int bounce) const;
};

#endif /* PathTracer_hpp */
