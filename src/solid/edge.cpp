//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Solid.h"
#include "Edge.h"
#include "HalfEdge.h"

void vrEdge::SwapHes(void)
{
	vrHalfEdge *he = he1;
	he1 = he2;
	he2 = he;
}

/***********************************************************************/
vrVertex *vrEdge::GetVertex(SFBool whichHe) const
{
	if (whichHe == HE1) {
		ASSERT(he1);
		return he1->GetVertex();
	} else {
		ASSERT(he2);
		ASSERT(whichHe == HE2);
		return he2->GetVertex();
	}
}

Uint32 vrEdge::GetVertexIndex(SFBool whichHe) const
{
	if (whichHe == HE1) {
		ASSERT(he1);
		return he1->GetIndex();
	} else {
		ASSERT(he2);
		ASSERT(whichHe == HE2);
		return he2->GetIndex();
	}
}

vrLoop *vrEdge::GetLoop(SFBool whichHe) const
{
	if (whichHe == HE1) {
		ASSERT(he1);
		return he1->GetLoop();
	} else {
		ASSERT(he2);
		ASSERT(whichHe == HE2);
		return he2->GetLoop();
	}
}

vrSolid *vrEdge::GetSolid(void) const
{
	ASSERT(he1);
	ASSERT(he2);
	ASSERT(he1->GetSolid() == he2->GetSolid());

	return he1->GetSolid();
}

/*********************************************************************/
vrEdge::vrEdge(vrSolid *s)
{ 
  ASSERT(s);
  
  he1   = NULL;
  he2   = NULL; 
  index = (Uint32)-1;
  m_Mark  = BRANDNEW;

  s->AddEdge(this); 
}

vrEdge::vrEdge(const vrEdge& e)
{
ASSERT(0);

/*
	ASSERT(map);

	he1   = e.he1;
	he2   = e.he2;
	index = (Uint32)-1;
	m_Mark  = UNKNOWN;
*/
}

/*
void vrEdge::RemapPointers(CMapPtrToPtr *map)
{
	ASSERT(map);

	void *he=NULL;
	if (map->Lookup(he1, he))
		he1 = (vrHalfEdge *)he;
	
	he=NULL;
	if (map->Lookup(he2, he))
		he2 = (vrHalfEdge *)he;
}
*/

vrEdge::vrEdge(void)
{ 
  he1   = NULL;
  he2   = NULL; 
  index = (Uint32)-1;
  m_Mark  = BRANDNEW;
}

