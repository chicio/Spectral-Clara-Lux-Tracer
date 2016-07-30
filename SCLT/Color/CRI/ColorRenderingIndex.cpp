//
//  ColorRenderingIndex.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 21/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"

#include <stdio.h>
#include <math.h>

#include "TestColorSamples.hpp"
#include "MacbethColorChecker.hpp"
#include "Illuminant.hpp"
#include "Vector3D.hpp"
#include "CIEXYZ.hpp"
#include "CIEUCS.hpp"
#include "CIEUVW.hpp"
#include "CIELab.hpp"
#include "ChromaticAdaptationTransform.hpp"
#include "ColorMatchingFunction.hpp"
#include "ColorRenderingIndex.hpp"

float ColorRenderingIndex::testSampleMethod(Spectrum<constant::spectrumSamples>& spectrumTestLight) const {
    
    //Convert test light spectrum to CIE XYZ 1931.
    ColorMatchingFunction* colorMatchingFunction = new Standard2ObserverColorMatchingFunction();
    Vector3D tristimulusTestLight = CIE1931XYZ::tristimulusValuesForEmissiveSource(spectrumTestLight,
                                                                                   colorMatchingFunction);
    
    //Convert test light tristimulus to light xy chromaticity values.
    Vector3D chromaticityTestLight = CIE1931XYZ::chromaticityValues(tristimulusTestLight);
    
    //Convert test light xy chromaticity values to CIE 1960 UCS chromaticity.
    CIEUCSChromaticities chromaticityUCSTestLight = CIEUCS::chromaticity(chromaticityTestLight);
    
    //Calculate CCT and CIE 1960 UCS chromaticity approximation for reference illuminant.
    float CCT = calculateCCTUsingMcCamyAlgorithm(chromaticityTestLight);
    CIEUCSChromaticities chromaticityUCSRefLight = CIEUCS::chromaticityForBlackBodyUsingCCT(CCT);
    
    //If CCT < 5000 K calculate black body spectrum else use d65.
    Spectrum<constant::spectrumSamples> spectrumReferenceLight;
    
    if(CCT < 5000.0f) {
        spectrumReferenceLight = blackBodySpectrum(CCT);
    } else {
        spectrumReferenceLight = Spectrum<constant::spectrumSamples>(Illuminant::d65);
    }
    
    //Load eight munsell test sample spectrum.
    Spectrum<constant::spectrumSamples> testSampleColor[8] = {
        Spectrum<constant::spectrumSamples>(testColorSamples::munsellTsc01),
        Spectrum<constant::spectrumSamples>(testColorSamples::munsellTsc02),
        Spectrum<constant::spectrumSamples>(testColorSamples::munsellTsc03),
        Spectrum<constant::spectrumSamples>(testColorSamples::munsellTsc04),
        Spectrum<constant::spectrumSamples>(testColorSamples::munsellTsc05),
        Spectrum<constant::spectrumSamples>(testColorSamples::munsellTsc06),
        Spectrum<constant::spectrumSamples>(testColorSamples::munsellTsc07),
        Spectrum<constant::spectrumSamples>(testColorSamples::munsellTsc08),
    };
    
    CIEUVWCoordinates cieUVWcoorIlluminantRef[8];
    CIEUVWCoordinates cieUVWcoorIlluminantF4[8];
    float deltaEi[8];
    
    for (int i = 0; i < 8; i++) {
        
        //Calcuate CIE UVW for all test sample under REFERENCE illuminant.
        Spectrum<constant::spectrumSamples> testSampleRefLight = testSampleColor[i] * spectrumReferenceLight;
        Vector3D tristimulusTestSampleRefLight = CIE1931XYZ::tristimulusValues(testSampleRefLight,
                                                                               spectrumReferenceLight,
                                                                               colorMatchingFunction);
        
        CIEUCSChromaticities ucsTestSampleRefLight = CIEUCS::chromaticityFromTristimulus(tristimulusTestSampleRefLight);
        ucsTestSampleRefLight = ChromaticAdaptationTransform::vonKries(chromaticityUCSTestLight,
                                                                       chromaticityUCSRefLight,
                                                                       ucsTestSampleRefLight);

        CIEUVWCoordinates objectCIEUVWReferenceLight = CIEUVW::UVWValues(ucsTestSampleRefLight,
                                                                         chromaticityUCSRefLight,
                                                                         tristimulusTestSampleRefLight);
        cieUVWcoorIlluminantRef[i] = objectCIEUVWReferenceLight;
        
        //Calculate CIE UVW for all test sample under TEST illuminant.
        Spectrum<constant::spectrumSamples> testColorTestLight = testSampleColor[i] * spectrumTestLight;
        Vector3D tristimulusTestSampleTestLight = CIE1931XYZ::tristimulusValues(testColorTestLight,
                                                                                spectrumTestLight,
                                                                                colorMatchingFunction);
        
        CIEUCSChromaticities ucsTestSampleTestLight = CIEUCS::chromaticityFromTristimulus(tristimulusTestSampleTestLight);
        ucsTestSampleTestLight = ChromaticAdaptationTransform::vonKries(chromaticityUCSTestLight,
                                                                        chromaticityUCSRefLight,
                                                                        ucsTestSampleTestLight);
        
        CIEUVWCoordinates objectCIEUVWTestLight = CIEUVW::UVWValues(ucsTestSampleTestLight,
                                                                    chromaticityUCSRefLight,
                                                                    tristimulusTestSampleTestLight);
        cieUVWcoorIlluminantF4[i] = objectCIEUVWTestLight;
        
        //Calculate euclidean distance between pair of coordinate.
        deltaEi[i] = sqrtf(powf(cieUVWcoorIlluminantRef[i].U - cieUVWcoorIlluminantF4[i].U, 2.0f) +
                           powf(cieUVWcoorIlluminantRef[i].V - cieUVWcoorIlluminantF4[i].V, 2.0f) +
                           powf(cieUVWcoorIlluminantRef[i].W - cieUVWcoorIlluminantF4[i].W, 2.0f));
    }
    
    //Calculate special CRI (one for each sample).
    float specialCRIi[8];
    float sumSpecialCRIi = 0.0f;
    
    for (int i = 0; i < 8; i++) {
        
        specialCRIi[i] = 100.0f - 4.6f * deltaEi[i];
        sumSpecialCRIi += specialCRIi[i];
    }
    
    //Calculate CRI as arithmetic mean of the special CRIs.
    float CRI = sumSpecialCRIi/8.0f;
    
    //Clear pointers.
    delete colorMatchingFunction;
    
    return CRI;
}

float ColorRenderingIndex::r96aMethod(Spectrum<constant::spectrumSamples>& spectrumTestLight) const {
    
    ColorMatchingFunction* colorMatchingFunction = new Standard2ObserverColorMatchingFunction();
    
    //Convert test light spectrum to CIE XYZ 1931.
    Vector3D tristimulusTestLight = CIE1931XYZ::tristimulusValuesForEmissiveSource(spectrumTestLight,
                                                                                   colorMatchingFunction);
    
    //Convert test light tristimulus to light xy chromaticity values.
    Vector3D chromaticityValuesTestLight = CIE1931XYZ::chromaticityValues(tristimulusTestLight);
    
    //Calculate CCT and CIE 1960 UCS chromaticity approximation for reference illuminant.
    float CCT = calculateCCTUsingMcCamyAlgorithm(chromaticityValuesTestLight);
    
    //Calculate reference light choosing between 6 predefined reference.
    //Some CCT:
    // - d65 6504K
    // - d50 5003K
    float cctReferenceIlluminant[6] = {
        2700.0f,
        2950.0f,
        3450.0f,
        4200.0f,
        5003.0f,
        6504.0f
    };
    
    float cctDifferences[6] = {
        fabsf(cctReferenceIlluminant[0] - CCT),
        fabsf(cctReferenceIlluminant[1] - CCT),
        fabsf(cctReferenceIlluminant[2] - CCT),
        fabsf(cctReferenceIlluminant[3] - CCT),
        fabsf(cctReferenceIlluminant[4] - CCT),
        fabsf(cctReferenceIlluminant[5] - CCT),
    };
    
    Spectrum<constant::spectrumSamples> referencePredefinedIlluminant[6] = {
        blackBodySpectrum(cctReferenceIlluminant[0]),
        blackBodySpectrum(cctReferenceIlluminant[1]),
        blackBodySpectrum(cctReferenceIlluminant[2]),
        blackBodySpectrum(cctReferenceIlluminant[3]),
        Spectrum<constant::spectrumSamples>(Illuminant::d50),
        Spectrum<constant::spectrumSamples>(Illuminant::d65)
    };
    
    int cctPosition = -1;
    float minCCTDifference = 0.0f;
    
    for (int i = 0; i < 6; i++) {

        if (cctPosition == -1 || cctDifferences[i] < minCCTDifference) {
            minCCTDifference = cctDifferences[i];
            cctPosition = i;
        }
    }

    Spectrum<constant::spectrumSamples> spectrumReferenceLight = referencePredefinedIlluminant[cctPosition];
    
    //New test color samples from macbeth.
    Spectrum<constant::spectrumSamples> newTestColorSamples[10] = {
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::red),
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::orange),
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::yellow),
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::yellowGreen),
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::green),
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::cyan),
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::blue),
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::magenta),
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::lightSkin),
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::darkSkin)
    };
    
    Spectrum<constant::spectrumSamples> d65(Illuminant::d65);
    Vector3D tristimulusD65 = CIE1931XYZ::tristimulusValuesForEmissiveSource(d65, colorMatchingFunction);
    Vector3D chromaticityD65 = CIE1931XYZ::chromaticityValues(tristimulusD65);
    
    CIELabCoordinate cieLabSampleRefLight[10];
    CIELabCoordinate cieLabSampleTestLight[10];
    float deltaEi[10];
    
    for (int i = 0; i < 10; i++) {
        
        //Sample under REFERENCE light tristimulus value.
        Spectrum<constant::spectrumSamples> newTestSampleRefLight = newTestColorSamples[i] * spectrumReferenceLight;
        Vector3D tristimulusNewTestSampleRefLight = CIE1931XYZ::tristimulusValues(newTestSampleRefLight,
                                                                                             spectrumReferenceLight,
                                                                                             colorMatchingFunction);
        
        //Sample under REFERENCE light CIECAT94.
        tristimulusNewTestSampleRefLight = ChromaticAdaptationTransform::ciecat94(tristimulusNewTestSampleRefLight,
                                                                                  chromaticityValuesTestLight,
                                                                                  chromaticityD65,
                                                                                  tristimulusD65);
        
        //Sample under REFERENCE light conversion to CIELab.
        CIELabCoordinate labSampleRefLight = CIELab::LabValues(tristimulusNewTestSampleRefLight, tristimulusD65);
        cieLabSampleRefLight[i] = labSampleRefLight;
        
        //Sample under TEST light tristimulus value.
        Spectrum<constant::spectrumSamples> newTestSampleTestLight = newTestColorSamples[i] * spectrumTestLight;
        Vector3D tristimulusNewTestSampleTestLight = CIE1931XYZ::tristimulusValues(newTestSampleTestLight,
                                                                                   spectrumTestLight,
                                                                                   colorMatchingFunction);

        //Sample under TEST light CIECAT94.
        tristimulusNewTestSampleTestLight = ChromaticAdaptationTransform::ciecat94(tristimulusNewTestSampleTestLight,
                                                                                   chromaticityValuesTestLight,
                                                                                   chromaticityD65,
                                                                                   tristimulusD65);

        //Sample under TEST light conversion to CIELab.
        CIELabCoordinate labSampleTestLight = CIELab::LabValues(tristimulusNewTestSampleTestLight, tristimulusD65);
        cieLabSampleTestLight[i] = labSampleTestLight;
        
        //Calculate euclidean distance between pair of coordinate.
        deltaEi[i] = sqrtf(powf(cieLabSampleRefLight[i].L - cieLabSampleTestLight[i].L, 2.0f) +
                           powf(cieLabSampleRefLight[i].a - cieLabSampleTestLight[i].a, 2.0f) +
                           powf(cieLabSampleRefLight[i].b - cieLabSampleTestLight[i].b, 2.0f));
    }
    
    //Calculate special CRI (one for each sample).
    float specialCRIi[10];
    float sumSpecialCRIi = 0.0f;
    
    for (int i = 0; i < 10; i++) {
        
        specialCRIi[i] = 100.0f - 3.248f * deltaEi[i];
        sumSpecialCRIi += specialCRIi[i];
    }
    
    //Calculate CRI as arithmetic mean of the special CRIs.
    float CRIr96a = sumSpecialCRIi/10.0f;
    
    //Clear pointers.
    delete colorMatchingFunction;
    
    return CRIr96a;
}

float ColorRenderingIndex::calculateCCTUsingMcCamyAlgorithm(Vector3D chromaticityValuesLight) const {
    
    float n = (chromaticityValuesLight.x - 0.3320f) / (chromaticityValuesLight.y - 0.1858f);
    float CCT = -449.0f * powf(n, 3.0f) + 3525.0f * powf(n, 2.0f) - 6823.3f * n + 5520.33f;
    
    return CCT;
}

Spectrum<constant::spectrumSamples> ColorRenderingIndex::blackBodySpectrum(float CCT) const {
    
    //Compute black body spectrum from CCT.
    float samplesBlackBody[constant::spectrumSamples];
    
    float h = 6.6260693e-34f; //Planck constant's.
    float c = 299792458.0f;   //Speed of light.
    float k = 1.3806505e-23f; //Boltzmann's constant.
    
    float c1 = 2.0f * constant::pi * h * powf(c, 2.0f);
    float c2 = h * c / k;
    
    float wavelenght = constant::spectrumStartWavelenght;
    
    for (int i = 0; i < constant::spectrumSamples; i++) {
        
        float wavelenghtMeter = wavelenght * 1e-9f;
        samplesBlackBody[i] = (c1 / powf(wavelenghtMeter, 5.0f)) * (1.0f / (exp(c2/(wavelenghtMeter * CCT)) - 1.0f));
        wavelenght = wavelenght + constant::spectrumWalenghtSampleDistance;
    }
    
    Spectrum<constant::spectrumSamples> spectrum(samplesBlackBody);
    
    return spectrum;
}
