//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Solid\Solid.h"

#if 0
SFBool vrSolid::hasDegenerateFaces(vrFace **faceOut) const
{
	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
    if (f->isDegenerate())
		{
      if (faceOut) 
				*faceOut = f;
      return TRUE;
    }
  }

  if (faceOut) *faceOut = NULL;
  return FALSE;
}

void vrSolid::RemoveDegenerateFaces(void)
{
  LISTPOS fPos = faces.GetHeadPosition();
	while (pos)
	{
		vrFace *f = faces.GetNext(fPos);
    if (f->isDegenerate())
		{
      CollapseFace(f);
    }
  }
}
#endif

void vrSolid::CollapseFace(vrFace *removedFace)
{
//  DEB(removedFace, "Collapsing this face");

  ASSERT(removedFace);
  ASSERT(!removedFace->GetSecondLoop());

  vrHalfEdge *he = removedFace->GetFirstHe();
  vrHalfEdge *hen = he->Next();
  vrHalfEdge *hep = he->Prev();

  lkef(he->GetMate(), he);
  
  he = hen;
  while (he != hep)
	{
    hen = he->Next();
    lkev(he, he->GetMate());
    he = hen;
  }
  lkev(he, he->GetMate());

//  DEB(this, "vrSolid after removal of Degenerate face");
}

SFBool vrFace::isDegenerate(void) const
{
  SFVec3f v = *loops.GetHead()->GetFirstHe()->GetVertex();

  LISTPOS lPos = loops.GetHeadPosition();
	while (lPos)
	{
		vrLoop *l = loops.GetNext(lPos);

		LISTPOS hPos = l->halfedges.GetHeadPosition();
		while (hPos)
		{
			vrHalfEdge *he = l->halfedges.GetNext(hPos);

      if (!(v == *he->GetVertex())) 
			{
        return !vrCompare(Area(), 0.0f);
      }
    }
  }

//  DEB(this, "This face is Degenerate");
  return TRUE;
}

