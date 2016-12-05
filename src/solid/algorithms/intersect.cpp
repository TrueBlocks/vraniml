//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Solid\Vertex.h"

extern SFBool Contains(vrVertex *, vrVertex *, vrVertex *);

/***********************************************************************/
/* 
 * Intersects an edge (v1--->v2) with a vertex v3 
*/
SFBool Intersects(vrVertex *v1, vrVertex *v2, vrVertex *v3, SFFloat& t)
{
  SFFloat len;
  
//  VRTRACE("Intersects edge with vertex (v1--->v2, v3)\n");
//  DEB(v1, "v1");
//  DEB(v2, "v2");
//  DEB(v3, "v3");
  
  SFVec3f r1 = *v2 - *v1;
  len = DotProduct(r1, r1);

//  VRTRACE("len: %f\n", len);
//  if (vrEquals(len, 0.0, EPS_SQUARED)) {
  if (len == 0.0) {
//    VRTRACE("len == 0.0 ----> returning v1 ?= v3: %d\n", (*v1 == *v3));
    t = 0.0f;
    return (*v1 == *v3);
  } 

  SFVec3f r2 = *v3 - *v1;
  t = DotProduct(r1, r2) / len;

  SFVec3f testv = *v1 + t * r1;


//  VRTRACE("t: %f testv: %f %f %f\n", t, testv.x, testv.y, testv.z);
//  VRTRACE("t: %f ----> returning (testv == *v3): %d\n", t, (testv == *v3));

  return (testv == *v3);
}

/***********************************************************************/
/* 
 * Intersects two edges (v1--->v2) and (v3--->v4) 
 */
SFBool Intersects(vrVertex *v1, vrVertex *v2, vrVertex *v3, vrVertex *v4,
		   SFInt32 drop, SFFloat& t1, SFFloat& t2)
{
  SFFloat d, a1, a2, b1, b2, c1, c2;
  
//  VRTRACE("Intersect two edges (v1-->v2) with (v3-->v4)\n");
//  DEB(v1, "v1");
//  DEB(v2, "v2");
//  DEB(v3, "v3");
//  DEB(v4, "v4");

  /* Project the points on an axial plane */
  switch (drop) {
  case 0:
    a1 = v2->y - v1->y;
    a2 = v2->z - v1->z;
    b1 = v3->y - v4->y;
    b2 = v3->z - v4->z;
    c1 = v1->y - v3->y;
    c2 = v1->z - v3->z;
    break;
  case 1:
    a1 = v2->x - v1->x;
    a2 = v2->z - v1->z;
    b1 = v3->x - v4->x;
    b2 = v3->z - v4->z;
    c1 = v1->x - v3->x;
    c2 = v1->z - v3->z;
    break;
  case 2:
    a1 = v2->x - v1->x;
    a2 = v2->y - v1->y;
    b1 = v3->x - v4->x;
    b2 = v3->y - v4->y;
    c1 = v1->x - v3->x;
    c2 = v1->y - v3->y;
    break;
  default:
    a1 = b1 = c1 = a2 = b2 = c2 = 0.0f;
    {
      // Should never happen
			//Uint32 invalid_drop=0;
      ASSERT(0);
    }
  }

  d = (a1*b2 - a2*b1);

//  VRTRACE("a1: %f  a2: %f  b1: %f  b2: %f  c1: %f  c2: %f\n", a1, a2, b1, b2, c1, c2);
//  VRTRACE("d: %f\n", d);

  if (vrCompare(d, 0.0f) == 0)
	{
//    VRTRACE("d equals 0.0 returning FALSE\n");
    return FALSE;
  }

  t1 = (c2*b1 - c1*b2) / d;
  t2 = (a2*c1 - a1*c2) / d;

//  VRTRACE("t1: %f   t2: %f returning TRUE\n", t1, t2);

  return TRUE;
}

