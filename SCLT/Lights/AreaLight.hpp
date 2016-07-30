//
//  AreaLight.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 31/10/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef AreaLight_hpp
#define AreaLight_hpp

#include <vector>
#include <random>
#include <chrono>

#include "Constants.hpp"
#include "Light.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Sphere.hpp"
#include "Spectrum.hpp"

class AreaLight : public Light {
    
    /// Generator used to get random double.
    std::default_random_engine generator;
    
    /*!
     Setup of the area light. This method execute all the action needed to setup the area light. 
     Called from the various constructor implementation.
     
     @param origin origin of the area light.
     @param radius radius of the area light.
     */
    void setupAreaLight(const Point3D& origin, float radius);
    
    /*!
     Method used to generate random unit vector.
     This vectors are used to generate random
     points on the sphere area light.
     
     @see http://mathworld.wolfram.com/SpherePointPicking.html
     @see Graphics gems vol. III
     @see http://stackoverflow.com/questions/13775510/soft-shadows-spherical-area-light-source
     */
    Vector3D generateRandomSphereUnitVector();
    
    /*!
     Method used to generate random points on the sphere used as light area.
     */
    void generateRandomPointsOnSphere();
    
public:
    
    /// Sphere used to simulate the area of the light.
    Sphere* lightSphere;
    
    /// Array used to maintain a list of random point on the sphere surface. Used in soft shadow rendering.
    std::vector<Point3D> randomSpherePoints;

    /*!
     Constructor.
     
     @param origin origin of the area light. It corresponds to the center of the area.
     @param color the color of the area light.
     @param radius the radius of the sphere used as area light.
     
     @returns an AreaLight instance.
     */
    AreaLight(Point3D origin, Vector3D color, float radius);

    /*!
     Constructor.
     
     @param origin origin of the area light.
     @param lightSpectrum the SPD of the area light.
     @param radius the radius of the sphere used as area light.
     
     @returns an AreaLight instance.
     */
    AreaLight(Point3D origin, Spectrum<constant::spectrumSamples> lightSpectrum, float radius);
    
    /*
     Default constructor.
     */
    ~AreaLight();
};

#endif /* AreaLight_hpp */
