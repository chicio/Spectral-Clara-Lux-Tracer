//
//  PathReader.hpp
//  Framework
//
//  Created by Fabrizio Duroni on 21/01/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#ifndef PathReader_hpp
#define PathReader_hpp

#include <string>

class PathReader {
public:
    
    /*!
     Read path of file on multiple platform.
     
     @param containerFolder container folder.
     @param fileName file name.
     @param extension extension of the file.
     
     @returns pah to the file.
     */
    static std::string getPath(std::string containerFolder, const char* fileName, const char* extension);
};

#endif /* PathReader_hpp */
