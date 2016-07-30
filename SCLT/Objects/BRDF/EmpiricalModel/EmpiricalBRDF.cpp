//
//  EmpiricalBRDF.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 06/05/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "EmpiricalBRDF.hpp"
#include "MaterialRGB.hpp"

float EmpiricalBRDF::specularFactor(const EmpiricalBRDFModel empiricalBRDFModel,
                                    const Ray& ray,
                                    const Point3D& point,
                                    const Vector3D& lightDirection,
                                    const Vector3D& normal,
                                    const Model* object) {
 
    MaterialRGB* material = static_cast<MaterialRGB *>(object->material);
    
    Vector3D Vn = ray.origin - point;
    Vn.normalize();
    
    if(empiricalBRDFModel == Phong) {
        
        //Phong model.
        Vector3D productNormalLightDirection = normal * (2 * (lightDirection.dot(normal)));
        Vector3D R = productNormalLightDirection - lightDirection;
        R.normalize();
        
        float cosAlpha = powf(std::fmax(0.0f, R.dot(Vn)), material->sh);
        
        return cosAlpha;
    } else {
        
        //Blinn-Phong model.
        Vector3D H = lightDirection + Vn;
        H.normalize();
        
        float cosGamma = powf(std::fmax(0.0f, H.dot(normal)), material->sh);
        
        return cosGamma;
    }
}
