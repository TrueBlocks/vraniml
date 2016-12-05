//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "types.h"

#include "vec3f.h"

SFVec3f::SFVec3f(const SFVec2f& v)
{
	x = v.x;
	y = v.y;
	z = 0.0;
}

SFFloat SignedDistance(const SFVec3f& pt1, const SFVec3f& pt2, const SFVec3f& dir)
{
  SFVec3f v = pt2 - pt1;

  SFFloat dist = Magnitude(v);

  if (Normalize(v) == Normalize(dir))
	{
    return -dist;
  } else
	{
    return dist;
  }
}

SFVec3f Projection(const SFVec3f& v, const SFVec3f& u)
{
  SFFloat len = Length(v);
  ASSERT(len);
  return (DotProduct(u, v) * v) / (len*len);
}

SFVec3f OrthoProjection(const SFVec3f& v, const SFVec3f& u)
{
  return u - Projection(v, u);
}

void Minimize(SFVec3f& min, const SFVec3f& Candidate)
{
  if (Candidate.x < min.x)
    min.x = Candidate.x;

  if (Candidate.y < min.y)
    min.y = Candidate.y;

  if (Candidate.z < min.z)
    min.z = Candidate.z;
}

void Maximize(SFVec3f& max, const SFVec3f& Candidate)
{
  if (Candidate.x > max.x)
    max.x = Candidate.x;

  if (Candidate.y > max.y)
    max.y = Candidate.y;

  if (Candidate.z > max.z)
    max.z = Candidate.z;
}

void GetProjectedVerts(const SFVec3f& v, SFFloat *px, SFFloat *py, SFInt32 which)
{
  switch (which)
	{
  case 0:
    *px = v.y;
    *py = v.z;
    break;
  case 1:
    *px = v.x;
    *py = v.z;
    break;
  case 2:
    *px = v.x;
    *py = v.y;
    break;
  }
}
