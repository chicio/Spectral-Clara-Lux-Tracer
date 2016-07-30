//
//  Camera.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 30/10/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "ViewPlane.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"

class Camera {
private:
    
    /// Position of the camera in world coordinate.
    Point3D viewReferencePoint;
    /// Look at point (used in view plane normal calculation).
    Point3D lookat;
    /// Up direction of the camera.
    Vector3D viewUp;
    /// Distance of the camera from the view plane.
    float viewPlanedistance;
    /// U unit vector.
    Vector3D u;
    /// V unit vector.
    Vector3D v;
    /// N unit vector.
    Vector3D n;
    /// Vector used in the calculation of the rays in the camera coordinate system.
    /// It is a scaling of the n vector so that it would to be coherent with the view
    /// plane distance (because I need it to do the diff during camera ray direction
    /// calculation, see below).
    Vector3D nComponent;
    /// Half view plane width. Used during camera calculation (see below).
    float viewPlaneHalfWidth;
    /// Half view plane height. Used during camera calculation (see below).
    float viewPlaneHalfHeight;
    
    /*!
     Calculate vectors used as a base for the camera coordinate system.
     */
    void setupCameraCoordinateSystem();
    
public:
    
    /*!
     Constructor.
     
     @param sceneViewReferencePoint view reference point.
     @param sceneLookAtPoint look-at point.
     @param sceneViewUp view up direction vector.
     @param sceneViewPlane the view plane.
     @param sceneViewPlanedistance the distance of the camera from the view plane.
     
     @returns a Camera instance.
     */
    Camera(const Point3D& sceneViewReferencePoint,
           const Point3D& sceneLookAtPoint,
           const Vector3D& sceneViewUp,
           const ViewPlane& sceneViewPlane,
           float sceneViewPlanedistance);
    
    /*!
     Method used to generate a ray in the camera coordinate reference system.
     
     @see "Ray tracing from the ground up", page 151 cap. "A pratical viewing system".
     
     @param viewPlaneX a x component of a point on the view plane.
     @param viewPlaneY a y component of a point on the view plane.
     
     @returns a Vector3D used as ray distance vector.
     */
    Vector3D rayInCameraCoordinateSystem(float viewPlaneX, float viewPlaneY) const;
};

#endif /* Camera_hpp */
