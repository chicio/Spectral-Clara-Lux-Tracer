//
//  Material.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 15/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Material.hpp"

Material::~Material() {
    
    delete texture;
    delete perlinTexture;
    delete bumpMap;
}
