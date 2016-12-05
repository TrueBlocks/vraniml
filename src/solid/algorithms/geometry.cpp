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
#include "Solid\Vertex.h"

void vrSolid::CalcPlaneEquations(void)
{
	// Calc face equations first
	LISTPOS fpos = faces.GetHeadPosition();
	while (fpos)
	{
		vrFace *f = faces.GetNext(fpos);
		f->CalcEquation();
	}
}

extern SFFloat AngleBetween(const SFVec3f& v1, const SFVec3f& v2);
void vrSolid::MarkCreases(SFFloat crease)
{
	LISTPOS ePos = edges.GetHeadPosition();
	while (ePos)
	{
		vrEdge *e = edges.GetNext(ePos);
		if (!e->GetHe(HE1) || !e->GetHe(HE2))
			e->SetMark(CREASE);
		else
		{
			SFVec3f n1, n2;
			n1 = e->GetLoop(HE1)->GetFace()->GetNormal();
			n2 = e->GetLoop(HE2)->GetFace()->GetNormal();
			double angle = AngleBetween(n1, n2);
			if (angle >= crease)
			{
				e->SetMark(CREASE);
			}
		}
	}
}

void vrSolid::Triangulate(void)
{
	LISTPOS pos = faces.GetHeadPosition();
	while (pos)
	{
		vrFace *face = faces.GetNext(pos);
		face->Triangulate();
	}
}

void vrSolid::Merge(vrSolid *s2)
{
  vrFace *f;
  vrEdge *e;
  vrVertex *v;

  // Move all faces, edges and verts from s2 to this and delete s2
  while (s2->faces.GetHead()) 
	{
    f = s2->faces.GetHead();
    s2->faces.RemoveAt(f);
    AddFace(f);
    f->SetSolid(this);
  }
  while (s2->edges.GetHead()) {
    e = s2->edges.GetHead();
    s2->edges.RemoveAt(e);
    AddEdge(e);
  }
  while (s2->verts.GetHead()) {
    v = s2->verts.GetHead();
    s2->verts.RemoveAt(v);
    AddVertex(v);
  }

  Renumber();
}

void vrSolid::TransformGeometry(const vrMatrix& m)
{
  LISTPOS vPos = verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = verts.GetNext(vPos);
    v->SetLocation(m * (*v));
  }

	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
		f->SetMark2(CALCED);
	}
}

void vrSolid::Arc(Uint32 fIndex, Uint32 vIndex, SFFloat cx, SFFloat cy, SFFloat radius, SFFloat height, SFFloat startAngle, SFFloat endAngle, Uint32 steps)
{
  SFFloat angle = startAngle * M_PI / 180.0f;
  SFFloat stepSize = (endAngle - startAngle) * M_PI / (180.0f * steps);
  SFFloat x, y;

  Uint32 prevIndex = vIndex;

  for (Uint32 i=0;i<steps; i++)
	{
    angle += stepSize;
    x = cx + (SFFloat)cos(angle) * radius;
    y = cy + (SFFloat)sin(angle) * radius;
    smev(fIndex, prevIndex, x, y, height);
    prevIndex = verts.GetCount()-1;
  }

  //
  // From the book: a more general solution would check that the last
  // point of the arc is actually a vertex of 'f' and apply 'mef'
  // instead of 'mev'.  This would be needed for filliting.
  //
  CHECK(this);
}

void vrSolid::ArcSweep(vrFace *f, Uint32 n, const SFVec3f vvv[])
{
  for (Uint32 i=0;i<n;i++)
	{
    TranslationalSweep(f, vvv[i]);
  }
}

void vrSolid::TranslationalSweep(vrFace *f, const SFVec3f& vvv)
{
  vrVertex *v;
  vrHalfEdge *first, *scan;

  LISTPOS lPos = f->loops.GetHeadPosition();
	while (lPos)
	{
    vrFace *face;
		vrLoop *l = f->loops.GetNext(lPos);
    first = l->GetFirstHe();

    scan = first->Next();
    v = scan->GetVertex();
    lmev(scan, scan, (*v + vvv));
		while (scan != first) 
		{
      v = scan->Next()->GetVertex();
      lmev(scan->Next(), scan->Next(), *v + vvv);
      face = lmef(scan->Prev(), scan->Next()->Next());
			if (scan->GetEdge() && scan->GetEdge()->Marked(INVISIBLE))
			{
//				scan->GetEdge()->m_Mark &= (~INVISIBLE);
				ASSERT(face);
				ASSERT(face->GetLoopOut());
				ASSERT(face->GetLoopOut()->halfedges.GetHead());
				ASSERT(face->GetLoopOut()->halfedges.GetHead()->GetEdge());
				face->GetLoopOut()->halfedges.GetHead()->GetEdge()->m_Mark = INVISIBLE;
				face->SetMark2(INVISIBLE);
			}
      scan = scan->Next()->GetMate()->Next();
    }
    face = lmef(scan->Prev(), scan->Next()->Next());
		if (scan->GetEdge() && scan->GetEdge()->Marked(INVISIBLE))
		{
//			scan->GetEdge()->m_Mark &= (~INVISIBLE);
			ASSERT(face);
			ASSERT(face->GetLoopOut());
			ASSERT(face->GetLoopOut()->halfedges.GetHead());
			ASSERT(face->GetLoopOut()->halfedges.GetHead()->GetEdge());
			face->GetLoopOut()->halfedges.GetHead()->GetEdge()->m_Mark = INVISIBLE;
			face->SetMark2(INVISIBLE);
		}
  }

  CHECK(this);
}

void vrSolid::RotationalSweep(Uint32 nFaces)
{
  vrHalfEdge *he;
  vrFace *headf, *tailf;
  SFBool closed_fig=FALSE;

  // If it's not a wire make it one
  if (!isWire()) {
    // This is a lamina
    ASSERT(isLamina());
    closed_fig = TRUE;
    he = faces.GetHead()->GetLoopOut()->GetFirstHe();
    lmev(he, he->GetMate()->Next(), *he->GetVertex());
//    lkef(he->Prev(), mate(he->Prev()));
    lkef(he->Prev()->GetMate(), he->Prev());
  }

  headf = faces.GetHead();
  tailf = SweepWire(nFaces);

  // if it was made a wire, glue it back together
  if (closed_fig)
	{
    lkfmrh(headf, tailf);
    LoopGlue(headf);
  } else
	{
    ASSERT(headf != tailf);

    //
    // If either the begining or ending of wire was on x-axis then 
    // collapse the degenerate face that was created 
    //
    if (headf->isDegenerate())
		{
      CollapseFace(headf);
    }
    if (tailf->isDegenerate())
		{
      CollapseFace(tailf);
    }
  }

  Renumber();
	CHECK(this);
}


#pragma warning(disable : 4706)
vrFace *vrSolid::SweepWire(Uint32 nFaces)
{
	// Handles only wires.  Does not handle lamina's or higher order serfaces 
  vrHalfEdge *first, *cfirst, *last, *scan=NULL;
  vrMatrix m = RotationXMatrix(vrDeg2Rad(360.0f/nFaces));
  SFVec3f v;
  vrFace *tailf;

  ASSERT(isWire());

  first = faces.GetHead()->GetFirstHe();
  
  // Find one end of the wire
  while (first->GetEdge() != first->Next()->GetEdge())
    first = first->Next();
  last = first->Next();

  // Find the other end
  while (last->GetEdge() != last->Next()->GetEdge())
    last = last->Next();
  cfirst = first;

  while (--nFaces) 
	{
    v = m * *cfirst->Next()->GetVertex();
    lmev(cfirst->Next(), cfirst->Next(), v);
    scan = cfirst->Next();
    while (scan != last->Next()) 
		{
      v = m * *scan->Prev()->GetVertex();
      lmev(scan->Prev(), scan->Prev(), v);
      lmef(scan->Prev()->Prev(), scan->Next());
      scan = scan->Next()->Next()->GetMate();
    }
    last = scan;
    cfirst = cfirst->Next()->Next()->GetMate();
  }

  ASSERT(scan);
  tailf = lmef(cfirst->Next(), first->GetMate());
  while (cfirst != scan) {
    lmef(cfirst, cfirst->Next()->Next()->Next());
    cfirst = cfirst->Prev()->GetMate()->Prev();
  }

  return tailf;
}

void vrSolid::Twist(PFF func)
{
  LISTPOS vPos = verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = verts.GetNext(vPos);
    SFFloat x, y, z;
    x = v->x;
    y = v->y;
    z = func(v->z);
    v->x = x * (SFFloat)cos(z) - y * (SFFloat)sin(z);
    v->y = x * (SFFloat)sin(z) + y * (SFFloat)cos(z);
  }

//  CHECK(this);
}

void vrSolid::Glue(vrSolid *s2, vrFace *f1, vrFace *f2)
{
  // Merge the two solids together
  Merge(s2);
  delete s2;
  
  //
  // Assuming that the two given faces are coincident, kill one of the
  // faces and make it an inner loop of the other.
  //
  lkfmrh(f1, f2);
  
  //
  // Now join the duplicate verticies together and eliminate the 
  // duplicate loop.
  //
  LoopGlue(f1);

  CHECK(this);
}

void vrSolid::LoopGlue(vrFace *f)
{
  vrHalfEdge *h1, *h2, *h1next;

  ASSERT(f->nLoops() > 1);

  h1 = f->GetFirstHe();
  h2 = f->GetFirstHeFromSecondLoop();

  // Find the first matching vertex -- if no matches are found caller is in error so ASSERT
#ifdef _DEBUG
  vrHalfEdge *start = h2;
#endif
  while (!(*h1->GetVertex() == *h2->GetVertex()))
	{
    h2 = h2->Next();
    ASSERT(h2 != start);
  }

  lmekr(h1, h2);
  lkev(h1->Prev(), h2->Prev());

  while (h1->Next() != h2) {
    h1next = h1->Next();
    lmef(h1->Next(), h1->Prev());
    lkev(h1->Next(), h1->Next()->GetMate());
    lkef(h1->GetMate(), h1);
    h1 = h1next;
  }

  lkef(h1->GetMate(), h1);

  CHECK(this);
}

void vrSolid::Join(vrHalfEdge *he1, vrHalfEdge *he2, SFBool swap)
{
  vrFace *oldFace = he1->GetFace();
  vrFace *newFace = NULL;

  if (he1->GetLoop() == he2->GetLoop()) 
	{
    if (he1->Prev()->Prev() != he2) 
		{
      if (swap) 
			{
        newFace = lmef(he2->Next(), he1);
      } else 
			{
        newFace = lmef(he1, he2->Next());
      }
    }
  } else 
	{
    lmekr(he1, he2->Next());
  }

  if (he1->Next()->Next() != he2) 
	{
    lmef(he2, he1->Next());
    if (newFace && oldFace->GetSecondLoop()) 
		{
      laringmv(oldFace, newFace);
    }
  }
}

vrFace *vrSolid::Cut(vrHalfEdge *he, SFBool setOp)
{
  vrFace *oldFace = NULL;

  if (he->GetEdgeLoop(HE1) == he->GetEdgeLoop(HE2)) {
    oldFace = he->GetFace();
    if (setOp)
	{
      lkemr(he->GetEdgeHe(HE2), he->GetEdgeHe(HE1));
    } else
	{
      lkemr(he->GetEdgeHe(HE1), he->GetEdgeHe(HE2));
    }
  } else
	{
    lkef(he->GetEdgeHe(HE1), he->GetEdgeHe(HE2));
  }

  return oldFace;
}

void vrSolid::MoveFace(vrFace *f, vrSolid *s)
{
  vrFace *f2;

  ASSERT(f);
  ASSERT(s);
  
  if (f->Marked2(VISITED))
    return;

  f->SetMark2(VISITED);

  AddUndoRecord(MOVEFACE, f->GetIndex(), 100); //s->GetIndex());

  faces.RemoveAt(f);
  s->AddFace(f);
  f->SetSolid(s);

  LISTPOS lPos = f->loops.GetHeadPosition();
	while (lPos)
	{
		vrLoop *l = f->loops.GetNext(lPos);

		LISTPOS hPos = l->halfedges.GetHeadPosition();
		while (hPos)
		{
			vrHalfEdge *he = l->halfedges.GetNext(hPos);

      //vrHalfEdge *m = he->GetMate();
      f2 = he->GetMateFace();
      if (f2->GetSolid() != s)
			{
  	  	MoveFace(f2, s);
      }
    }
  }
}

