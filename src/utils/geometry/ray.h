#ifndef __RAY_H3D
#define __RAY_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

#include "vec2f.h"
#include "vec3f.h"
#include "matrix.h"
#define vrLine vrRay

/*----------------------------------------------------------------------
CLASS
	vrRay

	Represents a line segment in 3-space.

DESCRIPTION
	<ul>
	Utility class for representing 3d rays or line segments.  Used in 
	various places for calculation of intersections, etc.
	</ul>

NOTES
	<ul>
	<li>The symbol vrLine is #defined as a synonym of vrRay and is used interchangably.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// A vrRay can be used to calculate intersections for visiblity
	// calculations or plane intersections (among other things):
	SFNode model = new vrBox;

	// a bounding box from some VRML model
	vrBoundingBox box = model->GetBoundingBox(); 
	vrRay lineOfSite = GetLineOfSite();

	if (box.Intersect(lineOfSite))
		prinf("Ray hits bounding box\n");
	else
		prinf("Ray does not hit bounding box\n");

	vrPlane plane1(xAxis, 1.0);
	vrPlane plane2(yAxis, 1.0);

	// The intersection of two planes is a ray:
	vrRay intersection = plane1.Intersect(plane2);
	printf("intersection: (%f,%f) to (%f,%f)\n", 
			intersection.m_Loc.x,
			intersection.m_Loc.y,
			intersection.m_Dir.x,
			intersection.m_Dir.y);
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class vrRay 
{
public:
  //<doc>------------------------------------------------------------
  // <dd>The starting point of the ray.
	// [default:] (0.0,0.0,0.0)
	//
  SFVec3f        m_Loc;

  //<doc>------------------------------------------------------------
  // <dd>The direction and magnitude of the ray.
	// [default:] (0.0,0.0,0.0)
	//
  SFVec3f        m_Dir;

public:
  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	vrRay          (void);

  //<doc>------------------------------------------------------------
  // <dd>Copy constructor.
	//
	vrRay          (const vrRay& ray);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] from: The starting point of the ray.
	// [in] dir: The direction and magnitude of the ray.
	//
	vrRay          (const SFVec3f& from, const SFVec3f& dir);

  //<doc>------------------------------------------------------------
  // <dd>Destructor.
	//
	~vrRay          (void);

  //<doc>------------------------------------------------------------
  // <dd>Equal operator.
	//
  vrRay&      operator=      (const vrRay& r);
  
  //<doc>------------------------------------------------------------
  // <dd>Return the distance of the vector from this line.
	//
	// [in] v: The query vector.
	//
  SFFloat     GetDistance    (const SFVec3f& v) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns the value calculated by substituing the vector into the line equation.
	//
	// [in] v: The vector.
	//
  SFFloat     Evaluate       (const SFVec3f& v) const;

  //<doc>------------------------------------------------------------
  // <dd>Return the point on the line represented by the value of 't' when the line equation is evaluated.
	//
	// [in] t: The value of 't' at which to evaluate the line.
	//
  SFVec3f     Extrapolate    (SFFloat t) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns the value of 't' that would evaluate to the given vector.
	//
	// [in] v: The vector (it should be on the line).
	//
  SFFloat     Interpolate    (const SFVec3f& x) const;

  //<doc>------------------------------------------------------------
  // <dd>Reflect the vector about the line.
	//
	// [in] v: The vector to reflect.
	//
  SFVec3f     ReflectRay     (const SFVec3f& v) const;

  //<doc>------------------------------------------------------------
  // <dd>Transform the ray by the given matrix.
	//
	// [in] tform: The transformation to apply to this line.
	//
  void        ApplyTransform (const vrMatrix& tform);

private:
  void        Precompute     (void);
  SFVec3f     m_LocSqrd;
  SFVec3f     m_LocDir;
  SFVec3f     m_DirSqrd;
};

//----------------------------------------------------------------------
inline vrRay::vrRay(void) 
{
  m_Loc = SFVec3f(0.0f);
  m_Dir = Normalize(SFVec3f(1.0f));
  Precompute();
}

inline vrRay::vrRay(const vrRay& ray) 
{
  m_Loc = ray.m_Loc;
  m_Dir = ray.m_Dir;
  Precompute();
}

inline vrRay::vrRay(const SFVec3f& from, const SFVec3f& direction) 
{
  m_Loc = from;
  m_Dir = Normalize(direction);
  Precompute();
}

inline vrRay::~vrRay() 
{
}

inline vrRay& vrRay::operator=(const vrRay& ray)
{
  m_Loc = ray.m_Loc;
  m_Dir = ray.m_Dir;
  Precompute();
    
  return *this;
}

//----------------------------------------------------------------------
inline SFVec3f vrRay::Extrapolate(SFFloat t) const
{ 
  return m_Loc + m_Dir * t; 
}

inline SFFloat vrRay::Interpolate(const SFVec3f& x) const
{
  for (SFInt32 i = 0; i < 3; i++) 
    if (fabs(m_Dir[i]) > 0.00001) 
      return (x[i] - m_Loc[i]) / m_Dir[i];
  
  return 0.0f;
}
  
inline SFVec3f vrRay::ReflectRay(const SFVec3f& N) const
{ 
  return N * 2.0f * DotProduct(N, -m_Dir) + m_Dir; 
}
  
inline void vrRay::Precompute(void)
{
  m_LocSqrd = m_Loc * m_Loc;
  m_LocDir  = m_Loc * m_Dir;
  m_DirSqrd = m_Dir * m_Dir;
}

inline void vrRay::ApplyTransform(const vrMatrix& tform)
{
  m_Loc = tform * m_Loc;
  m_Dir = RotateOnly(tform, m_Dir);
  Precompute();
}

inline SFFloat vrRay::GetDistance(const SFVec3f& v) const
{
  SFVec3f vv  = OrthoProjection(m_Dir, v);
  SFFloat len = Length(vv);
  return len;
}

//----------------------------------------------------------------------
extern SFBool Colinear(const SFVec3f& v1, const SFVec3f& v2, const SFVec3f& v3);

#endif
