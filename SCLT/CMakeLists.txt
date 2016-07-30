cmake_minimum_required(VERSION 2.8)
project(SCLT)

#Set build type
set(CMAKE_BUILD_TYPE Release)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

#Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "Enable pthread support")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

#Add source files
set(SOURCE_FILES
    Camera/Camera.cpp
    Camera/Camera.hpp
    Camera/ViewPlane.hpp
    Color/CIEColorSpaces/CIELab.cpp
    Color/CIEColorSpaces/CIELab.hpp
    Color/CIEColorSpaces/CIEUCS.cpp
    Color/CIEColorSpaces/CIEUCS.hpp
    Color/CIEColorSpaces/CIEUVW.cpp
    Color/CIEColorSpaces/CIEUVW.hpp
    Color/CIEColorSpaces/CIEXYZ.cpp
    Color/CIEColorSpaces/CIEXYZ.hpp
    Color/CRI/ColorRenderingIndex.cpp
    Color/CRI/ColorRenderingIndex.hpp
    Color/ChromaticAdaptationTransform.cpp
    Color/ChromaticAdaptationTransform.hpp
    Color/ColorMatchingFunction.hpp
    Color/Illuminant.hpp
    Color/MacbethColorChecker.hpp
    Color/sRGB.hpp
    Color/TestColorSamples.hpp
    Lights/AreaLight.cpp
    Lights/AreaLight.hpp
    Lights/Light.hpp
    Lights/ShadowCalculator.cpp
    Lights/ShadowCalculator.hpp
    Math/MathUtils.hpp
    Math/Matrix.cpp
    Math/Matrix.hpp
    Math/Point3D.cpp
    Math/Point3D.hpp
    Math/RandomNumberGenerator.cpp
    Math/RandomNumberGenerator.hpp
    Math/SphericalCoordinate.cpp
    Math/SphericalCoordinate.hpp
    Math/Vector3D.cpp
    Math/Vector3D.hpp
    Objects/BRDF/EmpiricalModel/EmpiricalBRDF.cpp
    Objects/BRDF/EmpiricalModel/EmpiricalBRDF.hpp
    Objects/BRDF/EmpiricalModel/EmpiricalBRDFModel.hpp
    Objects/BRDF/PhysicalModel/BRDF.cpp
    Objects/BRDF/PhysicalModel/BRDF.hpp
    Objects/BRDF/PhysicalModel/Lambertian.cpp
    Objects/BRDF/PhysicalModel/Lambertian.hpp
    Objects/BRDF/PhysicalModel/Measured.cpp
    Objects/BRDF/PhysicalModel/Measured.hpp
    Objects/BRDF/PhysicalModel/OrenNayar.cpp
    Objects/BRDF/PhysicalModel/OrenNayar.hpp
    Objects/BRDF/PhysicalModel/SpecularReflection.cpp
    Objects/BRDF/PhysicalModel/SpecularReflection.hpp
    Objects/BRDF/PhysicalModel/SpecularTransmission.cpp
    Objects/BRDF/PhysicalModel/SpecularTransmission.hpp
    Objects/BRDF/PhysicalModel/TorranceSparrow.cpp
    Objects/BRDF/PhysicalModel/TorranceSparrow.hpp
    Objects/Material/Material.cpp
    Objects/Material/Material.hpp
    Objects/Material/MaterialBRDF.cpp
    Objects/Material/MaterialBRDF.hpp
    Objects/Material/MaterialRGB.cpp
    Objects/Material/MaterialRGB.hpp
    Objects/ObjParser/ObjParser.cpp
    Objects/ObjParser/ObjParser.hpp
    Objects/Scene/tinyxml2/tinyxml2.cpp
    Objects/Scene/tinyxml2/tinyxml2.h
    Objects/Scene/Scene.cpp
    Objects/Scene/Scene.hpp
    Objects/Skyboxes/CubeMappingSkybox.cpp
    Objects/Skyboxes/CubeMappingSkybox.hpp
    Objects/AxisAlignedBoundingBox.cpp
    Objects/AxisAlignedBoundingBox.hpp
    Objects/Fresnel.cpp
    Objects/Fresnel.hpp
    Objects/Intersection.hpp
    Objects/Model.cpp
    Objects/Model.hpp
    Objects/Polygon.cpp
    Objects/Polygon.hpp
    Objects/PolygonalMesh.cpp
    Objects/PolygonalMesh.hpp
    Objects/Sphere.cpp
    Objects/Sphere.hpp
    Objects/Square.cpp
    Objects/Square.hpp
    Rays/Ray.cpp
    Rays/Ray.hpp
    Rays/ShadowRay.cpp
    Rays/ShadowRay.hpp
    Shading/PathBRDF.cpp
    Shading/PathBRDF.hpp
    Shading/ShadingModel.hpp
    Shading/ShadingModelFactory.cpp
    Shading/ShadingModelFactory.hpp
    Shading/ShadingModelType.hpp
    Shading/ShadingRGBModel.hpp
    Shading/ShadingSpectrumModel.cpp
    Shading/ShadingSpectrumModel.hpp
    Shading/Whitted.cpp
    Shading/Whitted.hpp
    Shading/WhittedBRDF.cpp
    Shading/WhittedBRDF.hpp
    Textures/lodepng/lodepng.cpp
    Textures/lodepng/lodepng.h
    Textures/ProceduralTextures/BumpMapping/BumpMap.cpp
    Textures/ProceduralTextures/BumpMapping/BumpMap.hpp
    Textures/ProceduralTextures/PerlinNoise/PerlinNoise.cpp
    Textures/ProceduralTextures/PerlinNoise/PerlinNoise.hpp
    Textures/ProceduralTextures/PerlinTextures/Marble/MarbleTexture.cpp
    Textures/ProceduralTextures/PerlinTextures/Marble/MarbleTexture.hpp
    Textures/ProceduralTextures/PerlinTextures/Turbulence/TurbulenceTexture.cpp
    Textures/ProceduralTextures/PerlinTextures/Turbulence/TurbulenceTexture.hpp
    Textures/ProceduralTextures/PerlinTextures/PerlinTexture.cpp
    Textures/ProceduralTextures/PerlinTextures/PerlinTexture.hpp
    Textures/Texture.cpp
    Textures/Texture.hpp
    Tracers/PathTracer.cpp
    Tracers/PathTracer.hpp
    Tracers/Tracer.cpp
    Tracers/Tracer.hpp
    Tracers/TracerModelFactory.cpp
    Tracers/TracerModelFactory.hpp
    Tracers/TracerModelType.hpp
    Tracers/TracerRGB.cpp
    Tracers/TracerRGB.hpp
    Tracers/TracerSpectrum.cpp
    Tracers/TracerSpectrum.hpp
    Utils/PathReader.cpp
    Utils/PathReader.hpp
    Utils/StringUtils.cpp
    Utils/StringUtils.hpp
    Constants.hpp
    SCLT.cpp
    SCLT.hpp
    Spectrum.hpp
    main.cpp
    UtilsCommandLine/pch.cpp
    UtilsCommandLine/pch.h)

#Include directories
include_directories(.)
include_directories(Camera)
include_directories(Color)
include_directories(Color/CIEColorSpaces)
include_directories(Color/CRI)
include_directories(Lights)
include_directories(Math)
include_directories(Objects)
include_directories(Objects/BRDF)
include_directories(Objects/BRDF/EmpiricalModel)
include_directories(Objects/BRDF/PhysicalModel)
include_directories(Objects/Material)
include_directories(Objects/ObjParser)
include_directories(Objects/Scene)
include_directories(Objects/Scene/tinyxml2)
include_directories(Objects/Skyboxes)
include_directories(Rays)
include_directories(Shading)
include_directories(Textures)
include_directories(Textures/lodepng)
include_directories(Textures/ProceduralTextures)
include_directories(Textures/ProceduralTextures/BumpMapping)
include_directories(Textures/ProceduralTextures/PerlinNoise)
include_directories(Textures/ProceduralTextures/PerlinTextures)
include_directories(Textures/ProceduralTextures/PerlinTextures/Marble)
include_directories(Textures/ProceduralTextures/PerlinTextures/Turbulence)
include_directories(Tracers)
include_directories(Utils)
include_directories(UtilsCommandLine)

#Create executable
add_executable(SpectralClaraLuxTracer ${SOURCE_FILES})

#Set output binary directory
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../..)
