//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "types.h"

#include "image.h"

SFImage::SFImage()
{
	m_Width = 0;
	m_Height = 0;
	m_nComponents = 0;
	m_ColorData = NULL;
}

SFImage::SFImage(long w, long h, long nC)
{
	m_Width       = w;
	m_Height      = h;
	m_nComponents = nC;
	ASSERT(m_nComponents > 0 && m_nComponents < 4);
	long size = m_Width * m_Height * m_nComponents;
	m_ColorData = new char[size];
}

SFImage::~SFImage(void)
{
	if (m_ColorData)
		delete [] m_ColorData;
	m_ColorData = NULL;
}
