//
//  String.hpp
//  Framework
//
//  Created by Fabrizio Duroni on 21/01/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#ifndef StringUtils_hpp
#define StringUtils_hpp

#include <sstream>
#include <vector>
#include <string>

class StringUtils {
public:

    /*!
     Explode a string.
     
     @param string string to be exploded.
     @param separator separator char.
     
     @returns string exploded in a vector.
     */
    static std::vector<std::string> explode(const std::string &s, char delim);
};

#endif /* String_hpp */
