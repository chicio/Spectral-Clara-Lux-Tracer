//
//  ShadowCalculator.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 14/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef ShadowCalculator_hpp
#define ShadowCalculator_hpp

#include "AreaLight.hpp"
#include "Point3D.hpp"

class Tracer;

class ShadowCalculator {
private:
    
    /// Reference to the ray tracer.
    const Tracer& tracer;
    
    /*!
     Calculate soft shadow percentage.
     
     @param light area light used during test.
     @param pointToBeTested point to be tested.
     
     @returns the percentage of shadow as float.
     */
    float softShadow(const AreaLight* light, const Point3D& pointToBeTested) const;
    
    /*!
     Check if a point is in shadow or not. It checks comparing its position with the position of a point
     on the current light tested.
     
     @param pointToBeTested point to be tested.
     @param lightPoint point on the current light tested.
     
     @returns a bool that indicate if a point is in shadow or not.
     */
    bool inShadow(const Point3D& pointToBeTested, const Point3D& lightPoint) const;
    
public:
    
    /*!
     Constructor.
     
     @param tracer Tracer used to render the scene.
     */
    ShadowCalculator(const Tracer& tracer) : tracer(tracer) {};
    
    /*!
     Calculate visible percentage of a given point in the scene.
     If standard shadow are activate we receive 0 (shadow) or 1 (not shadow). 
     In case of soft shadow we have a variable percentage.
     
     @param pointToBeTested point to be tested.
     */
    float visiblePercentage(const Point3D& pointToBeTested);
};

#endif /* ShadowCalculator_hpp */
