//
//  Constants.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 08/08/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Constants_hpp
#define Constants_hpp

#include <cmath>

typedef enum FresnelFactorModel {
    FresnelEquations,
    SchlickApproximation
} FresnelFactorModel;

namespace constant {

    /******** General constants **********/
    
    /// pi float constant.
    const float pi = 3.14159265358979323846f;
    /// Constant used to add small quantitiy to origins of rays to avoid self intersection.
    const float epsilon = 0.0001f;
    /// Max number of bounce done by rays in ray tracer loop.
    const int maxNumberOfBounce = 5;
    /// Number of shadow ray (used in some shading model).
    const int numberOfShadowRay = 64;
    /// Fresnel factor model used for dieletric.
    const FresnelFactorModel fresnelFactorModel = FresnelEquations;

    /********* Spectrum constants *********/
    
    /// Spectrum sample.
    const int spectrumSamples = 81;
    /// Start wavelenght.
    const float spectrumStartWavelenght = 380.0f;
    /// End wavelenght.
    const float spectrumEndWalenght = 780.0f;
    /// Walenght sample distance.
    const float spectrumWalenghtSampleDistance = 5.0f; 
    
    /****** RGB constants ******/
    
    //N.B.: Use the value commented to simulate a quadratic attenuation on RGB scenes.
    //@see http://www.ozone3d.net/tutorials/glsl_lighting_phong_p4.php
    
    /// Constant attenuation.
    const float c1 = 1; //0
    /// Linear attenuation.
    const float c2 = 0; //0
    /// Quadratic attenuation
    const float c3 = 0; //0.000005
}

#endif
