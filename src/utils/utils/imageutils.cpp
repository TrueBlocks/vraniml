//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "..\Utility.h"

#include "ImageUtils.h"

#include "Windows.h"

#undef LEADTOOLS
//#define LEADTOOLS

#ifdef LEADTOOLS
#error // you need to buy a license to leadtools to use this option
#include "\LeadTools70\Include\L_Bitmap.h"
#include "\LeadTools70\Include\L_Error.h"

SFBool vrReadTextureImage(SFImage& image, const SFString& remoteFile)
{
	SFString val = remoteFile;
	SFString inName = vrCacheFile(val);

	// Get some information about the file
	FILEINFO fileInfo;
	if (L_FileInfo((char*)inName, &fileInfo)==SUCCESS)
	{
		// Create and open a leadtools bitmap
		pBITMAPHANDLE pBitmap = new BITMAPHANDLE;
		ASSERT(pBitmap); 
		L_InitBitmap(pBitmap, 0, 0, 0);

		if (L_LoadBitmap((char*)inName, pBitmap, fileInfo.BitsPerPixel, ORDER_RGB) == SUCCESS)
		{
			if (pBitmap->BitsPerPixel < 24)
			{
				// No support for anything other than 24 bit deep bitmaps yet.
				if (pBitmap)
				{
					L_FreeBitmap(pBitmap);
					delete pBitmap;
				}
				return FALSE;
			}
			
			// Create the image data after filtering the texture to a suitable
			// 'nxm' size where 'n' and 'm' are both powers of 2
			ASSERT(image.m_Width);
			ASSERT(image.m_Height);
			ASSERT(image.m_nComponents == 3);
			ASSERT(image.m_ColorData);
			image.m_Width       = vrPow2LT(fileInfo.Width,  image.m_Width);
			image.m_Height      = vrPow2LT(fileInfo.Height, image.m_Height);
			image.m_nComponents = 3;
			ASSERT(image.m_nComponents >0 && image.m_nComponents < 4);
			long size = image.m_Width * image.m_Height * image.m_nComponents;
			unsigned char *p = (unsigned char *)image.m_ColorData;

			// Filter the leadtools image to the size needed by OpenGL
			int ret = L_ResampleBitmap(pBitmap, image.m_Width, image.m_Height);
//			ret = L_SaveBitmap("\\test.jpg", pBitmap, fileInfo.Format, fileInfo.BitsPerPixel, 2);

			// Flip it over since it's upside down -- don't know why but it is
			L_FlipBitmap(pBitmap);

			L_AccessBitmap(pBitmap);
			for (int i=0; i < image.m_Width; i++)
			{
//				for (int j=image.m_Height-1; j>=0; j--)
				for (int j=0; j<image.m_Height; j++)
				{
					long val;
					unsigned char *vv = (unsigned char *)&val;
					L_GetBitmapRowCol(pBitmap, vv, i, j, image.m_nComponents);
					p[0] = vv[0];
					p[1] = vv[1];
					p[2] = vv[2];
					p += image.m_nComponents;
					ASSERT(p < ((unsigned char *)image.m_ColorData + size + 1));
					ASSERT(0<((int)image.m_ColorData)+size+1-(int)p);
				}
			}
			L_ReleaseBitmap(pBitmap);
		}

		// Cleanup the leadtools bitmap
		if (pBitmap)
		{
			L_FreeBitmap(pBitmap);
			delete pBitmap;
		}
	} else
	{
		return FALSE;
	}

	return TRUE;
}

#else
#include "..\imglib\imglib.h"

SFBool vrReadTextureImage(SFImage& img, const SFString& remoteFile)
{
	SFString val = remoteFile;
	SFString inName = vrCacheFile(val);

	inputStream in(inName) ;
	if (!in.isOpen())
		return FALSE;

	BitmapImage image;

	ImageType type = GetStreamImageType(in);
	if (type == UnknownImage)
    return 0;
	if (type == GifImage)
  {
		printf("GIF not supported\n");
		return 0;
	}

#ifdef _DEBUG
	ASSERT(ReadImage(in, image, NULL, NULL) == type);
#else
	ReadImage(in, image, NULL, NULL);
#endif

	// Create the image data after filtering the texture to a suitable
	// 'nxm' size where 'n' and 'm' are both powers of 2
	ASSERT(img.m_Width);
	ASSERT(img.m_Height);
	ASSERT(img.m_nComponents); // == 3);
	ASSERT(img.m_ColorData);

	img.m_Width       = vrPow2LT(image.Width(), img.m_Width);
	img.m_Height      = vrPow2LT(image.Height(), img.m_Height);
	SFInt32 bc = image.BitCount();
	img.m_nComponents = ((bc==24) ? 3 : ((bc==16) ? 2 : 1));
	ASSERT(img.m_nComponents >0 && img.m_nComponents < 4);

#if 0
	long size = img.m_Width * img.m_Height * img.m_nComponents;
	memcpy(img.m_ColorData, image.ImageData(), size);
#else
	// Flip it over since it's upside down -- don't know why but it is
	// ALJ! The image is upside-down and probably not a power o' 2 in width and height.  Snip
	// out a piece from its upper-left corner that is.
	long	src_rowbytes	= image.Width() * img.m_nComponents,
                dest_rowbytes	= img.m_Width * img.m_nComponents;
	char	*src		= (char *)image.ImageData() + (image.Height() - 1) * src_rowbytes,
		*dest		= (char *)img.m_ColorData + (img.m_Height - 1) * dest_rowbytes;
	for (long row = 0; row < img.m_Height; row++)
	{
		// One line at a time...
		memcpy(dest, src, dest_rowbytes);
		src		-= src_rowbytes;
		dest	-= dest_rowbytes;
	}
#endif

	return TRUE;
}
#endif

