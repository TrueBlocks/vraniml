//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "types.h"

#include "boundingbox.h"

//----------------------------------------------------------------------
vrBoundingBox::vrBoundingBox()
{ 
  m_Min =  FLT_MAX;
  m_Max = -FLT_MAX;
}

vrBoundingBox::vrBoundingBox(const vrBoundingBox& aBox)
{ 
  m_Min = aBox.m_Min;
  m_Max = aBox.m_Max;
}
  
vrBoundingBox::vrBoundingBox(const SFVec3f& min, const SFVec3f& max)
{ 
  m_Min = min;
  m_Max = max;
}
  
vrBoundingBox::~vrBoundingBox() 
{ 
}
  
vrBoundingBox& vrBoundingBox::operator=(const vrBoundingBox& aBox)
{ 
  m_Min = aBox.m_Min;
  m_Max = aBox.m_Max;
	return *this;
}
  
//----------------------------------------------------------------------
SFFloat vrBoundingBox::SurfaceArea() const
{
  SFVec3f ext = m_Max - m_Min;
  
  return (2 * (ext.x * ext.y + ext.x * ext.z + ext.y * ext.z));
}

SFBool vrBoundingBox::IsInside(const SFVec3f& v) const
{
  return !(v.x < m_Min.x ||
						v.x > m_Max.x ||
						v.y < m_Min.y ||
						v.y > m_Max.y ||
						v.z < m_Min.z ||
						v.z > m_Max.z);
}

//----------------------------------------------------------------------
SFBool Overlap(const vrBoundingBox& x, const vrBoundingBox& y)
{
  if (x.m_Max.x < y.m_Min.x)
		return FALSE;
	
	if (x.m_Min.x > y.m_Max.x)
		return FALSE;

	if (x.m_Max.y < y.m_Min.y)
		return FALSE;
		
	if (x.m_Min.y > y.m_Max.y)
		return FALSE;
		
	if (x.m_Max.z < y.m_Min.z)
		return FALSE;
		
	if (x.m_Min.z > y.m_Max.z)
    return FALSE;

	return TRUE;
}

vrBoundingBox Intersect(const vrBoundingBox& x, const vrBoundingBox& y)
{
  if (x.IsDefault())
    return y;
  else if (y.IsDefault())
    return x;
  
  vrBoundingBox ret = x;
  
  if (Overlap(ret, y))
	{
    Maximize(ret.m_Min, y.m_Min);
    Minimize(ret.m_Max, y.m_Max);
    return ret;
  } else {
    // Null intersection.
    return vrBoundingBox(SFVec3f(0.0f), SFVec3f(0.0f));
  }
}

vrBoundingBox Union(const vrBoundingBox& x, const vrBoundingBox& y)
{
  SFVec3f min = x.m_Min;
  SFVec3f max = x.m_Max;
  
  Minimize(min, y.m_Min);
  Maximize(max, y.m_Max);
  
  return vrBoundingBox(min, max);
}

vrBoundingBox TransformBox(const vrBoundingBox& box, const vrMatrix& tform)
{
  vrBoundingBox ret;
  
  ret.Include(tform * SFVec3f(box.m_Min.x, box.m_Min.y, box.m_Min.z));
  ret.Include(tform * SFVec3f(box.m_Min.x, box.m_Min.y, box.m_Max.z));
  ret.Include(tform * SFVec3f(box.m_Min.x, box.m_Max.y, box.m_Min.z));
  ret.Include(tform * SFVec3f(box.m_Min.x, box.m_Max.y, box.m_Max.z));
  ret.Include(tform * SFVec3f(box.m_Max.x, box.m_Min.y, box.m_Min.z));
  ret.Include(tform * SFVec3f(box.m_Max.x, box.m_Min.y, box.m_Max.z));
  ret.Include(tform * SFVec3f(box.m_Max.x, box.m_Max.y, box.m_Min.z));
  ret.Include(tform * SFVec3f(box.m_Max.x, box.m_Max.y, box.m_Max.z));
  
  return ret;
}

SFInt32 vrBoundingBox::Intersect(const vrRay& ray, SFFloat *tmin, SFFloat *tmax) const
{
	SFFloat t1, t2;
	SFFloat minx, maxx, miny, maxy, minz, maxz;

	if (fabs(ray.m_Dir.x) < 0.001)
	{
		if (m_Min.x < ray.m_Loc.x && m_Max.x > ray.m_Loc.x)
		{
			minx = -FLT_MAX;
			maxx = FLT_MAX;
		} else
		{
			return FALSE;
		}
	} else
	{
		t1 = (m_Min.x - ray.m_Loc.x) / ray.m_Dir.x;
		t2 = (m_Max.x - ray.m_Loc.x) / ray.m_Dir.x;
		if (t1 < t2)
		{
			minx = t1;
			maxx = t2;
		} else
		{
			minx = t2;
			maxx = t1;
		}
		if (maxx < 0)
		{
			return FALSE;
		}
	}

	if (fabs(ray.m_Dir.y) < 0.001)
	{
		if (m_Min.y < ray.m_Loc.y && m_Max.y > ray.m_Loc.y)
		{
			miny = -FLT_MAX;
			maxy = FLT_MAX;
		}
		else
		{
			return FALSE;
		}
	} else
	{
		t1 = (m_Min.y - ray.m_Loc.y) / ray.m_Dir.y;
		t2 = (m_Max.y - ray.m_Loc.y) / ray.m_Dir.y;
		if (t1 < t2)
		{
			miny = t1;
			maxy = t2;
		} else
		{
			miny = t2;
			maxy = t1;
		}
		if (maxy < 0)
		{
			return FALSE;
		}
	}

	if (fabs(ray.m_Dir.z) < 0.001)
	{
		if (m_Min.z < ray.m_Loc.z && m_Max.z > ray.m_Loc.z)
		{
			minz = -FLT_MAX;
			maxz = FLT_MAX;
		}
		else
		{
			return FALSE;
		}
	} else
	{
		t1 = (m_Min.z - ray.m_Loc.z) / ray.m_Dir.z;
		t2 = (m_Max.z - ray.m_Loc.z) / ray.m_Dir.z;
		if (t1 < t2)
		{
			minz = t1;
			maxz = t2;
		} else
		{
			minz = t2;
			maxz = t1;
		}
		if (maxz < 0)
		{
			return FALSE;
		}
	}

	if (tmin)
	{
		*tmin = minx;
		if (miny > *tmin)
			*tmin = miny;
		if (minz > *tmin)
			*tmin = minz;
	}

	if (tmax)
	{
		*tmax = maxx;
		if (maxy < *tmax)
			*tmax = maxy;
		if (maxz < *tmax)
			*tmax = maxz;
	}

	return TRUE;
}

