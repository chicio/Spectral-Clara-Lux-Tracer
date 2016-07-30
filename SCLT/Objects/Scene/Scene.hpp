//
//  Scene.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 15/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <vector>

#include "tinyxml2.h"
#include "CubeMappingSkybox.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Light.hpp"
#include "AreaLight.hpp"
#include "Model.hpp"
#include "Sphere.hpp"
#include "Polygon.hpp"
#include "Square.hpp"
#include "Material.hpp"
#include "MaterialRGB.hpp"
#include "MaterialBRDF.hpp"
#include "EmpiricalBRDF.hpp"
#include "ShadingModelType.hpp"
#include "TracerModelType.hpp"
#include "MacbethColorChecker.hpp"
#include "PolygonalMesh.hpp"

using namespace tinyxml2;

class Scene {
private:
    
    /// Flag used to indicate if the scene is valid.
    bool sceneIsNotValid;
    /// Variable used to store a string with the error message if the scene is invalid.
    std::string errorDescription;
    
    /*!
     Setup camera from scene data.
     
     @param cameraElement camera element from scene XML.
     
     @returns true if the camera is created, else false.
     */
    bool setupCamera(XMLElement* cameraElement);
    
    /*!
     Setup RGB light from scene data.
     
     @param lightElement light element from scene XML.
     @param lightOrigin light origin element from scene XML.
     @param lightType light type.
     
     @returns true if RGB light is created, else false.
     */
    bool setupRGBLight(const XMLElement* lightElement, const XMLElement* lightOrigin, std::string lightType);

    /*!
     Setup spectral light from scene data.
     
     @param lightElement light element from scene XML.
     @param lightOrigin light origin element from scene XML.
     @param lightType light type.
     
     @returns true if spectral light is created, else false.
     */
    bool setupSpectralLight(const XMLElement* lightElement, const XMLElement* lightOrigin, std::string lightType);

    /*!
     Setup SCLT specific parameter from scene data.
     
     @param doc scene XML doc.
     @param sceneType scene type.
     
     @returns true if specific parameter are correct, else false.
     */
    bool setupSCLTParameter(const tinyxml2::XMLDocument& doc, std::string sceneType);
    
    /*!
     Setup a specific object from scene data.
     
     @param object object.
     @param objectElement object element from scene XML.
     
     @returns true if object is created, else false.
     */
    bool setupObject(Model** object, XMLElement *objectElement);
    
    /*!
     Setup RGB material from scene data.
     
     @param object object.
     @param material material element from scene XML.

     @returns true if material is created, else false.
     */
    bool setupRGBObjectMaterial(Model* object, const XMLElement* material);
    
    /*!
     Setup skybox using cubemapping.
     
     @param doc scene XML doc.
     */
    void setupSkyboxWithCubeMapping(const tinyxml2::XMLDocument& doc);

    /*!
     Setup BRDF material from scene data.
     
     @param object object.
     @param material material element from scene XML.
        
     @returns true if material is created, else false.
     */
    bool setupBRDFObjectMaterial(Model* object, const XMLElement* material);

    /*!
     Setup axis aligned boundign box for polygonal mesh.
     
     @param object object.
     @param aabb aabb element from scene XML.
     
     @returns true if aabb is created, else false.
     */
    bool setupAABB(AxisAlignedBoundingBox& aabb, const XMLElement* aabbElement);
    
    /*!
     Setup illuminant SPD from scene data.
     
     @param lightSpectrumName illuminant name.
     @param lightSpectrum illuminant SPD.
     
     @returns true if illumnant exists, else false.
     */
    bool getSpectrumIlluminant(std::string lightSpectsrumName, Spectrum<constant::spectrumSamples>& lightSpectrum);
    
    /*!
     Setup Macbeth SPD from scene data.
     
     @param macbethColorName macbeth color name.
     @param spectrum macbeth SPD.
     
     @returns true if macbeth SPD exists, else false.
     */
    bool getMacbethSpectrum(std::string macbethColorName, Spectrum<constant::spectrumSamples>& spectrum);
    
    /*!
     Check if attribute exists on scene XML element.
     
     @param element scene XML element.
     @param attributesNames name of attributes to be checked.
     
     @returns true if attributes exists, else false.
     */
    bool attributesExist(const XMLElement* element, std::vector<const char*> attributesNames);
        
public:
    
    /// View reference point used for the camera.
    Point3D viewReferencePoint;
    /// Look at point used with the camera.
    Point3D lookAtPoint;
    /// Light used during rendering.
    Light *light;
    /// Original light spectrum, not modified by brightness attenuation in case of path tracing.
    Spectrum<constant::spectrumSamples> originalLightSpectrum;
    /// Light brightness, used to regulate the SPD of light in path tracing.
    float lightBrightness;
    /// Geometric bbjects to be rendered.
    std::vector<Model *> objects;
    /// View plane distance used in camera.
    float viewPlaneDistance;
    /// Skybox used for cube mapping.
    CubeMappingSkybox *cubeMappingSkybox;
    /// Tracer model.
    TracerModelType tracerModelType;
    /// Shading model used to rendere the scene. This must be coherent with the tracer model choosen.
    ShadingModelType shadingModelType;
    /// Light model to be used if specific type of shading model are choosen (eg.: ShadingWhittedRGB)
    EmpiricalBRDFModel empiricalLighting;
    /// Path tracer number of samples.
    int numberOfSamples;
    

    /*!
     Constructor.
     
     @param sceneId identifier of the scene.
     @param cameraPositon position of the camera.
     @param isSoftShadowActive flag used to check if I need an area light or point light.
     */
    Scene(std::string sceneName);
    
    /*!
     Parse a scene file based on the name received.
     Load all scene property in this objects, so that they could
     be read by other SCLT components.
     
     @param sceneName the scene name (without extension).
     
     @returns true if the scene XML file is valid and scene is correct, else false.
     */
    bool loadScene(std::string sceneName);
    
    /*!
     Function that check if the scene is valid.
     
     @returns a bool indicating that the scene is valid.
     */
    bool isSceneValid();
    
    /*!
     Function used to read scene error description.
     
     @returns a string containing the errors description.
     */
    std::string getSceneErrorsDescription();
    
    /*!
     Default desctructor.
     */
    ~Scene();
};

#endif
