//
//  PolygonalMesh.hpp
//  SCLTFramework
//
//  Created by Fabrizio Duroni on 16/06/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#ifndef PolygonalMesh_hpp
#define PolygonalMesh_hpp

#include <vector>

#include "Model.hpp"
#include "AxisAlignedBoundingBox.hpp"
#include "Polygon.hpp"

class PolygonalMesh: public Model {
private:
    
    /// Polygon of the mesh.
    std::vector<Model *> meshPolygons;
    /// AABB that surrond the polygon mesh.
    AxisAlignedBoundingBox bbox;
    
public:
    
    /*!
     Constructor.
     
     @param polygonsList list of polygons of the mesh.
     @param axis aligned bounding box of the mesh.
     */
    PolygonalMesh(const std::vector<Model *>& polygonsList,
                  const AxisAlignedBoundingBox& aabb) : meshPolygons(polygonsList), bbox(aabb) {};
    
    /*!
     Calculate the intersection of the polygonal mesh with a ray.
     
     @param ray the ray used to calculate the intersection.
     
     @returns a dictionary that contains t, intersection point, normal and the polygon of the polygonal mesh intersected.
     */
    Intersection* intersect(const Ray& ray);
    
    /*!
     Calculate texture coordinate.
     
     @param intersectionPoint point of intersection.
     
     @returns texture coordinate.
     */
    TextureCoordinate textureCoordinate(const Point3D& intersectionPoint) const;
    
    /*!
     Destructor.
     */
    ~PolygonalMesh();
};

#endif /* PolygonalMesh_hpp */
