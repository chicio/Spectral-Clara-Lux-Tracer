//
//  Utils.m
//  Spectral Clara Lux tracer
//
//  Created by Fabrizio Duroni on 08/07/15.
//  Copyright (c) 2015 Fabrizio Duroni. All rights reserved.
//

#import "Support.h"

@implementation Support

+ (NSDate *)currentTime:(NSString *)message {
    
    NSDate *date = [NSDate date];
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    dateFormatter.dateFormat = @"HH:mm:ss";
    [dateFormatter setTimeZone:[NSTimeZone systemTimeZone]];
    NSLog(@"%@: %@", message, [dateFormatter stringFromDate:date]);
    
    return date;
}

+ (NSString *)dateDifferenceBetween:(NSDate *)endDate andStartDate:(NSDate *)startDate {
    
    NSTimeInterval dateDifference = [startDate timeIntervalSinceDate:endDate];
    
    NSString *difference = [NSString stringWithFormat:@"%02li:%02li:%02li",
                                lround(floor(dateDifference / 3600.)) % 100,
                                lround(floor(dateDifference / 60.)) % 60,
                                lround(floor(dateDifference)) % 60];
    
    return difference;
}

@end