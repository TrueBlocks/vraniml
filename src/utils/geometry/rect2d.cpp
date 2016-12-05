//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "types.h"

#include "rect2d.h"

//-----------------------------------------------------------------------------
SFFloat vrRect2D::Width(void) const
{
	return (right-left);
}

SFFloat vrRect2D::Height(void) const
{
	return (bottom-top);
}

SFVec2f vrRect2D::Size(void) const
{
	return SFVec2f((right-left), (bottom-top));
}

