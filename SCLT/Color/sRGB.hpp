//
//  ColorUtils.hpp
//  SCLTFramework
//
//  Created by Fabrizio Duroni on 17/03/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#ifndef sRGB_hpp
#define sRGB_hpp

#include "MathUtils.hpp"
#include "Vector3D.hpp"

typedef enum CompandingFunction {
    GammaCompanding,
    sRGBCompading
} CompandingFunction;

class sRGB {
public:
    
    /*!
     Apply gamma correction for sRGB using a standard gamma compading of 2.2, or use specific rgb compading function.
     
     @see Gamma http://www.brucelindbloom.com/WorkingSpaceInfo.html#Specifications
     @see https://it.wikipedia.org/wiki/Correzione_di_gamma     
     
     @param rgbColor color to which we apply the gamma correction.
     @param compadingFunction type of companding function to be applied.
     */
    inline static void sRGBGammaCorrection(Vector3D& rgbColor, CompandingFunction compadingFunction) {
        
        if (compadingFunction == GammaCompanding) {
            
            //Gamma approximation value for rgb = 2.2
            float power = 1.0f/2.2f;
            
            rgbColor.x = powf(rgbColor.x, power);
            rgbColor.y = powf(rgbColor.y, power);
            rgbColor.z = powf(rgbColor.z, power);
        } else {
            
            float power = 1.0f/2.4f;
            
            //sRGB companding function
            rgbColor.x = (rgbColor.x <= 0.0031308f ? 12.92f * rgbColor.x : 1.055f * powf(rgbColor.x, power) - 0.055f);
            rgbColor.y = (rgbColor.y <= 0.0031308f ? 12.92f * rgbColor.y : 1.055f * powf(rgbColor.y, power) - 0.055f);
            rgbColor.z = (rgbColor.z <= 0.0031308f ? 12.92f * rgbColor.z : 1.055f * powf(rgbColor.z, power) - 0.055f);
        }
    }
    
    /*!
     Convert RGB values in 0-1 range to RGB value in 0-255 range.
     
     @param rgbColor color to be converted in 0-255 range
     */
    inline static void sRGBStandardRange(Vector3D& rgbColor) {
        
        rgbColor.x *= 255;
        rgbColor.y *= 255;
        rgbColor.z *= 255;
        
        rgbColor.x = MathUtils::clamp(rgbColor.x, 0.0f, 255.0f);
        rgbColor.y = MathUtils::clamp(rgbColor.y, 0.0f, 255.0f);
        rgbColor.z = MathUtils::clamp(rgbColor.z, 0.0f, 255.0f);
        
        rgbColor.x = (std::isnan(rgbColor.x) ? 0.0f : rgbColor.x);
        rgbColor.y = (std::isnan(rgbColor.y) ? 0.0f : rgbColor.y);
        rgbColor.z = (std::isnan(rgbColor.z) ? 0.0f : rgbColor.z);
    }
};

#endif /* sRGB_hpp */
