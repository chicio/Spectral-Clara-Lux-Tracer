//
//  ShadingRGBModel.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 06/05/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#ifndef ShadingRGBModel_hpp
#define ShadingRGBModel_hpp

#include "ShadingModel.hpp"

class ShadingRGBModel : public ShadingModel {
public:
    
    /*!
     Method to be implemented by all the subclasses to apply
     a specific shading model using RGB data.
     
     @param intersection the data of a ray intersection.
     @param ray the current ray.
     @param bounce current bounce.
     @param tracer tracer user for the scene. In this case must be a child of TracerRGB.
     
     @returns a RGB color obtained from the shade process.
     */
    virtual Vector3D shade(const Intersection& intersection,
                           const Ray& ray,
                           const int bounce,
                           const TracerRGB& tracer) const = 0;
    
    /*!
     Destructor.
     */
    virtual ~ShadingRGBModel() {};
};

#endif /* ShadingRGBModel_hpp */
