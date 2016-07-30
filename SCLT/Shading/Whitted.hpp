//
//  WhittedRGB.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 11/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Whitted_hpp
#define Whitted_hpp

#include "Intersection.hpp"
#include "ShadingModel.hpp"
#include "EmpiricalBRDF.hpp"
#include "MaterialRGB.hpp"
#include "Fresnel.hpp"
#include "TracerRGB.hpp"

class Whitted : public ShadingRGBModel {
private:
    
    /*!
     Get emissive light for an object.
     
     @param object object used in calculation.
     
     @returns the emissive color as Vector3D.
     */
    static Vector3D emissiveLight(const Model& object);
    
    /*!
     Get ambient light for an object.
     
     @param intersectionPoint intersection point.
     @param object object I use in calculation.
     @param lightColor color of the light.
     
     @returns the ambient color as Vector3D.
     */
    static Vector3D ambientLight(const Point3D& intersectionPoint, const Model& object, const Vector3D& lightColor);
    
    /*!
     Get diffuse light for an object.
     
     @param normal the normal of the object.
     @param intersectionPoint the point of intersection.
     @param lightDirection the light direction.
     @param lightWithSoftShadowAttenuation the light (attenuated with soft shadow percentage).
     @param object the object used in calculation.
     
     @returns diffuse components as RGB Vector3D.
     */
    static Vector3D diffuseLight(const Vector3D& normal,
                                 const Point3D& intersectionPoint,
                                 const Vector3D& lightDirection,
                                 const Vector3D& lightWithSoftShadowAttenuation,
                                 const Model& object);
    
    /*!
     Get diffuse and specular light for an object.
     Specular light component is calculated using Phong or Blinn-Phong.
     
     @param empiricalBRDFModel the empirical BRDF model to be used.
     @param ray The ray used in calculation.
     @param intersectionData data of intersection (object, normal, point...).
     @param light Light object (Standard or AreaLight).
     @param softShadowPercentage the percentage of received light (used with soft shadow).
     
     @results Vector3D that represent specular and diffusive light contribution based on phong lighting model.
     */
    static Vector3D diffuseAndSpecularLight(const EmpiricalBRDFModel empiricalBRDFModel,
                                            const Ray& ray,
                                            const Intersection& intersectionData,
                                            const Light& light,
                                            const float softShadowPercentage);
    
    /*!
     Recursive calculation of reflection and trasmission (refraction).
     
     @param ray The ray used in calculation.
     @param normal  the normal of the object.
     @param closestObject the object used in calculation.
     @param closestIntersectionPoint the point of intersection.
     @param tracer the tracer used.
     @param bounce current bounce.
     
     @returns color obtained from reflection + refraction.
     */
    Vector3D reflectionAndTransmission(const Ray& ray,
                                       const Vector3D& normal,
                                       const Model& closestObject,
                                       const Point3D closestIntersectionPoint,
                                       const TracerRGB& tracer,
                                       const int bounce) const;
    
public:
    
    /*
     Shading operation.
     
     @param intersectionData intersection data.
     @param ray current ray.
     @param bounce current bounce.
     @param tracer current tracer.
     
     @returns RGB colors using Whitted model.
     */
    Vector3D shade(const Intersection& intersectionData,
                   const Ray& ray,
                   const int bounce,
                   const TracerRGB& tracer) const;
};

#endif /* Whitted_hpp */
