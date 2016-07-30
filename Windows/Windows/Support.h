//
// Support.h
// Declaration of the Support class.
//
// Created by Fabrizio Duroni on 06/01/16.
// Copyright © 2015 Fabrizio Duroni. All rights reserved.
//

#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <string>

namespace SpectralClaraLuxTracer {

	class Support {
	public:

		/*!
		Format specifier.

		@see http://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf

		@param format string to be formatted.
		@param args arguments.

		@returns string with format.
		*/
		template<typename ... Args> static std::string stringFormat(const std::string& format, Args ... args) {

			size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1;
			std::unique_ptr<char[]> buf(new char[size]);
			snprintf(buf.get(), size, format.c_str(), args ...);
			return std::string(buf.get(), buf.get() + size - 1); 
		}
	};
}
