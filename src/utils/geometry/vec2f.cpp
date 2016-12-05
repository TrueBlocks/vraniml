//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "types.h"

#include "vec2f.h"
#include "vec3f.h"

SFVec2f Normalize(const SFVec2f& v1)
{
  SFVec3f v = v1 / Magnitude(v1);
	return SFVec2f(v.x, v.y);
}

