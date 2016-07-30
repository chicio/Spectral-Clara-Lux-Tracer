//
//  Light.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 31/10/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Light_hpp
#define Light_hpp

#include "Illuminant.hpp"
#include "Spectrum.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"

class Light {
public:
    
    /// Origin of the light.
    Point3D origin;
    /// Color of the light.
    Vector3D color;
    /// Spectrum associated to light.
    Spectrum<constant::spectrumSamples> spectrum;
    
    /*!
     Default constructor.
     */
    Light() : origin{Point3D(0, 0, 0)}, color{Vector3D(255, 255, 255)}, spectrum{Illuminant::d65} {}

    /*!
     Constructor.
    
     @param origin origin of the light.
     @param color the color of the light.
    
     @returns an Light instance.
     */
    Light(Point3D origin, Vector3D color) : origin{origin}, color{color} {}
    
    /*!
     Constructor.
     
     @param origin origin of the light.
     @param spectrum the spectrum of light.
     
     @returns an Light instance.
     */
    Light(Point3D origin, Spectrum<constant::spectrumSamples> spectrum) : origin{origin}, spectrum{spectrum} {}
    
    /*
     Default constructor.
     */
    virtual ~Light() {};
};

#endif /* Light_hpp */
