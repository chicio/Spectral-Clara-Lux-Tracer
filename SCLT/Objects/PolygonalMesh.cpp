//
//  PolygonalMesh.cpp
//  SCLTFramework
//
//  Created by Fabrizio Duroni on 16/06/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Tracer.hpp"
#include "PolygonalMesh.hpp"

Intersection* PolygonalMesh::intersect(const Ray& ray) {
    
    bool aabbIntersected = bbox.intersect(ray);
    
    //AABB not intersected, so there's no need to test the polygons of the mesh.
    if(!aabbIntersected) {
        
        return nullptr;
    }
    
    //Get the polygon the ray intersect with (if there's one.)
    Intersection* result = Tracer::closestIntersectionFromObjectList(ray, meshPolygons);
    
    return result;
}

TextureCoordinate PolygonalMesh::textureCoordinate(const Point3D& intersectionPoint) const {
    
    /* To be implemented in subclasses */
    TextureCoordinate tc;
    tc.u = 0.0f;
    tc.v = 0.0f;
    
    return tc;
}

PolygonalMesh::~PolygonalMesh() {

    //Clean polygons of the mesh.
    for(auto &object:meshPolygons) {
        
        delete object;
    }
    
    meshPolygons.clear();
}
