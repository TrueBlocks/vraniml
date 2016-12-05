//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "BoolOp.h"
#include "BoolVertexClassify.h"

SFBool  SectorWithin     (const SFVec3f& fInter, const SFVec3f& vNext, const SFVec3f& vPrev, const SFVec3f& vCross, SFBool bi);
SFBool  SectorOverlap    (vrHalfEdge *he1, vrHalfEdge *he2);
SFBool  SectorsIntersect (vrVertex *v1, vrVertex *v2, vrVertex *v3, vrVertex *v4, SFBool drop);

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
SFBool SectorTest(vrVVNeighborhood *nhA, vrVVNeighborhood *nhB)
{
// Summary:
//
//  if (faces are co-planar)
//	{
//		use SectorOverlap to determine if sectors intersect
//  } else
//  {
//		use SectorWithin to determine if sectors intersect
//
//#if 0
//  ...then (if this first test returns FALSE) Mantyla does this:
//       Reverse the CrossProduct of the Face Normals and Try Again
//#endif
//  }
//
//
//
//
  SFVec3f fInter(0.0f);
  
  vrHalfEdge *h1 = nhA->he;
  vrHalfEdge *h2 = nhB->he;
  
//  DEBI(h1->GetFace(), "\t\th1->GetFace()");
//  DEBI(h2->GetFace(), "\t\th2->GetFace()");

  if (Colinear(h1->GetFaceNormal(), h2->GetFaceNormal(), &fInter))
	{
		VRTRACE("\t\tSectorOverlap: ");
    return SectorOverlap(h1, h2);
  } else
	{
		SFBool biA = (nhB->fromBisect) ? 0 : nhA->fromBisect; // 1== first half, 2 == second half
		SFBool biB = (nhA->fromBisect) ? 0 : nhB->fromBisect; // 1== first half, 2 == second half

		ASSERT(fInter!=SFVec3f(0.0f));

VRTRACE("\t\tA-Normal: %d ", nhA->fromBisect);
		SFBool c1 = SectorWithin(fInter, nhA->vNext, nhA->vPrev, nhA->vCross, biA);
VRTRACE("\n\t\tB-Normal: %d ", nhB->fromBisect);
		SFBool c2 = SectorWithin(fInter, nhB->vNext, nhB->vPrev, nhB->vCross, biB);

		VRTRACE("\n\t\tc1: %d  c2: %d\n", c1, c2);

		if (c1 && c2)
		{
			VRTRACE("\t\treturning TRUE\n");
			return TRUE;
  	} else
		{
#ifdef _DEBUG
			SFBool cc1=c1;
			SFBool cc2=c2;
#endif

			fInter = -fInter;

VRTRACE("\t\tA-Negate: %d ", nhA->fromBisect);
			c1 = SectorWithin(fInter, nhA->vNext, nhA->vPrev, nhA->vCross, biA);
VRTRACE("\n\t\tB-Negate: %d ", nhB->fromBisect);
			c2 = SectorWithin(fInter, nhB->vNext, nhB->vPrev, nhB->vCross, biB);

			VRTRACE("\n\t\tc1: %d  c2: %d\n", c1, c2);

			if (c1 && c2)
			{
				ASSERT(cc1 == cc2);
				VRTRACE("\t\treturning TRUE\n");
				return TRUE;
			}
		}
  
		VRTRACE("\t\treturning FALSE\n");
		return FALSE;
	}

	ASSERT(0);
	// never happens
	return FALSE;
}
 
SFBool SectorOverlap(vrHalfEdge *he1, vrHalfEdge *he2)
{
	SFVec3f n1 = Normalize(he1->GetFaceNormal());
	SFVec3f n2 = Normalize(he2->GetFaceNormal());

#ifdef _DEBUG
	ASSERT(n1 == n2 || n1 == -n2);
#endif

	if (n1 == -n2)
	{
//		VRTRACE("\t\tSectorOverlap: (%d-%d-%d) (%d-%d-%d) --> Normals opposite --> return FALSE\n",
//      he1->Prev()->GetIndex(), he1->GetIndex(), he1->Next()->GetIndex(),
//      he2->Prev()->GetIndex(), he2->GetIndex(), he2->Next()->GetIndex());
		VRTRACE("--> normals opposite --> FALSE\n");
		return FALSE;
  }

//	VRTRACE("\t\tSectorOverlap: (%d-%d-%d) (%d-%d-%d)\n",
//      he1->Prev()->GetIndex(), he1->GetIndex(), he1->Next()->GetIndex(),
//      he2->Prev()->GetIndex(), he2->GetIndex(), he2->Next()->GetIndex());

	vrVertex *v1 = he1->Prev()->GetVertex();
	vrVertex *v2 = he1->GetVertex();
	vrVertex *v3 = he1->Next()->GetVertex();

	vrVertex *v4 = he2->Prev()->GetVertex();
	vrVertex *v5 = he2->GetVertex();
	vrVertex *v6 = he2->Next()->GetVertex();

	SFInt32 drop = GetDominantComp(he1->GetFaceNormal());
	ASSERT(drop == GetDominantComp(he2->GetFaceNormal()));

	//
	//   v1          v2           v3
 	//   0-----------0------------0
  //
	//       v4          v5           v6
 	//       0-----------0------------0
	//
	// Note: these may not be in a line, but they are in a plane....

	if (SectorsIntersect(v1, v2, v4, v5, drop))
		return TRUE;

  if (SectorsIntersect(v1, v2, v5, v6, drop))
		return TRUE;

  if (SectorsIntersect(v2, v3, v4, v5, drop))
		return TRUE;

  if (SectorsIntersect(v2, v3, v5, v6, drop))
		return TRUE;
  
  VRTRACE("--> no overlap --> FALSE\n");
  return FALSE;
}

#if 1
#define NOINTER 0
#define COLINEAR 1
#define INTER 2

int lines_intersect(vrVertex *v1, vrVertex *v2, vrVertex *v3, vrVertex *v4, long drop, SFFloat& x, SFFloat& y)
{
	float x1=0, x2=0, x3=0, x4=0, y1=0, y2=0, y3=0, y4=0;

  switch (drop)
	{
	case 0:
    x1 = v1->y;
    x2 = v2->y;
    x3 = v3->y;
    x4 = v4->y;
    y1 = v1->z;
    y2 = v2->z;
    y3 = v3->z;
    y4 = v4->z;
    break;
  case 1:
    x1 = v1->x;
    x2 = v2->x;
    x3 = v3->x;
    x4 = v4->x;
    y1 = v1->z;
    y2 = v2->z;
    y3 = v3->z;
    y4 = v4->z;
    break;
  case 2:
    x1 = v1->x;
    x2 = v2->x;
    x3 = v3->x;
    x4 = v4->x;
    y1 = v1->y;
    y2 = v2->y;
    y3 = v3->y;
    y4 = v4->y;
    break;
	default:
		{
			// should not happen
			ASSERT(0);
		}
	}

VRTRACE("--> (%d-%d)x(%d-%d) --> ", v1->GetIndex(), v2->GetIndex(), v3->GetIndex(), v4->GetIndex());

	float a1, a2, b1, b2, c1, c2;
	float r1, r2, r3, r4;
	float denom, num;
	
	// Coefficients of line equation for L12
	a1 = y2 - y1;
	b1 = x1 - x2;
	c1 = x2 * y1 - x1 * y2;
	
	// Evaluate pt3 and pt4 in L12
	r3 = a1 * x3 + b1 * y3 + c1;
	r4 = a1 * x4 + b1 * y4 + c1;

#if 1
	// One of them better be on the line!
	ASSERT(vrCompare(r3, 0.0f) == 0 || vrCompare(r4, 0.0f) == 0);
#else
	// If pt3 and pt 4 are not on line L12 and they are 
	//  on the same side of the line as each other 
	//  they can't intersect.
	if (r3 != 0 &&
			r4 != 0 &&
			SAME_SIGNS(r3, r4))
			return NOINTER;
#endif
			
	// Coefficients of line equation for L34
	a2 = y4 - y3;
	b2 = x3 - x4;
	c2 = x4 * y3 - x3 * y4;
	
	// Evaluate pt1 and pt2 in L34
	r1 = a2 * x1 + b2 * y1 + c2;
	r2 = a2 * x2 + b2 * y2 + c2;

#if 1
	// One of them better be on the line!
	ASSERT(vrCompare(r1, 0.0f) == 0 || vrCompare(r2, 0.0f) == 0);
#else
	// If pt1 and pt2 are not on line L34 and they are 
	//  on the same side of the line as each other 
	//  they can't intersect.
	if (r1 != 0 &&
			r2 != 0 &&
			SAME_SIGNS(r1, r2))
			return NOINTER;
#endif

	denom = a1 * b2 - a2 * b1;
	if (denom == 0)
	{
VRTRACE("colinear --> TRUE\n");
		return COLINEAR;
	}

	//r1 == dist of x1 y1 from L34
	//r2 == dist of x2 y2 from L34
	//r3 == dist of x3 y3 from L12
	//r4 == dist of x4 y4 from L12 (neg == 
	if (r1 < 0.0 || r2 < 0.0)
	{
VRTRACE("r1 < 0.0 or r2 < 0.0 --> FALSE\n");
		return NOINTER;
	}
	
	if (r3 < 0.0 || r4 < 0.0)
	{
VRTRACE("r3 < 0.0 or r4 < 0.0 --> FALSE\n");
return NOINTER;
	}

  num = b1 * c2 - b2 * c1;
	x = num / denom;

	num = a2 * c1 - a1 * c2;
	y = num / denom;

VRTRACE("intersects --> TRUE\n");
	return INTER;
}
#endif

SFBool SectorsIntersect(vrVertex *v1, vrVertex *v2, vrVertex *v3, vrVertex *v4, SFBool drop)
{
#if 1
	SFFloat x, y;
	return lines_intersect(v1, v2, v3, v4, drop, x, y);
#else
  //
	// Note: Test two edges ((v1->v2) and (v3->v4)) in the same plane for intersection
  //

//	VRTRACE("\t\t\tTesting (%d %d)-->(%d %d)\n", v1->GetIndex(), v2->GetIndex(), v3->GetIndex(), v4->GetIndex());

  SFFloat t1, t2;
  
  if (Intersects(v1, v2, v3, v4, drop, t1, t2)) 
	{
    SFInt32 c10 = vrCompare(t1, 0.0f);
    SFInt32 c20 = vrCompare(t2, 0.0f);
    SFInt32 c21 = vrCompare(t2, 1.0f);
    if (c20 == 0 || c21 == 0)
		{
//		  VRTRACE("\t\t\t\tVertex intersection --> returning TRUE\n");
      return TRUE;
    }

    if (c21 == -1 && c20 == 1)
		{
		  if (c10 >= 0)
			{
//  		  VRTRACE("\t\t\t\tRegular crossing --> returning TRUE\n");
			  return TRUE;
			}
    }
  }

//  VRTRACE("\t\t\t\tNo crossing --> returning FALSE\n");
  return FALSE;
#endif
}

SFBool SectorWithin(const SFVec3f& fInter, const SFVec3f& vNext, const SFVec3f& vPrev, const SFVec3f& vCross, SFBool bi)
{
  //
	// Called when the faces of the two halfedges are NOT co-planar
	//
//	VRTRACE("\t\tSectorWithin:\n\t\t\tcross of face normals: (%f, %f, %f)\n", fInter.x, fInter.y, fInter.z);
	
	SFVec3f cross1, cross2;
//	VRTRACE("\t\t\twith vPrev: (%f, %f, %f)\n", vPrev.x, vPrev.y, vPrev.z);
	if(Colinear(vPrev, fInter, &cross2))
	{
		VRTRACE("--> Prev ");
		SFFloat dot = DotProduct(fInter, vPrev);
    if (vrCompare(dot, 0.0f) == 1)
		{
//			VRTRACE("\t\t\tco-linear --> same direction --> intersects\n");
			VRTRACE("--> same --> TRUE");
			return TRUE; //(bi != 1);
		} else
		{
			ASSERT(vrCompare(dot, 0.0f) != 0);
//			VRTRACE("\t\t\tco-linear --> opposite direction --> does not intersect\n");
			VRTRACE("--> opposite --> FALSE");
			return FALSE;
		}
  }

//	VRTRACE("\t\t\twith vNext: (%f, %f, %f)\n", vNext.x, vNext.y, vNext.z);
  if (Colinear(fInter, vNext, &cross1))
 	{
		VRTRACE("--> Next ");
		SFFloat dot = DotProduct(fInter, vNext);
    if (vrCompare(dot, 0.0f) == 1)
		{
//			VRTRACE("\t\t\tco-linear --> same direction --> intersects\n");
			VRTRACE("--> same --> TRUE");
			return TRUE; //(bi != 2);
		} else
		{
			ASSERT(vrCompare(dot, 0.0f) != 0);
//			VRTRACE("\t\t\tco-linear --> opposite direction --> does not intersect\n");
			VRTRACE("--> opposite --> FALSE");
			return FALSE;
		}
  }

#ifdef _DEBUG
if(vCross == SFVec3f(0.0f))
{
	ASSERT(0);
	ASSERT(Colinear(cross1, cross2));
	ASSERT(Colinear(vNext, vPrev));
}
#endif

/*
if (vCross==SFVec3f(0.0f))
{
	return TRUE;
}
*/

//	VRTRACE("\t\t\tcross of vNext and vPrev: (%f, %f, %f)\n", vCross.x, vCross.y, vCross.z);
  SFFloat angle1 = DotProduct(cross1, vCross);
  SFFloat angle2 = DotProduct(cross2, vCross);

  SFInt32 cl1 = vrCompare(angle1, 0.0f, EPS_SQUARED);
  SFInt32 cl2 = vrCompare(angle2, 0.0f, EPS_SQUARED);

//	VRTRACE("\t\t\tangle of cross1 and vCross: %f >90 degrees?(t1): %d\n", angle1, cl1);
//	VRTRACE("\t\t\tangle of cross1 and vCross: %f >90 degrees?(t2): %d\n", angle2, cl2);
//	VRTRACE("\t\t\treturning %d (cl1 < 0 && cl2 < 0)\n", (cl1 < 0 && cl2 < 0));

  return (cl1 < 0 && cl2 < 0);
}
 
