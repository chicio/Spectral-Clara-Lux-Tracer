//
//  Material.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 05/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include "Texture.hpp"
#include "PerlinTexture.hpp"
#include "MarbleTexture.hpp"
#include "TurbulenceTexture.hpp"
#include "BumpMap.hpp"
#include "Constants.hpp"

class Material {
public:
    
    /// Perlin texture associated with the material (Marble, turbulence...), if there's one.
    PerlinTexture* perlinTexture;
    /// Set a bump mapping texture, if there's one (supported only on some shading models at the moment).
    BumpMap* bumpMap;
    /// Texture to be applied to the object (supported only on some shading models at the moment).
    Texture* texture;
    
    /*!
     Destructor.
     */
    ~Material();
};

#endif
