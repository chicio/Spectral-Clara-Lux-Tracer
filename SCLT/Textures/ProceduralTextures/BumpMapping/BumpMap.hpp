//
//  BumpMap.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 14/08/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef BumpMap_hpp
#define BumpMap_hpp

#include "PerlinNoise.hpp"
#include "Vector3D.hpp"
#include "Point3D.hpp"

class BumpMap {
private:
    
    /// Scale factor to be applied during normal bump map.
    float scale;
    
public:
    
    /*!
     Constructor.
     
     @param scale the scale factor applied to the normal calculation.
     
     @returns a bump map instance.
     */
    BumpMap(float scale) : scale{scale} {};
    
    /*!
     Return the normal of the object modified using the bump map.
     
     @param point the point to which I apply the bump map.
     @param normal normal to be modified.
     
     @param the new normal to be used in light calculation.
     */
    Vector3D bumpMapTexture(const Point3D& point, const Vector3D& normal) const;
};

#endif
