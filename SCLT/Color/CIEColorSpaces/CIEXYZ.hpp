//
//  CIEXYZ.hpp
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 14/11/15.
//  Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#ifndef CIEXYZ_hpp
#define CIEXYZ_hpp

#include "Vector3D.hpp"
#include "ColorMatchingFunction.hpp"
#include "Spectrum.hpp"

class CIE1931XYZ {
public:
    
    /*!
     Calculate tristimulus value given a color matching function and a spectrum 
     (the last one as a result of the product of an object spectrum and an illuminant
     spectrum). Result is given as a Vector3D, and is normalized with respect to 
     the illuminant spectrum.
     
     @param objectProductIlluminantSpectrum product between object SPD and illuminant SPD.
     @param illuminantSpectrum the SPD of the illuminant.
     @param color matching function.
     
     @returns a Vector3D that contains CIE XYZ values.
     */
    static Vector3D tristimulusValues(Spectrum<constant::spectrumSamples>& objectProductIlluminantSpectrum,
                                      Spectrum<constant::spectrumSamples>& illuminantSpectrum,
                                      const ColorMatchingFunction* colorMatchingFunction);

    /*!
     Calculate tristimulus value for a given EMISSIVE SOURCE given a color matching function and
     the source spectrum.
     
     @param illuminantSpectrum spectrum of the illuminant.
     @param color matching function.
     
     @returns a Vector3D that contains CIE XYZ values.
     */
    static Vector3D tristimulusValuesForEmissiveSource(Spectrum<constant::spectrumSamples>& illuminantSpectrum,
                                                       const ColorMatchingFunction* colorMatchingFunction);
    
    /*!
     Convert tristimulus values to chromaticity values.
     
     @returns chromaticity values.
     */
    static Vector3D chromaticityValues(Vector3D tristimulus);
    
    /*!
     Convert chromaticity values to tristimulus given Y component
     
     @param chromaticityValues chromaticity values.
     @param Y trisimulus Y original value.
     
     @returns the tristimulus values obtained.
     */
    static Vector3D tristimulusValues(Vector3D chromaticityValues, float Y);
    
    /*!
     Convert tristimulus values to sRGB.
     The method convert the tristimulus values received to sRGB.
     
     @see http://www.brucelindbloom.com/Eqn_XYZ_to_RGB.html
     @see http://www.brucelindbloom.com/Eqn_RGB_XYZ_Matrix.html
     @see "Physically based rendering" page 273.
        
     @param tristimulus vector of tristimulus values.
     @param compadingFunction the compading function selected.
     
     @returns Vector3D of sRGB values.
     */
    static Vector3D tristimulusTosRGB(const Vector3D& tristimulus);
};

#endif /* CIEXYZ_hpp */
