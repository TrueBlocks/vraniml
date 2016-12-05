//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "..\Utility.h"

#include "Version.h"

void vrGetVersion(vrVersionInfo *info)
{
	info->product     = "VRaniML v0.9.04";
	info->vendor      = "Great Hill Corporation";
	info->majorNum    = 0;
	info->minorNum    = 9;
	info->releaseNum  = 4;
  info->buildDate   = __DATE__;
	info->buildTime   = __TIME__;
}

