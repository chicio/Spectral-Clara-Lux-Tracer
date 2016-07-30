//
//  MeasuredBRDF.cpp
//  Framework
//
//  Created by Fabrizio Duroni on 19/01/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>

#include "SphericalCoordinate.hpp"
#include "Matrix.hpp"
#include "StringUtils.hpp"
#include "PathReader.hpp"
#include "Measured.hpp"

#ifndef __APPLE__
#undef max
#endif 

Measured::Measured(const char* filename, bool interpolated) : BRDF(Diffuse) {
    
    samplesInterpolated = interpolated;
    
    std::string path = PathReader::getPath("BRDFs", filename, "astm");
    
    std::ifstream brdfFile(path);
    
    //Ignore header file.
    for (int i = 0; i < 22; i++) {
        
        brdfFile.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    
    for(std::string line; getline(brdfFile,line);) {
        
        std::vector<std::string> lineExploded(StringUtils::explode(line, ','));
        
        //Setup sample coordinate position.
        float thetaI = std::stof(lineExploded[0]);
        float phiI = std::stof(lineExploded[1]);
        float thetaO = std::stof(lineExploded[2]);
        float phiO = std::stof(lineExploded[3]);
        
        Vector3D wi(sinf(thetaI) * cosf(phiI), cosf(thetaI), sinf(thetaI) * sinf(phiI));
        Vector3D wo(sinf(thetaO) * cosf(phiO), cosf(thetaO), sinf(thetaO) * sinf(phiO));
        
        Point3D samplePoint = marschnerBRDFMapping(wo, wi);
        
        //Setup spectrum data.
        lineExploded.erase(lineExploded.begin(),lineExploded.begin()+4);
        
        float spectrumSamples[31];
        
        for(std::vector<std::string>::size_type i = 0; i != lineExploded.size(); i++) {
            
            spectrumSamples[i] = std::stof(lineExploded[i]);
        }
        
        Spectrum<constant::spectrumSamples> spectrumResampled = generateSpectrumFromSample(400.0f,
                                                                                           700.0f,
                                                                                           10.0f,
                                                                                           spectrumSamples,
                                                                                           31);
        
        //Create sample.
        MeasuredBRDFSample sample;
        sample.coordinate = samplePoint;
        sample.spectrum = spectrumResampled;
        
        //Add sample.
        sampleBRDF.push_back(sample);
    }    
}

Spectrum<constant::spectrumSamples> Measured::generateSpectrumFromSample(float startSampleWavelenght,
                                                                         float endSampleWavelenght,
                                                                         float distanceBetweenSample,
                                                                         float* samples,
                                                                         int numberOfSamples) {
    
    Spectrum<constant::spectrumSamples> spectrumResampled;
    float currentWavelenght = constant::spectrumStartWavelenght;
    int currentSpectrumPosition = 0;
    
    if (startSampleWavelenght > constant::spectrumStartWavelenght) {
        
        float diffStartWavelenght = startSampleWavelenght - constant::spectrumStartWavelenght;
        float outOfBoundWalenghts = diffStartWavelenght / constant::spectrumWalenghtSampleDistance;
        float wavelenghtRange = constant::spectrumEndWalenght - constant::spectrumStartWavelenght;
        
        for (int i = 0; i < outOfBoundWalenghts; i++) {
            
            if(samplesInterpolated == true) {
                
                float diffCurrentAndStartWalenght = currentWavelenght - constant::spectrumStartWavelenght;
                spectrumResampled[i] = samples[0] * (diffCurrentAndStartWalenght / wavelenghtRange);
            }
            
            currentWavelenght = constant::spectrumStartWavelenght + (i + 1) * constant::spectrumWalenghtSampleDistance;
            currentSpectrumPosition++;
        }
    }
    
    for (; currentWavelenght <= endSampleWavelenght; currentWavelenght += constant::spectrumWalenghtSampleDistance) {
        
        int samplePosition = 0;
        float currentSampleWavelenght = 0;
        
        for (int i = 0; i < numberOfSamples; i++) {
            
            currentSampleWavelenght = startSampleWavelenght + i * distanceBetweenSample;
            
            if(currentSampleWavelenght >= currentWavelenght) {
                
                break;
            }
            
            samplePosition++;
        }
        
        if(currentSampleWavelenght == currentWavelenght) {
            
            //No need to interpolate.
            spectrumResampled[currentSpectrumPosition] = samples[samplePosition];
        } else if(samplesInterpolated == true) {
            
            //Interpolate between the last two wavelenght.
            float diffCurrentWavelenghtAndDistanceSample = currentSampleWavelenght - distanceBetweenSample;
            float numeratorPreviousSample = 1.0f - (currentWavelenght - diffCurrentWavelenghtAndDistanceSample);
            float numeratorNextSample = currentWavelenght - diffCurrentWavelenghtAndDistanceSample;
            float denominator = currentSampleWavelenght - diffCurrentWavelenghtAndDistanceSample;
            float previousInterpolationFactor = 1.0f - (numeratorPreviousSample / denominator);
            float nextInterpolationFactor = numeratorNextSample / denominator;
            
            float previousSampleInterpolated = samples[samplePosition - 1] * previousInterpolationFactor;
            float nextSampleInterpolated = samples[samplePosition] * nextInterpolationFactor;
            
            spectrumResampled[currentSpectrumPosition] = previousSampleInterpolated + nextSampleInterpolated;
        }
        
        currentSpectrumPosition++;
    }
    
    
    return spectrumResampled;
}

Point3D Measured::marschnerBRDFMapping(const Vector3D &wo, const Vector3D &wi) const {
    
    float cosI = SphericalCoordinate::cosThetaInTangentSpace(wi);
    float cosO = SphericalCoordinate::cosThetaInTangentSpace(wo);
    float sinI = SphericalCoordinate::sinThetaInTangentSpace(wi);
    float sinO = SphericalCoordinate::sinThetaInTangentSpace(wo);
    
    float diffPhi = SphericalCoordinate::phi(wi) - SphericalCoordinate::phi(wo);
    
    if (diffPhi < 0.0f) {
        
        diffPhi += 2.0f * constant::pi;
    }
    
    if (diffPhi >= 2.0f * constant::pi) {
        
        diffPhi -= 2.0f * constant::pi;
    }
    
    if (diffPhi > constant::pi) {
        
        diffPhi = 2.0f * constant::pi - diffPhi;
    }
    
    float cosIcosO = cosI * cosO;
    
    if(cosIcosO < 0.0f) {
        
        return Point3D(0.0f, 0.0f, 0.0f);
    }
    
    return Point3D(sinI * sinO, cosIcosO, diffPhi / constant::pi);
}

Spectrum<constant::spectrumSamples> Measured::f(const Vector3D& wi,
                                                const Vector3D& wo,
                                                const Intersection& intersection) const {
    
    //Tangent space
    Vector3D tangent = intersection.normal.cross(wi);
    Vector3D bitangent = tangent.cross(intersection.normal);
    tangent.normalize();
    bitangent.normalize();
    
    //Change of coordinate
    Matrix m = Matrix::changeOfCoordinateSystemMatrix(bitangent, intersection.normal, tangent);
    
    Vector3D wiInTangentSpace = m * wi;
    Vector3D woInTangentSpace = m * wo;
    
    Point3D pointFromVectors = marschnerBRDFMapping(woInTangentSpace, wiInTangentSpace);
    
    int numberOfSampleFounded = 0;
    int maxNumberOfSample = 2;
    float maxDistanceSquare = 5.0f;
    float distanceSquareLimit = 0.01f;
    float sumWeights = 0.0f;
    
    Spectrum<constant::spectrumSamples> spectrum;
    
    while (true) {
        
        for(std::vector<std::string>::size_type i = 0; i != sampleBRDF.size(); i++) {
            
            float distanceSquared = Point3D::distanceSquared(sampleBRDF[i].coordinate, pointFromVectors);
            
            if(distanceSquared < distanceSquareLimit) {
                
                float weight = expf(-100.0f * distanceSquared);
                spectrum = spectrum + sampleBRDF[i].spectrum * weight;
                sumWeights += weight;
                numberOfSampleFounded++;
            }
        }
        
        if(numberOfSampleFounded > maxNumberOfSample || distanceSquareLimit > maxDistanceSquare) {

            //Normalize spectrum
            if(sumWeights > 0.0f) {
                
                spectrum = spectrum.clamp() / sumWeights;
            }
            
            break;
        }
        
        distanceSquareLimit = distanceSquareLimit * 2.0f;
    }
    
    return spectrum;
}

Spectrum<constant::spectrumSamples> Measured::samplef(Vector3D* wi,
                                                      const Vector3D& wo,
                                                      const Intersection& intersection) const {
    
    *wi = cosineWeightedHemisphereBRDFDirectionSampling(intersection);

    Spectrum<constant::spectrumSamples> spectrum = f(*wi, wo, intersection);
    
    return spectrum;
}

float Measured::pdf(const Vector3D& wi, const Vector3D& wo, const Intersection& intersection) const {
    
    float pdf = (fabsf(wi.dot(intersection.normal))/constant::pi);

    return pdf;
}
