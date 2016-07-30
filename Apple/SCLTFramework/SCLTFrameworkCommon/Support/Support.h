//
//  Utils.h
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 08/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Support : NSObject

/*!
 Print the current time with a message associated.
 
 @param message a message to be concatenated with the time.
 */
+ (NSDate *)currentTime:(NSString *)message;

/*!
 Calculate date difference as string.
 
 @param endDate end date.
 @param startDate start date.
 
 @returns difference as string.
 */
+ (NSString *)dateDifferenceBetween:(NSDate *)endDate andStartDate:(NSDate *)startDate;

@end