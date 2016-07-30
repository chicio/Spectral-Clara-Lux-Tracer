//
//  ProgressDelegate.m
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 08/01/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
 Protocol used in ray tracer to receive update
 on the status of the render. Only on apple platform.
 */
@protocol ProgressDelegate <NSObject>

@required
-(void)rayTracerProgressUpdate:(float)progress;

@end