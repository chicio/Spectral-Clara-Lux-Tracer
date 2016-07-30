//
//  String.cpp
//  Framework
//
//  Created by Fabrizio Duroni on 21/01/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"
#include "StringUtils.hpp"

std::vector<std::string> StringUtils::explode(const std::string &s, char delim) {
    
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        
        elems.push_back(item);
    }
    
    return elems;
}
