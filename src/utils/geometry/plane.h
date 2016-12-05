#ifndef __PLANE_H3D
#define __PLANE_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

#include "ray.h"

/*----------------------------------------------------------------------
CLASS
	vrPlane

	Represents a plane in 3-space.  Used as the basis of a polygon.

DESCRIPTION
	<ul>
	Utility class for representing 3d plane.  Used in 
	various places for calculation intersections and as the
	basis for a polygon.
	</ul>

NOTES
	<ul>
	<li>None.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// Can be used for various calculations:

	vrPlane plane1(xAxis, 1.0);
	vrPlane plane2(yAxis, 1.0);

	// The intersection of two planes is a ray:
	vrRay intersection = plane1.Intersect(plane2);

	// The distance of a point to a plane:
	SFFloat distance = plane1.GetDistance(origin);
	ASSERT(distance == 1.0);
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class vrPlane
{
protected:
  //<doc>------------------------------------------------------------
  // <dd>The normal of the plane.
	// [default:] xAxis
	//
  SFVec3f        m_Normal;

  //<doc>------------------------------------------------------------
  // <dd>The distance of the plane.
	// [default:] 0.0
	//
  SFFloat        m_D;

public:
  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	vrPlane        (void);

  //<doc>------------------------------------------------------------
  // <dd>Copy constructor.
	//
	vrPlane        (const vrPlane& p);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] A: A value for the plane.
	// [in] B: B value for the plane.
	// [in] C: C value for the plane.
	// [in] D: D value for the plane.
	//
	vrPlane        (SFFloat A, SFFloat B, SFFloat C, SFFloat D);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] normal: normal to the plane.
	// [in] D: Distance of the plane.
	//
	vrPlane        (const SFVec3f& normal, SFFloat D);

  //<doc>------------------------------------------------------------
  // <dd>Destructor.
	//
	~vrPlane        (void);

  //<doc>------------------------------------------------------------
  // <dd>Equal operator.
	//
	vrPlane&    operator=      (const vrPlane& p);

  //<doc>------------------------------------------------------------
  // <dd>Return the distance of the vector to the plane.
	//
	// [in] v: SFVec3f value which to calculate the distance to.
	//
	SFFloat     GetDistance    (const SFVec3f& v) const;

  //<doc>------------------------------------------------------------
  // <dd>Return the plane's normal.
	//
	SFVec3f     GetNormal      (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Return the plane's distance.
	//
	SFFloat     GetD           (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Return the line that represents the intersection of this plane with the given plane.
	//
	// [in] plane: The plane to intersect with this plane.
	//
	vrLine      Intersect      (const vrPlane& p) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if the given ray intersects this plane.
	//
	// [in]  line: The query line.
	// [out] t: the value of 't' at which the query line would be evaluated where it intersects the plane.
	// [in]  tmax: The maximum value of 't' at which an intersection can occur.
	//
	SFBool      Intersect      (const vrLine& line, SFFloat& t, SFFloat maxt) const;

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if the plane crosses the X axis.
	//
	// [out] pt: The point at which the plane crosses the X axis.
	//
	SFBool      XIntercept     (SFVec3f *pt) const;

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if the plane crosses the Y axis.
	//
	// [out] pt: The point at which the plane crosses the Y axis.
	//
	SFBool      YIntercept     (SFVec3f *pt) const;

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if the plane crosses the Z axis.
	//
	// [out] pt: The point at which the plane crosses the Z axis.
	//
	SFBool      ZIntercept     (SFVec3f *pt) const;

private:
	void        Draw           (void) const;
};

inline SFVec3f vrPlane::GetNormal(void) const
{
	return m_Normal;
}

inline SFFloat vrPlane::GetD(void) const
{
	return m_D;
}

inline SFFloat vrPlane::GetDistance(const SFVec3f& v) const
{
	//
	// Formula for distance of point (x,y,z) to plane (a,b,c,d):
	// (page 852 of Anton)
	//
	//				     ax + by + cz + d          Dot(N, v) + d
	//         -----------------------  =   ---------------
	//          sqrt(a^2 + b^2 + c^2)         Length(N)
	//
	// Since length of normal is 1.0 this evaluates to the following
	//
  ASSERT(vrEquals(Length(m_Normal),1.0f));
	return DotProduct(v, m_Normal) + m_D;
}

#endif
