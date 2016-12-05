//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Loop.h"
#include "Vertex.h"
#include "Face.h"

SFBool vrLoop::GetVertexLocations(Uint32& max, SFVec3f *vecs) const
{
	vrHalfEdge *he;
  vrVertex   *v1;
	Uint32 i=0;

	LISTPOS hPos = halfedges.GetHeadPosition();
	while (hPos && i < max)
	{
		he = halfedges.GetNext(hPos);

    v1 = he->GetVertex();
		vecs[i++] = *v1;
  }
    
  return (i < max);
}

void vrLoop::AddHalfEdge(vrHalfEdge *he)
{
	ASSERT(he);
	halfedges.AddHead(he);
  he->SetLoop(this);
}

// Note: The names before and he are confused here!!!!
// Fix them in new code
void vrLoop::AddHalfEdge(vrHalfEdge *before, vrHalfEdge *he)
{
	ASSERT(before);
	ASSERT(he);
	halfedges.InsertNode(before, he);
}

void vrLoop::RemoveHe(vrHalfEdge *he)
{
	ASSERT(he);
	halfedges.RemoveAt(he);
}

vrHalfEdge *vrLoop::GetFirstHe(void) const
{
  return (vrHalfEdge *)halfedges.GetHead();
}

SFBool vrLoop::isOuterLoop(void) const
{
  ASSERT(GetFace());
  return (GetFace()->GetLoopOut() == this);
}

vrSolid *vrLoop::GetSolid(void) const
{
	ASSERT(face);
	return face->GetSolid();
}

vrLoop::vrLoop(vrFace *f, SFBool isOuter) 
{ 
  ASSERT(f);
  face = f; 

  if (isOuter)
	{
    ASSERT(!f->GetLoopOut());
  }

  f->AddLoop(this, isOuter); 
}

vrLoop::vrLoop(const vrLoop& l)
{
ASSERT(0);
/*
	ASSERT(map);

#ifdef _DEBUG
	void *x;
#endif

  vrHalfEdge *he;
	LISTPOS hPos = l.halfedges.GetTailPosition();
	while (hPos)
	{
		he = l.halfedges.GetPrev(hPos);
    ASSERT(!map->Lookup(he, x));
		vrHalfEdge *newHe = new vrHalfEdge(*he);
		map->SetAt(he, newHe);
		AddHalfEdge(newHe);
	}

	face = l.face;
*/
}

/*
void vrLoop::RemapPointers(CMapPtrToPtr *map)
{
	ASSERT(map);

	LISTPOS hPos = halfedges.GetHeadPosition();
	while (hPos)
	{
		vrHalfEdge *he = halfedges.GetNext(hPos);
		he->RemapPointers(map);
	}

	void *f=NULL;
	if (map->Lookup(face, f))
		face = (vrFace*)f;
}
*/

vrLoop::~vrLoop()
{
  /* 
   * Don't use an iterator here becuase the list is a ring and the iterator
   * depends on the first element of the loop to be available for the Valid method.
   * but the first element of the ring will have been deleted.
   */
  vrHalfEdge *he = halfedges.GetHead();
  if (he) {
    /* Make this ring a non-ring */
    he->Prev()->SetNext(NULL);
    he->SetPrev(NULL);
  }
  while (he) 
	{
    vrHalfEdge *n = he->Next();
    delete he;
    he = n;
  }
	halfedges.RemoveAll();
}

/*********************************************************************************/
/* Return the nearest (euclidean distance) halfedge to the given halfedge */
vrHalfEdge *vrLoop::GetNearest(vrHalfEdge *he) const
{
  ASSERT(he);

  /* The given halfedge must not be part of this loop */
  ASSERT(he->GetLoop() != this);

  vrHalfEdge *ret = NULL, *cur;
  SFFloat   min = FLT_MAX;

  /* Check each vertex for the closest one to the given he. */
	LISTPOS hPos = halfedges.GetHeadPosition();
	while (hPos)
	{
		cur = halfedges.GetNext(hPos);
    
		SFFloat d = Distance(*he->GetVertex(), *cur->GetVertex());
    if (d < min) 
		{
      min = d;
      ret = cur;
    }
  }

  ASSERT(ret);
  return ret;
}

/*********************************************************************************/
SFFloat vrLoop::Area(void) const
{
  vrHalfEdge *he;
  vrVertex   *v1, *v2, *v3;
  SFVec3f aa, bb, cc, dd(0.0f), norm;

	LISTPOS hPos = halfedges.GetHeadPosition();
	he = halfedges.GetNext(hPos);
	ASSERT(he);
	v1 = he->GetVertex();
	while (hPos)
	{
		he = halfedges.GetNext(hPos);

    v2 = he->GetVertex();
    v3 = he->Next()->GetVertex();
    aa = *v2 - *v1;
    bb = *v3 - *v1;
    cc = CrossProduct(aa, bb);
    dd += cc;
  }
    
  return (0.5f * DotProduct(face->GetNormal(), dd));
}

