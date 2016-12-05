#ifndef _TYPES_H_
#define _TYPES_H_
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//----------------------------------------------------------------------

#include <math.h>
#include <float.h>
#include <stdlib.h>

// Basic types
typedef int       SFBool;
typedef long      SFInt32;
typedef float     SFFloat;

// Some useful constants
#ifndef NULL
#define NULL (0)
#endif

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

#endif
