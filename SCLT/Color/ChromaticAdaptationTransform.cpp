//
//  ChromaticAdaptationTransform.cpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 26/12/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "Spectrum.hpp"
#include "Illuminant.hpp"
#include "CIELab.hpp"
#include "ColorMatchingFunction.hpp"
#include "ChromaticAdaptationTransform.hpp"
#include "CIEXYZ.hpp"

CIEUCSChromaticities ChromaticAdaptationTransform::vonKries(const CIEUCSChromaticities& chromaticityTestLight,
                                                            const CIEUCSChromaticities& chromaticityRefLight,
                                                            const CIEUCSChromaticities& chromaticitySampleTestLight) {
    
    float cr = (4.0f - chromaticityRefLight.u - 10.0f * chromaticityRefLight.v) / chromaticityRefLight.v;
    float dr = (1.708f * chromaticityRefLight.v - 1.481f * chromaticityRefLight.u + 0.404f) / chromaticityRefLight.v;
    
    float ct = (4.0f - chromaticityTestLight.u - 10.0f * chromaticityTestLight.v) / chromaticityTestLight.v;
    float dt = (1.708f * chromaticityTestLight.v - 1.481f * chromaticityTestLight.u + 0.404f) / chromaticityTestLight.v;
    
    float ctiNumerator = (4.0f - chromaticitySampleTestLight.u - 10.0f * chromaticitySampleTestLight.v);
    float cti = ctiNumerator / chromaticitySampleTestLight.v;
    float dtiNumerator = (1.708f * chromaticitySampleTestLight.v - 1.481f * chromaticitySampleTestLight.u + 0.404f);
    float dti = dtiNumerator / chromaticitySampleTestLight.v;
    
    float uadaptNumerator = (10.872f + 0.404f * (cr/ct) * cti - 4.0f * (dr/dt) * dti);
    float uadaptDenominator = (16.518f + 1.481f * (cr/ct) * cti - (dr/dt) * dti);
    float uadapt = uadaptNumerator / uadaptDenominator;
    
    float vadaptNumerator = 5.520f;
    float vadaptDenominator = (16.518f + 1.481f * (cr/ct) * cti - (dr/dt) * dti);
    float vadapt = vadaptNumerator / vadaptDenominator;
    
    CIEUCSChromaticities adaptedCoordinates(uadapt, vadapt);
    
    return adaptedCoordinates;
}

Vector3D ChromaticAdaptationTransform::ciecat94(const Vector3D& tristimulus,
                                                const Vector3D& chromaticityTestLight,
                                                const Vector3D& chromaticityRefLight,
                                                const Vector3D& tristimulusTestLight) {
    
    //Convert to rgb.
    float R = 0.40024f * tristimulus.x + 0.70760f * tristimulus.y - 0.08081f * tristimulus.z;
    float G = -0.22630f * tristimulus.x + 1.16532f * tristimulus.y + 0.04570f * tristimulus.z;
    float B = 0.0f * tristimulus.x + 0.0f * tristimulus.y - 0.91822f * tristimulus.z;
    
    //Step 1: computes chromaticity correlates.
    
    float PtNumerator = (0.48105f * chromaticityTestLight.x + 0.78841f * chromaticityTestLight.y - 0.08081f);
    float Pt = PtNumerator / chromaticityTestLight.y;
    float QtNumerator = (-0.27200f * chromaticityTestLight.x + 1.11962f * chromaticityTestLight.y + 0.04570f);
    float Qt = QtNumerator / chromaticityTestLight.y;
    float St = 0.91822f * (1.0f - chromaticityTestLight.x - chromaticityTestLight.y) / chromaticityTestLight.y;
    
    float PrNumerator = (0.48105f * chromaticityRefLight.x + 0.78841f * chromaticityRefLight.y - 0.08081f);
    float Pr = PrNumerator / chromaticityRefLight.y;
    float QrNumerator = (-0.27200f * chromaticityRefLight.x + 1.11962f * chromaticityRefLight.y + 0.04570f);
    float Qr = QrNumerator / chromaticityRefLight.y;
    float Sr = 0.91822f * (1.0f - chromaticityRefLight.x - chromaticityRefLight.y) / chromaticityRefLight.y;
    
    //Step 2: compute coefficient fo adapting

    //Adapting luminance of the test field is a value that is not specified on any
    //CIE document. Use the same as for the reference light.
    float Lt = 63.66f;
    float D = 1.0f;
    CIELabCoordinate labSampleTestLight = CIELab::LabValues(tristimulus, tristimulusTestLight);
    float alpha = 0.1151f * log10f(Lt) + 0.0025f * (labSampleTestLight.L - 50.0f) + 0.22f * D + 0.51f;
    
    //Setp 3: compute adapting chromaticity correlates.
    
    float Padapting = alpha * Pt + (1.0f - alpha) * Pr;
    float Qadapting = alpha * Qt + (1.0f - alpha) * Qr;
    float Sadapting = alpha * St + (1.0f - alpha) * Sr;
    
    //Step 4: compute effective adapting response.
    
    float Lr = 63.66f;
        
    float Rt = Lt * Pt;
    float Gt = Lt * Qt;
    float Bt = Lt * St;
    
    float Rr = Lr * Pr;
    float Gr = Lr * Qr;
    float Br = Lr * Sr;
    
    //Step 5: compute exponent of red, blue and green transformation.
    
    float betaRt = (6.469f + 6.326f * powf(Rt, 0.4495f)) / (6.469f + powf(Rt, 0.4495f));
    float betaGt = (6.469f + 6.326f * powf(Gt, 0.4495f)) / (6.469f + powf(Gt, 0.4495f));
    float betaRr = (6.469f + 6.326f * powf(Rr, 0.4495f)) / (6.469f + powf(Rr, 0.4495f));
    float betaGr = (6.469f + 6.326f * powf(Gr, 0.4495f)) / (6.469f + powf(Gr, 0.4495f));
    float betaBt = 0.7844f * (0.8414f + 8.091f  * powf(Bt, 0.5128f)) / (0.8414f + powf(Bt, 0.5128f));
    float betaBr = 0.7844f * (0.8414f + 8.091f  * powf(Br, 0.5128f)) / (0.8414f + powf(Br, 0.5128f));
    
    //Step 6: calculate K.

    float n = 0.1f;
    float Y = 0.5f;
    
    float pFirstTerm = powf(((Y * Padapting + n) / (20.0f * Padapting + n)), 2.0f * betaRt / 3.0f);
    float pSecondTerm = powf(((Y * Qadapting + n) / (20.0f * Qadapting + n)), 2.0f * betaGt / 3.0f);
    float p = pFirstTerm * pSecondTerm;
    
    float qFirstTerm = powf(((Y * Pr + n) / (20.0f * Pr + n)), 2.0f * betaRr / 3.0f) ;
    float qSecondTerm = powf(((Y * Qr + n) / (20.0f * Qr + n)), 2.0f * betaGr / 3.0f);
    float q = qFirstTerm * qSecondTerm;
    
    float K = p / q;
    
    //Calculate adaptation.
    float powRTristimulus = powf(((R + n) / tristimulus.y * Padapting + n), betaRt / betaRr);
    float Rc = (tristimulus.y * Pr + n) * powf(K, 1.0f / betaRr) * powRTristimulus - n;
    float powGTristimulus = powf(((G + n) / tristimulus.y * Qadapting + n), betaGt / betaGr);
    float Gc = (tristimulus.y * Qr + n) * powf(K, 1.0f / betaGr) * powGTristimulus - n;
    float powBTristimulus = powf(((B + n) / tristimulus.y * Sadapting + n), betaBt / betaBr);
    float Bc = (tristimulus.y * Sr + n) * powf(K, 1.0f / betaBr) * powBTristimulus - n;
    
    float Xr = 1.85995f * Rc - 1.12939f * Gc + 0.21990f * Bc;
    float Yr = 0.36119f * Rc + 0.63881f * Gc + 0.0f * Bc;
    float Zy = 0.0f * Rc + 0.0f * Gc + 1.08906f * Bc;
    
    Vector3D tristimulusAdapted;
    tristimulusAdapted.x = isnan(Xr) ? 0.0f : Xr;
    tristimulusAdapted.y = isnan(Yr) ? 0.0f : Yr;
    tristimulusAdapted.z = isnan(Zy) ? 0.0f : Zy;
    
    return tristimulusAdapted;
}
