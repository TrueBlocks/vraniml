#ifndef __IMAGE_H3D
#define __IMAGE_H3D
//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
//<doc>
// Returns TRUE if the given filename can be read.  Also returns the image
// data in the SFImage parameter.
SFBool UL_Interface vrReadTextureImage(SFImage& image, const SFString& filename);

#endif