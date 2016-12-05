//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "types.h"

#include "plane.h"

//----------------------------------------------------------------------
vrPlane::vrPlane(void)
{
  m_Normal = SFVec3f(1.0f, 0.0f, 0.0f);
  m_D      = 0.0f;
}

vrPlane::vrPlane(const vrPlane& p)
{
	m_Normal = p.m_Normal;
  ASSERT(!vrCompare(Length(m_Normal), 1.0f));
  m_D      = p.m_D;
}

vrPlane::vrPlane(SFFloat A, SFFloat B, SFFloat C, SFFloat D)
{
  m_Normal.x = A;
  m_Normal.y = B;
  m_Normal.z = C;
	m_Normal   = Normalize(m_Normal);
  m_D        = D;
}

vrPlane::vrPlane(const SFVec3f& normal, SFFloat D)
{
  m_Normal.x = normal.x;
  m_Normal.y = normal.y;
  m_Normal.z = normal.z;
	m_Normal   = Normalize(m_Normal);
  m_D        = D;
}

vrPlane::~vrPlane()
{
}

vrPlane& vrPlane::operator=(const vrPlane& p)
{
  m_Normal = p.m_Normal;
  ASSERT(!vrCompare(Length(m_Normal), 1.0f));
  m_D      = p.m_D;
  return *this;
}

//----------------------------------------------------------------------
// Algorithm from Graphics Gems III page 233
vrLine vrPlane::Intersect(const vrPlane& p) const
{
  SFFloat I = m_D;
  SFFloat J = p.m_D;
  SFVec3f M = m_Normal;
  SFVec3f N = p.m_Normal;
  SFVec3f L = CrossProduct(M,N);

  SFVec3f P;

  // Planes are parallel
  if (L == SFVec3f(0.0f))
    return vrLine(SFVec3f(0.0f), SFVec3f(0.0f));

   // Pick the largest component of L, this to avoid numerical problems
  switch (GetDominantComp(L))
	{
  case 0:
    P[0] = 0.0f;
    P[1] = (M[2]*J - N[2]*I) / L[0];
    P[2] = (N[1]*I - M[1]*J) / L[0];
    return vrLine(P, L);
  case 1:
    P[0] = (M[2]*J - N[2]*I) / L[1];
    P[1] = 0.0f;
    P[2] = (N[0]*I - M[0]*J) / L[1];
    return vrLine(-P, L);
  case 2:
    P[0] = (M[1]*J - N[1]*I) / L[2];
    P[1] = (N[0]*I - M[0]*J) / L[2];
    P[2] = 0.0f;
    return vrLine(P, L);
  }
  
  // Should never happen
	ASSERT(0);
  return vrLine(SFVec3f(0.0f), SFVec3f(0.0f));
}

SFBool vrPlane::Intersect(const vrLine& ray, SFFloat& t, SFFloat maxt) const
{
  SFFloat dot = DotProduct(m_Normal, ray.m_Dir);
  
  // Watch for near-zero denominator
  if (fabs(dot) < 0.00001) 
    return FALSE;
  
  t = (-m_D - DotProduct(m_Normal, ray.m_Loc)) / dot;
  
  return (maxt == maxt);
}

SFBool vrPlane::XIntercept(SFVec3f *res) const
{
  SFFloat val = m_Normal.x;

  (*res)[0] = (*res)[1] = (*res)[2] = 0.0f;

  if (val != 0.0)
	{
    (*res)[0] = -m_D/val;
    return TRUE;
  } else
	{
    return FALSE;
  }
}

SFBool vrPlane::YIntercept(SFVec3f *res) const
{
  SFFloat val = m_Normal.y;

  (*res)[0] = (*res)[1] = (*res)[2] = 0.0f;

  if (val != 0.0)
	{
    (*res)[1] = -m_D/val;
    return TRUE;
  } else
	{
    return FALSE;
  }
}

SFBool vrPlane::ZIntercept(SFVec3f *res) const
{
  SFFloat val = m_Normal.z;

  (*res)[0] = (*res)[1] = (*res)[2] = 0.0f;

  if (val != 0.0)
	{
    (*res)[2] = -m_D/val;
    return TRUE;
  } else
	{
    return FALSE;
  }
}
