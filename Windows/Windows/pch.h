//
// pch.h
// Header for standard system include files.
//

//File used on windows to build precompiled header.
//On Apple platforms this source file is useless.
//I check on _MSC_VER to be sure we do all the stuff needed
//only when the system is compile for windows.

#ifdef _MSC_VER

#pragma once

#define _USE_MATH_DEFINES

#include <collection.h>
#include <ppltasks.h>

#include "App.xaml.h"

#endif