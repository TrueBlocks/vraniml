//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Solid\Solid.h"

#undef EULER_CHECK
#define EULER_CHECK(a)

/**/
/**************************************************************************/
void vrSolid::mvfs(SFFloat x, SFFloat y, SFFloat z)
{
  EULER_CHECK(this);

  vrFace *f = new vrFace(this);
  vrLoop *l = new vrLoop(f);
  vrVertex *vert = new vrVertex(this, x, y, z);
#pragma warning(disable:4189)
  vrHalfEdge *he = new vrHalfEdge(l, vert);

  AddUndoRecord(KVFS, 0, 0);

  ASSERT(faces.GetHead() == f);
  ASSERT(edges.GetHead() == NULL);
  ASSERT(verts.GetHead() == vert);

  ASSERT(f->GetSolid()     == this);
  ASSERT(f->GetLoopOut()   == l);
  ASSERT(f->GetFirstLoop() == l);
  ASSERT(f->nLoops()       == 1);

  ASSERT(l->GetFace()    == f);
  ASSERT(l->GetFirstHe() == he);

  ASSERT(he->GetLoop()   == l);
  ASSERT(he->GetVertex() == vert);
  ASSERT(he->GetEdge()   == NULL);
  ASSERT(he->Next()      == he->Prev());
  ASSERT(he->Next()      == he);

  ASSERT(vert->x == x && 
         vert->y == y && 
         vert->z == z);
  ASSERT(vert->GetHe() == NULL);

  EULER_CHECK(this);
}

/**/
/******************************************************************************/
void vrSolid::lringmv(vrLoop *l, vrFace *toFace, SFBool isOuter)
{
 // EULER_CHECK(this);

  vrFace *fromFace = l->GetFace();

  /* This call will ASSERT if l is an outer loop of fromFace */
  fromFace->RemoveLoop(l);

  toFace->AddLoop(l, isOuter);

//  EULER_CHECK(this);
}

/******************************************************************************/
void vrSolid::laringmv(vrFace *f1, vrFace *f2)
{
  EULER_CHECK(this);

  SFInt32 drop = GetDominantComp(f1->GetNormal());

  /*
   * If any of f1's non-outer loops is outside of 
   * f1's outer loop move that loop to f2 (as an
   * inner loop of f2).
   */
  vrLoop *f1out = f1->GetLoopOut();

  LISTPOS lPos = f1->loops.GetHeadPosition();
  while (lPos) 
	{
    vrLoop *l = f1->loops.GetNext(lPos);
    if (l != f1out) 
		{
      vrIntersectRecord rec;
      vrHalfEdge *he = l->GetFirstHe();
      if (!f1out->Contains(he->GetVertex(), drop, rec)) 
			{
				lringmv(l, f2, FALSE);
      }
    }
  }

  EULER_CHECK(this);
}

/**/
/******************************************************************************/
vrFace *vrSolid::lmfkrh(vrLoop *l)
{
  EULER_CHECK(this);

  vrFace *oldFace = l->GetFace();
  
  /* It is assumed that l is not the outer loop of it's face */
  ASSERT(oldFace->GetLoopOut() != l);
  oldFace->RemoveLoop(l);

  vrFace *newFace = new vrFace(this, oldFace->GetColor(vrWhite));

  AddUndoRecord(KFMRH, oldFace->GetIndex(), newFace->GetIndex());

  /* Add the loop as the outer loop of the face */
  newFace->AddLoop(l, TRUE);

  EULER_CHECK(this);

  return newFace;
}

/**/
/***********************************************************************************/
vrVertex *vrSolid::lmev(vrHalfEdge *he1, vrHalfEdge *he2, SFFloat x, SFFloat y, SFFloat z)
{
  EULER_CHECK(this);

  ASSERT(he1 && he2);
  HECHECK(he1, he2, "lmev");
  ASSERT(he1->GetVertex() == he2->GetVertex());
#ifdef _DEBUG
if (he1->GetVertex() != he2->GetVertex())
{
//AfxMessageBox("Failure of previous assert will cause hang --> quiting");
exit(0);
}
#endif

  vrEdge *nevrEdge = new vrEdge(this);
  vrVertex *newVert = new vrVertex(this, x, y, z);
  
  AddUndoRecord(KEV, he1->GetFace()->GetIndex(), he1->GetIndex(), newVert->GetIndex());

  vrHalfEdge *he = he1;
  while (he != he2) 
	{
    he->SetVertex(newVert);
    he = he->GetMate()->Next();
  }

  /* These are reversed from the book.  The book was wrong */
  nevrEdge->AddHalfEdge(he2->GetVertex(), he1, HE2);
  nevrEdge->AddHalfEdge(newVert,     he2, HE1);
 
  newVert->SetHe(he2->Prev());
  he2->GetVertex()->SetHe(he2);

  ASSERT(newVert->GetHe() == nevrEdge->GetHe(HE1));
  ASSERT(newVert->GetHe()->GetVertex() == newVert);
  ASSERT(newVert->GetHe()->GetEdge() == nevrEdge);

  EULER_CHECK(this);

  return newVert;
}

/**/
/******************************************************************************/
void vrSolid::lmekr(vrHalfEdge *he1, vrHalfEdge *he2)
{
  EULER_CHECK(this);

  ASSERT(he1 && he2);
  HECHECK(he1, he2, "lmekr");

  /* Different loops */
  ASSERT(he1->GetLoop() != he2->GetLoop());
  /* Same face */
  ASSERT(he1->GetFace() == he2->GetFace());

  vrLoop *loop1 = he1->GetLoop();
  vrLoop *loop2 = he2->GetLoop();
  vrFace *f = loop1->GetFace();
  
  vrEdge *nevrEdge = new vrEdge(this);
  
  AddUndoRecord(KEMR, f->GetIndex(), 
	       he2->GetIndex(), 
	       he1->GetIndex(),
	       0,
	       0,
	       (f->GetLoopOut() == loop2) ? 0 : 1);

  vrHalfEdge *he = loop2->GetFirstHe();
  do {
    he->SetLoop(loop1);
  } while((he = he->Next()) != loop2->GetFirstHe());

  vrHalfEdge *nhe1 = nevrEdge->AddHalfEdge(he1->GetVertex(), he1, HE1);
  vrHalfEdge *nhe2 = nevrEdge->AddHalfEdge(he2->GetVertex(), he2, HE2);
  
  nhe1->SetNext(he2);
  nhe2->SetNext(he1);
  he2->SetPrev(nhe1);
  he1->SetPrev(nhe2);
  
  if (f->GetLoopOut() == loop2) {
    f->SetLoopOut(loop1);
	}
  loop2->GetFace()->RemoveLoop(loop2);

  /* Don't want to remove the halfedge's just the loop */
  loop2->SetFirstHe(NULL);
  delete loop2;

  EULER_CHECK(this);
}

/**/
/******************************************************************************/
vrFace *vrSolid::lmef(vrHalfEdge *he1, vrHalfEdge *he2)
{
  EULER_CHECK(this);

  /* He's exist and are in the same loop */
  ASSERT(he1 && he2);
  HECHECK(he1, he2, "lmef");
  ASSERT(he1->GetLoop() == he2->GetLoop());

  /* He's are not adjacent (if they are we get a null face) */
  /* This ASSERT is a quess so if it hits don't assume it should have */
  ASSERT(he1->Next() != he2);
  ASSERT(he2->Next() != he1);

  /* This next line may be overly stringent and not really neeeded */
  ASSERT(he1->GetLoop()->GetFirstHe()->GetEdge());

  vrLoop *oldLoop = he1->GetLoop();
  vrFace *oldFace = oldLoop->GetFace();

  vrFace *newFace = new vrFace(this, oldFace->GetColor(vrWhite));
  vrLoop *newLoop = new vrLoop(newFace);
  vrEdge *nevrEdge = new vrEdge(this);
  
  AddUndoRecord(KEF, he1->GetFace()->GetIndex(), he1->GetIndex(), he2->GetIndex());

  vrHalfEdge *he = he1;
  while (he != he2) {
    he->SetLoop(newLoop);
    he = he->Next();
  }
  
  vrHalfEdge *nhe1 = nevrEdge->AddHalfEdge(he2->GetVertex(), he1, HE2);
  vrHalfEdge *nhe2 = nevrEdge->AddHalfEdge(he1->GetVertex(), he2, HE1);

  nhe1->Prev()->SetNext(nhe2);
  nhe2->Prev()->SetNext(nhe1);
  
  vrHalfEdge *temp = nhe2->Prev();
  nhe2->SetPrev(nhe1->Prev());
  nhe1->SetPrev(temp);

  oldLoop->SetFirstHe(nhe2);

  /* 
   * Don't use append here becuase we don't want to disturb the next/prev pointers 
   */
  newLoop->SetFirstHe(nhe1);

  ASSERT(newFace->GetSolid() == this);
  ASSERT(newFace->GetLoopOut() == newLoop);
  ASSERT(newLoop->GetFace() == newFace);

  ASSERT(he2->GetLoop() == oldLoop);
  ASSERT(nhe2->GetLoop() == oldLoop);

  ASSERT(nhe1->GetEdge() == nevrEdge);
  ASSERT(nhe2->GetEdge() == nevrEdge);

  oldFace->SetMark2(ALTERED);

  EULER_CHECK(this);

  return newFace;
}

/**/
/******************************************************************************/
void vrSolid::lkvfs(void)
{
  EULER_CHECK(this);

  vrVertex *v = verts.GetHead();
  if (v) {
    AddUndoRecord(MVFS, v->GetIndex(), 0, 0, 0, 0, 0, v->x, v->y, v->z, 0.0f);
  }

  EULER_CHECK(this);
}

/**/
/******************************************************************************/
void vrSolid::lkfmrh(vrFace *f1, vrFace *f2)
{
  EULER_CHECK(this);

  ASSERT(!f2->GetSecondLoop());
  ASSERT(f2->GetSolid() == f1->GetSolid());
  ASSERT(this == f1->GetSolid());

  AddUndoRecord(MFKRH,
	       f1->GetIndex(),
	       f2->GetLoopOut()->GetFirstHe()->GetIndex(),
	       f2->GetLoopOut()->GetFirstHe()->Next()->GetIndex(),
	       0, 0, f2->GetIndex());

  /*
   * It's OK to not have a lout in f2 becuase it 
   * will soon be deleted.
   */
  f2->SetLoopOut(NULL);
	vrLoop *l = f2->GetFirstLoop();
  while (l) {
    lringmv(l, f1, FALSE);
		l = f2->GetFirstLoop();
  }

  faces.RemoveAt(f2);
  /* There are no loops left in f2 */
  delete f2;

  EULER_CHECK(this);
}


/**/
/******************************************************************************/
void vrSolid::lkev(vrHalfEdge *he1, vrHalfEdge *he2)
{
  EULER_CHECK(this);

  ASSERT(he1 && he2);
  HECHECK(he1, he2, "lkev");

  /* he's are mates... (mate function will ASSERT on the case where he1->edge == NULL) */
  ASSERT(he1->GetMate() == he2);
  ASSERT(he2->GetMate() == he1);
  ASSERT(he1->GetEdge() == he2->GetEdge());
	// he1 is first
	ASSERT((!he1->isNullStrut() && !he2->isNullStrut()) || he1->Prev() == he2);

  /* ...with different vertices */
  ASSERT(he1->GetVertex() != he2->GetVertex());

  vrVertex *v1 = he1->GetVertex();
  vrVertex *v2 = he2->GetVertex();

//	DEB(this, "this solid");
//	DEB(he1->GetFace(), "lkev: he1->GetFace()");
//	DEB(he2->GetFace(), "lkev: he2->GetFace()");
//	DEB(he1, "lkev: he1");
//	DEB(he2, "lkev: he2");

  AddUndoRecord(MEV,
	       he1->GetFace()->GetIndex(),
	       he2->GetFace()->GetIndex(),
	       he1->Next()->GetIndex(),
	       v1->GetIndex(),
	       he2->Next()->GetIndex(),
	       v1->GetIndex(),
	       he1->GetVertex()->x, he1->GetVertex()->y, he1->GetVertex()->z);

  vrHalfEdge *he = he2->Next();
  while (he != he1) {
    he->SetVertex(v2);
    he = he->GetMate()->Next();
  }
  
  if (he2->isNullStrut())
	{
  	v2->SetHe(he2->Next()->Next());
	} else {
  	v2->SetHe(he2->Next());
	}

  vrEdge *e = he1->GetEdge();

	vrHalfEdge *ret = e->DeleteHalfEdge(he1);
	if (ret) {
		ret->GetLoop()->SetFirstHe(ret);
	}
	
	ret = e->DeleteHalfEdge(he2);
	if (ret) {
		ret->GetLoop()->SetFirstHe(ret);
	}

//  he1->wloop->edges.SetHead(e->DeleteHalfEdge(he1));
  /* Note: this is not an append because the loop already existed before this function */
//  he2->wloop->edges.SetHead(e->DeleteHalfEdge(he2));

  /* ...otherwise this references a deleted item (i.e. he2) */
//  v2->he = he2->Next();
  if (!v2->GetEdge()) v2->SetHe(NULL);
 
  edges.RemoveAt(e);
  verts.RemoveAt(v1);
  delete e;
  delete v1;

  EULER_CHECK(this);
}

/**/
/******************************************************************************/
void vrSolid::lkemr(vrHalfEdge *he1, vrHalfEdge *he2)
{
  EULER_CHECK(this);
  
  ASSERT(he1 && he2);
  HECHECK(he1, he2, "lkemr");

  /* This next line may be overly stringent */
  ASSERT(he1 != he2);

  /* They are mates... */
  ASSERT(he1 == he2->GetMate());
  ASSERT(he2 == he1->GetMate());
  ASSERT(he1->GetEdge() == he1->GetEdge());
  /* ...and in the same loop */
  ASSERT(he1->GetLoop() == he2->GetLoop());

//	/* Is it always the outer loop??? (may not be but let's check) */
//	ASSERT(he1->GetLoop() == he2->GetFace()->GetLoopOut());

  vrLoop *oldLoop  = he1->GetLoop();
  vrEdge *killEdge = he1->GetEdge();
  
//  DEB(oldLoop, "oldLoop\n");
//  DEB(killEdge, "killEdge\n");

  vrLoop *newLoop  = new vrLoop(oldLoop->GetFace(), FALSE);

  AddUndoRecord(MEKR,
	       he1->GetFace()->GetIndex(),
	       he1->GetIndex(),
	       he2->Next()->GetIndex(),
	       he2->GetIndex(),
	       he1->Next()->GetIndex());

  vrHalfEdge *he3 = he1->Next();
  he1->SetNext(he2->Next());
  he2->Next()->SetPrev(he1);
  he2->SetNext(he3);
  he3->SetPrev(he2);
  
  vrHalfEdge *he4 = he2;
  do {
    he4->SetLoop(newLoop);
  } while((he4 = he4->Next()) != he2);
  
  /* This line is not in the book, but makes the unlink inside DeleteHalfEdge work right */
  newLoop->SetFirstHe(he2);

  he3 = killEdge->DeleteHalfEdge(he1);
  he4 = killEdge->DeleteHalfEdge(he2);

  oldLoop->SetFirstHe(he3);
  newLoop->SetFirstHe(he4);

  /* what if he3 or he3->next is NULL??? */
  ASSERT(he3 && he4);
  ASSERT(he3->Next() && he4->Next());
  ASSERT(!he3->Marked(DELETED));
  ASSERT(!he4->Marked(DELETED));
  ASSERT(!he3->Next()->Marked(DELETED));
  ASSERT(!he4->Next()->Marked(DELETED));

  he3->GetVertex()->SetHe((he3->GetEdge()) ? he3 : NULL);
  he4->GetVertex()->SetHe((he4->GetEdge()) ? he4 : NULL);
  he3->Next()->GetVertex()->SetHe((he3->Next()->GetEdge()) ? 
  		he3->Next() : NULL);
  he4->Next()->GetVertex()->SetHe((he4->Next()->GetEdge()) ? 
  	  he4->Next() : NULL);
  
  edges.RemoveAt(killEdge);
  delete killEdge;

  EULER_CHECK(this);
}

/**/
/*********************************************************************************/
void vrSolid::lkef(vrHalfEdge *he1, vrHalfEdge *he2)
{
  EULER_CHECK(this);

  ASSERT(he1 && he2);
  HECHECK(he1, he2, "lkef");

  /* they are mates... */
  ASSERT(he1->GetMate() == he2);
  ASSERT(he2->GetMate() == he1);
  ASSERT(he1->GetEdge() == he2->GetEdge());
  /* ...in different faces. */
  ASSERT(he1->GetFace() != he2->GetFace());

  vrEdge *killEdge = he1->GetEdge();

  vrLoop *loop1 = he1->GetLoop();
  vrFace *f1    = loop1->GetFace();

  vrLoop *loop2 = he2->GetLoop();
  vrFace *f2    = loop2->GetFace();

	ASSERT(f1 != f2);

#if 0
    LISTPOS lPos = f1->loops.GetHeadPosition();
		while (lPos)
		{
			vrLoop *l = f1->loops.GetNext(lPos);
      if (l != loop2)
			{
				AddEulerOp(RINGMV, f1->index,
											 f2->index,
											 l->edges.GetHead()->vertex->index,
											 l->edges.GetHead()->Next()->vertex->index,
											 (l = f1->lout) ? 1 : 0);
      }
    }
#endif
  AddUndoRecord(MEF,
	       f1->GetIndex(),
	       he1->GetIndex(), 
	       he2->Next()->Next()->GetIndex(),
	       he2->GetIndex(), 
	       he1->Next()->Next()->GetIndex(),
	       f2->GetIndex());

	/* Move all loops from f2 to f1 */
  f2->SetLoopOut(NULL);
	vrLoop *l = f2->GetFirstLoop();
  while (l)
	{
		lringmv(l, f1, FALSE);
    l = f2->GetFirstLoop();
  }
 
  /* Reset all he's loop pointers to the new loop */
  vrHalfEdge *he = loop2->GetFirstHe();
  do
	{
    he->SetLoop(loop1);
  } while((he = he->Next()) != loop2->GetFirstHe());
 
  vrHalfEdge *temp;
  he1->Prev()->SetNext(he2);
  he2->Prev()->SetNext(he1);
  temp = he2->Prev();
  he2->SetPrev(he1->Prev());
  he1->SetPrev(temp);
 
  vrVertex *v1 = he1->GetVertex();
  vrVertex *v2 = he2->GetVertex();

#if ORIGINAL_CODE
  killEdge->DeleteHalfEdge(he2);
  killEdge->DeleteHalfEdge(he1);
 
  /* This references possibly deleted memory */
  v2->he = he1->Next();
  if (!v2->he->edge) v2->he = NULL;
  
  v1->he = he2->Next();
  if (!v1->he->edge) v1->he = NULL;
  
  loop1->SetHead(he1->Next());

#else
  vrHalfEdge *he3 = killEdge->DeleteHalfEdge(he2);
  vrHalfEdge *he4 = killEdge->DeleteHalfEdge(he1);
 
  ASSERT(he3 && he4);
  ASSERT(he3->Next() && he4->Next());
  ASSERT(!he3->Marked(DELETED));
  ASSERT(!he4->Marked(DELETED));
  ASSERT(!he3->Next()->Marked(DELETED));
  ASSERT(!he4->Next()->Marked(DELETED));
  
  v2->SetHe(he4->Next());
  if (!v2->GetHe()->GetEdge()) v2->SetHe(NULL);
  
  v1->SetHe(he3->Next());
  if (!v1->GetHe()->GetEdge()) v1->SetHe(NULL);
  
  loop1->SetFirstHe(he4->Next());
#endif  

  f2->loops.RemoveAll(); // so it doesn't get deleted twice
  faces.RemoveAt(f2);
  delete f2;
  
  loop2->SetFirstHe(NULL);
  f1->RemoveLoop(loop2);
  delete loop2;

  edges.RemoveAt(killEdge);
  delete killEdge;

  f1->SetMark2(ALTERED);

  EULER_CHECK(this);
}

/*========================================================================*/
/* This file contains all low level euler operations                      */
/*========================================================================*/

/*********************************************************************/
/*
 * KillVertexFaceSolid
 */
void vrSolid::kvfs(void)
{
  lkvfs();
}

/*********************************************************************/
/*
 * MakeEdgeVertex
 */
SFBool vrSolid::mev(Uint32 f1, Uint32 f2, 
		   Uint32 v1, Uint32 v2, Uint32 v3,
		   SFFloat x, SFFloat y, SFFloat z)
{
  vrFace     *face1 = findFace(f1);
  vrFace     *face2 = findFace(f2);
  vrHalfEdge *he1   = findHalfEdge(face1, v1, v2);
  vrHalfEdge *he2   = findHalfEdge(face2, v1, v3);

  lmev(he1, he2, x, y, z);

  return SUCCESS;
}

/*********************************************************************/
/*
 * SimpleMakeEdgeVertex
 */
SFBool vrSolid::smev(Uint32 f, Uint32 v1, SFFloat x, SFFloat y, SFFloat z)
{
  vrFace     *face = findFace(f);
  vrHalfEdge *he1  = findHalfEdge(face, v1);

  lmev(he1, he1, x, y, z);
  
  return SUCCESS;
}

/*********************************************************************/
/*
 * KillEdgeVertex2 -- kev for half edges not in the same face
 */
SFBool vrSolid::kev2(vrHalfEdge *he1, vrHalfEdge *he2)
{
  /* he's are in different faces */
  ASSERT(he1->GetFace() != he2->GetFace());

  lkev(he1, he2);  // Mantyla has 'lkev(he2, he1)'

  return SUCCESS;
}

/*********************************************************************/
/*
 * KillEdgeVertex
 */
SFBool vrSolid::kev(Uint32 f, Uint32 v1, Uint32 v2)
{
  vrFace *face    = findFace(f);
  vrHalfEdge *he1 = findHalfEdge(face, v1, v2);
  vrHalfEdge *he2 = he1->GetMate();

  /* he's are in same loop */
  ASSERT(he1->GetLoop() == he2->GetLoop());

  /* make sure v1 is an endpoint*/
  ASSERT(he1->Next() == he2);

  lkev(he1, he2);  // Mantyla has 'lkev(he2, he1)'

  return SUCCESS;
}

/*********************************************************************/
/*
 * MakeEdgeFace
 */
SFBool vrSolid::mef(Uint32 f, Uint32 v1, Uint32 v2, Uint32 v3, Uint32 v4)
{
  vrFace     *face = findFace(f);
  vrHalfEdge *he1  = findHalfEdge(face, v1, v2);
  vrHalfEdge *he2  = findHalfEdge(face, v3, v4);

  lmef(he1, he2);

  return SUCCESS;
}

/*********************************************************************/
/*
 * SimpleMakeEdgeFace
 */
SFBool vrSolid::smef(Uint32 f, Uint32 v1, Uint32 v3)
{
  vrFace     *face = findFace(f);
  vrHalfEdge *he1  = findHalfEdge(face, v1);
  vrHalfEdge *he2  = findHalfEdge(face, v3);

  lmef(he1, he2);

  return SUCCESS;
}

/*********************************************************************/
/*
 * KillEdgeFace
 */
SFBool vrSolid::kef(Uint32 f, Uint32 v1, Uint32 v2)
{
  vrFace *face     = findFace(f);
  vrHalfEdge *he   = findHalfEdge(face, v1, v2);

  lkef(he->GetMate(), he);   // Mantyla has 'lkef(he, mate(he))'

  return SUCCESS;
}

/*********************************************************************/
/*
 * KillEdgeMakeRing
 */
SFBool vrSolid::kemr(Uint32 f, Uint32 v1, Uint32 v2)
{
  vrFace *face = findFace(f);
  vrHalfEdge *he   = findHalfEdge(face, v1, v2);

  lkemr(he, he->GetMate());

  return SUCCESS;
}

/*********************************************************************/
/*
 * MakeEdgeKillRing
 */
SFBool vrSolid::mekr(Uint32 f, Uint32 v1, Uint32 v2, Uint32 v3, Uint32 v4)
{
  vrFace *face = findFace(f);
  vrHalfEdge *he1   = findHalfEdge(face, v1, v2);
  vrHalfEdge *he2   = findHalfEdge(face, v3, v4);

  lmekr(he1, he2);

  return SUCCESS;
}

/*********************************************************************/
/*
 * KillFaceMakeRingHole
 */
SFBool vrSolid::kfmrh(Uint32 f1, Uint32 f2)
{
  vrFace *face1 = findFace(f1);
  vrFace *face2 = findFace(f2);
  
  lkfmrh(face1, face2);
  
  return SUCCESS;
}

/*********************************************************************/
/*
 * MakeFaceKillRingHole
 */
SFBool vrSolid::mfkrh(Uint32 f, Uint32 v1, Uint32 v2)
{
  vrFace *face = findFace(f);
  vrHalfEdge *he = findHalfEdge(face, v1, v2);

  lmfkrh(he->GetLoop());

  return SUCCESS;
}

/*********************************************************************/
/*
 * RingMove
 */
SFBool vrSolid::ringmv(Uint32 f1, Uint32 f2, Uint32 v1, Uint32 v2, SFBool inout)
{
  vrFace *face1 = findFace(f1);
  vrFace *face2 = findFace(f2);
  
  vrHalfEdge *he = findHalfEdge(face1, v1, v2);

  lringmv(he->GetLoop(), face2, inout);

  return SUCCESS;
}

/**/
/*********************************************************************************/
vrHalfEdge *vrEdge::AddHalfEdge(vrVertex *v, vrHalfEdge *where, SFBool sign)
{
  vrHalfEdge *he;

  ASSERT(v);
  ASSERT(where);
  ASSERT(sign == HE1 || sign == HE2);

  HECHECK(where, NULL, "addhe");

  if (!where->GetEdge()) {
    he = where;
  } else {
    he = new vrHalfEdge(where);
  }

  he->SetEdge(this);
  he->SetVertex(v);
  he->SetLoop(where->GetLoop());
  
  if (sign == HE1) {
    he1 = he;
  } else {
    he2 = he;
  }

  return he;
}


/**/
/*********************************************************************************/
vrHalfEdge *vrEdge::DeleteHalfEdge(vrHalfEdge *he)
{
  ASSERT(he);
  HECHECK(he, NULL, "delhe");

  if (!he->GetEdge()) 
	{
    if (he->GetLoop()) 
		{
      he->GetLoop()->RemoveHe(he);
    }
    delete he;
    return NULL;
  } else if (he == he->Next()) 
	{
    he->SetEdge(NULL);
    return he;
  } else 
	{
    vrHalfEdge *ret = he->Prev();
    if (he->GetLoop()) 
		{
      he->GetLoop()->RemoveHe(he);
    }
    delete he;
    return ret;
  }
}
