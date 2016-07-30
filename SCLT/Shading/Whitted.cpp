//
//  WhittedRGB.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 11/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Whitted.hpp"

Vector3D Whitted::shade(const Intersection& intersectionData,
                        const Ray& ray,
                        const int bounce,
                        const TracerRGB& rayTracer) const {
    
    //Init color.
    Vector3D color(0.0f, 0.0f, 0.0f);
    
    //Shadow.
    float shadowPercentage = rayTracer.shadowCalculator->visiblePercentage(intersectionData.point);
    
    //Add ambient and emissive components.
    color = color + emissiveLight(*intersectionData.object);
    color = color + ambientLight(intersectionData.point, *intersectionData.object, rayTracer.scene->light->color);
    color = color + diffuseAndSpecularLight(Phong, ray, intersectionData, *rayTracer.scene->light, shadowPercentage);
    
    //Limit bounce ray.
    if(bounce == 0.0f) {
        
        return color;
    }

    color = color + reflectionAndTransmission(ray,
                                              intersectionData.normal,
                                              *intersectionData.object,
                                              intersectionData.point,
                                              rayTracer,
                                              bounce);
    
    return color;
}

Vector3D Whitted::emissiveLight(const Model& object) {
    
    //Emission is max light * ke. Pure additive component.
    MaterialRGB* material = static_cast<MaterialRGB *>(object.material);
    
    Vector3D maxLight(255.0, 255.0, 255.0);
    Vector3D emission = maxLight.pprod(material->ke);
    
    return emission;
}

Vector3D Whitted::ambientLight(const Point3D &intersectionPoint,
                               const Model& object,
                               const Vector3D &lightColor) {
    
    MaterialRGB* material = static_cast<MaterialRGB *>(object.material);
    
    //Normalize factor.
    float colorNorm = 1.0f/255.0f;
    
    Vector3D ambientLight = material->ka.pprod(lightColor);
    
    //Apply perlin texture if there's one.
    if(object.material->perlinTexture != nullptr) {
        
        ambientLight = material->perlinTexture->readTexture(intersectionPoint).pprod(ambientLight) * colorNorm;
    }
    
    //Apply standard (color map) texture if there's one.
    if(object.material->texture != nullptr) {
        
        TextureCoordinate textureCoordinate = object.textureCoordinate(intersectionPoint);
        ambientLight = material->texture->readTexture(textureCoordinate).pprod(ambientLight) * colorNorm;
    }
        
    return ambientLight;
}

Vector3D Whitted::diffuseLight(const Vector3D& normal,
                               const Point3D& intersectionPoint,
                               const Vector3D& lightDirection,
                               const Vector3D& lightWithSoftShadowAttenuation,
                               const Model& object) {
    
    MaterialRGB* material = static_cast<MaterialRGB *>(object.material);
    
    //Normalize factor.
    float colorNorm = 1.0f/255.0f;
    
    //Calculate diffuse weight.
    float cosTetha = std::fmax(0.0f, normal.dot(lightDirection));
    
    Vector3D diffuseLight = (material->kd * cosTetha).pprod(lightWithSoftShadowAttenuation);
    
    //Apply perlin texture if there's one.
    if (object.material->perlinTexture != nullptr) {
        
        diffuseLight = object.material->perlinTexture->readTexture(intersectionPoint).pprod(diffuseLight) * colorNorm;
    }
    
    //Apply standard (color map) texture if there's one.
    if(object.material->texture != nullptr) {
        
        TextureCoordinate textureCoordinate = object.textureCoordinate(intersectionPoint);
        diffuseLight = material->texture->readTexture(textureCoordinate).pprod(diffuseLight) * colorNorm;
    }
    
    //Standard case. No procedural texture. Read material parameter.
    return diffuseLight;
}

Vector3D Whitted::diffuseAndSpecularLight(const EmpiricalBRDFModel empiricalBRDFModel,
                                          const Ray& ray,
                                          const Intersection& intersectionData,
                                          const Light& light,
                                          const float softShadowPercentage) {
    
    Model* object = intersectionData.object;
    Vector3D normal = intersectionData.normal;
    Point3D point = intersectionData.point;
    MaterialRGB* material = static_cast<MaterialRGB *>(object->material);
    
    //If the material has bump mapping
    //apply distorsion to the normal.
    if (object->material->bumpMap != nullptr) {
        
        //Get bumped normal.
        //The bump map must be applied on the ORIGINAL normal.
        //This is way I need to normalized it, after bump mapping.
        normal = object->material->bumpMap->bumpMapTexture(point, intersectionData.originalNormal);
        normal.normalize();
    }
    
    //Apply soft shadow to light intensity.
    Vector3D lightWithSoftShadowAttenuation = light.color * softShadowPercentage;
    
    //Calculate light direction.
    Vector3D lightDirection = light.origin - point;
    lightDirection.normalize();
    
    //Diffuse.
    Vector3D diffuse = diffuseLight(normal, point, lightDirection, lightWithSoftShadowAttenuation, *object);
    
    //Specular.
    EmpiricalBRDF empBRDF;
    float specularFactor = empBRDF.specularFactor(empiricalBRDFModel, ray, point, lightDirection, normal, object);
    Vector3D specular = lightWithSoftShadowAttenuation.pprod(material->ks * specularFactor);
    
    //Light attenuation.
    float d = (light.origin - point).magnitude();
    float lightAttenuation = std::fmin(1.0f/(constant::c1 + constant::c2 * d + constant::c3 * powf(d, 2.0f)), 1.0f);
    
    //Sum diffuse and specular.
    Vector3D diffuseAndSpecular = (diffuse + specular) * lightAttenuation;
    
    return diffuseAndSpecular;
}


Vector3D Whitted::reflectionAndTransmission(const Ray& ray,
                                            const Vector3D& normal,
                                            const Model& closestObject,
                                            const Point3D closestIntersectionPoint,
                                            const TracerRGB& tracer,
                                            const int bounce) const {
    
    MaterialRGB* material = static_cast<MaterialRGB *>(closestObject.material);
    
    //If the material is a pure reflective
    //or pure transmissive the percentage of
    //reflected or refracted ray is 1, and obviously
    //ONLY ONE TYPE OF RAY WILL BE TRACED.
    float fresnelReflected = 1.0f;
    float fresnelRefracted = 1.0f;
    
    //Calculate cosI between ray and normal.
    float cosI = ray.direction.dot(normal);
    
    //Calculate fresnel for reflective and transmissive material.
    if(material->isTransmissive == true && material->isReflective == true) {
        
        Fresnel fresnel(material->refractiveIndex);
        fresnelReflected = fresnel.dieletricReflectivePercentage(cosI);
        fresnelRefracted = 1.0f - fresnelReflected;
    }
    
    Vector3D reflectiveColor(0.0f, 0.0f, 0.0f);
    Vector3D refractiveColor(0.0f, 0.0f, 0.0f);
    
    //Reflection.
    if (material->isReflective == true) {
        
        //If object is reflective ray trace the reflective ray.
        Vector3D reflectedRayDirection = Ray::reflectedRayDirection(normal,
                                                                    ray.direction,
                                                                    cosI);
        
        //Setup reflection ray.
        Ray reflectionRay(MathUtils::addEpsilon(closestIntersectionPoint, reflectedRayDirection),
                          reflectedRayDirection);
        
        //Trace reflected ray
        reflectiveColor = tracer.trace(reflectionRay, bounce - 1) * fresnelReflected;
    }
    
    //Refraction.
    if(material->isTransmissive == true) {
        
        //If the object is transmissive ray trace the refracted ray, if it exists.
        float n = 0.0f;
        Vector3D* refractedRayDirection = Ray::refractedRayDirection(normal,
                                                                     ray.direction,
                                                                     material->refractiveIndex,
                                                                     cosI,
                                                                     n);
        
        if(refractedRayDirection != nullptr) {
            
            Ray refractedRay(MathUtils::addEpsilon(closestIntersectionPoint, *refractedRayDirection),
                             *refractedRayDirection);
            
            refractiveColor = tracer.trace(refractedRay, bounce - 1) * fresnelRefracted;
            
            delete refractedRayDirection;
        }
    }
    
    //Sum shading + reflective + refractive.
    Vector3D color = reflectiveColor + refractiveColor;
    
    return color;
}
