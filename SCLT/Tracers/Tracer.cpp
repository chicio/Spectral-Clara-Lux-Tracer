//
//  Tracer.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 19/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "AreaLight.hpp"
#include "AxisAlignedBoundingBox.hpp"
#include "Tracer.hpp"

Tracer::Tracer(Scene* sceneToBeRendered) {
    
    scene = sceneToBeRendered;
    shadowCalculator = new ShadowCalculator(*this);
};

Intersection* Tracer::closestIntersection(const Ray& ray) const {
    
    //Start intersection test from the scene object list.
    //Some objects are composed with other ones (for example polygonal mesh).
    //They would test the intersection of their subcomponent and return the closest intersection if there's one.
    Intersection *closestIntersectionData = Tracer::closestIntersectionFromObjectList(ray, scene->objects);
    
    return closestIntersectionData;
}

Tracer::~Tracer() {
    
    delete shadowCalculator;
}
