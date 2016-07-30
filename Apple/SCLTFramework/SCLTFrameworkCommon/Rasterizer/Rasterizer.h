//
//  Rasterizer.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 05/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#include <vector>
#include "Vector3D.hpp"
#import <Foundation/Foundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif

@interface Rasterizer : NSObject

#if TARGET_OS_IPHONE

/*!
 Rasterize a sequence of pixel to the screen as UIImage.

 @param pixelsColorData the color of each pixel of the image.
 @param height height of the image part to be rendered.
 @param width width of the image to be rendered.
 
 @returns an UIImage created from the sequence of pixel received.
 */
- (UIImage *)rasterize:(const std::vector<Vector3D>)pixelsColorData andHeight:(float)height andWidth:(float)width;

#else

/*!
 Rasterize a sequence of pixel to the screen as UIImage.
 
 @param pixelsColorData the color of each pixel of the image.
 @param height height of the image part to be rendered.
 @param width width of the image to be rendered.
 
 @returns an UIImage created from the sequence of pixel received.
 */
- (NSImage *)rasterize:(const std::vector<Vector3D>)pixelsColorData andHeight:(float)height andWidth:(float)width;

#endif

@end
