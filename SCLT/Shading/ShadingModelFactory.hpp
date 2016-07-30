//
//  ShadingModelFactory.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 14/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef ShadingModelFactory_hpp
#define ShadingModelFactory_hpp

#include "ShadingModel.hpp"
#include "ShadingSpectrumModel.hpp"
#include "ShadingRGBModel.hpp"
#include "ShadingModelType.hpp"

class ShadingModelFactory {
public:

    /*!
     Generate the shading model to be used during rendering
     of the current scene.
     
     @param shadingModelType the type of shading model to be used.
     
     @returns a shading model.
     */
    ShadingRGBModel* createShadingModelRGB(ShadingModelType shadingModelType);
    
    /*!
     Generate the shading model to be used during rendering
     of the current scene.
     
     @param shadingModelType the type of shading model to be used.
     
     @returns a shading model.
     */
    ShadingSpectrumModel* createShadingModelSpectrum(ShadingModelType shadingModelType);
};

#endif /* ShadingModelFactory_hpp */
