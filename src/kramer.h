#ifndef __KRAMER_H3D
#define __KRAMER_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

// LIB3D is defined for the DLL makefile, not defined for apps
#if defined(LIB3D)
#define LIBInterface __declspec(dllexport)
#else                                                 
#define LIBInterface __declspec(dllimport)
#endif                                                

// Macros and defines used throughout
#include "Utils\Utility.h"

// Predeclare all node classes
#include "Classes.h"

#endif