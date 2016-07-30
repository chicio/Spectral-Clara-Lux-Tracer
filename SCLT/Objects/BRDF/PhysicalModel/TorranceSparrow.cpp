//
//  TorranceSparrow.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 27/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "TorranceSparrow.hpp"
#include "Ray.hpp"
#include "Fresnel.hpp"


TorranceSparrow::TorranceSparrow(Spectrum<constant::spectrumSamples> reflectanceSpectrum,
                                 float refractiveIndex,
                                 float exponent) : BRDF(Specular),
                                                   reflectanceSpectrum{reflectanceSpectrum},
                                                   refractiveIndex{refractiveIndex},
                                                   exponent{exponent},
                                                   fresnel(refractiveIndex) {}

float TorranceSparrow::G(const Vector3D& wi, const Vector3D& wo, const Vector3D& wh, const Vector3D& normal) const {
    
    float normalDotWh = wh.dot(normal);
    float normalDotWo = wo.dot(normal);
    float normalDotWi = wi.dot(normal);
    float woDotWh = wo.dot(wh);
    
    float G = fminf(1.0f, std::fminf((2.0f * normalDotWh * normalDotWo)/woDotWh,
                                     (2.0f * normalDotWh * normalDotWi)/woDotWh));
    
    return G;
}

float TorranceSparrow::D(const Vector3D& wh, const Vector3D& normal) const {
    
    float cosThetaH = wh.dot(normal);
    float D = ((exponent + 2.0f) / (2.0f * constant::pi)) * powf(cosThetaH, exponent);
    
    return D;
}

Spectrum<constant::spectrumSamples> TorranceSparrow::calculateTorranceSparrow(const Vector3D& wi,
                                                                              const Vector3D& wo,
                                                                              const Vector3D& wh,
                                                                              const Vector3D& normal) const {
    
    float cosThetaO = wo.dot(normal);
    float cosThetaI = wi.dot(normal);
    
    if(cosThetaI <= 0.0f || cosThetaO <= 0.0f) {
        
        return Spectrum<constant::spectrumSamples>(0.0f);
    }
    
    float cosThetaH = wi.dot(wh);
    float reflectivePercentage = fresnel.dieletricReflectivePercentage(cosThetaH);
    float numerator = D(wh, normal) * G(wi, wo, wh, normal) * reflectivePercentage;
    float denominator = (4.0f * cosThetaI * cosThetaO);
    
    Spectrum<constant::spectrumSamples> torranceSparrow = reflectanceSpectrum * numerator / denominator;
    
    return torranceSparrow;
};

Spectrum<constant::spectrumSamples> TorranceSparrow::f(const Vector3D& wi,
                                                       const Vector3D& wo,
                                                       const Intersection& intersection) const {
    
    //Get half angle vector.
    Vector3D wh = wi + wo;
    wh.normalize();
    
    //Calculate torrance sparrow.
    Spectrum<constant::spectrumSamples> torranceSparrow = calculateTorranceSparrow(wi, wo, wh, intersection.normal);
    
    return torranceSparrow;
}

Spectrum<constant::spectrumSamples> TorranceSparrow::samplef(Vector3D* wi,
                                                             const Vector3D& wo,
                                                             const Intersection& intersection) const {

    float u1 = RandomNumberGenerator::instance().generateRandomFloat();
    float u2 = RandomNumberGenerator::instance().generateRandomFloat();

    //Sample half angle vector based on blinn distribution.
    float cosTheta = std::pow(u1, 1.0f/(exponent + 1));
    float sinTheta = sqrtf(std::fmaxf(0.0f, 1.0f - powf(cosTheta, 2.0f)));
    float phi = u2 * 2.0f * constant::pi;

    //Setup wh with the obtained sample coordinates.
    Vector3D wh(sinTheta * cosf(phi), cosTheta, sinTheta * sinf(phi));

    //Generate tangent space (local coordinates) using normal.
    Vector3D tangent;
    Vector3D bitangent;
    
    MathUtils::generateCoodinateSystem(intersection.normal, tangent, bitangent);
    
    //Convert sample in world coordinate, considering canonical base.
    Matrix m = Matrix::inverseChangeOfCoordinateSystemMatrix(tangent, intersection.normal, bitangent);
    wh = m * wh;
    
    //wo opposite to normal, so invert wh.
    if(wo.dot(intersection.normal) < 0.0f) {
        
        wh = wh * -1.0f;
    }
    
    //Calculate wi vector as a reflection of wo with respect to wh.
    *wi = Ray::reflectedRayDirection(wh, wo * -1.0f, wo.dot(wh) * -1.0f);
    
    //Calculate torrance sparrow.
    Spectrum<constant::spectrumSamples> torranceSparrow = calculateTorranceSparrow(*wi, wo, wh, intersection.normal);

    return torranceSparrow;
}

float TorranceSparrow::pdf(const Vector3D& wi, const Vector3D& wo, const Intersection& intersection) const{
    
    Vector3D wh = wi + wo;
    wh.normalize();
    
    float whDotwo = wh.dot(wo);
    
    if(whDotwo <= 0.0f) {
        
        return 0.0f;
    }
    
    float pdfNumerator = ((exponent + 1) * powf(intersection.normal.dot(wh), exponent));
    float pdfDenominator = (2.0f * constant::pi * 4.0f * whDotwo);
    float pdf = pdfNumerator / pdfDenominator;
    
    return pdf;
}
