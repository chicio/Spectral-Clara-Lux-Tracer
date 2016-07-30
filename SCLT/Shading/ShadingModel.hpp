//
//  Surface.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 11/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef ShadingModel_hpp
#define ShadingModel_hpp

#include "Constants.hpp"
#include "Intersection.hpp"
#include "ShadingModel.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include "Spectrum.hpp"

class Tracer;
class TracerRGB;

class ShadingModel {
public:
    
    /*!
     Destructor.
     */
    virtual ~ShadingModel() {};
};

#endif /* shadingModel_hpp */
