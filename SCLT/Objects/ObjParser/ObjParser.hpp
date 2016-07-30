//
//  ObjParser.hpp
//  Spectral Clara Lux Tracer
//
//  Created by Fabrizio Duroni on 08/06/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#ifndef ObjParser_hpp
#define ObjParser_hpp

#include <iostream>
#include <vector>

#include "Polygon.hpp"

class ObjParser {
private:

    /// Vector of vertex indices.
    std::vector<int> verticesIndices;
    /// Vector of normal indices.
    std::vector<int> normalsIndices;
    /// Vector of vertices.
    std::vector<Point3D> vertices;
    /// Vector of normals.
    std::vector<Vector3D> normals;
    /// Vector of polygon shapes created.
    std::vector<Model *> polygonalShapes;
    
public:
    
    /*!
     Get polygonal shapes created.
     
     @returns int that corresponds to the number of vertices to draw.
    */
    std::vector<Model *> getPolygonalShapes();
    
    /*!
     Parse obj file.
     
     @param filePath path of the obj file.
     @param set back face culling for the polygons of a mesh.
     
     @returns true if parsing is fine, else false.
     */
    bool parseObj(const char* filePath, bool backFaceCulling);
};

#endif /* ObjParser_hpp */
