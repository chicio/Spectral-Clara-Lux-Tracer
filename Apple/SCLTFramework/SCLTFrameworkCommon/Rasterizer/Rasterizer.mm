//
//  Rasterizer.m
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 05/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#include "Constants.hpp"
#import "Rasterizer.h"

/// Number of bytes used to represent a pixel (RGBA).
const int bytesPerPixel = 4;
/// Bits used for each pixel array element.
const int bitsPerComponent = 8;

@interface Rasterizer() {

    /// Device dependent colorspace.
    CGColorSpaceRef _colorSpace;
}
@end

@implementation Rasterizer

- (instancetype)init
{
    self = [super init];

    if (self) {
        
        _colorSpace = CGColorSpaceCreateDeviceRGB();
    }
    
    return self;
}

#if TARGET_OS_IPHONE

- (UIImage *)rasterize:(const std::vector<Vector3D>)pixelsColorData andHeight:(float)height andWidth:(float)width {
    
    unsigned char *pixelData =  (unsigned char *) calloc(height * width * 4, sizeof(unsigned char));;

    for (std::vector<Vector3D>::size_type i = 0; i < pixelsColorData.size(); i++) {
        
        const size_t offset = i * bytesPerPixel;
        
        Vector3D colorPerPixel = pixelsColorData[i];
        
        pixelData[offset] = colorPerPixel.x; //red
        pixelData[offset+1] = colorPerPixel.y; //green
        pixelData[offset+2] =  colorPerPixel.z; //blue
        pixelData[offset+3] = 255; // alpha not considered.
    }
    
    //Create bitmap context.
    const size_t BytesPerRow = ((bitsPerComponent * width) / 8) * bytesPerPixel;
    CGContextRef gtx = CGBitmapContextCreate(pixelData,
                                             width,
                                             height,
                                             bitsPerComponent,
                                             BytesPerRow,
                                             _colorSpace,
                                             kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    
    //Create UIImage.
    CGImageRef toCGImage = CGBitmapContextCreateImage(gtx);
    UIImage *screenImage = [[UIImage alloc] initWithCGImage:toCGImage];
    
    //Invert y coordinate.
    screenImage = [UIImage imageWithCGImage:screenImage.CGImage
                                      scale:screenImage.scale
                                orientation:UIImageOrientationDownMirrored];
    
    CGImageRelease(toCGImage);
    CGContextRelease(gtx);
    free(pixelData);
    
    return screenImage;
}

#else

- (NSImage *)rasterize:(const std::vector<Vector3D>)pixelsColorData andHeight:(float)height andWidth:(float)width {
    
    unsigned char *pixelData =  (unsigned char *) calloc(height * width * 4, sizeof(unsigned char));;
    
    for (std::vector<Vector3D>::size_type i = 0; i < pixelsColorData.size(); i++) {
        
        const size_t offset = i * bytesPerPixel;
        
        Vector3D colorPerPixel = pixelsColorData[i];
        
        pixelData[offset] = colorPerPixel.x; //red
        pixelData[offset+1] = colorPerPixel.y; //green
        pixelData[offset+2] =  colorPerPixel.z; //blue
        pixelData[offset+3] = 255; // alpha not considered.        
    }
    
    //Create bitmap context.
    const size_t BytesPerRow = ((bitsPerComponent * width) / 8) * bytesPerPixel;
    CGContextRef gtx = CGBitmapContextCreate(pixelData,
                                             width,
                                             height,
                                             bitsPerComponent,
                                             BytesPerRow,
                                             _colorSpace,
                                             kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
    
    
    NSSize imageSize;
    imageSize.height = height;
    imageSize.width = width;
    
    //Create UIImage.
    CGImageRef toCGImage = CGBitmapContextCreateImage(gtx);
    NSImage *screenImage = [[NSImage alloc]initWithCGImage:toCGImage size:imageSize];
    
    CGImageRelease(toCGImage);
    CGContextRelease(gtx);
    free(pixelData);
    
    return [self flipImage:screenImage];
}

- (NSImage *)flipImage:(NSImage *)image {
    
    NSImage *existingImage = image;
    NSSize existingSize = [existingImage size];
    NSSize newSize = NSMakeSize(existingSize.width, existingSize.height);
    NSImage *flipedImage = [[NSImage alloc] initWithSize:newSize];

    [flipedImage lockFocus];
    [[NSGraphicsContext currentContext] setImageInterpolation:NSImageInterpolationHigh];
    
    NSAffineTransform *t = [NSAffineTransform transform];
    [t translateXBy:0.0 yBy:existingSize.height];
    [t scaleXBy:1.0 yBy:-1.0];
    [t concat];
    
    [existingImage drawAtPoint:NSZeroPoint
                      fromRect:NSMakeRect(0, 0, newSize.width, newSize.height)
                     operation:NSCompositeSourceOver
                      fraction:1.0];
    
    [flipedImage unlockFocus];
    
    return flipedImage;
}

#endif

@end
