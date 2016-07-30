//
//  SCLTFrameworkOSXTests.m
//  SCLTFrameworkOSXTests
//
//  Created by Fabrizio Duroni on 19/05/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#import <XCTest/XCTest.h>

#include "Constants.hpp"
#include "Illuminant.hpp"
#include "MacbethColorChecker.hpp"
#include "Spectrum.hpp"
#include "ColorRenderingIndex.hpp"
#include "ColorMatchingFunction.hpp"
#include "CIEXYZ.hpp"
#include "sRGB.hpp"

@interface SCLTFrameworkOSXTests : XCTestCase

@end

@implementation SCLTFrameworkOSXTests

- (void)setUp {

    [super setUp];
}

- (void)tearDown {

    [super tearDown];
}

/*!
 Test case 1: check CRI test samples.
 
 Check calculation of color rendering index using Test samples method.
 */
- (void)testCRISampleMethod {
    
    Spectrum<constant::spectrumSamples> spectrumfl4(Illuminant::fl4);
    ColorRenderingIndex cri;
    float criTestSample = cri.testSampleMethod(spectrumfl4);
    
    XCTAssertTrue(criTestSample >= 50.8f, @"Test case 1: CRI test samples method test failed - FAILED");
    XCTAssertTrue(criTestSample <= 51.2f, @"Test case 1: CRI test samples method test failed - FAILED");
}

/*!
 Test case 2: check CRI R96a.
 
 Check calculation of color rendering index using R96a.
 */
- (void)testCRIR96aMethod{
    
    Spectrum<constant::spectrumSamples> spectrumfl4(Illuminant::fl4);
    ColorRenderingIndex cri;
    float crir96a = cri.r96aMethod(spectrumfl4);
    
    //Less strict range for R96a.
    XCTAssertTrue(crir96a > 50.0f,  @"Test case 2: CRI R96a test failed - FAILED");
    XCTAssertTrue(crir96a < 60.0f,  @"Test case 2: CRI R96a test failed - FAILED");
}

/*!
 Test case 3: check tristimulus conversion.
 
 Check tristimulus values conversion.
 Data based on "RGB coordinates of the Macbeth ColorChecker", Danny Pascale, The Babel Color Company.
 BabelColor avg. without CAT.
 */
- (void)testTristimulusValuesConversion {
    
    const int colorToBeTested = 5;
    ColorMatchingFunction* colorMatchingFunction = new Standard2ObserverColorMatchingFunction();
    
    //Test main color from macbeth color checker (most used in scenes).
    Spectrum<constant::spectrumSamples> macbethSPD[colorToBeTested] = {
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::red),
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::yellow),
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::green),
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::blue),
        Spectrum<constant::spectrumSamples>(MacbethColorChecker::orange)
    };
    
    Vector3D macbethSRGB[colorToBeTested] = {
        Vector3D(176.0f,  48.0f,  56.0f),
        Vector3D(238.0f, 200.0f,  22.0f),
        Vector3D( 71.0f, 149.0f,  72.0f),
        Vector3D( 43.0f,  62.0f, 147.0f),
        Vector3D(220.0f, 123.0f,  45.0f)
    };
    
    //Consider a margin error during the conversion process.
    const float error = 5.0f;
    
    for (int i = 0; i < colorToBeTested; i++) {
        
        Spectrum<constant::spectrumSamples> d65(Illuminant::d65);
        Spectrum<constant::spectrumSamples> colorIlluminantProduct = macbethSPD[i] * d65;
    
        Vector3D tristimulus = CIE1931XYZ::tristimulusValues(colorIlluminantProduct, d65, colorMatchingFunction);
        Vector3D rgb = CIE1931XYZ::tristimulusTosRGB(tristimulus);
        
        //Apply sRGB gamma correction.
        sRGB::sRGBGammaCorrection(rgb, sRGBCompading);
        
        //Convert to standard 0 - 255 RGB value.
        sRGB::sRGBStandardRange(rgb);

        //R component.
        XCTAssertTrue(rgb.x < macbethSRGB[i].x + error,  @"Test case 3: tristimulus conversion R failed - FAILED");
        XCTAssertTrue(rgb.x > macbethSRGB[i].x - error,  @"Test case 3: tristimulus conversion R failed - FAILED");
        
        //G component.
        XCTAssertTrue(rgb.y < macbethSRGB[i].y + error,  @"Test case 3: tristimulus conversion G failed - FAILED");
        XCTAssertTrue(rgb.y > macbethSRGB[i].y - error,  @"Test case 3: tristimulus conversion G failed - FAILED");
        
        //B component.
        XCTAssertTrue(rgb.z < macbethSRGB[i].z + error,  @"Test case 3: tristimulus conversion B failed - FAILED");
        XCTAssertTrue(rgb.z > macbethSRGB[i].z - error,  @"Test case 3: tristimulus conversion B failed - FAILED");
    }
}

@end
