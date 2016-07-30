//
//  Square.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 31/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Constants.hpp"
#include "Square.hpp"

Square::Square(const std::vector<Point3D> vertexList,
               const Point3D& pointOnPlane,
               const std::string sceneSkyboxSideName) : PolygonalShape(vertexList,
                                                                       pointOnPlane) {
    
    skyboxSideName = sceneSkyboxSideName;
}

TextureCoordinate Square::textureCoordinate(const Point3D& intersectionPoint) const {
    
    if(!skyboxSideName.empty()) {
        
        //Special cas: square used as skybox side.
        return textureCoordinateForSkybox(intersectionPoint);
    }
    
    //Not implemented at the moment.
    TextureCoordinate coordinate;
	coordinate.u = 0.0f;
	coordinate.v = 0.0f;

    return coordinate;
}

TextureCoordinate Square::textureCoordinateForSkybox(const Point3D& intersectionPoint) const {
    
    //Magnitude of one edge is the misure of a side of the square.
    Vector3D edge = edgeList[0];
    float squareSideMisure = edge.magnitude();
    
    TextureCoordinate coordinate;
	coordinate.u = 0.0f;
	coordinate.v = 0.0f;
    
    if(skyboxSideName.compare("bottom") == 0) {
        
        //Bottom
        coordinate.u = intersectionPoint.x/squareSideMisure;
        coordinate.v = 1.0f - intersectionPoint.z/squareSideMisure;
        return coordinate;
    }
    
    if(skyboxSideName.compare("front") == 0) {
        
        //Front
        coordinate.u = intersectionPoint.x/squareSideMisure;
        coordinate.v = intersectionPoint.y/squareSideMisure;
        return coordinate;
    }
    
    if(skyboxSideName.compare("left") == 0) {
        
        //Left
        coordinate.u = 1.0f - intersectionPoint.z/squareSideMisure;
        coordinate.v = intersectionPoint.y/squareSideMisure;
        return coordinate;
    }
    
    if(skyboxSideName.compare("top") == 0) {
        
        //Top
        coordinate.u = intersectionPoint.x/squareSideMisure;
        coordinate.v = 1.0f - intersectionPoint.z/squareSideMisure;
        return coordinate;
    }
    
    if(skyboxSideName.compare("right") == 0) {
        
        //Right
        coordinate.u = 1.0f - intersectionPoint.z/squareSideMisure; 
        coordinate.v = intersectionPoint.y/squareSideMisure;
        return coordinate;
    }
    
    if (skyboxSideName.compare("back") == 0) {
        
        //Back
        coordinate.u = intersectionPoint.x/squareSideMisure;
        coordinate.v = 1.0f - intersectionPoint.y/squareSideMisure;
        return coordinate;
    }
    
    return coordinate;
}
