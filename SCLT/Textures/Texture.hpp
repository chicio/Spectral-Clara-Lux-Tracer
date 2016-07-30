//
//  Texture.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 26/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <vector>

#include "Vector3D.hpp"

typedef struct TextureCoordinate {
    float u;
    float v;
} TextureCoordinate;

class Texture {
private:

    /// Vector used to store pixels data, 4 bytes each one, ordered RGBA.
    std::vector<unsigned char> image;
    /// width of the texture.
    unsigned width;
    /// height of the texture.
    unsigned height;
    
    /*!
     Read texel from texture image array of pixel.
     
     @param xp x coordinate of the texel.
     @param yp y coordinate of the texel.
     
     @returns a texel as Vector3D.
     */
    Vector3D getTexel(int xp, int yp);

public:
    
    /*!
     Constructor.
     
     @param imageName the name of the image to be loaded as texture.
     
     @returns a Texture instance.
     */
    Texture(const char* imageName);
    
    
    /*!
     Read texel color at specific texture coordinate.
          
     @param textureCoordinate The texture coordinate to be read.
     
     @returns a texel from texture as Vector3D.
     */
    Vector3D readTexture(TextureCoordinate textureCoordinate);
};

#endif /* Texture_hpp */
