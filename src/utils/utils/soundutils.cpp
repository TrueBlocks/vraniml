//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "..\Utility.h"

#include "Windows.h"
SFBool vrPlaySound(const SFString& url)
{
	if (url==nullString||url.Empty())
	{
		return PlaySound(NULL, NULL, 0);
	} else
	{
		SFString copy = url;
		SFString local = vrCacheFile(copy, 0);
		return PlaySound((LPCTSTR)(char*)local, NULL, SND_FILENAME|SND_ASYNC|SND_NODEFAULT|SND_NOSTOP); 
	}
}
