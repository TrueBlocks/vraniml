#ifndef _SFIMAGE_H3D
#define _SFIMAGE_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

/*----------------------------------------------------------------------
CLASS
	SFImage

	A pixel image used mostly for texture mapping.  Corresponds to the 
	VRML SFImage field type.

DESCRIPTION
	<ul>
	A pixel image used for texture mapping.  Corresponds to the 
	VRML SFImage field type.
	</ul>

NOTES
	<ul>
	<li>None.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// To read a texture file for example:
	SFImage image(128, 128, 4);
	if (vrReadTextureImage(image, "test.jpg"))
	{
		printf("Pixel    Red  Green   Blue\n");

		unsigned char *p = (unsigned char *)image.m_ColorData;
		for (int i=0; i < image.m_Width; i++)
		{
			for (int j=0; j<image.m_Height; j++)
			{
				SFColor color(*p, *(p+1), *(p+2));
				printf("%d %d %d\n", );
				printf("[%4d,%4d] --> %05d %05d %05d\n", i, j, color.x, color.y, color.z);
				p += image.m_nComponents;
			}
		}
	}
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class SFImage
{
public:
  //<doc>------------------------------------------------------------
  // <dd>The width of the image in pixels.
	// [default:] 0
	//
	SFInt32  m_Width;

  //<doc>------------------------------------------------------------
  // <dd>The height of the image in pixels.
	// [default:] 0
	//
	SFInt32  m_Height;

  //<doc>------------------------------------------------------------
  // <dd>The number of components in the image.
	// [default:] 0
	//
	SFInt32  m_nComponents;

  //<doc>------------------------------------------------------------
  // <dd>Pointer to the color data.
	// [default:] NULL
	//
	char    *m_ColorData;

  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	SFImage (void);

  //<doc>------------------------------------------------------------
  // <dd>Constructor (allocates color buffer).
	//
	// [in] width: Width of the image.
	// [in] height: Height of the image.
	// [in] nComponents: Number of components in the image.
	//
	SFImage (long width, long height, long nComponents=3);

  //<doc>------------------------------------------------------------
  // <dd>Destructor.
	//
	~SFImage (void);
};

#endif
