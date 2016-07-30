//
//  Texture.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 26/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"

#include <iostream>

#include "PathReader.hpp"
#include "Texture.hpp"
#include "lodepng.h"

Texture::Texture(const char* imageName) {
    
    std::string path = PathReader::getPath("Textures", imageName, "png");
    
    std::vector<unsigned char> png;
    unsigned error = lodepng::load_file(png, path);
    
    if(!error) {

        error = lodepng::decode(image, width, height, png);
    }

    if(error) {

        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }
}

Vector3D Texture::getTexel(int xp, int yp) {
    
    //Access directly to the pixels of the image from the array precalculated.
    int index = ((height - 1) - yp) * (width * 4) + xp * 4;
    Vector3D texel(image[index], image[index + 1], image[index + 2], image[index + 3]);
    
    return texel;
}

Vector3D Texture::readTexture(TextureCoordinate textureCoordinate) {
    
    //Ray tracing from the ground up pag. 650.
    int x = (int)floor((width - 1) * textureCoordinate.u);
    int y = (int)floor((height - 1) * textureCoordinate.v);
    
    Vector3D color = getTexel(x, y);
    
    return color;
}
