//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Solid\Solid.h"
#include "Solid\Face.h"
#include "Solid\Loop.h"
#include "Solid\Edge.h"
#include "Solid\HalfEdge.h"

#ifdef _DEBUG

/*
 * This whole file disapears when optimized -- also all functions
 * here are const so can not alter thier objects 
 */

/*********************************************************************************/
SFBool GoodMark(Uint32 m)
{
  switch (m) {
  case ALTERED:
  case BRANDNEW:
  case UNKNOWN:
  case ON:
  case ABOVE:
  case BELOW:
  case VISITED:
  case SOLID_A:
  case SOLID_B:
	case POINT_SET:
	case LINE_SET:
	case FACE_SET:
    return TRUE;
  }
  return FALSE;
}

void vrSolid::Verify(void) const
{
#if 0
  if (!AfxGetApp()->GetProfileInt("Debug", "Verify", FALSE))
	{
    return;
  }
#endif

  ASSERT(GoodMark(m_Mark));

  // Do the simplest tests first, this will cause less core dumps
  Uint32 nLoops=0;
	LISTPOS fPos = faces.GetHeadPosition();
//  ASSERT(fPos); // At least one face 
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
    ASSERT(GoodMark(!f->GetMark1()));
//    ASSERT(GoodMark(!f->GetMark2()));
    ASSERT(f->GetIndex() < 50000);
    ASSERT(f->GetSolid() == this);

    LISTPOS lPos = f->loops.GetHeadPosition();
		while (lPos)
		{
			//vrLoop *l = f->loops.GetNext(lPos);
			f->loops.GetNext(lPos);
			nLoops++;
    }
  }
  
	LISTPOS ePos = edges.GetHeadPosition();
	while (ePos)
	{
		vrEdge *e = edges.GetNext(ePos);
//    ASSERT(GoodMark(e->GetMark()));
    ASSERT(e->GetIndex() < 50000);
  }
  
	LISTPOS vPos = verts.GetHeadPosition();
//  ASSERT(vPos); // At least one vertex 
	while (vPos)
	{
    vrVertex *v = verts.GetNext(vPos);
    ASSERT(GoodMark(v->GetMark()));
    ASSERT(v->GetIndex() < 50000);
  }

//  DEB(this, "Verify");
  int nHoles = nLoops - faces.GetCount();
//  VRTRACE("-----------%d + %d - 2 =?  %d + %d (%d =? %d)\n", 
//	 faces.GetCount(), verts.GetCount(), edges.GetCount(), nHoles,
//	 faces.GetCount() + verts.GetCount() -2, edges.GetCount() + nHoles);
#if 0
  if (AfxGetApp()->GetProfileInt("Debug", "VerifyEulerFormula", FALSE))
	{
    ASSERT(faces.GetCount() + verts.GetCount() - 2 == edges.GetCount() + nHoles);
  } else {
#endif
    if (faces.GetCount() + verts.GetCount() - 2 != edges.GetCount() + nHoles) {
      //VRTRACE("-----------%d + %d - 2 !=  %d + %d (%d != %d)\n", 
	    // faces.GetCount(), verts.GetCount(), edges.GetCount(), nHoles,
	    // faces.GetCount() + verts.GetCount() -2, edges.GetCount() + nHoles);
    }
//  }

  fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
		f->Verify();
	}
  ePos = edges.GetHeadPosition();
	while (ePos)
	{
		vrEdge *e = edges.GetNext(ePos);
		e->Verify();
  }

  vPos = verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = verts.GetNext(vPos);
    v->Verify();
  }
}

void vrFace::Verify(void) const
{
  /* Date must be valid */
  ASSERT(solid);
  ASSERT(lout);
  ASSERT(GoodMark(mark1));
//  ASSERT(GoodMark(mark2));

  /* vrFace should be planar */
  if (Marked2(CALCED)) 
	{
		ASSERT(isPlanar());
	}

  /* There must be at least one loop */
  ASSERT(GetFirstLoop());

  Uint32 found=FALSE;

  LISTPOS lPos = loops.GetHeadPosition();
	while (lPos)
	{
		vrLoop *l = loops.GetNext(lPos);
    /* Verify all the loops */
    l->Verify();
    /* Every loop must backpoint to this face */
    ASSERT(l->GetFace() == this);
    if (l == lout) {
      found=TRUE;
    }
  }

  /* The face's solid must be aware for this face */
  ASSERT(solid->findFace(index));

  /* The outer loop must have been one of the face's loops */
  ASSERT(found);

  if (Marked2(CALCED)) 
	{
    if (FALSE)
		{
      /* A face's area should be non-zero */
      if (!solid->isWire()) 
			{
  	    ASSERT(Area());
      }
    }
  }
}

void vrLoop::Verify(void) const
{
  Uint32 iii=0;
  vrHalfEdge *head = halfedges.GetHead();
  vrHalfEdge *tail = halfedges.GetTail();

  /* There must be at least one halfedge in every loop */
  ASSERT(head);
  ASSERT(tail);
  if (head == tail) 
	{
    ASSERT(head->Next() == tail);
    ASSERT(tail->Prev() == head);
  }

	LISTPOS hPos = halfedges.GetHeadPosition();
	while (hPos)
	{
		vrHalfEdge *he = halfedges.GetNext(hPos);
    iii++;
    he->Verify();
  }

  /* The loop must point to a face... */
  ASSERT(face);
  /* ....that knows about it */
  ASSERT(GetSolid()->findFace(GetFace()->GetIndex()));
}

void vrEdge::Verify(void) const
{
//  ASSERT(GoodMark(m_Mark));
	//ASSERT(he1);
	//ASSERT(he2);

  /*
   * Even though the he's where checked from the loop verification we should
   * check here also because it's possible that an edge points to invalid he's
   * that are not pointed to by a loop 
   */
  if (he1) he1->Verify();
  if (he2) he2->Verify();
}

void vrHalfEdge::Verify(void) const
{
  ASSERT(GoodMark(m_Mark));

  /* The he must belong to a loop... */
  ASSERT(wloop);
  /* ...that knows about it */
  ASSERT(wloop->GetSolid()->findHalfEdge(wloop->GetFace(), GetIndex()));

  /* The edge pointer may be NULL... */
  if (edge) 
	{
    if (edge->GetHe(HE1) != this) 
		{
      /* ...but if it's not, the he better be the edge's he1 or he2 pointer */
      ASSERT(edge->GetHe(HE2));
    }
  }

  ASSERT(vertex);
  vertex->Verify();
}

void vrVertex::Verify(void) const
{
  ASSERT(GoodMark(m_Mark));
  ASSERT(index < 10000);
  if (he) 
	{
    ASSERT(GoodMark(he->GetMark()));
  }

}

#endif
