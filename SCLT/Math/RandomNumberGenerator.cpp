//
//  RandomNumberGenerator.cpp
//  SCLTFramework
//
//  Created by Fabrizio Duroni on 27/02/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "RandomNumberGenerator.hpp"

RandomNumberGenerator::RandomNumberGenerator() {
 
    //Seed random generator.
    unsigned seed = (int)std::chrono::system_clock::now().time_since_epoch().count();
    generator.seed(seed);
}

float RandomNumberGenerator::generateRandomFloat() {
    
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    float random = distribution(generator);
    
    return random;
}
