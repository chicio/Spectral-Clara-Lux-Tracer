//
//  PerlinNoise.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 14/08/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef PerlinNoise_hpp
#define PerlinNoise_hpp

#include <math.h>

class PerlinNoise {
private:
    
    /// Permutation array use in the noise generation procedure.    
    int _p[512];
    
    /*!
     Constructor.
     */
    PerlinNoise();
    
    /*
     Constructor.
     */
    PerlinNoise(PerlinNoise const& copy);            // Avoid copy
    
    /*!
     Overridden assign operator.
     */
    PerlinNoise& operator=(PerlinNoise const& copy); // Avoid copy
    
    /*!
     Ease/fade curve. 
     The curve used is 6t^5 - 15t^4 + 10t^3.
     
     @param t
     
     @returns float.
     */
    float fade(float t) const;
    
    /*!
     Linear interpolation.
     
     @param t
     @param a
     @param b
     
     @returns float.
     */
    float lerp(float t, float a, float b) const;
    
    /*!
     Calculate dot product between of the gradient
     selected and the 8 location vectors.
     
     @param hash
     @param x
     @param y
     @param z 
     
     @returns float.
     */
    float grad(int hash, float x, float y, float z) const;
    
public:
    
    static PerlinNoise& getInstance();
    
    /*!
     Generate noise given coordinate values.
     
     @param x x coordinate.
     @param y y coordinate.
     @param z z coordinate.
     
     @return noise generated with the given parameter.
     */
    float noise(float x, float y, float z) const;
};

#endif
