//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "types.h"

#include "rotation.h"

SFRotation::SFRotation(void)
{
	/* random */
}

SFRotation::SFRotation(const SFRotation& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

SFRotation::SFRotation(const SFVec3f& axis, SFFloat a) : SFVec3f(axis) 
{
	w = a;
}

SFRotation::SFRotation(SFFloat x, SFFloat y, SFFloat z, SFFloat a) : SFVec3f(x,y,z)
{
	w = a;
}
