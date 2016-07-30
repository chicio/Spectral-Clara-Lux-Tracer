//
//  CubeMappingSkybox.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 26/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "CubeMappingSkybox.hpp"

CubeMappingSkybox::CubeMappingSkybox() {
    
    front  = new Texture("Front");
    top    = new Texture("Top");
    bottom = new Texture("Bottom");
    back   = new Texture("Back");
    right  = new Texture("Right");
    left   = new Texture("Left");
}

Vector3D CubeMappingSkybox::readSkyboxTexture(const Ray& ray) const {
    
    TextureCoordinate textureCoordinate;
    Vector3D skyboxPixelColor(0, 0, 0);
    
    //The component that is greater, as absolute value, of the other two
    //is the one that the ray points to. Then using its sign it is possible to find the side:
    //- x => left or right
    //- y => top or bottom
    //- z => front or back
    
    if ((fabsf(ray.direction.x) >= fabsf(ray.direction.y)) &&
        (fabsf(ray.direction.x) >= fabsf(ray.direction.z))) {
        
        if (ray.direction.x > 0.0f) {
            
            textureCoordinate.u = 1.0f - (ray.direction.z / ray.direction.x +  1.0f) * 0.5f;
            textureCoordinate.v = (ray.direction.y / ray.direction.x + 1.0f) * 0.5f;
            skyboxPixelColor = right->readTexture(textureCoordinate);
        } else if (ray.direction.x < 0.0f) {
            
            textureCoordinate.u = 1.0f - (ray.direction.z / ray.direction.x + 1.0f) * 0.5f;
            textureCoordinate.v = 1.0f - (ray.direction.y / ray.direction.x + 1.0f) * 0.5f;
            skyboxPixelColor = left->readTexture(textureCoordinate);
        }
    } else if ((fabsf(ray.direction.y) >= fabsf(ray.direction.x)) &&
               (fabsf(ray.direction.y) >= fabsf(ray.direction.z))) {
        
        if (ray.direction.y > 0.0f) {
            
            textureCoordinate.u = (ray.direction.x / ray.direction.y + 1.0f) * 0.5f;
            textureCoordinate.v = 1.0f - (ray.direction.z / ray.direction.y + 1.0f) * 0.5f;
            skyboxPixelColor = top->readTexture(textureCoordinate);
        }else if (ray.direction.y < 0.0f) {
            
            textureCoordinate.u = 1.0f - (ray.direction.x / ray.direction.y + 1.0f) * 0.5f;
            textureCoordinate.v = (ray.direction.z/ray.direction.y + 1.0f) * 0.5f;
            skyboxPixelColor = bottom->readTexture(textureCoordinate);
        }
    }else if ((fabsf(ray.direction.z) >= fabsf(ray.direction.x)) &&
              (fabsf(ray.direction.z) >= fabsf(ray.direction.y))) {
        
        if (ray.direction.z > 0.0f) {
            
            textureCoordinate.u = (ray.direction.x / ray.direction.z + 1.0f) * 0.5f;
            textureCoordinate.v = (ray.direction.y / ray.direction.z + 1.0f) * 0.5f;
            skyboxPixelColor = front->readTexture(textureCoordinate);
        }else if (ray.direction.z < 0.0f) {
            
            textureCoordinate.u = (ray.direction.x / ray.direction.z + 1.0f) * 0.5f;
            textureCoordinate.v = 1.0f - (ray.direction.y / ray.direction.z + 1) * 0.5f;
            skyboxPixelColor = back->readTexture(textureCoordinate);
        }
    }
    
    return skyboxPixelColor;
}

CubeMappingSkybox::~CubeMappingSkybox() {
    
    delete front;
    delete top;
    delete bottom;
    delete back;
    delete right;
    delete left;
}
