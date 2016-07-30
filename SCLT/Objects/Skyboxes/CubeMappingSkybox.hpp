//
//  CubeMappingSkybox.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 26/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef CubeMappingSkybox_hpp
#define CubeMappingSkybox_hpp

#include "Texture.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"

class CubeMappingSkybox {
private:

    /// Top texture.
    Texture* top;
    /// Bottom texture.
    Texture* bottom;
    /// Right texture.
    Texture* right;
    /// Left texture.
    Texture* left;
    /// Front texture.
    Texture* front;
    /// Back texture.
    Texture* back;
    
public:
    
    /*!
     Default constructor.
     */
    CubeMappingSkybox();
    
    /*!
     Method used to read from a skybox texture.
     
     @see http://www.ics.uci.edu/~gopi/CS211B/RayTracing%20tutorial.pdf
     
     @param ray the ray to be tested.
     
     @returns The texel color.
     */
    Vector3D readSkyboxTexture(const Ray& ray) const;
    
    /*!
     Default destructor.
     */
    ~CubeMappingSkybox();
};

#endif /* CubeMappingSkybox_h */
