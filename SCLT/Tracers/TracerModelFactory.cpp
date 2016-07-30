//
//  TracerModelFactory.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 29/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "TracerRGB.hpp"
#include "TracerSpectrum.hpp"
#include "PathTracer.hpp"
#include "TracerModelFactory.hpp"

Tracer* TracerModelFactory::createTracer(TracerModelType tracerModelType, Scene* scene) {
    
    Tracer* tracer;
    
    switch (tracerModelType) {
        case TracerRGBModel:
            tracer = new TracerRGB(scene);
            break;
        case TracerSpectrumModel:
            tracer = new TracerSpectrum(scene);
            break;
        case PathTracerModel:
            tracer = new PathTracer(scene);
            break;
        default:
            tracer = nullptr;
            break;
    }
    
    return tracer;
}
