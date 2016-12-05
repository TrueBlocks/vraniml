//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Split.h"

/*********************************************************************/
void vrSplitRecord::Generate(void)
{
  nVerts = 0;
  
  // Precalculate the distance from all verticies to the splitting plane
  LISTPOS vPos = s->verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = s->verts.GetNext(vPos);
    v->SetScratch(SP.GetDistance(*v));
  }
  
	DEB(this, "After calcing distances");
	
	// Look for edges whose verts are on opposite sides of the splitting plane
  LISTPOS ePos = s->edges.GetHeadPosition();
	while (ePos)
	{
		vrEdge *e = s->edges.GetNext(ePos);

    e->SetMark(UNKNOWN);
    vrVertex *v1 = e->GetVertex(HE1);
    vrVertex *v2 = e->GetVertex(HE2);
    
    SFFloat d1 = v1->GetScratch();
    SFFloat d2 = v2->GetScratch();
    
		SFInt32 s1 = vrCompare(d1, 0.0f);
		SFInt32 s2 = vrCompare(d2, 0.0f);

    if ((s1 == -1 && s2 == 1) || (s1 == 1 && s2 == -1)) 
		{
      // Verts are on opposite sides of the splitting plane
			// Insert a vertex at the intersection point.
      SFFloat t = d1 / (d1 - d2);
      SFVec3f intersectionPt = *v1 + t * (*v2 - *v1);
      vrHalfEdge *he = e->GetHe(HE2)->Next();
      vrVertex *newVert = s->lmev(e->GetHe(HE1), he, intersectionPt);
      newVert->SetScratch(0.0f);
      AddVert(he->Prev()->GetVertex());
    } else 
		{
      // Verts are on the same side of splitting plane, check
			// for case where one or the other vert is on the plane
      if (s1 == 0) 
				AddVert(v1);
      if (s2 == 0)
				AddVert(v2);
    }
  }
}
