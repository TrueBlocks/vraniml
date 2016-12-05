//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "types.h"

#include "ray.h"

//----------------------------------------------------------------------
SFBool Colinear(const SFVec3f& v1, const SFVec3f& v2, const SFVec3f& v3)
{
	if (v1 == v2) return TRUE;
	if (v2 == v3) return TRUE;
	if (v1 == v3) return TRUE;

	vrLine line(v1, v2-v1);
	SFFloat dist = line.GetDistance(v3-v1);
	return (vrCompare(dist, 0.0f) == 0);
}

