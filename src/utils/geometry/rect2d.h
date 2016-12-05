#ifndef __RECT2D_H3D
#define __RECT2D_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

#include "vec2f.h"

/*----------------------------------------------------------------------
CLASS
	vrRect2D

	A utility class representing a 2d rectangle.

DESCRIPTION
	<ul>
	Utility class for representing 2D rectangle.  Corresponds directly to
	the MFC class CRect.  This class can be used as a standalone 2D bounding box.
	</ul>

NOTES
	<ul>
	<li>None.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// This class has various uses:
	
	// Get a bounding box from some VRML model.
	vrBoundingBox box = model->GetBoundingBox();

	vrRect2D front = box.GetFront();
	vrRect2D side = box.GetSide();
	vrRect2D top = box.GetTop();

	// Use the 2d bounding boxes for some calculation...
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class vrRect2D
{
public:
  //<doc>------------------------------------------------------------
  // <dd>The left component of the rectangle.
	// [default:] 0.0
	//
  SFFloat left;

  //<doc>------------------------------------------------------------
  // <dd>The top component of the rectangle.
	// [default:] 0.0
	//
  SFFloat top;

  //<doc>------------------------------------------------------------
  // <dd>The right component of the rectangle.
	// [default:] 0.0
	//
  SFFloat right;

  //<doc>------------------------------------------------------------
  // <dd>The bottom component of the rectangle.
	// [default:] 0.0
	//
  SFFloat bottom;

  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	vrRect2D  (void);

  //<doc>------------------------------------------------------------
  // <dd>Copy constructor.
	//
	vrRect2D  (const vrRect2D& rect);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] l: The left component of the rectangle.
	// [in] t: The top component of the rectangle.
	// [in] r: The right component of the rectangle.
	// [in] b: The bottom component of the rectangle.
	//
	vrRect2D  (SFFloat l, SFFloat t, SFFloat r, SFFloat b);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] tl: The top-left of the rectangle.
	// [in] br: The bottom-right of the rectangle.
	//
	vrRect2D  (const SFVec2f& tl, const SFVec2f& br);

  //<doc>------------------------------------------------------------
  // <dd>Destructor.
	//
	~vrRect2D  (void)
		{ };

  //<doc>------------------------------------------------------------
  // <dd>Equal operator.
	//
	vrRect2D&     operator= (const vrRect2D& pt);

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if the two rectangle are identical.
	//
	// [in] rect: The query rectangle.
	//
	SFBool        operator==(const vrRect2D& rect) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if the two rectangle are different.
	//
	// [in] rect: The query rectangle.
	//
	SFBool        operator!=(const vrRect2D& rect) const;

  //<doc>------------------------------------------------------------
  // <dd>Expand the recatangle in both width and height by pt.x and pt.y respectively.
	//
	// [in] pt: The amounts by which to grow the rectangle.
	//
  void          operator+=(const SFVec2f& pt);

  //<doc>------------------------------------------------------------
  // <dd>Shrink the recatangle in both width and height by pt.x and pt.y respectively.
	//
	// [in] pt: The amounts by which to shrink the rectangle.
	//
  void          operator-=(const SFVec2f& pt);

  //<doc>------------------------------------------------------------
  // <dd>Scale the recatangle in both width and height by pt.x and pt.y respectively.
	//
	// [in] pt: The amounts by which to scale the rectangle.
	//
  void          operator/=(const SFVec2f& pt);

  //<doc>------------------------------------------------------------
  // <dd>Scale the recatangle in both width and height by pt.x and pt.y respectively.
	//
	// [in] pt: The amounts by which to scale the rectangle.
	//
  void          operator*=(const SFVec2f& pt);

  //<doc>------------------------------------------------------------
  // <dd>Return the width of the rectangle.
	//
	SFFloat       Width     (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Return the height of the rectangle.
	//
	SFFloat       Height    (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Return the width and height of the rectangle.
	//
  SFVec2f       Size      (void) const;
};

//-----------------------------------------------------------------------------
inline vrRect2D::vrRect2D(void)
{
	// random values
}

inline vrRect2D::vrRect2D(const vrRect2D& rect)
{
	left   = rect.left;
	top    = rect.top;
	right  = rect.right;
	bottom = rect.bottom;
}

inline vrRect2D::vrRect2D(SFFloat l, SFFloat t, SFFloat r, SFFloat b)
{
	left   = l;
	top    = t;
	right  = r;
	bottom = b;
}

inline vrRect2D::vrRect2D(const SFVec2f& pt1, const SFVec2f& pt2)
{
	left   = pt1.x;
	top    = pt1.y;
	right  = pt2.x;
	bottom = pt2.y;
}

//-----------------------------------------------------------------------------
inline vrRect2D& vrRect2D::operator=(const vrRect2D& rect)
{
	left   = rect.left;
	top    = rect.top;
	right  = rect.right;
	bottom = rect.bottom;

	return *this;
}

inline SFBool vrRect2D::operator==(const vrRect2D& rect) const
{
	if (left   != rect.left)   return FALSE;
	if (top    != rect.top)    return FALSE;
	if (right  != rect.right)  return FALSE;
	if (bottom != rect.bottom) return FALSE;
	return TRUE;
}

inline SFBool vrRect2D::operator!=(const vrRect2D& rect) const
{
	return (SFBool)((!(*this == rect)));
}

inline void vrRect2D::operator+=(const SFVec2f& pt)
{
	left   += pt.x;
	right  += pt.x;
	top    += pt.y;
	bottom += pt.y;
}

inline void vrRect2D::operator-=(const SFVec2f& pt)
{
	left   -= pt.x;
	right  -= pt.x;
	top    -= pt.y;
	bottom -= pt.y;
}

inline void vrRect2D::operator/=(const SFVec2f& pt)
{
	left   /= pt.x;
	right  /= pt.x;
	top    /= pt.y;
	bottom /= pt.y;
}

inline void vrRect2D::operator*=(const SFVec2f& pt)
{
	left   *= pt.x;
	right  *= pt.x;
	top    *= pt.y;
	bottom *= pt.y;
}

#endif
