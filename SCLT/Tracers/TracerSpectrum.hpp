//
//  TracerSpectrum.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 18/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef TracerSpectrum_hpp
#define TracerSpectrum_hpp

#include "ColorMatchingFunction.hpp"
#include "ShadingModelFactory.hpp"
#include "Tracer.hpp"

class TracerSpectrum : public Tracer {
protected:
    
    /// Shading model.
    ShadingSpectrumModel* shadingModel;
    /// Color matching function.
    ColorMatchingFunction* colorMatchingFunction;
    
public:
    
    /*!
     Constructor.
     
     @param scene pointer to the scene.
     */
    TracerSpectrum(Scene* scene);
        
    /*!
     Get color given for the current pixel or subpixel (if using antialiasing).
     
     @param ray the current ray.
     
     @returns color as Vector3D.
     */
    Vector3D getColor(const Ray& ray, const int bounce) const;
    
    /*!
     Trace the ray received as parameter.
     
     @param ray the ray to be traced.
     
     @returns color for current ray as Vector3D.
     */
    Spectrum<constant::spectrumSamples> trace(const Ray& ray, const int bounce) const;
    
    /*!
     Destructor.
     */
    ~TracerSpectrum();
};

#endif /* TracerSpectrum_hpp */
