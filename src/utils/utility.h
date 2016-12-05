#ifndef _ALLUTILS_H
#define _ALLUTILS_H
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  This software is provided 'as-is', without any express
//  or implied warranty.  In no event will the authors be
//  held liable for any damages arising from the use of
//  this software.
//
//  Permission is granted to anyone to use this software
//  for any purpose, including commercial applications, and
//  to alter it and redistribute it freely, subject to the
//  following restrictions:
//
//  1. The origin of this software must not be misrepresented;
//     you must not claim that you wrote the original software.
//     If you use this software in a product, an acknowledgment
//     in the product documentation would be appreciated but is
//     not required.
//  2. Altered source versions must be plainly marked as such,
//     and must not be misrepresented as being the original
//     software.
//  3. This notice may not be removed or altered from any
//     source distribution.
//----------------------------------------------------------------------

// LIBUTIL is defined in the DLL makefile, not defined for apps
//#if defined(LIBUTIL)
//#define UL_Interface __declspec(dllexport)
//#else // !LIBUTIL
//#define UL_Interface __declspec(dllimport)
// Include the library so user doesn't have to
//#ifdef _DEBUG
//#pragma comment(lib, "vrutilsd.lib")
//#else
//#pragma comment(lib, "vrutils.lib")
//#endif
//#endif

// Basic types
typedef int       SFBool;
typedef long      SFInt32;
typedef float     SFFloat;

// Turn off un-interesting warnings from MS compiler
//#pragma warning(disable : 4100) // unused formal parameters
//#pragma warning(disable : 4251) // needs to have dll-interface
//#pragma warning(disable : 4201) // nonstandard extension used (in windows headers)
//#pragma warning(disable : 4514) // unreferenced inline function has been removed
//#pragma warning(disable : 4244) // conversion from a double to a float - possible loss of data
//#pragma warning(disable : 4305) // truncation from 'const double' to 'float'
//#pragma warning(disable : 4127) // conditional expression is constant
//#pragma warning(disable : 4275) // non dll-interface class used as base for dll-interface class
//#pragma warning(disable : 4710) // inline function not expanded
//#pragma warning(disable : 4702) // unreachable code

// Include standard headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
//#include <malloc.h>
#include <assert.h>
#include <stdarg.h>

// Some useful constants
#ifndef M_PI
#define M_PI (3.14159265358979323846f)
#endif

#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif

#ifndef ASSERT
#define ASSERT_DEFINED
#ifdef _DEBUG
	#define ASSERT(a) assert(a)
	#define VERIFY(a) assert(a)
#else
	#define ASSERT(a)
	#define VERIFY(a) a
#endif
#endif

#ifndef MIN
//<doc>
// Return the minimum of two values.
template<class TYPE>
inline TYPE MIN(TYPE a, TYPE b)
{
	return (TYPE)(((a<b) ? a : b));
}
#endif

#ifndef MAX
//<doc>
// Return the maximum of two values.
template<class TYPE>
inline TYPE MAX(TYPE a, TYPE b)
{
	return (TYPE)(((a>b) ? a : b));
}
#endif

// These inlines are unlikely to be already defined in app so we
// can expose them -- apps can use them if they want to.

//--------------------------------------------------------------
//<doc>
// Swap two values.
template<class TYPE>
inline void vrSwap(TYPE& x, TYPE& y)
{
  TYPE temp = x;
  x = y;
  y = temp;
}

//--------------------------------------------------------------
//<doc>
// Returns 'val' clamped to the range min to max.
template<class TYPE>
inline TYPE vrClamp(TYPE val, TYPE min, TYPE max)
{
	if (val < min) val = min;
	if (val > max) val = max;
	return val;
}

//--------------------------------------------------------------
//<doc>
// Returns TRUE if val is between (inclusive) start and stop.
template <class TYPE>
inline SFBool vrInRange(TYPE val, TYPE start, TYPE stop)
{
	return ((start <= val) && (stop >= val));
}

//--------------------------------------------------------------
//<doc>
// For any class that implements the mathematical operators '+', 
// '-', and '*' (which includes all the Single Valued and Multi 
// Valued data types) this inline returns a linear interpolation
// between fromVal and toVal based on the calculated ratio
// (t - fromKey) / (toKey - fromKey).
template<class TYPE>
inline TYPE vrInterpolate(TYPE fromVal, TYPE toVal, SFFloat fromKey, SFFloat toKey, SFFloat t)
{
	SFFloat ratio = (t - fromKey) / (toKey - fromKey);
	return fromVal + ((toVal - fromVal) * ratio);
}

//--------------------------------------------------------------
//<doc>
// Compare two values to within a tolerance (for floating point compare).
inline SFInt32 vrCompare(SFFloat a, SFFloat b, SFFloat tol=0.00001)
{
  SFFloat delta = (SFFloat)fabs(a-b);
  if (delta < tol) return 0;
  else if (a > b) return 1;
  else return -1;
}

//--------------------------------------------------------------
//<doc>
// Returns TRUE if two values are equal to within a tolerance (for floating point compare).
inline SFBool vrEquals(SFFloat f1, SFFloat f2, SFFloat tol=0.00001)
{
	return (vrCompare(f1, f2, tol) == 0);
}

//--------------------------------------------------------------
//<doc>
// Convert degrees to radians.
inline SFFloat vrDeg2Rad(SFFloat val)
{
	return (val / 180.0f * M_PI);
}

//--------------------------------------------------------------
//<doc>
// Convert radians to degrees.
inline SFFloat vrRad2Deg(SFFloat val)
{
	return (val / M_PI * 180.0f);
}

#define _MAXPOW (1<<30)
//--------------------------------------------------------------
//<doc>
// Return the smallest power of 2 less than or equal to the given value (or max).
inline SFInt32 vrPow2LT(SFInt32 n, SFInt32 max=_MAXPOW)
{
	SFInt32 test = 1;
	while (test<(1<<30))
	{
		if (n<test) 
			return MIN((SFInt32)max, (SFInt32)(test>>1));
		test = (test<<1);
	}
	return 0;
}

// Geometry related classes
#include "vec2f.h"
#include "vec3f.h"
#include "sfcolor.h"
#include "rotation.h"
#include "image.h"
#include "matrix.h"
#include "rect2d.h"
#include "boundingbox.h"
#include "ray.h"
#include "plane.h"

#if 0
// Container classes
#include "containers\list.h"
#include "containers\intrusivelist.h"
#include "containers\ringList.h"
#include "containers\stack.h"
#include "containers\array.h"
#include "containers\mfstring.h"

// Runtime typing and base node class
#include "runtimeclass.h"
#include "basenode.h"

// Other utilities
#include "utils\webutils.h"
#include "utils\timeutils.h"
#include "utils\imageutils.h"
#include "utils\soundutils.h"
#include "utils\dump.h"
#include "utils\version.h"
#endif

#endif
