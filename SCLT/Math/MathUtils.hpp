//
//  UtilsRayTracer.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 10/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include "Constants.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Matrix.hpp"

class MathUtils {
public:
    
    /*!
     Add a small quantity to the origins of ray.
     In this way I avoid self intersection with the object itself during intersection test.
     
     @param point point to be shifted.
     @param direction the direction along which Ishift the point (direction of the ray).
     
     @returns the point shifted.
     */
    inline static Point3D addEpsilon(const Point3D& point, const Vector3D& direction) {
        
        Vector3D distanceToAvoidSelfIntersection = direction * constant::epsilon;
        distanceToAvoidSelfIntersection.normalize();
        
        Point3D pointWithDistance = point + distanceToAvoidSelfIntersection;
        
        return pointWithDistance;
    }
    
    /*!
     Clamp a value to a specific range.
     
     @param value the value to be clamped.
     @param low low range limit.
     @param high high range limit.
     
     @returns the value clamped in the specified range.
     */
    template <typename T> static T clamp(const T& value, const T& low, const T& high) {
        
        return value < low ? low : (value > high ? high : value);
    }
    
    /*!
     Convert degree to radian.
     
     @param degree
     
     @returns radians value.
     */
    inline static float degreeToRadian(float degree) {
        
        float radian = (constant::pi / 180.0f) * degree;
        
        return radian;
    }
    
    /*!
     Generate a coorinate system from a vector.
     This method is useful for generate a tangent space coordinate system for isotropic BRDFs.
     
     @param vector1 vector from which the coordinate system is constructed. This must be normalized.
     @param vector2 second axis obtained.
     @param vector3 third axis obtained.
     */
    inline static void generateCoodinateSystem(const Vector3D& vector1, Vector3D& vector2, Vector3D& vector3) {

        if (std::fabs(vector1.x) > std::fabs(vector1.y)) {
            
            vector2 = Vector3D(vector1.z, 0, -vector1.x);
        } else {
            
            vector2 = Vector3D(0, -vector1.z, vector1.y);
        }
        
        vector2.normalize();
        
        vector3 = vector1.cross(vector2);
        vector3.normalize();
    }
};

#endif /* UtilsRayTracer_hpp */
