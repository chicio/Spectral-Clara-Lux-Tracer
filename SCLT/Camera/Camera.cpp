//
//  Camera.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 30/10/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Camera.hpp"

Camera::Camera(const Point3D& sceneViewReferencePoint,
               const Point3D& sceneLookAtPoint,
               const Vector3D& sceneViewUp,
               const ViewPlane& sceneViewPlane,
               float sceneViewPlanedistance) {
    
    viewReferencePoint = sceneViewReferencePoint;
    lookat = sceneLookAtPoint;
    viewUp = sceneViewUp;
    viewPlanedistance = sceneViewPlanedistance;
    
    //Set up the camera coordinate system.
    setupCameraCoordinateSystem();
    
    //I calculate here the n component used in the ray generation and
    //the half view plane width/height.
    //I init them here avoid to repeat this operation for every ray.
    //Scale n vector to be coherent with the view plane distance
    //(because I need it to do the diff in the next operation).
    nComponent = n * viewPlanedistance;
    
    //Half plane.
    viewPlaneHalfHeight = sceneViewPlane.height * 0.5f;
    viewPlaneHalfWidth = sceneViewPlane.width * 0.5f;
}

void Camera::setupCameraCoordinateSystem() {
    
    Vector3D nNotNormalized = viewReferencePoint - lookat;
    
    //Standard camera coordinate system.
    
    //n vector.
    n = Vector3D(nNotNormalized.x, nNotNormalized.y, nNotNormalized.z);
    n.normalize();
    
    //u vector is the cross product between the view up and the view plane normal n.
    u = viewUp.cross(nNotNormalized);
    u.normalize();

    //v vector.
    v = n.cross(u);
}

Vector3D Camera::rayInCameraCoordinateSystem(float viewPlaneX, float viewPlaneY) const {
    
    //I need to shift the coordinate on the view plane because
    //the reference system of the camera uvn is CENTERED IN THE
    //CENTER of the view plane.
    float xTemp = viewPlaneX - viewPlaneHalfWidth;
    float yTemp = viewPlaneY - viewPlaneHalfHeight;
    
    //Calculate components on the uv plane.
    Vector3D uComponent = u * xTemp;
    Vector3D vComponent = v * yTemp;
    
    //Ray direction normalized.
    //We consider also the distance from the view plane (see init method nComponent).
    //From ray tracing from the ground up:
    //"The nice thing about an ONB is that we can express any vector as a linear
    //combination of its basis vectors. We can therefore write the primary ray d
    //as d = x_vp * u + y_vp * v - distancevp * n"
    Vector3D rayDirection = ((uComponent + vComponent) - nComponent);
    rayDirection.normalize();
    
    return rayDirection;
}
