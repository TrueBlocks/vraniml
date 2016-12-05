#ifndef __SFCOLOR_H3D
#define __SFCOLOR_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

#include "vec3f.h"

/*----------------------------------------------------------------------
CLASS
	SFColor

	Represents an RGBA color.

DESCRIPTION
	<ul>
	Represents the SFColor field as defined in VRML.
	</ul>

NOTES
	<ul>
	<li>The red, green, blue and alpha values of colors should be clammed to
	the range 0.0 and 1.0.  This is done during normalization, addition or subtraction
	of colors but the user should avoid setting these values directly
	outside of this range.</li>
	<li>There is a large collection of pre-defined colors defined in the
	SFColor.h file.  You may use these in place of any SFColor value.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// You can add and subtract and multiply colors to your delight.
	
	SFColor red   = vrRed;
	SFColor green = vrGreen;
	SFColor white = vrWhite;
	
	SFColor lightRedishGreen = (red + green) / 4.0;
	SFColor grey = (white * .5);
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class SFColor : public SFVec3f 
{
public:
  //<doc>------------------------------------------------------------
  // <dd>The alpha component of the color (RGB is represented by x,y,z).
	// [default:] vrBlack
	//
	SFFloat         a;

  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	SFColor         (void);

  //<doc>------------------------------------------------------------
  // <dd>Copy constructor.
	//
	SFColor         (const SFColor& c);

  //<doc>------------------------------------------------------------
  // <dd>Desctructor.
	//
	~SFColor         (void);

  //<doc>------------------------------------------------------------
  // <dd>Equals operator.
	//
	SFColor& operator=      (const SFColor& c);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] red: The red component of the color.
	// [in] green: The green component of the color.
	// [in] blue: The blue component of the color.
	//
	SFColor         (SFFloat red, SFFloat green, SFFloat blue);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] red: The red component of the color.
	// [in] green: The green component of the color.
	// [in] blue: The blue component of the color.
	// [in] alpha: The alpha component of the color.
	//
	SFColor         (SFFloat red, SFFloat green, SFFloat blue, SFFloat alpha);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] all: A value assigned to all three color components of the color (alpha = 1.0).
	//
	SFColor         (SFFloat all);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] v: Values assigned to the three color components of the color (alpha = 1.0).
	//
	SFColor         (const SFVec3f& v);

  //<doc>------------------------------------------------------------
  // <dd>Add two colors and normalize.
	//
	// [in] c1: The first color.
	// [in] c2: The second color.
	//
	friend SFColor operator+(const SFColor& c1, const SFColor& c2)
		{
			return NormalizeColor(SFColor(c1.x+c2.x,c1.y+c2.y,c1.z+c2.z,vrClamp(c1.a+c2.a, 0.0f, 1.0f)));
		}

  //<doc>------------------------------------------------------------
  // <dd>Subtract two colors and normalize.
	//
	// [in] c1: The first color.
	// [in] c2: The second color.
	//
	friend SFColor operator-(const SFColor& c1, const SFColor& c2)
		{
			return NormalizeColor(SFColor(c1.x-c2.x,c1.y-c2.y,c1.z-c2.z,vrClamp(c1.a-c2.a, 0.0f, 1.0f)));
		}

  //<doc>------------------------------------------------------------
  // <dd>Multiply a colors by a scalar and normalize.
	//
	// [in] c: The first color.
	// [in] f: The scalar to multiply by.
	//
	friend SFColor operator*(const SFColor& c,  SFFloat f)
		{
			return NormalizeColor(SFColor(c.x*f,c.y*f,c.z*f,vrClamp(c.a*f, 0.0f, 1.0f)));
		}

  //<doc>------------------------------------------------------------
  // <dd>Normalize a color (i.e. make all value inRange(0.0, 1.0)).
	//
	// [in] c: The color to normalize.
	//
	friend SFColor  NormalizeColor (const SFColor& c);
};

inline SFColor::SFColor() 
{ 
	// vrBlack
	x = y = z = 0.0;
	a = 1.0;
}

inline SFColor::SFColor(const SFColor& c) 
{ 
  x = c.x; 
	y = c.y; 
	z = c.z; 
	a = c.a;
}

inline SFColor::~SFColor() 
{ 
}

inline SFColor& SFColor::operator=(const SFColor& c)
{
	x = c.x;
	y = c.y;
	z = c.z;
	a = c.a;
	return *this;
}

inline SFColor::SFColor(SFFloat f1, SFFloat f2, SFFloat f3) 
{ 
  x = f1; 
	y = f2; 
	z = f3; 
	a = 1.0;
}

inline SFColor::SFColor(SFFloat f1, SFFloat f2, SFFloat f3, SFFloat f4) 
{ 
  x = f1; 
	y = f2; 
	z = f3; 
	a = f4;
}

inline SFColor::SFColor(SFFloat f) 
{ 
  x = f;
	y = f;
	z = f; 
	a = 1.0;
}

inline SFColor::SFColor(const SFVec3f& v) 
{ 
  x = v.x; 
	y = v.y; 
	z = v.z; 
	a = 1.0;
}

// Compute a normalized version of a color (same hue, but less bright).
inline SFColor NormalizeColor(const SFColor& c)
{
  if (c.x > 1.0 || c.y > 1.0 || c.z > 1.0)
	{
    SFFloat max = c.x;
		if (c.y > max)
			max = c.y;
		if (c.z > max)
			max = c.z;
    if (max != 0.0)
		{
      return c / max;
    }
  }
  return c;
}

// Some usefull colors
#define vrBlack             SFColor(0.000000f, 0.000000f, 0.000000f)
#define vrWhite             SFColor(1.000000f, 1.000000f, 1.000000f)
#define vrRed               SFColor(1.000000f, 0.000000f, 0.000000f)
#define vrGreen             SFColor(0.000000f, 1.000000f, 0.000000f)
#define vrBlue              SFColor(0.000000f, 0.000000f, 1.000000f)
#define vrYellow            SFColor(1.000000f, 1.000000f, 0.000000f)
#define vrCyan              SFColor(0.000000f, 1.000000f, 1.000000f)
#define vrMagenta           SFColor(1.000000f, 0.000000f, 1.000000f)
#define vrAquamarine        SFColor(0.439216f, 0.858824f, 0.576471f)
#define vrBlueViolet        SFColor(0.623520f, 0.372549f, 0.623529f)
#define vrBrown             SFColor(0.647059f, 0.164706f, 0.164706f)
#define vrCadetBlue         SFColor(0.372549f, 0.623529f, 0.623529f)
#define vrCoral             SFColor(1.000000f, 0.498039f, 0.000000f)
#define vrCornflowerBlue    SFColor(0.258824f, 0.258824f, 0.435294f)
#define vrDarkGreen         SFColor(0.184314f, 0.309804f, 0.184314f)
#define vrDarkOliveGreen    SFColor(0.309804f, 0.309804f, 0.184314f)
#define vrDarkOrchid        SFColor(0.600000f, 0.196078f, 0.800000f)
#define vrDarkSlateBlue     SFColor(0.419608f, 0.137255f, 0.556863f)
#define vrDarkSlateGray     SFColor(0.184314f, 0.309804f, 0.309804f)
#define vrDarkSlateGrey     SFColor(0.184314f, 0.309804f, 0.309804f)
#define vrDarkTurquoise     SFColor(0.439216f, 0.576471f, 0.858824f)
#define vrDimGray           SFColor(0.329412f, 0.329412f, 0.329412f)
#define vrDimGrey           SFColor(0.329412f, 0.329412f, 0.329412f)
#define vrFirebrick         SFColor(0.556863f, 0.137255f, 0.137255f)
#define vrForestGreen       SFColor(0.137255f, 0.556863f, 0.137255f)
#define vrGold              SFColor(0.800000f, 0.498039f, 0.196078f)
#define vrGoldenrod         SFColor(0.858824f, 0.858824f, 0.439216f)
#define vrGray              SFColor(0.752941f, 0.752941f, 0.752941f)
#define vrGreenYellow       SFColor(0.576471f, 0.858824f, 0.439216f)
#define vrGrey              SFColor(0.752941f, 0.752941f, 0.752941f)
#define vrIndianRed         SFColor(0.309804f, 0.184314f, 0.184314f)
#define vrKhaki             SFColor(0.623529f, 0.623529f, 0.372549f)
#define vrLightBlue         SFColor(0.749020f, 0.847059f, 0.847059f)
#define vrLightGray         SFColor(0.658824f, 0.658824f, 0.658824f)
#define vrLightGrey         SFColor(0.658824f, 0.658824f, 0.658824f)
#define vrLightSteelBlue    SFColor(0.560784f, 0.560784f, 0.737255f)
#define vrLimeGreen         SFColor(0.196078f, 0.800000f, 0.196078f)
#define vrMaroon            SFColor(0.556863f, 0.137255f, 0.419608f)
#define vrMediumAquamarine  SFColor(0.196078f, 0.800000f, 0.600000f)
#define vrMediumBlue        SFColor(0.196078f, 0.196078f, 0.800000f)
#define vrMediumForestGreen SFColor(0.419608f, 0.556863f, 0.137255f)
#define vrMediumGoldenrod   SFColor(0.917647f, 0.917647f, 0.678431f)
#define vrMediumOrchid      SFColor(0.576471f, 0.439216f, 0.858824f)
#define vrMediumSeaGreen    SFColor(0.258824f, 0.435294f, 0.258824f)
#define vrMediumSlateBlue   SFColor(0.498039f, 0.000000f, 1.000000f)
#define vrMediumSpringGreen SFColor(0.498039f, 1.000000f, 0.000000f)
#define vrMediumTurquoise   SFColor(0.439216f, 0.858824f, 0.858824f)
#define vrMediumVioletRed   SFColor(0.858824f, 0.439216f, 0.576471f)
#define vrMidnightBlue      SFColor(0.184314f, 0.184314f, 0.309804f)
#define vrNavy              SFColor(0.137255f, 0.137255f, 0.556863f)
#define vrNavyBlue          SFColor(0.137255f, 0.137255f, 0.556863f)
#define vrOrange            SFColor(0.800000f, 0.196078f, 0.196078f)
#define vrOrangeRed         SFColor(1.000000f, 0.000000f, 0.498039f)
#define vrOrchid            SFColor(0.858824f, 0.439216f, 0.858824f)
#define vrPaleGreen         SFColor(0.560784f, 0.737255f, 0.560784f)
#define vrPink              SFColor(0.737255f, 0.560784f, 0.560784f)
#define vrPlum              SFColor(0.917647f, 0.678431f, 0.917647f)
#define vrSalmon            SFColor(0.435294f, 0.258824f, 0.258824f)
#define vrSeaGreen          SFColor(0.137255f, 0.556863f, 0.419608f)
#define vrSienna            SFColor(0.556863f, 0.419608f, 0.137255f)
#define vrSkyBlue           SFColor(0.196078f, 0.600000f, 0.800000f)
#define vrSlateBlue         SFColor(0.000000f, 0.498039f, 1.000000f)
#define vrSpringGreen       SFColor(0.000000f, 1.000000f, 0.498039f)
#define vrSteelBlue         SFColor(0.137255f, 0.419608f, 0.556863f)
#define vrTan               SFColor(0.858824f, 0.576471f, 0.439216f)
#define vrThistle           SFColor(0.847059f, 0.749020f, 0.847059f)
#define vrTurquoise         SFColor(0.678431f, 0.917647f, 0.917647f)
#define vrViolet            SFColor(0.309804f, 0.184314f, 0.309804f)
#define vrVioletRed         SFColor(0.800000f, 0.196078f, 0.600000f)
#define vrWheat             SFColor(0.847059f, 0.847059f, 0.749020f)
#define vrYellowGreen       SFColor(0.600000f, 0.800000f, 0.196078f)

extern SFInt32 MAX_COLORS;
extern SFColor colorMap[];

//<nodoc>-----------------------------------------------------
//
// Converts an SFColor to a window COLORREF
inline SFInt32 RGBA(const SFColor& col)
{
	SFInt32 a[4];
	a[0] = ((int)(col.x * 255.));
	a[1] = ((int)(col.y * 255.)) << 8;
	a[2] = ((int)(col.z * 255.)) << 16;
	a[3] = ((int)(col.a * 255.)) << 24;
	SFInt32 i = (a[0] | a[1] | a[2] | a[3]);
	return i;
}

#endif
