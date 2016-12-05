//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Solid\Solid.h"
#include "Solid\Vertex.h"
#include "Solid\Loop.h"

SFBool Contains(vrVertex *v1, vrVertex *v2, vrVertex *v3)
{
  SFFloat t;

  if (Intersects(v1, v2, v3, t)) {
    if (t >= (0.0-0.00001) && t <= (1.0+0.00001)) {
      return TRUE;
    }
  }
  
  return FALSE;
}

SFBool vrLoop::BoundaryContains(vrVertex *v, vrIntersectRecord& rec) const
{
  /* 
   * Check to see if the vertex is coincident with any verts in this loop 
   */
//  VRTRACE("Checking for VERT HIT's\n");

  LISTPOS hPos = halfedges.GetHeadPosition();
	while (hPos)
	{
		vrHalfEdge *he = halfedges.GetNext(hPos);

//		DEB(he->GetVertex(), "he->GetVertex()");
//		DEB(v, "v");
    if (*he->GetVertex() == *v) 
		{
//			VRTRACE("Found a VERTEX HIT");
      rec.RecordHit(NULL, he->GetVertex(), VERTEX_HIT);
      return TRUE;
    }
  }

  /* 
   * Check to see if the vertex intersects any edges of this face 
   */
//	VRTRACE("No VERTEX_HIT looking for EDGE_HITS\n");
  hPos = halfedges.GetHeadPosition();
	while (hPos)
	{
		vrHalfEdge *he = halfedges.GetNext(hPos);

//		DEB(he->GetVertex(), "he->GetVertex()");
//		DEB(he->Next()->GetVertex(), "he->Next()->GetVertex()");
//		DEB(v, "v");
    if (::Contains(he->GetVertex(), he->Next()->GetVertex(), v)) 
		{
//			VRTRACE("Found an EDGE_HIT\n");
      rec.RecordHit(he, NULL, EDGE_HIT);
      return TRUE;
    }
  }

  /* 
   * vrVertex does not hit any edges or verts of the face 
   */
//	VRTRACE("No Boundary hits\n");
  return FALSE;
}

SFBool vrLoop::Contains(vrVertex *v, SFInt32 drop, vrIntersectRecord& rec) const
{
#if 0
  SFFloat t1, t2;

  /* 
   * Check first for hits of 'v' with verts or edges of loop 
   */
	VRTRACE("Looking for Boundary hits\n");
  if (BoundaryContains(v, rec)) {
    return TRUE;
  }

	VRTRACE("Looking for vrFace hits\n");
  /* 
   * If not, pick any edge of the loop... 
   */
  vrHalfEdge *he2 = edges.GetHead();

 retry:
  /* 
   * ...and find it's midpoint. 
   */
  vrVertex *v1 = he2->GetVertex();
  vrVertex *v2 = he2->Next()->GetVertex();

  /* 
   * ...the ray (v--->aux) is a ray to infinity 
   */
  vrVertex aux((*v1 + *v2) / 2.0);

  vrHalfEdge *he = he2;  // Mantyla has 'he = l->edges.GetHead()' but I found it didn't work
  Uint32 cnt = 0;
  
  /* 
   * Now scan the edges, intersecting each with the ray and count the hits. 
   */
  do {
		DEB(v1, "v1");
		DEB(v2, "v2");
		DEB(&aux, "aux");
		DEB(v, "v");

    if (Intersects(v, &aux, v1, v2, drop, t1, t2)) {
			VRTRACE("Intersects: t1: %f  t2: %f\n", t1, t2);
			
      /* If the test ray hits a vertex in the loop.... */
      if (vrEquals(t2, 0.0) || vrEquals(t2, 1.0)) {
				VRTRACE("vrRay hits a vertex -- Trouble trying again\n");
				/* If the ray hits a vertex directly, then panic and start over (this is rare) */
				he2 = he2->Next(); 
				ASSERT(he2 != edges.GetHead());
				/* ...try a different ray */
				goto retry;
      }

      /* else if the test ray actually hits the edge, increment count */
      if (fLess(t2, 1.0) && fGreater(t2, 0.0)) {
				VRTRACE("vrRay hits edge\n");
				if (fGreaterEquals(t1, 0.0)) {
			  	cnt++;
					VRTRACE("And bumps cnt: %d\n", cnt);
				}
      }
    } else {
			VRTRACE("No Intersects\n");
		}

		VRTRACE("Finding next edge\n");
    /* Get the next edge */
    he = he->Next();
    v1 = he->GetVertex();
    v2 = he->Next()->GetVertex();
  } while (he != he2);
  
  /* An even number of hits means the point is outside, odd and the point is inside */
  return (cnt % 2);
#else
//	VRTRACE("Looking for Boundary hits\n");
  if (BoundaryContains(v, rec)) {
    return TRUE;
  }

	return CheckForContainment(*v, drop);
#endif
}

SFBool vrFace::Contains(vrVertex *v, vrIntersectRecord& rec) const
{
  SFInt32 drop = GetDominantComp(m_Normal);
//	VRTRACE("dominant comp: %d\n", drop);

  /* If the vertex is inside the face's outside loop... */
//  VRTRACE("Checking lout\n");
  if (lout->Contains(v, drop, rec)) {
//		VRTRACE("Inside lout\n");
    if (rec.GetType() == VERTEX_HIT || rec.GetType() == EDGE_HIT) {
//			VRTRACE("VERTEX or EDGE HIT\n");
      return TRUE;
    }

//		VRTRACE("Checking other loops\n");
    LISTPOS lPos = loops.GetHeadPosition();
		while (lPos)
		{
			vrLoop *l = loops.GetNext(lPos);
      /* ...and outside all of the face's inside loops.... */
      if ((l != lout) && l->GetFirstHe()->Next()->Next() != l->GetFirstHe()) 
			{
				if (l->Contains(v, drop, rec)) 
				{
					if (rec.GetType() == VERTEX_HIT || rec.GetType() == EDGE_HIT) 
					{
						/* 
	     			 * It may have hit an edge or vertex on the inside loop, in which 
			    	 * case its inside 
	     		 	 */
						return TRUE;
					}
				  rec.RecordHit(NULL, NULL, INSIDE_LOOP_NO_HIT);
				  return FALSE;
				}
      }
    }
//		VRTRACE("Done -- FACEHIT\n");
    rec.RecordHit(NULL, NULL, FACE_HIT);
    /* ...then it intersects */
    return TRUE;
  }
  
//	VRTRACE("Outside lout\n");
  return FALSE;
}

SFBool vrSolid::Contains(vrSolid *B) const
{
  //
  // Test to see if this wsolid contains the given
  // wsolid.
  // 
  // Because this function is called by the SFBool 
  // operation only after having determined
  // that either A contains B, B contains A or
  // A and B are completely seperate (that is the
  // wsolids do not intersect) it is sufficient
  // to find just one 'conclusive' vertex.  A 'conclusive'
  // vertex is one that is clearly out (that is, a vertex 
  // not coincident with any face).
  //
	LISTPOS vPos = B->verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = B->verts.GetNext(vPos);
		//
		// The vertex must pass the test for every face in A
		// before concluding that B is contained.  If the
		// vertex fails for any face we can conclude B
		// is not contained.
		//
		SFBool conclusive=TRUE;

		LISTPOS fPos = faces.GetHeadPosition();
		while (fPos)
		{
			vrFace *f = faces.GetNext(fPos);
			SFFloat d = f->GetDistance(*v);
   		if (vrCompare(d, 0.0f) == 0) 
			{
				conclusive=FALSE;
   		} else 
			{
	   		if (d > 0.0+0.00001) 
				{
					// the vertex is clearly outside of this wsolid
					return FALSE;
   			}
			}
 		}
		if (conclusive) 
			return TRUE;
	}

	//
	// This will be the exceedingly rare case when
	// every vertex of V is coincident with a face
	// of this wsolid.  Therefor we should conclude
	// that this wsolid does contain B.
	//
	return TRUE;
}
