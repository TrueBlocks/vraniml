//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "HalfEdge.h"
#include "Edge.h"
#include "Vertex.h"
#include "Face.h"
#include "Loop.h"

vrHalfEdge::~vrHalfEdge()
{
  edge   = NULL;
  vertex = NULL;
  wloop  = NULL;
  m_Mark  = DELETED;
	if (data)
		delete data;
	data = NULL;
}

void vrHalfEdge::SetColor(const SFColor& color)
{
	if (!data)
	{
//		SFInt32 size = GetDataSize(COLOR);
//		data = (ColorData *)malloc(size);
//		data->size = size;
//		data->type = COLOR;
//	} else
//	{
//		data = AddComponent(data, COLOR);
		data = new ColorData;
		data->type = 0;
	}
	data->SetColor(color);
}

void vrHalfEdge::SetNormal(const SFVec3f& normal)
{
	if (!data)
	{
//		SFInt32 size = GetDataSize(NORMAL);
//		data = (ColorData *)malloc(size);
//		data->size = size;
//		data->type = NORMAL;
//	} else
//	{
//		data = AddComponent(data, NORMAL);
		data = new ColorData;
		data->type = 0;
	}
	data->SetNormal(normal);
}

void vrHalfEdge::SetTexCoord(const SFVec2f& coord)
{
	if (!data)
	{
//		SFInt32 size = GetDataSize(TEXCOORD);
//		data = (ColorData *)malloc(size);
//		data->size = size;
//		data->type = TEXCOORD;
//	} else
//	{
//		data = AddComponent(data, TEXCOORD);
		data = new ColorData;
		data->type = 0;
	}
	data->SetTexCoord(coord);
}

SFColor vrHalfEdge::GetColor(const SFColor& def) const
{ 
	if (data)
		if (data->type & COLOR)
			return data->GetColor();

	return GetVertex()->GetColor(def);
}

SFVec3f vrHalfEdge::GetNormal(const SFVec3f& def) const
{ 
	if (data)
		if (data->type & NORMAL)
			return data->GetNormal();

	return GetVertex()->GetNormal(def);
}

SFVec2f vrHalfEdge::GetTextureCoord(const SFVec2f& def) const
{ 
	if (data)
		if (data->type & TEXCOORD)
			return data->GetTexCoord();

	return GetVertex()->GetTextureCoord(def);
}

#ifdef _DEBUG
void DEBHE(vrHalfEdge *he, char *sss)
{
//	VRTRACE("(%3d %3d %3d%s)%s", 
//      he->Prev()->GetIndex(), he->GetIndex(), he->Next()->GetIndex(), 
//				((he->GetEdge()->GetHe(HE1) == he) ? "+" : "-"), sss);
}
#endif

void vrHalfEdge::SetNext(vrHalfEdge *node)
{
	next = node;
}
void vrHalfEdge::SetPrev(vrHalfEdge *node)
{
  prev = node;
}

SFBool vrHalfEdge::isNullStrut(void) const
{
  ASSERT(GetMate());

  if (this == GetMate()->Next() || this == GetMate()->Prev()) 
	{
    return TRUE;
  }

  return FALSE;
}

vrHalfEdge *vrHalfEdge::GetMate(void) const
{
  ASSERT(edge);

  if (this == edge->GetHe(HE1)) {
    return edge->GetHe(HE2);
  } else {
    return edge->GetHe(HE1);
  }
}

vrHalfEdge *vrHalfEdge::GetEdgeHe(SFBool whichHe) const
{
  ASSERT(edge);
  return edge->GetHe(whichHe);
}

vrLoop *vrHalfEdge::GetEdgeLoop(SFBool whichHe) const
{
  ASSERT(edge);
  return edge->GetLoop(whichHe);
}

Uint32 vrHalfEdge::GetIndex(void) const
{ 
  ASSERT(vertex);
  return vertex->GetIndex();
}

vrSolid *vrHalfEdge::GetSolid(void) const
{
  ASSERT(GetFace());
  return GetFace()->GetSolid();
}

vrFace *vrHalfEdge::GetFace(void) const
{
  ASSERT(wloop);
  return wloop->GetFace();
}

SFVec3f vrHalfEdge::GetFaceNormal(void) const
{
  ASSERT(GetFace());
  return GetFace()->GetNormal();
}

SFBool vrHalfEdge::isNullEdge(void) const
{
  ASSERT(Next());
  
  return (*vertex == *Next()->vertex);
}
 
SFVec3f vrHalfEdge::InsideVector() const
{
  ASSERT(Next());
  ASSERT(GetFace());

  SFVec3f dir = (*Next()->vertex - *vertex);

  return CrossProduct(GetFaceNormal(), dir);
}

/**********************************************************************/
vrHalfEdge::vrHalfEdge(vrHalfEdge *he)
{
  ASSERT(he);

  data = NULL;

  edge   = NULL;
  vertex = NULL;
  wloop  = NULL;
  m_Mark = BRANDNEW;

  /* Add the new he following the given he */
  he->wloop->AddHalfEdge(this, he);
}

vrHalfEdge::vrHalfEdge(vrLoop *l, vrVertex *v)
{
  ASSERT(l);
  ASSERT(v);
  
  data = NULL;

  edge   = NULL;
  vertex = v;
  wloop  = l;
  m_Mark = BRANDNEW;

  /* Add the new he to the end of the given loop's list */
  l->AddHalfEdge(this);
}

vrHalfEdge::vrHalfEdge(const vrHalfEdge& he)
{
  data=NULL;
  ASSERT(0);

/*
	ASSERT(map);

	wloop = he.wloop;
	
  void *x;
	if (!map->Lookup(he.vertex, x))
	{
		vertex = new vrVertex(*he.vertex);
		map->SetAt(he.vertex, vertex);
	} else
	{
		vertex = (vrVertex *)x;
	}
  
	if (!map->Lookup(he.edge, x))
	{
		edge   = new vrEdge(*he.edge);
		map->SetAt(he.edge, edge);
	} else
	{
		edge = (vrEdge *)x;
	}

	m_Mark = UNKNOWN;
*/
}

/*
void vrHalfEdge::RemapPointers(CMapPtrToPtr *map)
{
	ASSERT(map);

	vertex->RemapPointers(map);
	edge->RemapPointers(map);

	void *l=NULL;
	if (map->Lookup(wloop, l))
		wloop = (vrLoop *)l;
}
*/

vrHalfEdge::vrHalfEdge(vrVertex *v)
{
  data = NULL;

  edge   = NULL;
  vertex = v;
  wloop  = NULL;
  m_Mark = BRANDNEW;
}

/*********************************************************************/
SFBool vrHalfEdge::isWide(SFBool inc180) const
{
  ASSERT(Next());
  ASSERT(Prev());
  ASSERT(GetFace());

  SFVec3f v2 = (*Next()->GetVertex() - *GetVertex());
  SFVec3f v1 = (*Prev()->GetVertex() - *GetVertex());

  SFVec3f cross = CrossProduct(v1, v2);

  if (cross == SFVec3f(0.0f))
	{
	  // Caller tells us to include 180 degrees as wide
		return inc180;
  }

  cross = Normalize(cross);

  SFVec3f norm = GetFaceNormal();

  SFFloat dot = DotProduct(cross, norm);

  return ((dot < 0.0) ? TRUE : FALSE);
}

SFVec3f vrHalfEdge::Bisect(void) const
{
//	ASSERT(isWide(FALSE));

  ASSERT(Next());
  ASSERT(Prev());
  ASSERT(GetFace());

  SFVec3f vN = (*GetVertex() - *Next()->GetVertex());
  SFVec3f vP = (*GetVertex() - *Prev()->GetVertex());

  SFVec3f cross = CrossProduct(vN, vP);

  if (cross == SFVec3f(0.0f))
	{
    // Since halfedge's cannot be 360 degrees the angle formed must
		// be 180 degress.  In this special case we know that the cross 
		// of the next vector with the face normal gives the bisector.
		cross = CrossProduct(GetFaceNormal(), vN);
		return cross + *GetVertex();
  } else
	{
    return vN + vP + *GetVertex();
  }
}

/*
SFBool vrHalfEdge::isConvexEdge(void) const
{
  vrHalfEdge *h2;
  SFVec3f  dir, cross;
 
//  VRTRACE("\t\t\tisConvexEdge\n");
  h2 = Next();
  if (isNullEdge()) {
//    VRTRACE("\t\t\t\tisNullEdge is TRUE --> h2 = h2->Next()\n");
    h2 = h2->Next();
  }
  ASSERT(h2);
//  VRTRACE("\t\t\t\th2: (%d-%d-%d)\n",
//      h2->Prev()->GetIndex(), h2->GetIndex(), h2->Next()->GetIndex());

  dir   = (*h2->GetVertex() - *GetVertex());
  cross = CrossProduct(GetFaceNormal(), GetMateFaceNormal());

  if (cross == SFVec3f(0.0f)) {
//    VRTRACE("\t\t\t\tface and face->mate are coplanar --> returning TRUE\n");  
    return TRUE;
  }

  SFFloat dot = DotProduct(dir, cross);
//  VRTRACE("\t\t\t\tdot(%f) < 0.0 ? %d\n", dot, (dot < 0.0));

  return (dot < 0.0f);
}
 
SFBool vrHalfEdge::isSectorWide(Uint32 ind) const
{
  ASSERT(Prev());
  ASSERT(Next());
  ASSERT(GetFace());

//  VRTRACE("\t\t\tisSectorWide\n");

  SFVec3f v1, v2, cross;
 
  v1 = (*Prev()->GetVertex() - *GetVertex());
  v2 = (*Next()->GetVertex() - *GetVertex());

  cross = CrossProduct(v1, v2);

  if (cross == SFVec3f(0.0f)) {
//    VRTRACE("\t\t\t\tcross vanished --> returning TRUE\n");
    return TRUE;
  }

  SFFloat dot = DotProduct(cross, GetFaceNormal());
//  VRTRACE("\t\t\t\tdot(%f) > 0.0 ? %d\n", dot, (dot > 0.0));

  return ((dot > 0.0f) ? 0 : 1);
}
*/

#ifdef _DEBUG
SFBool HeChecks(vrHalfEdge *he1, vrHalfEdge *he2, char *s)
{
#if 0
  ASSERT(he1);
  if (he1->isNullEdge()) {
    VRTRACE("%s: he1->isNullEdge()\n", s);
  } else if (he1->isNullStrut()) {
    VRTRACE("%s: he1->isNullStrut()\n", s);
  }

  if (he2 && he2->isNullEdge()) {
    VRTRACE("%s: he2->isNullEdge()\n", s);
  } else if (he2 && he2->isNullStrut()) {
    VRTRACE("%s: he2->isNullStrut()\n", s);
  }

  if (he2) {
    if (he1 != he2) {
      if (!he1->isNullEdge() && he1->isMate(he2)) {
        VRTRACE("%s: he1->isMate(he2)\n", s);
      }
      if (!he2->isNullEdge() && he2->isMate(he1)) {
        VRTRACE("%s: he2->isMate(he1)\n", s);
      }
    } else {
      VRTRACE("%s: he1 == he2\n", s);
    }
  }

#endif
  return TRUE;
}
#endif

SFBool vrHalfEdge::isNeighbor(vrHalfEdge *he) const
{
  ASSERT(he);
  ASSERT(he->GetFace());
  ASSERT(GetFace());
  ASSERT(he->edge);
  ASSERT(edge);
  
//VRTRACE("\tisNeighbor (%3d-%3d-%3d)--(%3d-%3d-%3d)\n",
//    Prev()->GetIndex(), GetIndex(), Next()->GetIndex(),
//    he->Prev()->GetIndex(), he->GetIndex(), he->Next()->GetIndex());
//VRTRACE("\t\tthis->edge: HE1: (%3d-%3d-%3d)  HE2: (%3d-%3d-%3d)\n",
//		edge->GetHe(HE1)->Prev()->GetIndex(),
//		edge->GetHe(HE1)->GetIndex(),
//		edge->GetHe(HE1)->Next()->GetIndex(),
//		edge->GetHe(HE2)->Prev()->GetIndex(),
//		edge->GetHe(HE2)->GetIndex(),
//		edge->GetHe(HE2)->Next()->GetIndex());
//VRTRACE("\t\the->edge:   HE1: (%3d-%3d-%3d)  HE2: (%3d-%3d-%3d)\n",
//		he->edge->GetHe(HE1)->Prev()->GetIndex(),
//		he->edge->GetHe(HE1)->GetIndex(),
//		he->edge->GetHe(HE1)->Next()->GetIndex(),
//		he->edge->GetHe(HE2)->Prev()->GetIndex(),
//		he->edge->GetHe(HE2)->GetIndex(),
//		he->edge->GetHe(HE2)->Next()->GetIndex());
//
//  VRTRACE("\t\t\t(%1d+(%1d+%1d-%1d+%1d): %1d\n",
//      (GetFace() == he->GetFace()),
//      (this == edge->GetHe(HE1)),
//      (he == he->edge->GetHe(HE2)),
//      (this == edge->GetHe(HE2)),
//      (he == he->edge->GetHe(HE1)),
//      ((GetFace() == he->GetFace()) &&
//	     ((this == edge->GetHe(HE1) && he == he->edge->GetHe(HE2)) ||
//	      (this == edge->GetHe(HE2) && he == he->edge->GetHe(HE1)))));
  
  return ((GetFace() == he->GetFace()) &&
	  ((this == edge->GetHe(HE1) && he == he->edge->GetHe(HE2)) ||
	   (this == edge->GetHe(HE2) && he == he->edge->GetHe(HE1))));
}

