//
//  Material.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 05/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "MaterialRGB.hpp"

Material* MaterialRGB::glass() {
    
    MaterialRGB *material = new MaterialRGB();
    
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.0f, 0.0f, 0.0f);
    material->kd = Vector3D(0.588235f, 0.670588f, 0.729412f);
    material->ks = Vector3D(0.9f, 0.9f, 0.9f);
    material->sh = 96.0f;
    //Refractive index CROWN glass.
    material->refractiveIndex = 1.50;
    
    material->isTransmissive = true;
    material->isReflective = true;
    
    return material;
}

Material* MaterialRGB::glasswater() {
    
    MaterialRGB* material = new MaterialRGB();
    
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.0f, 0.0f, 0.0f);
    material->kd = Vector3D(0.588235f, 0.670588f, 0.729412f);
    material->ks = Vector3D(0.9f, 0.9f, 0.9f);
    material->sh = 96.0f;
    //Refractive index water (ice).
    material->refractiveIndex = 1.31f;
    
    material->isTransmissive = true;
    material->isReflective = true;
    
    return material;
}

Material* MaterialRGB::jade() {
    
    MaterialRGB* material = new MaterialRGB();
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.135f, 0.2225f, 0.1575f);
    material->kd = Vector3D(0.54f, 0.89f, 0.63f);
    material->ks = Vector3D(0.316228f, 0.316228f, 0.316228f);
    material->sh = 99.0f;
    material->isTransmissive = false;
    material->isReflective = false;
    
    return material;
}

Material* MaterialRGB::violet() {
    
    MaterialRGB* material = new MaterialRGB();
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.0f, 0.0f, 0.0f);
    material->kd = Vector3D(0.635294f, 0.0f, 1.0f);
    material->ks = Vector3D(0.0225f, 0.0225f, 0.0225f);
    material->sh = 76.8f;
    material->isTransmissive = false;
    material->isReflective = false;
    
    return material;
}

Material* MaterialRGB::matte() {
    
    MaterialRGB* material = new MaterialRGB();
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.2f, 0.2f, 0.2f);
    material->kd = Vector3D(0.9f, 0.9f, 0.9f);
    material->ks = Vector3D(0.0f, 0.0f, 0.0f);
    material->sh = 0.0f;
    material->isTransmissive = false;
    material->isReflective = false;
    
    return material;
}

Material* MaterialRGB::matte(const char* textureName) {
    
    MaterialRGB* material = new MaterialRGB();
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.2f, 0.2f, 0.2f);
    material->kd = Vector3D(0.9f, 0.9f, 0.9f);
    material->ks = Vector3D(0.0f, 0.0f, 0.0f);
    material->sh = 0.0f;
    material->isTransmissive = false;
    material->isReflective = false;
    material->texture = new Texture(textureName);
    
    return material;
}

Material* MaterialRGB::red() {
    
    MaterialRGB* material = new MaterialRGB();
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.0f, 0.0f, 0.0f);
    material->kd = Vector3D(1.0f, 0.0f, 0.0f);
    material->ks = Vector3D(0.0225f, 0.0225f, 0.0225f);
    material->sh = 0.0;
    material->isTransmissive = false;
    material->isReflective = false;
    
    return material;
}

Material* MaterialRGB::green() {
    
    MaterialRGB* material = new MaterialRGB();
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.0f, 0.0f, 0.0f);
    material->kd = Vector3D(0.0f, 1.0f, 0.0f);
    material->ks = Vector3D(0.0225f, 0.0225f, 0.0225f);
    material->sh = 12.8f;
    material->isTransmissive = false;
    material->isReflective = false;
    
    return material;
}
Material* MaterialRGB::mediumGray() {
    
    MaterialRGB* material = new MaterialRGB();
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.0f, 0.0f, 0.0f);
    material->kd = Vector3D(0.454902f, 0.454902f, 0.454902f);
    material->ks = Vector3D(0.0225f, 0.0225f, 0.0225f);
    material->sh = 12.8f;
    material->isTransmissive = false;
    material->isReflective = false;
    
    return material;
}
Material* MaterialRGB::lightGray() {
    
    MaterialRGB* material = new MaterialRGB();
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.0f, 0.0f, 0.0f);
    material->kd = Vector3D(0.682353f, 0.682353f, 0.682353f);
    material->ks = Vector3D(0.0225f, 0.0225f, 0.0225f);
    material->sh = 12.8f;
    material->isTransmissive = false;
    material->isReflective = false;
    
    return material;
}

Material* MaterialRGB::bronze() {
    
    MaterialRGB* material = new MaterialRGB();
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.2125f, 0.1275f, 0.054f);
    material->kd = Vector3D(0.714f, 0.4284f, 0.18144f);
    material->ks = Vector3D(0.393548f, 0.271906f, 0.166721f);
    material->sh = 25.6f;
    material->isTransmissive = false;
    material->isReflective = true;
    
    return material;
}

Material* MaterialRGB::chrome() {
    
    MaterialRGB* material = new MaterialRGB();
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.25f, 0.25f, 0.25f);
    material->kd = Vector3D(0.4f, 0.4f, 0.4f);
    material->ks = Vector3D(0.774597f, 0.774597f, 0.774597f);
    material->sh = 76.8f;
    material->isTransmissive = false;
    material->isReflective = true;
    
    return material;
}

Material* MaterialRGB::silver() {
    
    MaterialRGB* material = new MaterialRGB();
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.19225f, 0.19225f, 0.19225f);
    material->kd = Vector3D(0.50754f, 0.50754f, 0.50754f);
    material->ks = Vector3D(0.508273f, 0.508273f, 0.508273f);
    material->sh = 51.2f;
    material->isTransmissive = false;
    material->isReflective = true;
    
    return material;
}

Material* MaterialRGB::rubyBumpMapped(float scale) {
    
    MaterialRGB* material = new MaterialRGB();
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.1745f, 0.01175f, 0.01175f);
    material->kd = Vector3D(0.61424f, 0.04136f, 0.04136f);
    material->ks = Vector3D(0.727811f, 0.626959f, 0.626959f);
    material->sh = 76.8f;
    material->isTransmissive = false;
    material->isReflective = false;
    material->bumpMap = new BumpMap(scale);
    
    return material;
}

Material* MaterialRGB::flameMarble() {
    
    MaterialRGB* material = new MaterialRGB();
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.3f, 0.2f, 0.2f);
    material->kd = Vector3D(0.9f, 0.9f, 0.9f);
    material->ks = Vector3D(0.727811f, 0.626959f, 0.626959f);
    material->sh = 76.8f;
    material->isTransmissive = false;
    material->isReflective = false;
    material->perlinTexture = new MarbleTexture(Vector3D(162.0f, 5.0f, 1.0f), Vector3D(254.0f, 190.0f, 3.0f));
    
    return material;
}

Material* MaterialRGB::blueTurbulence() {
    
    MaterialRGB* material = new MaterialRGB();
    material->ke = Vector3D(0.0f, 0.0f, 0.0f);
    material->ka = Vector3D(0.3f, 0.2f, 0.2f);
    material->kd = Vector3D(0.9f, 0.9f, 0.9f);
    material->ks = Vector3D(0.727811f, 0.626959f, 0.626959f);
    material->sh = 50.0f;
    material->isTransmissive = false;
    material->isReflective = false;
    material->perlinTexture = new TurbulenceTexture(Vector3D(255.0f, 255.0f, 255.0f), Vector3D(0.0f, 0.0f, 200.0f));
    
    return material;
}
