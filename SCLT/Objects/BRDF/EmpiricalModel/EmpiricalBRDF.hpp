//
//  EmpiricalBRDF.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 05/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef EmpiricalBRDFModel_hpp
#define EmpiricalBRDFModel_hpp

#include "Ray.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Model.hpp"

typedef enum EmpiricalBRDFModel {
    Phong,
    BlinnPhong
} EmpiricalBRDFModel;

class EmpiricalBRDF {
public:
    
    /*!
     Calculate specular factor used during shading calculation.
     
     @param empiricalBRDFModel the empirical BRDF model to be used.
     @param ray The ray used in calculation.
     @param point point of intersection.
     @param lightDirection light direction.
     @param normal normal of the object.
     @parma object object used in calculation.
     
     @returns float representing the specular factor.
     */
    float specularFactor(const EmpiricalBRDFModel empiricalBRDFModel,
                         const Ray& ray,
                         const Point3D& point,
                         const Vector3D& lightDirection,
                         const Vector3D& normal,
                         const Model* object);
    
};

#endif /* EmpiricalBRDFModel_hpp */
