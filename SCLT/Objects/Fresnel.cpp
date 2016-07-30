//
//  Fresnel.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 12/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Fresnel.hpp"

float Fresnel::dieletricReflectivePercentage(float cosI) const {
    
    float ni;
    float nt;
    
    //The default refractive index for n1 is 1 (vacuum).
    if(cosI < 0.0f) {
        
        //I am going from vacuum inside our transmissive material.
        ni = 1.0f;
        nt = refractiveIndex;
        cosI = -1.0f * cosI;
    } else {
        
        //I am going from inside our transmissive material to vacuum.
        ni = refractiveIndex;
        nt = 1.0f;
    }
    
    //Fresnel equations.
    float n = ni/nt;
    float cosThetaT = fmaxf(0.0f, sqrtf(1.0f - powf(n, 2.0f) * (1.0f - (powf(cosI, 2.0f) ))));
    
    if (cosThetaT == 0.0f) {
        
        //Total internal reflection.
        return 1.0f;
    }
    
    float fresnelReflected;
    
    if(constant::fresnelFactorModel == FresnelEquations) {
        
        float niCosI = ni * cosI;
        float ntCosThetaT = nt * cosThetaT;
        float ntCosI = nt * cosI;
        float niCosThetaT = ni * cosThetaT;
        
        //Fresnel equations.
        float reflectionPerpendicular = (niCosI - ntCosThetaT) / (niCosI + ntCosThetaT);
        float reflectionParallel = (ntCosI - niCosThetaT) / (ntCosI + niCosThetaT);
        fresnelReflected = (powf(reflectionPerpendicular, 2.0f) + powf(reflectionParallel, 2.0f)) / 2.0f;
    } else {
        
        //Schlick's approximation.
        float r0 = powf(((ni - nt) / (ni + nt)), 2.0f);
        fresnelReflected = r0 + (1.0f - r0) * powf(1.0f - cosI, 5.0f);
    }
    
    return fresnelReflected;
}
