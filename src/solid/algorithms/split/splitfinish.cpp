//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Split.h"

/*********************************************************************/
void vrSplitRecord::Finish(void)
{
  for (Uint32 i=0;i<nFaces;i++) 
	{
    ASSERT(nFaces+i < MAX_NEW_FACES*2);
    if (faces[i]->GetFirstLoop() == faces[i]->GetLoopOut()) 
		{
      VRTRACE("changing outer loop for NULL faces\n");
      faces[i]->SetLoopOut(faces[i]->GetSecondLoop());
    }
    faces[nFaces+i] = s->lmfkrh(faces[i]->GetFirstLoop());
//    CHECK(s);
  }

  *A = new vrSolid();
  *B = new vrSolid();

#ifdef _DEBUG
//	LISTPOS fPos = s->faces.GetHeadPosition();
//	while (fPos)
//	{
//		vrFace *f = s->faces.GetNext(fPos);
//    f->SetMark1(f->GetMark2());
//  }
#endif

  FinishClassify();

  (*A)->Cleanup();
  (*B)->Cleanup();

#ifdef _DEBUG
//	LISTPOS fPos = (*A)->faces.GetHeadPosition();
//	while (fPos)
//	{
//		vrFace *f = (*A)->faces.GetNext(fPos);
//		f->SetMark2(f->GetMark1());
//	}
//	fPos = (*B)->faces.GetHeadPosition();
//	while (fPos)
//	{
//		vrFace *f = (*B)->faces.GetNext(fPos);
//		f->SetMark2(f->GetMark1());
//  }
#endif

  /*
   * Since all faces have been moved, calling Cleanup will remove any edges
   * or verts still pointed at by s.  We want to do this so when
   * s is deleted it will not delete these edges or verts.
   */
  s->Cleanup();
  //s->SetFirstEdge(NULL);
  //s->SetFirstVertex(NULL);
}

void vrSplitRecord::FinishClassify(void)
{
  for (Uint32 i=0;i<nFaces;i++)
	{
    s->MoveFace(faces[i],        *A);
    s->MoveFace(faces[nFaces+i], *B);
  }
  
  /*
   * Pick up any faces in components of the origonal solid that where not cut 
   * by the plane.  These components will be entirly on one side or the other
   * of the plane, so checking just one vertex is enough to identify which.
   */
	while (s->GetFirstFace())
	{
		vrFace *f   = s->GetFirstFace();
		vrVertex *v = f->GetFirstVertex();
		ASSERT(v);
		v->SetScratch(SP.GetDistance(*v));
		if (vrCompare(v->GetScratch(), 0.0f) == BELOW) 
		{
			s->MoveFace(f, *A);
		} else {
			s->MoveFace(f, *B);
		}
	}
}
