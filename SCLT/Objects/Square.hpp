//
//  Square.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 31/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Square_hpp
#define Square_hpp

#include "Polygon.hpp"

class Square : public PolygonalShape {
private:
    
    /*!
     Fast texture mapping if the square is used as skybox side.
     
     @param intersectionPoint point of intersection.
     
     @returns texture coordinate.
     */
    TextureCoordinate textureCoordinateForSkybox(const Point3D& intersectionPoint) const;
    
public:

    /// If setted, we use the square as a side of a polygon square skybox (fast texture mapping technique).
    std::string skyboxSideName;
    
    /*!
     Constructor.
     
     @param vertexList vector of vertex.
     @param pointOnPlane point on plane of square.
     @param sceneSkyboxSideName skybox side name (if needed).
     */
    Square(const std::vector<Point3D> vertexList, const Point3D& pointOnPlane, const std::string sceneSkyboxSideName);
    
    /*!
     Calculate texture coordinate for a square.
     NAIVE calculation WITHOUT interpolation or other standard method.
     Works well ONLY with axis aligned polygon. 
     
     @param intersectionPoint pooint of intersection.
     
     @returns texture coordinate.
     */
    TextureCoordinate textureCoordinate(const Point3D& intersectionPoint) const;
};

#endif /* Square_hpp */
