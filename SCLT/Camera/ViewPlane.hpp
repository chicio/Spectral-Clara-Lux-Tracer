//
//  ViewPlane.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 30/10/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef ViewPlane_hpp
#define ViewPlane_hpp

class ViewPlane {
public:
    
    /// Width of the view plane.
    int width;
    /// Height of the view plane.
    int height;
    /// Area of the view plane.
    int area;

    /*!
     Default constructor.
     ViewPlane default dimension 500 * 500.
     
     @returns a Point3D.
     */
    ViewPlane() : width{500}, height{500}, area{500 * 500} {}
    
    /*!
     Constructor.
     
     @attention Semplification: viewplane and viewport are the same (position and dimension).
     
     @param width the width of the view plane.
     @param height the height of the view plane.
     
     @returns a View Plane instance.
     */
    ViewPlane(int width, int height) : width{width}, height{height}, area{width * height} {};
};

#endif /* ViewPlane_hpp */
