#ifndef __AXISALIGNEDBOX_H3D
#define __AXISALIGNEDBOX_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

#include "ray.h"
#include "rect2d.h"

/*----------------------------------------------------------------------
CLASS
	vrBoundingBox

	A bounding box is used to calculate the axis-aligned space represented
	by a set of SFVec3f values.

DESCRIPTION
	<ul>
	Each VRML Grouping Node has a vrBoundingBox data member that represents
	the space occupied by all the objects contained in the grouping node.  This
	class represents that bounding box as two SFVec3f values for the max and
	min extents of the box.  Users may use this class as a standalone bounding box
	utility also.
	</ul>

NOTES
	<ul>
	<li>The bounding box is represented as two SFVec3f fields for the
	min and max extents of the box.</li>
	<li>The bounding box is axis aligned.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// To add values to a bounding box:
	vrBoundingBox box;
	box.Include(SFVec3f(-1.0));
	box.Include(SFVec3f(1.0));

	ASSERT(box.IsInside(SFVec3f(0.0)) == TRUE);
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class vrBoundingBox
{
protected:
  //<doc>------------------------------------------------------------
  // <dd>Largest x, y and z components contained in the bounding box.
	// [default:] [-INFINITY]
	//
  SFVec3f         m_Min;

  //<doc>------------------------------------------------------------
  // <dd>Smallest x, y and z components contained in the bounding box.
	// [default:] [+INFINITY]
	//
  SFVec3f         m_Max;

public:
  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	vrBoundingBox(void);

  //<doc>------------------------------------------------------------
  // <dd>Copy constructor.
	//
	vrBoundingBox(const vrBoundingBox& aBox);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] min: The minimum extent of the bounding box.
	// [in] max: The maximum extent of the bounding box.
	//
	vrBoundingBox(const SFVec3f& min, const SFVec3f& max);

  //<doc>------------------------------------------------------------
  // <dd>Destructor.
	//
	~vrBoundingBox(void);

  //<doc>------------------------------------------------------------
  // <dd>Equals operator.
	//
	vrBoundingBox&    operator=       (const vrBoundingBox& aBox);

  //<doc>------------------------------------------------------------
  // <dd>Returns the value of m_Min.
	//
	SFVec3f           GetMin          (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns the value of m_Max.
	//
	SFVec3f           GetMax          (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns a 2D rectangle represented by the front of the bounding box.
	//
	vrRect2D          GetFront        (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns a 2D rectangle represented by the top of the bounding box.
	//
	vrRect2D          GetTop          (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns a 2D rectangle represented by the side of the bounding box.
	//
	vrRect2D          GetSide         (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns an SFVec3f at the center of the bounding box.
	//
	SFVec3f           GetCenter       (void) const
		{ return (GetMin() + ((GetMax() - GetMin()) / 2.0)); }

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if the bounding box is in it's default state.
	//
	SFBool            IsDefault       (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Add an SFVec3f to the bounding box, growing it if necessary.
	//
	// [in] newPt: The point to add to the bounding box growing it if needed.
	//
	void              Include         (const SFVec3f& newPt);

  //<doc>------------------------------------------------------------
  // <dd>Add another bounding box to this bounding box, growing it if necessary.
	//
	// [in] aBox: A vrBoundingBox to add to this box, growing it if needed.
	//
	void              Include         (const vrBoundingBox & aBox);

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if the query vertex is inside the bounding box.
	//
	// [in] v: The query vertex.
	//
	SFBool            IsInside        (const SFVec3f& v) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if the ray intersects the bounding box.
	//
	// [in] ray: The query ray.
	// [out] tmin: The value of 't' at which the ray is evaluted where it crosses 
	//             into the bounding box.  May be NULL.
	// [out] tmax: The value of 't' at which the ray is evaluted where it crosses
	//             out of bounding box.  May be NULL.
	//
	SFInt32					 Intersect    (const vrRay& ray, float *tmin=NULL, float *tmax=NULL) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns the union of two bounding boxes.
	//
	// [in] box1: The first bounding box.
	// [in] box2: The second bounding box.
	//
	friend vrBoundingBox  Union       (const vrBoundingBox& box1, const vrBoundingBox& box2);

  //<doc>------------------------------------------------------------
  // <dd>Returns the intersection of two bounding boxes (empty bounding box if no intersection).
	//
	// [in] box1: The first bounding box.
	// [in] box2: The second bounding box.
	//
	friend vrBoundingBox  Intersect   (const vrBoundingBox& box1, const vrBoundingBox& box2);

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if the two bounding boxes intersect.
	//
	// [in] box1: The first bounding box.
	// [in] box2: The second bounding box.
	//
	friend SFBool         Overlap     (const vrBoundingBox& box1, const vrBoundingBox& box2);

  //<doc>------------------------------------------------------------
  // <dd>Transforms the bounding box to a different space.
	//
	// [in] box: The bounding box to transform.
	// [in] tform: The transformation to apply to the given bounding box.
	//
	friend vrBoundingBox  TransformBox(const vrBoundingBox& box, const vrMatrix& tform);

  //<nodoc>------------------------------------------------------------
  // <dd>Returns the surface area of the bounding box.
	//
	SFFloat           SurfaceArea     (void) const;
};

inline SFVec3f vrBoundingBox::GetMin() const
{
  return m_Min;
}

inline SFVec3f vrBoundingBox::GetMax() const
{
  return m_Max;
}

inline SFBool vrBoundingBox::IsDefault() const
{
  return ((m_Min == SFVec3f(-FLT_MAX)) || (m_Max == SFVec3f(-FLT_MAX)));
}

inline void vrBoundingBox::Include(const SFVec3f& newVec)
{
  Minimize(m_Min, newVec);
  Maximize(m_Max, newVec);
}

inline void vrBoundingBox::Include(const vrBoundingBox& bbox)
{
  Minimize(m_Min, bbox.m_Min);
  Maximize(m_Max, bbox.m_Max);
}

inline vrRect2D vrBoundingBox::GetFront(void) const
{
  return vrRect2D(m_Min.x, m_Min.y, m_Max.x, m_Max.y);
}

inline vrRect2D vrBoundingBox::GetSide(void) const
{
  return vrRect2D(m_Min.z, m_Min.y, m_Max.z, m_Max.y);
}

inline vrRect2D vrBoundingBox::GetTop(void) const
{
  return vrRect2D(m_Min.x, m_Min.z, m_Max.x, m_Max.z);
}

#endif
