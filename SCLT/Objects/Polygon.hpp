//
//  Polygon.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 08/08/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Polygon_hpp
#define Polygon_hpp

#include <vector>

#include "Model.hpp"
#include "Ray.hpp"
#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "Material.hpp"

class PolygonalShape : public Model {
protected:
    
    /// Origin of the plane as a Point3D. It could be a vertex of the polygon.
    Point3D pointOnPlane;
    /// Plane normal.
    Vector3D normal;
    /// Plane original normal.
    Vector3D originalNormal;
    /// Vertex list of the polygon.
    std::vector<Point3D> vertexList;
    /// Edge list. I calculate them on init. Used only for intersection test.
    std::vector<Vector3D> edgeList;
    /// Backface culling. Activate in main list.
    bool backfaceCulling;
    
    /*!
     Check the intersection of ray with the plane
     of the polygon.
     
     @param ray ray to be tested.
    
     @returns t if intersect or -1
     */
    float intersectWithPlaneOfPolygon(const Ray& ray);
    
public:
    
    /*!
     Constructor.
     
     @param aVertexList a list of vertex of the polygon.
     @param aPointOnPlane point on plane of polygon.
     @param backFaceCullingActive bool used to check if back face culling is activated.
    
     @returns a PolygonShape instance.
     */
    PolygonalShape(const std::vector<Point3D> aVertexList,
                   const Point3D& aPointOnPlane,
                   bool backFaceCullingActive = false);
    
    /*!
     Calculate the intersection of the polygon with a ray.
    
     @param ray the ray used to calculate the intersection.
    
     @returns a dictionary that contains t, intersection point, normal and the polygon itself.
     */
     Intersection* intersect(const Ray& ray);
    
    /*!
     Calculate texture coordinate.
     
     @param intersectionPoint point of intersection.
     
     @returns texture coordinate.
     */
    TextureCoordinate textureCoordinate(const Point3D& intersectionPoint) const;
};

#endif /* Polygon_h */
