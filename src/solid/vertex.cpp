//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Vertex.h"
#include "Solid.h"

vrHalfEdge *FindFirst(vrVertex *v)
{
	vrHalfEdge *he = v->GetHe();
	vrHalfEdge *prev = he->Prev();

	do
	{
		ASSERT(prev);
		he = prev->GetMate();
		if (he)
			prev = he->Prev();
	} while (he);

	return prev;
}

void vrVertex::CalcNormal(void)
{
	static int recursed=FALSE;
	
 	SFVec3f n      = 0.0;
	SFInt32    nFaces = 0;

	vrHalfEdge *crease = NULL;
	vrHalfEdge *nocrease = NULL;
	vrHalfEdge *start = GetHe();
	vrHalfEdge *he = start;

	// Look at all the impinging half edges... trying to figure out one of three
	// cases:
	//
	//  1. All impinging edges are 'creased'
	//  2. No impinging edges are 'creased'
	//  3. One or more (but not all) are 'creased'
	//
	// While we are at it accumulate the normals (for case 2)
	//

	int loops=TRUE;
	do 
	{
		if (he->GetEdge()->Marked(CREASE))
		{
			crease = he;
		} else
		{
			nocrease = he;
		}

		SFVec3f nn = he->GetFaceNormal();
		n += nn;
		nFaces++;
		// hack for some bug somewhere
		if (nFaces>1000)
		{
			n = SFVec3f(0,1,0);
			SetNormal(n);
			return;
		}

		if (!he->GetMate())
		{
			loops=FALSE;
			he = start;
		} else
		{
			he = he->GetMate()->Next();
		}
	} while (he != start);

	// In some cases the vertex may not be surrounded by a complete loop of halfedges,
	// for example, if the object is not a solid.  Because of this case we want
	// start the looping for the normal calc at the first halfedge that impinges
	// on this vertex.  If the vertex does not form a complete halfedge loop 
	// then find the real first vertex by traversing backwards around the vertex 
	// and change the verts 'he' pointer and call ourselves again.
	if (!loops && !recursed)
	{
//		vrHalfEdge *hh = FindFirst(this);
//		SetHe(hh);
//		recursed=TRUE;
//		CalcNormal();
//		recursed=FALSE;
//		return;
	}

	if (!crease)
	{
		// We found no creases (case 2), so the vertex can store the normal
		n /= (float)nFaces;
		SetNormal(Normalize(n));
		return;
	}

	if (!nocrease)
	{
		// We found no 'nocreases' (case 1), the he's normals are already cleared,
		// leave the vertex normals clear and the face normal will get picked up.
		return;
	}

	// In the last case (3), store the normals on the half edges, so starting
	// with the face after some crease, put normals on all the half edges around this
	// entire vertex (ignore the fact that we might be able to save some memory
	// by sharing the normal among he's)
#define MAX_HES 256
	vrHalfEdge *heTable[MAX_HES];
	nFaces = 0;

	n = 0.0;
	
	if (!crease->GetMate())
	{
		crease->SetNormal(crease->GetFaceNormal());
	} else
	{
		he = crease->GetMate()->Next();
		start = he;
		do 
		{
			ASSERT(nFaces < MAX_HES);
			heTable[nFaces++] = he;

			SFVec3f nn = he->GetFaceNormal();
			n += nn;

			if (he->GetEdge()->Marked(CREASE))
			{
				// we've concluded a face group so set the normals
				// for all the faces we've encountered so far
				n /= (float)nFaces;
				for (int i=0;i<nFaces;i++)
				{
					heTable[i]->SetNormal(Normalize(n));
				}
				nFaces=0;
				n = 0.0;
			}

			if (!he->GetMate())
			{
				he = start;
			} else
			{
				he = he->GetMate()->Next();
			}
		} while (he != start);

		if (nFaces)
		{
			n /= (float)nFaces;
			for (int i=0;i<nFaces;i++)
			{
				heTable[i]->SetNormal(Normalize(n));
			}
		}
	}
}

void vrVertex::SetColor(const SFColor& color)
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

void vrVertex::SetNormal(const SFVec3f& normal)
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

void vrVertex::SetTexCoord(const SFVec2f& coord)
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

SFColor vrVertex::GetColor(const SFColor& def) const
{ 
	if (data)
		if (data->type & COLOR)
			return data->GetColor();

	return def;
}

SFVec3f vrVertex::GetNormal(const SFVec3f& def) const
{ 
	if (data)
		if (data->type & NORMAL)
			return data->GetNormal();

	return def;
}

SFVec2f vrVertex::GetTextureCoord(const SFVec2f& def) const
{ 
	if (data)
		if (data->type & TEXCOORD)
			return data->GetTexCoord();

	return def;
}

//----------------------------------------------------------------------
vrVertex::vrVertex(void) : SFVec3f()
{ 
  data = NULL;
	he      = NULL; 
  index   = (Uint32)-1;
  m_Mark  = BRANDNEW;

//#ifdef _DEBUG
//  prevIndex=(Uint32)-10;
//#endif
}

vrVertex::vrVertex(const SFVec3f& vvv) : SFVec3f(vvv)
{ 
  data = NULL;
  he      = NULL; 
  index   = (Uint32)-1;
  m_Mark  = BRANDNEW;

//#ifdef _DEBUG
//  prevIndex=(Uint32)-10;
//#endif
}

vrVertex::vrVertex(const vrVertex& v) : SFVec3f(v.x, v.y, v.z)
{
  data=NULL;
/*
	// Note: this pointer will get re-mapped shortly
	//       see Solid copy constructor
	he = v.he;

	index   = v.index;
	id      = 0; // don't use Rw's index
	scratch = v.scratch;
	m_Mark  = UNKNOWN;
*/
}

/*
void vrVertex::RemapPointers(CMapPtrToPtr *map)
{
	ASSERT(map);

	void *h=NULL;
	if (map->Lookup(he, h))
		he = (vrHalfEdge *)h;
}
*/

vrVertex::vrVertex(vrSolid *s, SFFloat x, SFFloat y, SFFloat z) : SFVec3f(x,y,z)
{ 
  ASSERT(s);

  data = NULL;
  he      = NULL; 
  index   = (Uint32)-1;
  m_Mark  = BRANDNEW;

//#ifdef _DEBUG
//  prevIndex=(Uint32)-10;
//#endif

  s->AddVertex(this); 
}

vrVertex::~vrVertex()
{
#ifdef _DEBUG
  he     = NULL;
  index  = (Uint32)-1;
  m_Mark = DELETED;
#endif
	if (data)
		delete data;
	data = NULL;
}

vrVertex& vrVertex::operator=(const vrVertex& v)
{
	SFVec3f::operator=(v);
	
	// Note: this pointer will get re-mapped shortly
	//       see Solid assignment operator
	he = v.he;

	index   = v.index;
	scratch = 0.0f;
	m_Mark  = BRANDNEW;

	return *this;
}

