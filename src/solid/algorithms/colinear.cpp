//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

/*
//*******************************************************************
SFBool vrSolid::hasColinearVerts(void) const
{
	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
//DEB(f, "f in hasColinear Verts");
		if (f->hasColinearVerts())
			return TRUE;
	}
  return FALSE;
}

void vrSolid::RemoveColinearVerts(void)
{
  //
  // Don't use iterator here because a face might collapse 
  // out from under us. 
  //
  LISTPOS pos = faces.GetHeadPosition();
	while (pos)
	{
		vrFace *f = faces.GetNext(pos);
    if (f->isDegenerate()) 
		{
      CollapseFace(f);
    } else
		{
      f->RemoveColinearVerts();
    }
  }
}

//********************************************************************
SFBool vrFace::hasColinearVerts(vrLoop **loopOut, vrHalfEdge **heOut) const
{
  LISTPOS lPos = loops.GetHeadPosition();
	while (lPos)
	{
		vrLoop *l = loops.GetNext(lPos);
    if (l->hasColinearVerts(heOut))
		{
      if (loopOut) 
				*loopOut = l;
      return TRUE;
    }
  }

  if (loopOut) *loopOut = NULL;
  return FALSE;
}

void vrFace::RemoveColinearVerts(void)
{
//  extern SFInt32 indents;
//  indents+=2;
  vrLoop *l;
  vrHalfEdge *he;
	
  while (hasColinearVerts(&l, &he))
	{
    DEB(this, "\tColinearity in this face");
    VRTRACE("at: ");
    DEBHE(he, "\n");
    l->RemoveColinearVertex(he);
  }
//  indents-=2;
}

//********************************************************************
SFBool vrLoop::hasColinearVerts(vrHalfEdge **heOut) const
{
	LISTPOS hPos = halfedges.GetHeadPosition();
	while (hPos)
	{
		vrHalfEdge *he = halfedges.GetNext(hPos);
	  ASSERT(he->Prev());
  	ASSERT(he->Next());
	  vrVertex *v1 = he->Prev()->GetVertex();
	  vrVertex *v  = he->GetVertex();
  	vrVertex *v2 = he->Next()->GetVertex();
		ASSERT(v1 && v2 && v);

    if (Colinear(*v1,*v,*v2))
		{
      if (heOut) 
				*heOut = he;
      return TRUE;
    }
  }
  
  if (heOut) 
		*heOut = NULL;
  return FALSE;
}

void vrLoop::RemoveColinearVertex(vrHalfEdge *he)
{
//  extern SFInt32 indents;
//  indents+=4;
  VRTRACE("\t\tRemoveCollin\n");
  vrFace *f = face;
//DEB(f, "Face before removal");

#if 0
  // isNullEdge should be first because if he->edge is NULL, isNullStrut will ASSERT
  if (he->isNullEdge())
	{
    VRTRACE("\t\t\tisNullEdge: calling kef(%d %d %d)\n\t\t\tface: ", 
        face->GetIndex(), he->GetIndex(), he->GetIndex());
    DEB(face, "\n\t\t\the: ");
    DEBHE(he, "\n");

    if (face->nLoops()>1)
		{
      // This loop is not the lout!
      vrLoop *l = he->GetLoop();
      ASSERT(l);
      
      // Delete the halfedge
      l->RemoveHe(he);
      delete he;
      
      if (l->GetFirstHe() == NULL)
			{
        // Remove the he's loop from the face....
        face->RemoveLoop(l);
        delete l;
      }

      f->AdjustOuterLoop();

    } else
		{
      VRTRACE("This face is about to disappear but the above algos\n"
            "assume that it will stay in existance.  This is a bug\n");
      ASSERT(0);
    }
    
  } else if (he->isNullStrut())
	{
    
    if (he == he->GetMate()->Next()) 
		{
      VRTRACE("\t\t\tisNullStrut: calling kev(%d %d)\n\t\t\the: ", 
          he->GetIndex(), he->GetMate()->GetIndex());
      DEBHE(he, "\n\t\t\tmate: ");
      DEBHE(he->GetMate(), "\n");
      face->GetSolid()->lkev(he, he->GetMate());
    } else 
		{
      ASSERT(he == he->GetMate()->Prev());
      VRTRACE("\t\t\tisNullStrut: calling kev(%d %d)\n\t\t\the: ", 
          he->GetMate()->GetIndex(), he->GetIndex());
      DEBHE(he->GetMate(), "\n");
      DEBHE(he, "\n\t\t\tmate: ");
      face->GetSolid()->lkev(he->GetMate(), he);
    }
    
  } else
#endif
	vrFace *mate = he->GetMate()->GetFace();
//  DEB(f,    "Face before removal of colinearity");
  DEB(mate, "Mate before removal of colinearity");

	{
    
    VRTRACE("\t\t\tkev2(%d %d)\n\t\t\the: ", 
        he->GetIndex(), he->GetMate()->GetIndex());
    DEBHE(he, "\n\t\t\tmate: ");
    DEBHE(he->GetMate(), "\n");
    face->GetSolid()->kev2(he, he->GetMate());
    
  }
  
  DEB(f,    "Face after removal of colinearity");
  DEB(mate, "Mate after removal of colinearity");

//  indents-=4;
}
*/
