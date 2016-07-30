//
//  TracerRGB.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 18/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef TracerRGB_hpp
#define TracerRGB_hpp

#include "ShadingModelFactory.hpp"
#include "Tracer.hpp"

class TracerRGB : public Tracer {
public:
    
    /// Shading model.
    ShadingRGBModel* shadingModel;
    
    /*!
     Constructor.
     
     @param scene pointer to the scene.
     */
    TracerRGB(Scene* scene);
    
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
    Vector3D trace(const Ray& ray, const int bounce) const;
};

#endif /* TracerRGB_hpp */
