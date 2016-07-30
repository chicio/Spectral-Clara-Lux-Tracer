//
//  SCLT.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 07/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef SCLT_hpp
#define SCLT_hpp

#include "ViewPlane.hpp"
#include "Scene.hpp"
#include "PerlinTexture.hpp"
#include "Material.hpp"
#include "Sphere.hpp"
#include "Polygon.hpp"
#include "Ray.hpp"
#include "MathUtils.hpp"
#include "CubeMappingSkybox.hpp"
#include "Constants.hpp"
#include "Vector3D.hpp"
#include "Point3D.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "AreaLight.hpp"
#include "ShadowRay.hpp"
#include "ShadingModel.hpp"
#include "Intersection.hpp"
#include "ShadowCalculator.hpp"
#include "Tracer.hpp"

#if defined(__APPLE__) && !defined(COMMAND_LINE)
#import "ProgressDelegate.h"
#endif

#if defined(_WIN32) && !defined(COMMAND_LINE)
#include "MainPage.xaml.h"
using namespace SpectralClaraLuxTracer;
#endif

class SCLT {
private:
    
    /// Antialiasing number of sample.
    int antialiasingNumOfSample;
    /// Scene name.
    std::string sceneName;
    /// Scene pointer.
    Scene* scene;
    /// Tracer pointer.
    Tracer* tracer;
    /// View plane.
    ViewPlane vplane;
    /// Total pixel to be calculated.
    int totalPixel;
    
#if defined(__APPLE__) && !defined(COMMAND_LINE)

    /// Progress delegate used on apple platform to update the progress bar.
    id<ProgressDelegate> progressDelegate;

#endif

#if defined(_WIN32) && !defined(COMMAND_LINE)

	/// Store a reference to mainpage object to delegate the update of the progress bar.
	MainPage^ mainPage;

#endif
    
public:

    /*!
     Init the ray tracer.
     
     @param viewPlane view plane used to render the scene.
     @param sceneName name of the scene to be loaded.
     @param antialiasingNumOfSample number of sample for antialiasing.
     
     returns a Ray tracer instance.
     */
    SCLT(ViewPlane viewPlane, std::string sceneName, int antialiasingNOfSample);
    
    /*!
     Start the ray tracer to compute each pixel of the image.
     The viewport and view plane are of the same dimension (and position).
     No need to scale or transform. The method runs asyn and returns the
     result in a block.
     
     @param scene A dictionary that contain all scene objects.
     @param finishTracking a block used to return the pixels color calculated.
     */
    std::vector<Vector3D> runSCLTRayTracer() const;
    
    /*!
     Check if scene created by SCLT is valid.
     If not, errorsDescription contains the error description.
     
     @returns a bool indicating that the scene is valid.
     */
    bool validScene(std::string& sceneErrorsDescription);
    
#if defined(__APPLE__) && !defined(COMMAND_LINE)
    
    /*!
     Method used to set the delegate that manage the
     progress bar update.
     
     @param delegate.
     */
    void setDelegate(id<ProgressDelegate> delegate);

#endif
    
#if defined(_WIN32) && !defined(COMMAND_LINE)

	void setDelegate(MainPage^ mp);

#endif
    
    /*!
     Method called to dispatch update on the status
     of the render. Each platform implement its own
     callback. This method is called after each pixel
     calculation.
     
     @param current pixel.
     */
    void progressUpdate(int currentPixel) const;
    
    /*!
     Destructor.
     Clean scene object.
     */
    ~SCLT();
};

#endif /* SCLT_hpp */
