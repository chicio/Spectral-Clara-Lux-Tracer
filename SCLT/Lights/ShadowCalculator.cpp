//
//  ShadowCalculator.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 14/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "ShadowCalculator.hpp"
#include "ShadowRay.hpp"
#include "Tracer.hpp"

float ShadowCalculator::visiblePercentage(const Point3D& pointToBeChecked) {
    
    //SHADOW.
    float shadowPercentage = 0.0f;
    
    AreaLight* light = dynamic_cast<AreaLight* >(tracer.scene->light);
    
    if(light != nullptr) {
        
        //Area light: soft shadow.
        shadowPercentage = softShadow(light, pointToBeChecked);
    } else {
        
        //Point light: standard shadow.
        bool isInShadow = inShadow(pointToBeChecked, tracer.scene->light->origin);
        
        if(!isInShadow) {
            
            shadowPercentage = 1.0f;
        }
    }
    
    return shadowPercentage;
}

float ShadowCalculator::softShadow(const AreaLight* light, const Point3D& pointToBeTested) const {

    float intersectionsWithLight = 0;

    //I test if the point of intersection is visible with n shadow ray generated from random points on an area light.
    for(std::vector<Point3D>::size_type i = 0; i != light->randomSpherePoints.size(); i++) {

        bool isInShadow = inShadow(pointToBeTested, light->randomSpherePoints[i]);

        if(isInShadow == false) {

            intersectionsWithLight++;
        }
    }

    //Last point is in shadow.
    return intersectionsWithLight/constant::numberOfShadowRay;
}

bool ShadowCalculator::inShadow(const Point3D& pointToBeTested, const Point3D& lightPoint) const {

    //Shadow ray calculation.
    ShadowRay shadowRay(pointToBeTested, lightPoint);

    //Calculate intersection
    Intersection *intersectionData = tracer.closestIntersection(*shadowRay.ray);

    //No intersection or intersection with light object.
    if(intersectionData == nullptr || intersectionData->object->isLight == true) {

        return false;
    }

    //Extract t (intersection distance) and d (distance from light).
    float t = intersectionData->t;
    float d = shadowRay.d;

    //Clear pointer.
    delete intersectionData;

    //If the intersection distance is greater than the distance between intersectionPoint and light then the point
    //is NOT in shadow.
    if(t > d) {

        return false;
    }

    //Ok, the point is in shadow.
    return true;
}
