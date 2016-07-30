//
//  Polygon.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 08/08/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Polygon.hpp"

PolygonalShape::PolygonalShape(const std::vector<Point3D> aVertexList,
                               const Point3D& aPointOnPlane,
                               bool backFaceCullingActive) {
    
    //Setup point on plane.
    pointOnPlane = aPointOnPlane;
    
    //Setup vertex list.
    vertexList = aVertexList;
    
    //Set back face culling flag.
    backfaceCulling = backFaceCullingActive;
    
    //Setup normal.
    Point3D v1 = vertexList[0];
    Point3D v2 = vertexList[1];
    Point3D v3 = vertexList[2];
    
    //Original normal (not normalized).
    originalNormal = (v1 - v2).cross(v1 - v3);
    
    //Normal already normalized.
    normal = (v1 - v2).cross(v1 - v3);
    normal.normalize();

    for(std::vector<Point3D>::size_type i = 0; i != vertexList.size(); i++) {

        Point3D nextVertex = vertexList[(i + 1) % vertexList.size()];
        Point3D currentVertex = vertexList[i];
        
        Vector3D edge = nextVertex - currentVertex;
        edgeList.push_back(edge);
    }
}

float PolygonalShape::intersectWithPlaneOfPolygon(const Ray& ray) {
    
    //Calculate denominator.
    float denominator = ray.direction.dot(normal);
    
    //Ray perpendicular to plane normal, so no intersection.
    //If activated, check also for back face culling.
    if(denominator == 0.0f || (backfaceCulling && denominator > 0.0f)) {
    
        return -1.0f;
    }
    
    //Calculate numerator.
    float numerator = -1.0f * (ray.origin - pointOnPlane).dot(normal);
    
    float t = numerator/denominator;
    
    //No intersection.
    if (t <= 0.0f) {
    
        return -1.0f;
    }
    
    return t;
}

Intersection* PolygonalShape::intersect(const Ray& ray) {
    
    //Check intersection of ray with polygon ray.
    float t = intersectWithPlaneOfPolygon(ray);
    
    if(t == -1.0f) {
    
        return nullptr;
    }
    
    Vector3D prodvs = ray.direction * t;
    Point3D intersectionPoint = ray.origin + prodvs;
    
    //Check that the intersection point is inside the polygon.
    for(std::vector<Point3D>::size_type i = 0; i != vertexList.size(); i++) {

        Vector3D crossProduct = edgeList[i].cross(intersectionPoint - vertexList[i]);
        float dotProduct = crossProduct.dot(normal);
        
        if (dotProduct < 0) {
            
            //Point is outside polygon.
            return nullptr;
        }
    }

    Intersection* result = new Intersection(intersectionPoint, t, normal, originalNormal, this);
    
    return result;
}

TextureCoordinate PolygonalShape::textureCoordinate(const Point3D& intersectionPoint) const {
    
    /* To be implemented in subclasses */
    TextureCoordinate tc;
    tc.u = 0.0f;
    tc.v = 0.0f;
    
    return tc;
}
