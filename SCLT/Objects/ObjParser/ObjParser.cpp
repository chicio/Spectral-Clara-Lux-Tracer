//
//  ObjParser.cpp
//  Spectral Clara Lux Tracer
//
//  Created by Fabrizio Duroni on 08/06/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include <cstring>
#include "ObjParser.hpp"

std::vector<Model *> ObjParser::getPolygonalShapes() {
    
    return polygonalShapes;
}

bool ObjParser::parseObj(const char* filePath, bool backFaceCulling) {
    
    FILE* file = fopen(filePath, "r");
    
    if(file == nullptr) {
        
        return false;
    }
    
    while(1) {
        
        char lineHeader[128];
        
        //Read the first word of the line.
        int res = fscanf(file, "%s", lineHeader);
        
        if(res == EOF) {
            
            //End of file, exit parser.
            break;
        }
        
        if (strcmp(lineHeader, "v") == 0) {
            
            Point3D vertex;
            int matches = fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            
            if(matches != 3) {
                
                return false;
            }
            
            vertices.push_back(vertex);
        }else if(strcmp(lineHeader, "vn") == 0) {
            
            Vector3D normal;
            int matches = fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            
            if(matches != 3) {
                
                return false;
            }
            
            normals.push_back(normal);
        }else if(strcmp(lineHeader, "f") == 0) {
            
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], normalIndex[3];
            int matches = fscanf(file,
                                 "%d//%d %d//%d %d//%d\n",
                                 &vertexIndex[0],
                                 &normalIndex[0],
                                 &vertexIndex[1],
                                 &normalIndex[1],
                                 &vertexIndex[2],
                                 &normalIndex[2]);
            
            if (matches != 6){
                
                return false;
            }
            
            //Indices array.
            verticesIndices.push_back(vertexIndex[0]);
            verticesIndices.push_back(vertexIndex[1]);
            verticesIndices.push_back(vertexIndex[2]);
            normalsIndices.push_back(normalIndex[0]);
            normalsIndices.push_back(normalIndex[1]);
            normalsIndices.push_back(normalIndex[2]);
            
            //Vertex list for a polygonal shape.
            std::vector<Point3D> polygonVertexList;
            
            for (int i = 0 ; i < 3; i++) {
                
                Point3D vertex = vertices[vertexIndex[i] - 1];
                polygonVertexList.push_back(vertex);
            }
            
            Model* polygonalShape = new PolygonalShape(polygonVertexList, polygonVertexList[0], backFaceCulling);
            polygonalShapes.push_back(polygonalShape);
        }
    }
    
    return true;
}
