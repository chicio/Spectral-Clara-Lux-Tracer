//
//  Scene.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 15/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "PathReader.hpp"
#include "ObjParser.hpp"
#include "Scene.hpp"

#include <iostream>

Scene::Scene(std::string sceneName) {
    
    //Init error description string.
    errorDescription = "";
    
    //Load scene based on name.
    sceneIsNotValid = loadScene(sceneName);
}

bool Scene::loadScene(std::string sceneName) {
    
    //Get scene file path
    std::string file = PathReader::getPath("", sceneName.c_str(), "xml");
    
    //Load scene file.
	tinyxml2::XMLDocument doc;
    doc.LoadFile(file.c_str());
    
    //Invalid xml.
    if(doc.ErrorID() != XML_NO_ERROR) {
        
        cubeMappingSkybox = nullptr;
        light = nullptr;
        
        errorDescription = "Scene file doesn't exists.";
        return true;
    }
    
    //Variable used to flag the scene as erroneous.
    bool errorsInScene = false;
    
    //Get scene type.
    //Assume spectral as default.
    std::string sceneType = doc.RootElement()->Attribute("type");
    sceneType = sceneType == "" ? "Spectral" : sceneType;
    
    //Read camera.
    XMLElement* cameraElement = doc.RootElement()->FirstChildElement("camera");
    errorsInScene = errorsInScene || setupCamera(cameraElement);
    
    //Light.
    const XMLElement* lightElement = doc.RootElement()->FirstChildElement("light");
    const XMLElement* lightOrigin = lightElement->FirstChildElement("origin");
    
    if(lightElement) {
        
        std::string lightType = lightElement->Attribute("type");
        
        if(sceneType == "RGB") {
            
            bool rgbLightCreation = setupRGBLight(lightElement, lightOrigin, lightType);
            errorsInScene = errorsInScene || rgbLightCreation;
        } else {
            
            bool spectralLightCreation = setupSpectralLight(lightElement, lightOrigin, lightType);
            errorsInScene = errorsInScene || spectralLightCreation;
        }
    } else {
        
        errorDescription = errorDescription + "The scene doesn't contain any light.\n";
        errorsInScene = true;
    }
    
    //Eventually set a cube mapping skybox.
    setupSkyboxWithCubeMapping(doc);
    
    //Objects
    XMLElement *objectsElement = doc.RootElement()->FirstChildElement("objects");
    
    if(!objectsElement) {
        
        errorDescription = errorDescription + "The scene doesn't contain any object.\n";
        errorsInScene = true;
    }
    
    //Init geometric objects.
    for(XMLElement *objectElement = objectsElement->FirstChildElement("object");
        objectElement != NULL;
        objectElement = objectElement->NextSiblingElement("object")) {
        
        std::string type = objectElement->Attribute("type");
        
        //Object creation
        Model* object;
        bool objectCreation = setupObject(&object, objectElement);
        errorsInScene = errorsInScene || objectCreation;
        
        //Object material creation.
        const XMLElement* material = objectElement->FirstChildElement("material");
        
        if(sceneType == "RGB") {
            
            bool materialRGBCreation = setupRGBObjectMaterial(object, material);
            errorsInScene = errorsInScene || materialRGBCreation;
        } else {
            
            bool materialBRDFCreation = setupBRDFObjectMaterial(object, material);
            errorsInScene = errorsInScene || materialBRDFCreation;
        }
        
        //add object.
        objects.push_back(object);
    }
    
    //Init polygonal mesh.
    for(XMLElement *objectElement = objectsElement->FirstChildElement("mesh");
        objectElement != NULL;
        objectElement = objectElement->NextSiblingElement("mesh")) {
        
        const XMLElement* objFile = objectElement->FirstChildElement("objFile");
        
        bool backFaceCulling = false;
        
        if(attributesExist(objFile, {"backFaceCulling"})) {
            
            backFaceCulling = objFile->FindAttribute("backFaceCulling")->BoolValue();
        }
        
        std::string objName = objFile->Attribute("name");
        std::string objFilePath = PathReader::getPath("OBJs", objName.c_str(), "obj");
        
        ObjParser objParser;
        objParser.parseObj(objFilePath.c_str(), backFaceCulling);
        std::vector<Model *> pList = objParser.getPolygonalShapes();

        const XMLElement* material = objectElement->FirstChildElement("material");
        
        for(std::vector<Model *>::size_type i = 0; i != pList.size(); i++) {

            if(sceneType == "RGB") {
                
                bool materialRGBCreation = setupRGBObjectMaterial(pList[i], material);
                errorsInScene = errorsInScene || materialRGBCreation;
            } else {
                
                bool materialBRDFCreation = setupBRDFObjectMaterial(pList[i], material);
                errorsInScene = errorsInScene || materialBRDFCreation;
            }
        }
        
        //Setup AABB.
        const XMLElement* aabbElement = objectElement->FirstChildElement("aabb");
        AxisAlignedBoundingBox aabb;
        setupAABB(aabb, aabbElement);

        //Create mesh.
        Model* mesh = new PolygonalMesh(pList, aabb);
        
        //Add mesh.
        objects.push_back(mesh);
    }
    
    //SCLT specific configuration.
    errorsInScene = errorsInScene || setupSCLTParameter(doc, sceneType);
        
    return errorsInScene;
}

bool Scene::attributesExist(const XMLElement* element, std::vector<const char*> attributesNames) {
    
    for(std::vector<const char*>::size_type i = 0; i != attributesNames.size(); i++) {

        if(!element->FindAttribute(attributesNames[i])) {
            
            return false;
        }
    }
    
    return true;
}

bool Scene::isSceneValid() {
    
    return !sceneIsNotValid;
}

std::string Scene::getSceneErrorsDescription() {
    
    return errorDescription;
}

bool Scene::setupCamera(XMLElement* cameraElement) {
    
    if(!cameraElement) {
        
        errorDescription = errorDescription + "Define a camera.\n";
        return true;
    }
    
    const XMLElement* viewReferencePointelement = cameraElement->FirstChildElement("viewReferencePoint");
    const XMLElement* lookAtPointElement = cameraElement->FirstChildElement("lookAtPoint");
    const XMLElement* viewPlaneElement = cameraElement->FirstChildElement("viewPlane");
    
    if (!viewReferencePointelement || !lookAtPointElement || !viewPlaneElement) {
        
        errorDescription = errorDescription + "Camera property not setted correctly.\n";
        return true;
    }
    
    if(!attributesExist(viewReferencePointelement, {"x", "y", "z"})) {
        
        errorDescription = errorDescription + "View reference point no setted correctly.\n";
        return true;
    }
    
    viewReferencePoint = Point3D(viewReferencePointelement->FindAttribute("x")->FloatValue(),
                                 viewReferencePointelement->FindAttribute("y")->FloatValue(),
                                 viewReferencePointelement->FindAttribute("z")->FloatValue());
    
    if(!attributesExist(lookAtPointElement, {"x", "y", "z"})) {
        
        errorDescription = errorDescription + "Look at point no setted correctly.\n";
        return true;
    }
    
    lookAtPoint = Point3D(lookAtPointElement->FindAttribute("x")->FloatValue(),
                          lookAtPointElement->FindAttribute("y")->FloatValue(),
                          lookAtPointElement->FindAttribute("z")->FloatValue());
    
    if(!attributesExist(viewPlaneElement, {"d"})) {
        
        errorDescription = errorDescription + "View plane distance no setted correctly.\n";
        return true;
    }
    
    viewPlaneDistance = viewPlaneElement->FindAttribute("d")->FloatValue();
    
    return false;
}

bool Scene::setupSCLTParameter(const tinyxml2::XMLDocument& doc, std::string sceneType) {
    
    bool errorsSCLTParamaters = false;
    
    const XMLElement* shadingModelTypeElement = doc.RootElement()->FirstChildElement("shadingModelType");
    const XMLElement* tracerModelTypeElement = doc.RootElement()->FirstChildElement("tracerModelType");
    
    if(!shadingModelTypeElement || !tracerModelTypeElement) {
        
        errorDescription = errorDescription + "Tracer model or shading model not defined.\n";
        return true;
    }

    std::string shadingModelTypeParameter = shadingModelTypeElement->GetText();
    std::string tracerModelTypeParameter = tracerModelTypeElement->GetText();
    
    //Tracer configuration.
    if(tracerModelTypeParameter == "TracerRGBModel") {
        
        tracerModelType = TracerRGBModel;
    } else if(tracerModelTypeParameter == "TracerSpectrumModel") {
        
        tracerModelType = TracerSpectrumModel;
    } else if(tracerModelTypeParameter == "PathTracerModel") {
        
        tracerModelType = PathTracerModel;
        
        //Get number of samples for path tracing.
        numberOfSamples = tracerModelTypeElement->FindAttribute("numberOfSamples")->IntValue();
    } else {
        
        errorDescription = errorDescription + "Tracer model not setted correctly.\n";
        errorsSCLTParamaters = true;
    }
    
    if(shadingModelTypeParameter == "WhittedShadingModel") {
        
        shadingModelType = WhittedShadingModel;
    } else if(shadingModelTypeParameter == "WhittedBRDFShadingModel") {
        
        shadingModelType = WhittedBRDFShadingModel;
    } else if(shadingModelTypeParameter == "PathTracingBRDFShadingModel") {
        
        shadingModelType = PathTracingBRDFShadingModel;
        
        //Add area light to intersectable objects.
        AreaLight* l = static_cast<AreaLight *>(light);
        
        Sphere* lightSphere = new Sphere(l->lightSphere->center, l->lightSphere->radius, true);
        lightSphere->material = MaterialBRDF::emissiveMaterial(l->spectrum);
        lightSphere->isLight = true;
        
        objects.push_back(lightSphere);
    } else {
        
        errorDescription = errorDescription + "Shading model not setted correctly.\n";
        errorsSCLTParamaters = true;
    }
    
    if(sceneType == "RGB") {
        
        const XMLElement* empiricalLightingModelElement = doc.RootElement()->FirstChildElement("empiricalLighting");
        
        if(!empiricalLightingModelElement) {
            
            errorDescription = errorDescription + "RGB empirical lighting model not defined.\n";
            errorsSCLTParamaters = true;
        }
        
        std::string empiricalLightingParameter = empiricalLightingModelElement->GetText();
        
        if(empiricalLightingParameter == "Phong") {
            
            empiricalLighting = Phong;
        } else if(empiricalLightingParameter == "BlinnPhong") {
            
            empiricalLighting = BlinnPhong;
        } else {
            
            errorDescription = errorDescription + "RGB empirical lighting model not setted correctly.\n";
            errorsSCLTParamaters = true;
        }
    }
    
    return errorsSCLTParamaters;
}

bool Scene::setupRGBLight(const XMLElement* lightElement, const XMLElement* lightOrigin, std::string lightType) {
    
    const XMLElement* lightColor = lightElement->FirstChildElement("color");
    
    if(!lightColor) {
        
        errorDescription = errorDescription + "RGB Light color not defined.\n";
        return true;
    }
    
    if(!lightOrigin) {
        
        errorDescription = errorDescription + "RGB Light origin not defined.\n";
        return true;
    }
    
    if(!attributesExist(lightOrigin, {"x", "y", "z"})) {
        
        errorDescription = errorDescription + "RGB light origin coordinates not valid.\n";
        return true;
    }
    
    if(!attributesExist(lightColor, {"r", "g", "b"})) {
        
        errorDescription = errorDescription + "RGB light color not valid.\n";
        return true;
    }
    
    if(lightType == "area") {
        
        const XMLElement *lightRadius = lightElement->FirstChildElement("radius");
        
        if(!lightRadius) {
            
            errorDescription = errorDescription + "RGB area Light radius not defined.\n";
            return true;
        }
        
        if(!attributesExist(lightRadius, {"r"})) {
            
            errorDescription = errorDescription + "RGB area light radius not valid.\n";
            return true;
        }
        
        light = new AreaLight(Point3D(lightOrigin->FindAttribute("x")->FloatValue(),
                                      lightOrigin->FindAttribute("y")->FloatValue(),
                                      lightOrigin->FindAttribute("z")->FloatValue()),
                              Vector3D(lightColor->FindAttribute("r")->FloatValue(),
                                       lightColor->FindAttribute("g")->FloatValue(),
                                       lightColor->FindAttribute("b")->FloatValue()),
                              lightRadius->FindAttribute("r")->FloatValue());
    } else if(lightType == "point") {
        
        light = new Light(Point3D(lightOrigin->FindAttribute("x")->FloatValue(),
                                  lightOrigin->FindAttribute("y")->FloatValue(),
                                  lightOrigin->FindAttribute("z")->FloatValue()),
                          Vector3D(lightColor->FindAttribute("r")->FloatValue(),
                                   lightColor->FindAttribute("g")->FloatValue(),
                                   lightColor->FindAttribute("b")->FloatValue()));
    } else {
        
        errorDescription = errorDescription + "Light type doesn't exists.\n";
        return true;
    }
    
    return false;
}

bool Scene::setupSpectralLight(const XMLElement* lightElement, const XMLElement* lightOrigin, std::string lightType) {
    
    if(!lightOrigin) {
        
        errorDescription = errorDescription + "Spectral light origin not defined.\n";
        return true;
    }
    
    if(!attributesExist(lightOrigin, {"x", "y", "z"})) {
        
        errorDescription = errorDescription + "Spectral light origin coordinates not valid.\n";
        return true;
    }
    
    if(!attributesExist(lightElement, {"spectrum"})) {
        
        errorDescription = errorDescription + "Spectral light has no spectrum.\n";
        return true;
    }
    
    std::string lightSpectrumName = lightElement->Attribute("spectrum");
    Spectrum<constant::spectrumSamples> lightSpectrum;
    
    if(!getSpectrumIlluminant(lightSpectrumName, lightSpectrum)) {
    
        errorDescription = errorDescription + "Spectral light spectrum doesn't exists.\n";
        return true;
    }
    
    //Save original light spectrum.
    //(not modified by brightness attenuation).
    originalLightSpectrum = lightSpectrum;
    
    //For path tracing, regulate spd of light with brightness parameter.
    if(attributesExist(lightElement, {"brightness"})) {
        
        float brightness = lightElement->FindAttribute("brightness")->FloatValue();
        lightSpectrum = lightSpectrum * brightness;
    }
    
    if(lightType == "area") {
        
        const XMLElement *lightRadius = lightElement->FirstChildElement("radius");
        
        if(!lightRadius) {
            
            errorDescription = errorDescription + "Spectral area Light radius not defined.\n";
            return true;
        }
        
        if(!attributesExist(lightRadius, {"r"})) {
            
            errorDescription = errorDescription + "Spectral area light radius not valid.\n";
            return true;
        }
        
        light = new AreaLight(Point3D(lightOrigin->FindAttribute("x")->FloatValue(),
                                      lightOrigin->FindAttribute("y")->FloatValue(),
                                      lightOrigin->FindAttribute("z")->FloatValue()),
                              lightSpectrum,
                              lightRadius->FindAttribute("r")->FloatValue());
    } else if(lightType == "point") {
        
        light = new Light(Point3D(lightOrigin->FindAttribute("x")->FloatValue(),
                                  lightOrigin->FindAttribute("y")->FloatValue(),
                                  lightOrigin->FindAttribute("z")->FloatValue()),
                          lightSpectrum);
    } else {
        
        errorDescription = errorDescription + "Light type doesn't exists.\n";
        return true;
    }
    
    return false;
}

bool Scene::getSpectrumIlluminant(std::string lightSpectrumName, Spectrum<constant::spectrumSamples>& lightSpectrum) {
    
    if(lightSpectrumName == "a") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::a);
    } else if(lightSpectrumName == "d50") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::d50);
    } else if(lightSpectrumName == "d65") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::d65);
    } else if(lightSpectrumName == "fl1") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::fl1);
    }else if(lightSpectrumName == "fl2") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::fl2);
    }else if(lightSpectrumName == "fl3") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::fl3);
    }else if(lightSpectrumName == "fl4") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::fl4);
    }else if(lightSpectrumName == "fl5") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::fl5);
    }else if(lightSpectrumName == "fl6") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::fl6);
    }else if(lightSpectrumName == "fl7") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::fl7);
    }else if(lightSpectrumName == "fl8") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::fl8);
    }else if(lightSpectrumName == "fl9") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::fl9);
    }else if(lightSpectrumName == "fl10") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::fl10);
    }else if(lightSpectrumName == "fl11") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::fl11);
    }else if(lightSpectrumName == "fl12") {
        
        lightSpectrum = Spectrum<constant::spectrumSamples>(Illuminant::fl12);
    }else {
        
        errorDescription = errorDescription + "Illuminant " + lightSpectrumName + " doesn't exists.\n";
        return false;
    }
    
    return true;
}

void Scene::setupSkyboxWithCubeMapping(const tinyxml2::XMLDocument& doc) {
    
    if(doc.RootElement()->FirstChildElement("cubeMappingSkybox")) {
        
        cubeMappingSkybox = new CubeMappingSkybox();
    } else {
        
        cubeMappingSkybox = nullptr;
    }
}

bool Scene::setupObject(Model** object, XMLElement* objectElement) {
    
    if(!attributesExist(objectElement, {"type"})) {
        
        errorDescription = errorDescription + "Object type not defined\n";
        return true;
    }
    
    std::string type = objectElement->Attribute("type");
    
    if(type == "sphere") {
        
        const XMLElement* sphereOrigin = objectElement->FirstChildElement("origin");
        const XMLElement* sphereRadius = objectElement->FirstChildElement("radius");
        
        if (!sphereOrigin) {
            
            errorDescription = errorDescription + "Sphere origin not defined.\n";
            return true;
        }
        
        if(!sphereRadius) {
            
            errorDescription = errorDescription + "Sphere radius not defined.\n";
            return true;
        }
        
        if(!attributesExist(sphereOrigin, {"x", "y", "z"})) {
            
            errorDescription = errorDescription + "Sphere origin coordinates not valid.\n";
            return true;
        }
        
        if(!attributesExist(sphereRadius, {"r"})) {
            
            errorDescription = errorDescription + "Sphere radius not defined.\n";
            return true;
        }
        
        *object = new Sphere(Point3D(sphereOrigin->FindAttribute("x")->FloatValue(),
                                     sphereOrigin->FindAttribute("y")->FloatValue(),
                                     sphereOrigin->FindAttribute("z")->FloatValue()),
                             sphereRadius->FindAttribute("r")->FloatValue());
    } else if (type == "square" || type == "polygonalshape") {
        
        std::vector<Point3D> vertexList;
        
        for(XMLElement* v = objectElement->FirstChildElement("vertex");
            v != NULL;
            v = v->NextSiblingElement("vertex")) {
            
            const XMLElement* vertexElement = v;
            
            if(!attributesExist(vertexElement, {"x", "y", "z"})) {
                
                errorDescription = errorDescription + "Vertex coordinates not valid.\n";
                return true;
            }
            
            Point3D vertex(vertexElement->FindAttribute("x")->FloatValue(),
                           vertexElement->FindAttribute("y")->FloatValue(),
                           vertexElement->FindAttribute("z")->FloatValue());
            
            vertexList.push_back(vertex);
        }
        
        const XMLElement* pointOnPlaneElement = objectElement->FirstChildElement("pointOnPlane");
        
        if(!pointOnPlaneElement) {
            
            errorDescription = errorDescription + "Point on plane not defined.\n";
            return true;
        }
        
        if(!attributesExist(pointOnPlaneElement, {"x", "y", "z"})) {
            
            errorDescription = errorDescription + "Point on plane coordinates not valid.\n";
            return true;
        }
        
        Point3D pointOnPlane(pointOnPlaneElement->FindAttribute("x")->FloatValue(),
                             pointOnPlaneElement->FindAttribute("y")->FloatValue(),
                             pointOnPlaneElement->FindAttribute("z")->FloatValue());
        
        if(type == "square") {
            
            std::string skyboxSideName = "";
            
            if(attributesExist(objectElement, {"skyboxSide"})) {
                
                skyboxSideName = objectElement->Attribute("skyboxSide");
            }
            
            *object = new Square(vertexList, pointOnPlane, skyboxSideName);
        } else {
            
            *object = new PolygonalShape(vertexList, pointOnPlane);
        }
    } else {
        
        errorDescription = errorDescription + "Object type" + type + " doesn't exists.\n";
        return true;
    }
    
    return false;
}

bool Scene::setupRGBObjectMaterial(Model* object, const XMLElement* material) {
    
    std::string materialType = material->Attribute("type");
    
    if (object) {
        
        if(materialType == "jade") {
            
            object->material = MaterialRGB::jade();
        } else if(materialType == "bronze") {
            
            object->material = MaterialRGB::bronze();
        } else if(materialType == "violet") {
            
            object->material = MaterialRGB::violet();
        } else if(materialType == "greeen") {
            
            object->material = MaterialRGB::green();
        } else if(materialType == "red") {
            
            object->material = MaterialRGB::red();
        } else if(materialType == "mediumGray") {
            
            object->material = MaterialRGB::mediumGray();
        } else if(materialType == "lightGray") {
            
            object->material = MaterialRGB::lightGray();
        } else if(materialType == "matte") {
            
            object->material = MaterialRGB::matte();
        } else if(materialType == "chrome") {
            
            object->material = MaterialRGB::chrome();
        } else if(materialType == "silver") {
            
            object->material = MaterialRGB::silver();
        } else if(materialType == "glass") {
            
            object->material = MaterialRGB::glass();
        } else if(materialType == "glasswater") {
            
            object->material = MaterialRGB::glasswater();
        } else if(materialType == "matteTextured") {
            
            const char* textureName = material->Attribute("textureName");
            object->material = MaterialRGB::matte(textureName);
        } else if(materialType == "rubyBumpMapped") {
            
            float scale = material->FindAttribute("scale")->FloatValue();
            object->material = MaterialRGB::rubyBumpMapped(scale);
        } else if(materialType == "flameMarble") {
            
            object->material = MaterialRGB::flameMarble();
        } else if(materialType == "blueTurbulence") {
            
            object->material = MaterialRGB::blueTurbulence();
        } else {
            
            errorDescription = errorDescription + "RGB material " + materialType + " doesn't exists.\n";
            return true;
        }
    }
    
    return false;
}

bool Scene::setupBRDFObjectMaterial(Model* object, const XMLElement* material) {
    
    std::string materialType = material->Attribute("type");
    
    if(materialType == "emissive") {
        
        std::string spectrumName = material->Attribute("spectrum");
        Spectrum<constant::spectrumSamples> spectrum;
        getSpectrumIlluminant(spectrumName, spectrum);
        
        object->material = MaterialBRDF::emissiveMaterial(spectrum);
    } else if(materialType == "matteLambertian") {
        
        std::string spectrumName = material->Attribute("spectrum");
        Spectrum<constant::spectrumSamples> spectrum;
        getMacbethSpectrum(spectrumName, spectrum);
        
        object->material = MaterialBRDF::matteMaterial(spectrum);
    } else if(materialType == "matteOrenNayar") {
        
        std::string spectrumName = material->Attribute("spectrum");
        Spectrum<constant::spectrumSamples> spectrum;
        getMacbethSpectrum(spectrumName, spectrum);
        
        float degree = material->FindAttribute("degree")->FloatValue();
        
        object->material = MaterialBRDF::matteMaterial(spectrum, degree);
    } else if(materialType == "plastic") {
        
        std::string spectrumDiffuseName = material->Attribute("spectrumDiffuse");
        Spectrum<constant::spectrumSamples> spectrumDiffuse;
        getMacbethSpectrum(spectrumDiffuseName, spectrumDiffuse);
        
        std::string spectrumSpecularName = material->Attribute("spectrumSpecular");
        Spectrum<constant::spectrumSamples> spectrumSpecular;
        getMacbethSpectrum(spectrumSpecularName, spectrumSpecular);
        
        float roughness = material->FindAttribute("roughness")->FloatValue();
        
        if(roughness == 0.0f) {
            
            //Default roughness value.
            roughness = 40.0f;
        }
        
        object->material = MaterialBRDF::plasticMaterial(spectrumDiffuse, spectrumSpecular,roughness);
    } else if(materialType == "glass") {
        
        object->material = MaterialBRDF::glassMaterial();
    } else if(materialType == "measured") {
        
        bool interpolated = false;
        
        if(attributesExist(material, {"interpolated"})) {
            
            interpolated = material->FindAttribute("interpolated")->BoolValue();
        }
        
        const char* measuredBRDFName = material->Attribute("name");
        object->material = MaterialBRDF::measuredMaterial(measuredBRDFName, interpolated);
    } else {
        
        errorDescription = errorDescription + "BRDF material " + materialType + " doesn't exists.\n";
        return true;
    }
    
    return false;
}

bool Scene::setupAABB(AxisAlignedBoundingBox& aabb, const XMLElement* aabbElement) {
    
    const XMLElement* min = aabbElement->FirstChildElement("min");
    const XMLElement* max = aabbElement->FirstChildElement("max");

    if (!min) {
        
        errorDescription = errorDescription + "AABB min not defined.\n";
        return true;
    }
    
    if(!max) {
        
        errorDescription = errorDescription + "AABB max not defined.\n";
        return true;
    }

    if(!attributesExist(min, {"x", "y", "z"})) {
        
        errorDescription = errorDescription + "AABB min not valid.\n";
        return true;
    }

    if(!attributesExist(max, {"x", "y", "z"})) {
        
        errorDescription = errorDescription + "AABB max not valid.\n";
        return true;
    }
    
    Point3D minAABBVertex(min->FindAttribute("x")->FloatValue(),
                          min->FindAttribute("y")->FloatValue(),
                          min->FindAttribute("z")->FloatValue());
    
    Point3D maxAABBVertex(max->FindAttribute("x")->FloatValue(),
                          max->FindAttribute("y")->FloatValue(),
                          max->FindAttribute("z")->FloatValue());
    
    aabb.min = minAABBVertex;
    aabb.max = maxAABBVertex;
    
    return false;
}

bool Scene::getMacbethSpectrum(std::string macbethColorName, Spectrum<constant::spectrumSamples>& spectrum) {
    
    if(macbethColorName == "darkSkin") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::darkSkin);
    } else if(macbethColorName == "lightSkin") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::lightSkin);
    } else if(macbethColorName == "blueFlower") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::blueFlower);
    } else if(macbethColorName == "orange") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::orange);
    } else if(macbethColorName == "purplishBlue") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::purplishBlue);
    } else if(macbethColorName == "purple") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::purple);
    } else if(macbethColorName == "yellowGreen") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::yellowGreen);
    } else if(macbethColorName == "blue") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::blue);
    } else if(macbethColorName == "green") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::green);
    } else if(macbethColorName == "red") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::red);
    } else if(macbethColorName == "yellow") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::yellow);
    } else if(macbethColorName == "magenta") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::magenta);
    } else if(macbethColorName == "cyan") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::cyan);
    } else if(macbethColorName == "white") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::white);
    } else if(macbethColorName == "neutral8") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::neutral8);
    } else if(macbethColorName == "neutral65") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::neutral65);
    } else if(macbethColorName == "black") {
        
        spectrum = Spectrum<constant::spectrumSamples>(MacbethColorChecker::black);
    } else {

        errorDescription = errorDescription + "Macbeth color " + macbethColorName + " doesn't exists.\n";
        return true;
    }
    
    return false;
}

Scene::~Scene() {
    
    //Clean cube mapping skybox.
    delete cubeMappingSkybox;
    
    //Clean area light.
    delete light;
    
    //Clean objects
    for(auto &object:objects) {

        delete object;
    }
    
    objects.clear();
}
