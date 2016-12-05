//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Solid\Solid.h"

SFBool CrossingsTest( SFFloat pgon[][2], Uint32 numverts, SFFloat point[2]);

SFBool vrLoop::CheckForContainment(const SFVec3f& pt, SFInt32 drop) const
{
  SFFloat p[100][2];

	SFInt32 i=0;

	LISTPOS hPos = halfedges.GetHeadPosition();
	while (hPos)
	{
		vrHalfEdge *he = halfedges.GetNext(hPos);

		vrVertex *v = he->GetVertex();
    switch (drop) {
    case 0:
      p[i][0] = v->y;
      p[i][1] = v->z;
      break;
    case 1:
      p[i][0] = v->x;
      p[i][1] = v->z;
      break;
    case 2:
      p[i][0] = v->x;
      p[i][1] = v->y;
      break;
    }
		i++;
  }
  
  SFFloat pt1[2];

  switch (drop) {
  case 0:
    pt1[0] = pt[1];
    pt1[1] = pt[2];
    break;
  case 1:
    pt1[0] = pt[0];
    pt1[1] = pt[2];
    break;
  case 2:
    pt1[0] = pt[0];
    pt1[1] = pt[1];
    break;
  }

  return CrossingsTest(p, i, pt1);
}

/* From Graphics Gems IV */
/* ======= Crossings algorithm ============================================ */
/* Shoot a test ray along +X axis.  The strategy, from MacMartin, is to
 * compare vertex Y values to the testing point's Y and quickly discard
 * edges which are entirely to one side of the test ray.
 *
 * Input 2D polygon _pgon_ with _numverts_ number of vertices and test point
 * _point_, returns 1 if inside, 0 if outside.  WINDING and CONVEX can be
 * defined for this test.
 */
#pragma warning(disable : 4706)

SFBool CrossingsTest( SFFloat pgon[][2], Uint32 numverts, SFFloat point[2])
{
  SFBool inside_flag;
  register SFInt32 j, yflag0, yflag1, xflag0;
  register SFFloat ty, tx, *vtx0, *vtx1;

  tx = point[0];
  ty = point[1];

  vtx0 = pgon[numverts-1];
  
#define Y 1
#define X 0
  /* get test bit for above/below X axis */
  yflag0 = ( vtx0[Y] >= ty );
  vtx1 = pgon[0];

  inside_flag = 0;

  for ( j = numverts+1; --j; ) {

    yflag1 = ( vtx1[Y] >= ty ) ;
    
    /*
     * check if endpoints straddle (are on opposite sides) of X axis
     * (i.e. the Y's differ); if so, +X ray could intersect this edge.
     */
    if ( yflag0 != yflag1 ) {
      xflag0 = ( vtx0[X] >= tx ) ;
      /*
       * check if endpoints are on same side of the Y axis (i.e. X's
       * are the same); if so, it's easy to test if edge hits or misses.
       */
      if ( xflag0 == ( vtx1[X] >= tx ) ) {
  
        /* if edge's X values both right of the point, must hit */
        if ( xflag0 ) 
          inside_flag = !inside_flag ;
      } else {
        /*
         * compute intersection of pgon segment with +X ray, note
         * if >= point's X; if so, the ray hits it.
         */
        if ( (vtx1[X] - (vtx1[Y]-ty)*
             (vtx0[X]-vtx1[X])/(vtx0[Y]-vtx1[Y])) >= tx ) {
          inside_flag = !inside_flag ;
        }
      }
    }
    
    /* move to next pair of vertices, retaining info as possible */
    yflag0 = yflag1;
    vtx0 = vtx1; 
    vtx1 += 2;
  }

  return inside_flag;
}

