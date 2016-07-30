//
//  Tracer.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 18/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Tracer_hpp
#define Tracer_hpp

#include <vector>

#include "Intersection.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include "Scene.hpp"
#include "ShadingModel.hpp"
#include "ShadowCalculator.hpp"
#include "Spectrum.hpp"

class Tracer {
public:
    
    /// Scene to be rendered.
    Scene* scene;
    /// Shadow calculator.
    ShadowCalculator* shadowCalculator;

    /*!
     Constructor.
     
     @param scene Scene to be rendered.		
     */
    Tracer(Scene* scene);
    
    /*!
     Get color given for the current pixel or subpixel (if using antialiasing).
     
     @param ray the current ray.
     
     @returns color as Vector3D.
     */
    virtual Vector3D getColor(const Ray& ray, const int bounce) const = 0;

    /*!
     Calculate the closest intersection of a ray with the current scene objects.
     
     @param ray ray to be tested for intersection.
     
     @returns Intersection data or null.
     */
    Intersection* closestIntersection(const Ray& ray) const;
    
    /*!
     Calculate the closest intersection of a ray with the current scene objects.
     
     @param ray ray to be tested for intersection.
     @param object object list to be tested.
     
     @returns Intersection data or null.
     */
    inline static Intersection* closestIntersectionFromObjectList(const Ray& ray, std::vector<Model *> objects) {
        
        float t = -1;

        Intersection *closestIntersectionData = nullptr;
        
        for(Model* object: objects) {
            
            //If there's an intersection.
            Intersection* intersectionData = object->intersect(ray);
            
            if(intersectionData != nullptr) {
                
                float intersectionT = intersectionData->t;
                
                //If intersectionT < t the intersection is near then the previous one.
                //(t == -1 means that this is the first intersection).
                if(t == -1 || intersectionT < t) {
                    
                    t = intersectionT;
                    
                    //Free memory of old intersection data.
                    delete closestIntersectionData;
                    
                    //Get pointer to new closest intersection.
                    closestIntersectionData = intersectionData;
                } else {
                    
                    //Clear intersection data.
                    delete intersectionData;
                }
            }
        }
        
        return closestIntersectionData;
    }
    
    /*!
     Descrutor.
     */
    virtual ~Tracer();
};

#endif /* Tracer_hpp */
