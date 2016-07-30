//
//  PathReader.cpp
//  Framework
//
//  Created by Fabrizio Duroni on 21/01/16.
//  Copyright © 2016 Fabrizio Duroni. All rights reserved.
//

#include "pch.h"

#include <iostream>
#include <fstream>

#if defined(__APPLE__) && !defined(COMMAND_LINE)
#import <Foundation/Foundation.h>
#if TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR
#include <pwd.h>
#endif
#endif

#if defined(_WIN32) && !defined(COMMAND_LINE)
using namespace Windows::Storage;
#endif

#include "PathReader.hpp"

std::string PathReader::getPath(std::string containerFolder, const char* fileName, const char* extension) {
    
#if defined(__APPLE__) && !defined(COMMAND_LINE)
    
    std::string filePathOfUser;
    
#if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
    
    CFURLRef ipadHomeDir = CFCopyHomeDirectoryURL();
    std::string ipadHomeDirStr(CFStringGetCStringPtr(CFURLGetString(ipadHomeDir),kCFStringEncodingUTF8));
    filePathOfUser = ipadHomeDirStr + "/Documents/";
    filePathOfUser.erase(0, 7);
    
#endif
    
#if TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_OS_SIMULATOR

    const char *userHomeChar = getpwuid(getuid())->pw_dir;
    filePathOfUser = userHomeChar;
    filePathOfUser = filePathOfUser + "/";
    
#endif
    
    //Search file in user home or app home directory for "Scenes" folder.
    filePathOfUser = filePathOfUser + "Scenes";
    
    if(!containerFolder.empty()) {
        
        filePathOfUser = filePathOfUser + "/" + containerFolder;
    }
    
    filePathOfUser = filePathOfUser + "/" + fileName + "."  + extension;
        
    //Test if file exists.
    std::ifstream infile(filePathOfUser.c_str());
    
    if(infile.good()) {
        
        std::cout << "User file: " << filePathOfUser << "\n";
        
        return filePathOfUser;
    }
    
    //Search in bundle (in default scenes and files).
    //Get file path using Core Foundation (opaque data type and pointer...).
    
    CFStringRef filenameCFString = CFStringCreateWithCString(NULL, fileName, kCFStringEncodingUTF8);
    CFStringRef extensionCFString = CFStringCreateWithCString(NULL, extension, kCFStringEncodingUTF8);
    
    //Get a reference to the main bundle.
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    
    //Get a reference to the file's URL.
    CFURLRef fileURL = CFBundleCopyResourceURL(mainBundle, filenameCFString, extensionCFString, NULL);
    
    if(!fileURL) {
        
        //File url is not valid, so return an empty path.
        return "";
    }
    
    //Convert the URL reference into a string reference.
    CFStringRef cfPath = CFURLCopyFileSystemPath(fileURL, kCFURLPOSIXPathStyle);
    
    //Get the system encoding method.
    CFStringEncoding encodingMethod = CFStringGetSystemEncoding();
    
    //Convert the string reference into a C string.
    const char* path = CFStringGetCStringPtr(cfPath, encodingMethod);
    
    std::string filePath(path);
    
    std::cout << "Bundle file: " << filePath << "\n";
    
#endif
    
#if defined(_WIN32) && !defined(COMMAND_LINE)

	//Search file in application data folder directory for "Scenes" folder.
	auto applicationDataFolder = ApplicationData::Current->LocalFolder->Path;
	std::wstring applicationDataFolderPath = std::wstring(applicationDataFolder->Data());
	std::string appDataFolder(applicationDataFolderPath.begin(), applicationDataFolderPath.end());

	std::string filePathOfUser = appDataFolder + "\\Scenes";

	if (!containerFolder.empty()) {

		filePathOfUser = filePathOfUser + "\\" + containerFolder;
	}

	filePathOfUser = filePathOfUser + "\\" + fileName + "." + extension;

	//Search file in application main folder directory.
	//Test if file exists.
	std::ifstream infile(filePathOfUser.c_str());

	if (infile.good()) {

		return filePathOfUser;
	}

    //Append extension to file name.
    std::string fn(fileName);
	fn.append(".");
    fn.append(extension);
    
    //Get app main folder app location info.
    auto installedLocationInfo = Windows::ApplicationModel::Package::Current->InstalledLocation->Path;
    
    //Get location path and convert it wstring->string.
    std::wstring appPath = std::wstring(installedLocationInfo->Data());
    std::string filePath(appPath.begin(), appPath.end());
    
	filePath.append("\\");
    filePath.append(fn);
        
#endif

#ifdef COMMAND_LINE

    std::string filePath(fileName);

#endif

    return filePath;
}
