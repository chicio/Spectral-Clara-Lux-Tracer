//
//  Fresnel.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 27/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Fresnel_hpp
#define Fresnel_hpp

#include <cmath>

#include "Constants.hpp"

class Fresnel {
private:
    
    /// The refractive index
    float refractiveIndex;
        
public:
    
    /*!
     Default constructor.
     */
    Fresnel() : refractiveIndex{0.0f} {};
    
    /*!
     Constructor.
     
     @param type type of fresnel model to be applied.
     @param refractiveIndex index of refraction.
     */
    Fresnel(float refractiveIndex) : refractiveIndex{refractiveIndex} {};
    
    /*!
     Calculate percentage of reflected light based on cosine of the angle of incident light.
     
     @param cosI cosine angle between incident light and normal.
     
     @returns percentage of reflected light (0.0 - 1.0).
     */
    float dieletricReflectivePercentage(float cosI) const;
};

#endif /* Fresnel_hpp */
