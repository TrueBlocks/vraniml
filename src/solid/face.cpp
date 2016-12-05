//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Solid.h"
#include "Face.h"
#include "Vertex.h"

SFBool CrossingsTest(SFFloat pgon[][2], Uint32 numverts, SFFloat point[2]);
SFBool IsEar(vrLoop *loop, vrHalfEdge *he)
{
	// If the neighborhood is wide (i.e. >= 180 degrees) then cannot be an ear
	if (he->isWide(TRUE))
	{
		return FALSE;
	}

	LISTPOS pos = loop->halfedges.GetHeadPosition();
	while (pos)
	{
		vrHalfEdge *c = loop->halfedges.GetNext(pos);

		vrHalfEdge *prev = he->Prev();
		vrHalfEdge *next = he->Next();
	  
		if (c != he && c != next && c != prev)
		{
			SFFloat p[3][2];
			p[0][0] = next->GetVertex()->x;
			p[0][1] = next->GetVertex()->z;
			p[1][0] = he->GetVertex()->x;
			p[1][1] = he->GetVertex()->z;
			p[2][0] = prev->GetVertex()->x;
			p[2][1] = prev->GetVertex()->z;
			SFFloat pp[2];
			pp[0] = c->GetVertex()->x;
			pp[1] = c->GetVertex()->z;
			if (CrossingsTest(p, 3, (SFFloat*)pp))
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

SFBool vrFace::IsComplex(void) const
{
	if (loops.GetCount()>1) return TRUE;
	
	int cnt=0;
	LISTPOS pos = lout->halfedges.GetHeadPosition();
	while (pos)
	{
		lout->halfedges.GetNext(pos);
		cnt++;
		if (cnt>3)
			return TRUE;
	}
	return FALSE;
}

void vrFace::Triangulate(void)
{
	if (IsComplex())
	{
		if (loops.GetCount()!=1)
		{
			vrHalfEdge *he1, *he2;
			FindTwoClosest(&he1, &he2);
		  if (he1 && he2 && GetSolid())
			{
				// and make an edge between them
				GetSolid()->lmekr(he1, he2);
				Triangulate();
			}
			return;
		} else
		{
			vrLoop *loop = GetLoopOut();
			LISTPOS hPos = loop->halfedges.GetHeadPosition();
			while (hPos)
			{
				vrHalfEdge *he = loop->halfedges.GetNext(hPos);
				he->SetNormal(m_Normal);
				if (IsEar(loop, he))
				{
					// Cut ear
					vrFace *ear = solid->lmef(he->Prev(), he->Next());
					LISTPOS pos = ear->GetLoopOut()->halfedges.GetHeadPosition();
					while (pos)
					{
						vrHalfEdge *h = ear->GetLoopOut()->halfedges.GetNext(pos);
						h->SetNormal(m_Normal);
					}
					ear->m_Normal = m_Normal;
					ear->SetMark2(CALCED);
					Triangulate();
					//ASSERT(!remains->IsComplex());
					return;
				}
			}
		}
	}
}

void vrFace::SetColor(const SFColor& color)
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

SFColor vrFace::GetColor(const SFColor& def) const
{ 
	if (data)
		if (data->type & COLOR)
			return data->GetColor();

	return def;
}

SFBool vrFace::GetVertexLocations(Uint32& max, SFVec3f *vecs) const
{
	ASSERT(lout);
	return lout->GetVertexLocations(max, vecs);
}

vrHalfEdge *vrFace::GetFirstHe(void) const
{
  ASSERT(loops.GetHead());
  return loops.GetHead()->GetFirstHe();
}

vrHalfEdge *vrFace::GetFirstHeFromSecondLoop(void) const
{
  ASSERT(loops.GetHead());
  ASSERT(loops.GetHead()->Next());
  return loops.GetHead()->Next()->GetFirstHe();
}

vrVertex *vrFace::GetFirstVertex(void) const
{
  ASSERT(loops.GetHead());
  ASSERT(loops.GetHead()->GetFirstHe());
  return loops.GetHead()->GetFirstHe()->GetVertex();
}

vrLoop *vrFace::GetSecondLoop(void) const
{
  ASSERT(loops.GetHead());
  return loops.GetHead()->Next();
}

void vrFace::AddLoop(vrLoop *l, SFBool isOuter)
{
  ASSERT(l);
  loops.AddTail(l);
  l->SetFace(this);
	if (isOuter) 
	{
		lout = l;
	}
}

void vrFace::RemoveLoop(vrLoop *l)
{
  ASSERT(l);
  ASSERT(l->GetFace() == this);
  /*
   * It is a mistake to remove the currently
   * active lout from the face, else the face has
   * no lout.
   */
 	ASSERT(l != lout);

  loops.RemoveAt(l);
}

SFBool vrFace::isPlanar(void) const
{
  SFVec3f n = GetNormal();
  SFFloat d = GetD();

  vrPlane pl(n , d);

  LISTPOS lPos = loops.GetHeadPosition();
	while (lPos)
	{
		vrLoop *l = loops.GetNext(lPos);

    vrHalfEdge *he, *first;
    first = he = l->GetFirstHe();
    do 
		{
      if (vrCompare(pl.GetDistance(*he->GetVertex()), 0.0f) != 0) 
			{
        return FALSE;
      }
      he = he->Next();
    } while (he != first);
  }

  return TRUE;
}

vrFace::vrFace(vrSolid *s, const SFColor& c) : vrPlane(0.0f, 0.0f, 0.0f, 0.0f)
{ 
  data = NULL;
	solid = s; 
  lout  = NULL; 
  index = (Uint32)-1;
  mark1 = 0;
  mark2 = BRANDNEW;

  s->AddFace(this); 
	SetColor(c);
}

vrFace::vrFace(const vrFace& f) : vrPlane(m_Normal, m_D)
{
  data = NULL;

ASSERT(0);
/*
	BOOL alloced = FALSE;
	if (!map)
	{
		alloced = TRUE;
		map = new CMapPtrToPtr(200);
	}

#ifdef _DEBUG
  void *x;
#endif
	
	LISTPOS lPos = f.loops.GetHeadPosition();
	while (lPos)
	{
		vrLoop *l = f.loops.GetNext(lPos);
		// make a copy
		ASSERT(!map->Lookup(l, x));
		vrLoop *newLoop = new vrLoop(*l);
		map->SetAt(l, newLoop);
		AddLoop(newLoop, (l == f.lout));
	}
	solid  = f.solid;
	calced=FALSE;

	mark1  = UNKNOWN;
	mark2  = UNKNOWN;
	col    = f.col;
	index  = (Uint32)-1;

	if (alloced)
	{
		delete map;
		map = NULL;
	}
*/
}

/*
void vrFace::RemapPointers(CMapPtrToPtr *map)
{
	ASSERT(map);
	
	LISTPOS lPos = loops.GetHeadPosition();
	while (lPos)
	{
		vrLoop *l = loops.GetNext(lPos);
		l->RemapPointers(map);
	}
}
*/

vrFace::~vrFace()
{
  if (data)
		delete data;
	data = NULL;
		
	LISTPOS lPos = loops.GetHeadPosition();
	while (lPos)
	{
		vrLoop *l = loops.GetNext(lPos);
		loops.RemoveAt(l);
    delete l;
  }
	loops.RemoveAll();
  lout  = NULL;
  solid = NULL;
  index = (Uint32)-1;
  mark1 = DELETED;
  mark2 = DELETED;
}

/*********************************************************************/
/* Create a ring inside a face at vertex 'v' */
vrEdge *vrFace::MakeRing(const SFVec3f& v)
{
  vrVertex vv(v);

#ifdef _DEBUG
	vrIntersectRecord rec;

  /* The face should contain the given vertex */
	if (!Contains(&vv, rec)) {
		DEB(this, "In this face");
		//VRTRACE("Tried to insert this vertex: %10.5f %10.5f %10.5f", v.x, v.y, v.z);
		DEB((&rec), "with this intersection record resulting");
		ASSERT(Contains(&vv, rec));
	}  
#endif
  
  vrHalfEdge *head, *he1, *he2;
  
  head = lout->GetFirstHe();
  solid->lmev(head, head, v);

  he1 = head->Prev();
  solid->lmev(he1, he1, v);
  
  he2 = he1->Prev();
  ASSERT(he1->Prev()->Prev()->Prev() == he1->GetMate());
	solid->lkemr(he1->GetMate(), he1);

  return he2->GetEdge();
}

/*********************************************************************/
//#include "Traversers\RenderTraverser.h"
//void vrFace::Traverse(vrRenderTraverser *t) const
//{
//	t->Traverse(this);
//}

#define MAX_VERTS_PER_POLYGON 1000
static SFInt32 poly[MAX_VERTS_PER_POLYGON];

vrHalfEdge *vrFace::NearestInteriorVertex(vrHalfEdge *he, SFFloat *dOut) const
{
  vrHalfEdge *ret = NULL;
  SFFloat   min = FLT_MAX;

  ASSERT(dOut);
  
  /* The given he must be on the outside loop */
  ASSERT(he->GetLoop() == lout);
  /* There must be at least one inner loop */
  ASSERT(nLoops() > 1);

  /* Search all internal loops for the nearest he to the given he */
  LISTPOS lPos = loops.GetHeadPosition();
	while (lPos)
	{
		vrLoop *l = loops.GetNext(lPos);

    if (l != he->GetLoop())
		{
      ASSERT(l != lout);  // double check
      vrHalfEdge *he1 = l->GetNearest(he);
      SFFloat dist = ::Distance(*he->GetVertex(), *he1->GetVertex());
      if (dist < min) 
			{
				min = dist;
				ret = he1;
      }
    }
  }
  
  /* There is never a case where there are no closest he's */
	*dOut = min;
  ASSERT(ret);
  return ret;
}

void vrFace::FindTwoClosest(vrHalfEdge **he1Out, vrHalfEdge **he2Out) const
{
	SFFloat min = FLT_MAX;

	ASSERT(he1Out);
	ASSERT(he2Out);
	
	*he1Out = NULL;
	*he2Out = NULL;
	
	vrHalfEdge *he1, *he2;
	SFFloat dist;

	LISTPOS hPos = lout->halfedges.GetHeadPosition();
	while (hPos)
	{
		he1 = lout->halfedges.GetNext(hPos);
		DEB(he1, "he1");
		he2 = NearestInteriorVertex(he1, &dist);

		if (dist < min) 
		{
			*he1Out = he1;
			*he2Out = he2;
			min = dist;
		}
	}

	ASSERT(*he1Out);
	ASSERT(*he2Out);
}

/*********************************************************************/
SFBool vrFace::CalcEquation(const vrLoop *l)
{
	SetMark2(CALCED);
	return CalcEquation(l, &m_Normal, &m_D);
}

SFBool vrFace::CalcEquation(const vrLoop *l, SFVec3f *normOut, SFFloat *dOut) const
{
  ASSERT(l->GetFace() == this);
	ASSERT(normOut);
	ASSERT(dOut);

  SFVec3f normal(0.0f);
  SFInt32 n = 0;

  SFVec3f center = SFVec3f(0.0f);

	LISTPOS hPos = l->halfedges.GetHeadPosition();
	while (hPos)
	{
		vrHalfEdge *he = l->halfedges.GetNext(hPos);

		SFVec3f vi = *he->GetVertex();
    SFVec3f vj = *he->Next()->GetVertex();

    normal.x += (vi.y - vj.y) * (vi.z + vj.z);
    normal.y += (vi.z - vj.z) * (vi.x + vj.x);
    normal.z += (vi.x - vj.x) * (vi.y + vj.y);
    center.x += vi.x;
    center.y += vi.y;
    center.z += vi.z;
    n++;

  }

  center /= (SFFloat)n;

  if (Length(normal)) 
	{
		*normOut = -Normalize(normal);
	  ASSERT(!vrCompare(Length(*normOut),1.0f));
    *dOut    = -DotProduct(*normOut, center);
    return SUCCESS;
  } else 
	{
//    Uint32 null_face=0;
//    ASSERT(null_face);
    return ERROR;
  }
}

SFVec3f vrFace::GetCenter(void) const
{
  SFInt32 n = 0;
  SFVec3f center = SFVec3f(0.0f);

  ASSERT(lout);

	LISTPOS hPos = lout->halfedges.GetHeadPosition();
  while (hPos) 
	{
    vrHalfEdge *he = lout->halfedges.GetNext(hPos);
		SFVec3f vi = *he->GetVertex();
    center += vi;
    n++;
  }

  center /= (SFFloat)n;
	return center;
}

SFFloat vrFace::Area(void) const
{
  /*
   * Area of a face is area of the outer loop....
   */
  SFFloat area = lout->Area();

  LISTPOS lPos = loops.GetHeadPosition();
	while (lPos)
	{
		vrLoop *l = loops.GetNext(lPos);
		if (l != lout) 
		{
      /* ... minus area of all holes */
      area -= l->Area();
    }
  }

  return area;
}

void vrFace::InvertNormal(void)
{
  SFVec3f n = GetNormal();
  CalcEquation();
  ASSERT(n == GetNormal());

  m_Normal = -m_Normal;
}

void vrFace::Revert(void)
{
  LISTPOS lPos = loops.GetHeadPosition();
	while (lPos)
	{
		vrLoop *l = loops.GetNext(lPos);

    vrHalfEdge *he = l->GetFirstHe();
    do 
		{
      /* revert the direction */
  		vrHalfEdge *next = he->Next();
			he->SetNext(he->Prev());
			he->SetPrev(next);
			he = next;
    } while (he != l->GetFirstHe());

    vrVertex *prev = he->Prev()->GetVertex();
    do
		{
			vrVertex *sav = he->GetVertex();
			he->SetVertex(prev);
			he->GetVertex()->SetHe(he);
			prev = sav;
			he = he->Next();
    } while (he != l->GetFirstHe());
  }
}

