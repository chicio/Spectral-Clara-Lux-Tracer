//
//  RandomNumberGenerator.hpp
//  SCLTFramework
//
//  Created by Fabrizio Duroni on 27/02/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#ifndef RandomNumberGenerator_hpp
#define RandomNumberGenerator_hpp

#include <random>
#include <chrono>

class RandomNumberGenerator {
private:
    
    /// Generator used to get random double.
    std::default_random_engine generator;
    
    /*!
     Private constructor for random generator singleton.
     */
    RandomNumberGenerator();
    
public:
    
    static RandomNumberGenerator& instance() {
        
        static RandomNumberGenerator rngInstance;
        return rngInstance;
    }
    
    /*!
     Generate a random float
     */
    float generateRandomFloat();
};

#endif /* RandomNumberGenerator_hpp */
