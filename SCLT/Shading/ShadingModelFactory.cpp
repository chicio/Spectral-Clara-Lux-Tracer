//
//  ShadingModelFactory.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 14/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Whitted.hpp"
#include "WhittedBRDF.hpp"
#include "PathBRDF.hpp"
#include "ShadingModelFactory.hpp"

ShadingRGBModel* ShadingModelFactory::createShadingModelRGB(ShadingModelType shadingModelType) {
    
    ShadingRGBModel* shadingModel;
    
    switch (shadingModelType) {
        case WhittedShadingModel:
            shadingModel = new Whitted();
            break;
        default:
			shadingModel = new Whitted();
			break;
    }
    
    return shadingModel;
}

ShadingSpectrumModel* ShadingModelFactory::createShadingModelSpectrum(ShadingModelType shadingModelType) {
    
    ShadingSpectrumModel* shadingModel;
    
    switch (shadingModelType) {
        case WhittedBRDFShadingModel:
            shadingModel = new WhittedBRDF();
            break;
        case PathTracingBRDFShadingModel:
            shadingModel = new PathBRDF();
            break;
        default:
			//Default use Whitted with spectrum
			shadingModel = new WhittedBRDF();
			break;
    }
    
    return shadingModel;
}
