//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Solid.h"

//----------------------------------------------------
// Constructors, destructors
//
vrSolid::vrSolid(void)
{
	m_SolidColor = TRUE;
	
	m_Mark = BRANDNEW;

#ifdef ENABLE_UNDO
  generateUndoLog=FALSE;
#endif

//#ifdef _DEBUG
//  check_eulers = FALSE;
//#endif
}

//----------------------------------------------------
vrSolid::vrSolid(const vrSolid& s) : vrBaseNode(s)
{
  m_SolidColor = TRUE;

	ASSERT(0);  // do not use copy constructor

/*
	// This might happen if two apps are accessing this
	// DLL at the same time.  We need this data
	// to be thread safe.
	ASSERT(!map);
	DEB(s);
	
	map = new CMapPtrToPtr(200);

	m_Mark = UNKNOWN;

//#ifdef _DEBUG
//  check_eulers = s.check_eulers;
//  void *x;
//#endif

#ifdef ENABLE_UNDO
  generateUndoLog=s.generateUndoLog;
#endif

  LISTPOS fPos = s.faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *oldFace = s.faces.GetNext(fPos);
		ASSERT(!map->Lookup(oldFace, x));
		vrFace *newFace = new vrFace(*oldFace);
		map->SetAt(oldFace, newFace);
		AddFace(newFace);
  }

	DEB(this);

//  afxDump.SetDepth(1);
//	map->Dump(afvrDump);
	
	fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
		f->SetSolid(this);
		f->RemapPointers(map);
  }

	delete map;
	map = NULL;

	DEB(this);

	Renumber();
	Cleanup();

	DEB(this);

	CHECK(this);
*/
}

//----------------------------------------------------
vrSolid::vrSolid(SFFloat x, SFFloat y, SFFloat z)
{
  m_SolidColor = TRUE;

  m_Mark = BRANDNEW;

#ifdef ENABLE_UNDO
  generateUndoLog=FALSE;
#endif

//#ifdef _DEBUG
//  check_eulers = FALSE;
//#endif

  mvfs(x,y,z);
}

//----------------------------------------------------
vrSolid::vrSolid(const SFVec3f& v)
{
  m_SolidColor = TRUE;

  m_Mark = BRANDNEW;

#ifdef ENABLE_UNDO
  generateUndoLog=FALSE;
#endif

//#ifdef _DEBUG
//  check_eulers = FALSE;
//#endif

  mvfs(v);
}

//----------------------------------------------------
vrSolid::~vrSolid()
{
  /* For undo purposes */
  kvfs();

  LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
		faces.RemoveAt(f);
    delete f;
	}
	faces.RemoveAll();

  LISTPOS ePos = edges.GetHeadPosition();
  while (ePos)
	{
		vrEdge *e = edges.GetNext(ePos);
		edges.RemoveAt(e);
    delete e;
  }
	edges.RemoveAll();

  LISTPOS vPos = verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = verts.GetNext(vPos);
		verts.RemoveAt(v);
    delete v;
  }
	verts.RemoveAll();

#ifdef ENABLE_UNDO
  LISTPOS ePos = undoLog.GetHeadPosition();
	while (pos)
	{
		vrEulerOp *eo = undoLog.GetNext(pos);
		undoLog.RemoveAt(eo);
    delete eo;
  }
	unduLog.RemoveAll();
#endif

  m_Mark = DELETED;
}

//----------------------------------------------------
vrBaseNode *vrSolid::Clone(void) const
{
	return new vrSolid(*this);
}

//----------------------------------------------------
// Marking
//
void vrSolid::SetFaceMarks(Uint32 newMark)
{
	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
		f->SetMark2(newMark);
  }
}

//----------------------------------------------------
void vrSolid::SetVertexMarks(Uint32 newMark)
{
  LISTPOS vPos = verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = verts.GetNext(vPos);
    v->SetMark(newMark);
  }
}

//----------------------------------------------------
// Queries
//
vrFace *vrSolid::findFace(Uint32 faceID) const
{
	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
    if (f->GetIndex() == faceID)
      return f;
  }

  // Should never happen
	//Uint32 not_found=0;
  //VRTRACE("face not found: %d\n", faceID);
  DEB(this, "solid");
  ASSERT(0);
  return NULL;
}

//----------------------------------------------------
vrEdge *vrSolid::findEdge(Uint32 edgeID) const
{
  LISTPOS ePos = edges.GetHeadPosition();
	while (ePos)
	{
		vrEdge *e = edges.GetNext(ePos);
    if (e->GetIndex() == edgeID)
		{
      return e;
    }
  }

  // Should never happen
	//Uint32 not_found=0;
  //VRTRACE("edge not found: %d\n", edgeID);
  DEB(this, "solid");
  ASSERT(0);
  return NULL;
}

//----------------------------------------------------
vrVertex *vrSolid::findVertex(Uint32 vertID) const
{
  LISTPOS vPos = verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = verts.GetNext(vPos);
    if (v->GetIndex() == vertID)
		{
//      ASSERT(v->GetIndex() == v->GetId()-1);
      return v;
    }
  }

  // Should never happen
	//Uint32 not_found=0;
  //VRTRACE("vertex not found: %d\n", vertID);
  DEB(this, "solid");
  ASSERT(0);
  return NULL;
}

//----------------------------------------------------
vrHalfEdge *vrSolid::findHalfEdge(vrFace *f, Uint32 v1, Uint32 v2) const
{
  LISTPOS lPos = f->loops.GetHeadPosition();
	while (lPos)
	{
		vrLoop *l = f->loops.GetNext(lPos);

		LISTPOS hPos = l->halfedges.GetHeadPosition();
		while (hPos)
		{
			vrHalfEdge *he = l->halfedges.GetNext(hPos);

      vrHalfEdge *hen = he->Next();
      ASSERT(hen);
      if (he->GetIndex() == v1 && hen->GetIndex() == v2)
			{
        return he;
      }
    }
  }
  
  // Should never happen
	//Uint32 not_found=0;
  //VRTRACE("halfedge not found: %d %d %d\n", f->GetIndex(), v1, v2);
  DEB(this, "solid");
  ASSERT(0);
  return NULL;
}

//----------------------------------------------------
vrHalfEdge *vrSolid::findHalfEdge(vrFace *f, Uint32 v1) const
{
  LISTPOS lPos = f->loops.GetHeadPosition();
	while (lPos)
	{
		vrLoop *l = f->loops.GetNext(lPos);

		LISTPOS hPos = l->halfedges.GetHeadPosition();
		while (hPos)
		{
			vrHalfEdge *he = l->halfedges.GetNext(hPos);

      if (he->GetIndex() == v1) {
        return he;
      }

    }
  }

  // Should never happen
	//Uint32 not_found=0;
  //VRTRACE("halfedge not found: %d %d\n", f->GetIndex(), v1);
  DEB(this, "solid");
  ASSERT(0);
  return NULL;
}

//----------------------------------------------------
// Geometric Queries
//
SFVec3f vrSolid::Extents(SFVec3f& minni, SFVec3f& maxxi) const
{
  maxxi = SFVec3f(-100000.0f, -100000.0f, -100000.0f);  // very small
  minni = SFVec3f( 100000.0f,  100000.0f,  100000.0f);  // very large
  
  LISTPOS vPos = verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = verts.GetNext(vPos);
    Maximize(maxxi, *v);
    Minimize(minni, *v);
  }

  return (maxxi - minni);
}

//----------------------------------------------------
SFFloat vrSolid::Volume(void) const
{
  SFVec3f c;
  SFFloat res;

  res = 0.0f;
  
	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);

    LISTPOS lPos = f->loops.GetHeadPosition();
		while (lPos)
		{
			vrLoop *l = f->loops.GetNext(lPos);

			vrHalfEdge *he1, *he2;

			LISTPOS hPos = l->halfedges.GetHeadPosition();
			he1 = l->halfedges.GetNext(hPos);
			ASSERT(he1);
			while (hPos)
			{
				he2 = l->halfedges.GetNext(hPos);

				c = CrossProduct(*he2->GetVertex(), *he1->GetVertex());
				res += DotProduct(*he2->Next()->GetVertex(), c) / 6.0f;

      }
    }
  } 

  return res;
}

//----------------------------------------------------
SFFloat vrSolid::Area(void) const
{
  SFFloat area=0.0f;

	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
		area += f->Area();
  }

  return area;
}

//----------------------------------------------------
SFVec3f vrSolid::Stats(Uint32& nVerts, Uint32& nEdges, Uint32& nFaces, Uint32& nLoops, Uint32& nHalfEdges) const
{
  nVerts = verts.GetCount();
  nFaces = faces.GetCount();
  nEdges = edges.GetCount();

  nLoops = 0;
  nHalfEdges = 0;
	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
    
		LISTPOS lPos = f->loops.GetHeadPosition();
		while (lPos)
		{
			vrLoop *l = f->loops.GetNext(lPos);

			LISTPOS hPos = l->halfedges.GetHeadPosition();
			while (hPos)
			{
				l->halfedges.GetNext(hPos);
				nHalfEdges++;
      }
      nLoops++;
    }
  }

  SFVec3f temp1, temp2;
  return Extents(temp1, temp2);
}

//----------------------------------------------------
// Building solids
//
void vrSolid::AddFace(vrFace *f)
{
	f->SetIndex(faces.NextIndex());
  faces.AddHead(f);
}

//----------------------------------------------------
void vrSolid::AddEdge(vrEdge *e)
{
  e->SetIndex(edges.NextIndex());
  edges.AddHead(e);
}

//----------------------------------------------------
void vrSolid::AddVertex(vrVertex *v)
{
  v->SetIndex(verts.NextIndex());
  verts.AddHead(v);
}

void vrSolid::Cleanup(void)
{ 
  //Uint32 nF=0;
  
  verts.RemoveAll();
  edges.RemoveAll();

	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
//    DEB(f, "cleaning up this face");    

    LISTPOS lPos = f->loops.GetHeadPosition();
		while (lPos)
		{
			vrLoop *l = f->loops.GetNext(lPos);
      ASSERT(l);
      
			LISTPOS hPos = l->halfedges.GetHeadPosition();
			while (hPos)
			{
				vrHalfEdge *he = l->halfedges.GetNext(hPos);

        ASSERT(he);
      	ASSERT(he->GetVertex());
      	if (he->GetEdge()) 
				{
	        if (!he->GetEdge()->Marked(VISITED)) 
					{
      	    he->GetEdge()->SetMark(VISITED);
	          AddEdge(he->GetEdge());
//              VRTRACE("cleanup: adding edge: %2d %2d\n", he->GetEdgeHe(HE1)->GetIndex(), he->GetEdgeHe(HE2)->GetIndex());
//          } else 
//          {
//            VRTRACE("already visited edge: %d\n", he->GetIndex());
          }
//        } else 
//        {
//          VRTRACE("No edge on he: %d\n", he->GetIndex());
        }

        if (!he->GetVertex()->IsMarked(VISITED)) 
				{
          he->GetVertex()->SetMark(VISITED);
          AddVertex(he->GetVertex());
//          VRTRACE("cleanup: adding vertex: %2d\n", he->GetIndex());
//        } else 
//        {
//          VRTRACE("Already visited v: %d\n", he->GetIndex());
        }

      }
    }

//    VRTRACE("Next face\n");
//    fit.Advance();
  }
}

void vrSolid::Revert(void)
{
	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
    f->Revert();
  }
}

void vrSolid::Renumber(void)
{
  Uint32 i=faces.nextIndex=0;
	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
    Uint32 ii = f->GetIndex();
    Uint32 jj = faces.NextIndex();
    f->SetIndex(jj);
    i++;

    AddUndoRecord(RENUMBER, FACE, ii, jj);
  }
  faces.n = i;
  i=edges.nextIndex=0;

  LISTPOS ePos = edges.GetHeadPosition();
	while (ePos)
	{
		vrEdge *e = edges.GetNext(ePos);
    Uint32 ii = e->GetIndex();
    Uint32 jj = edges.NextIndex();
    e->SetIndex(jj);
    i++;

    AddUndoRecord(RENUMBER, EDGE, ii, jj);
  }
  edges.n = i;
  i=verts.nextIndex=0;

  LISTPOS vPos = verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = verts.GetNext(vPos);
    Uint32 ii = v->GetIndex();
//#ifdef _DEBUG
//    v->prevIndex = ii;
//#endif
    Uint32 jj = verts.NextIndex();
    v->SetIndex(jj);
    i++;

    AddUndoRecord(RENUMBER, VERTEX, ii, jj);
  }
  verts.n = i;
}

SFBool vrSolid::Write(FILE *out, SFBool forward) const
{
	if (!out)
		out = stdout;
		
	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
		f->CalcEquation();
	}

	CHECK(this);

  SFColor curcol = vrBlack;
  
	fprintf(out, "#\n# vertex list\n");
	fprintf(out, "#\n# x, y, z, nx, ny, nz, tx, ty\n#\n");
	fprintf(out, "%d\n", verts.GetCount());

  LISTPOS vPos = verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = verts.GetNext(vPos);
		SFVec3f normal = v->GetNormal(SFVec3f(0));
		SFVec2f tCoord = v->GetTextureCoord(SFVec2f(0));
    fprintf(out, "% 5.5f % 5.5f % 5.5f % 5.5f % 5.5f % 5.5f % 5.5f % 5.5f\n", 
				v->x, v->y, v->z, 
				normal.x, normal.y, normal.z, 
				tCoord.x, tCoord.y);
  }

	fprintf(out, "#\n# face list (faces with colors)\n");
	fprintf(out, "#\n# nVerts v1 v2 v3 ... r g b\n#\n");

  fprintf(out, "%d\n", faces.GetCount());
	//long nF=0;
	
	fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
		long nLoops=0;
    LISTPOS lPos = f->loops.GetHeadPosition();
		while (lPos)
		{
			nLoops++;
			ASSERT(nLoops==1);

			vrLoop *l = f->loops.GetNext(lPos);
    
			Uint32 nVerts=0;
			LISTPOS hPos = l->halfedges.GetHeadPosition();
			while (hPos) 
			{
				l->halfedges.GetNext(hPos);
				nVerts++;
			}

			fprintf(out, "%d ", nVerts);
			
			hPos = l->halfedges.GetHeadPosition();
			while (hPos) 
			{
				vrHalfEdge *he = l->halfedges.GetNext(hPos);
				fprintf(out, "%d ", he->GetIndex());
			}
    }
    
    SFColor col = f->GetColor(vrBlack);
		fprintf(out, "%d %d %d\n", (int)(col.x*255), (int)(col.y*255), (int)(col.z*255));
  }

  return TRUE;
}

/*
vrBoundingBox vrSolid::GetBoundingBox(void) const
{
  vrBoundingBox box;

  LISTPOS vPos = verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = verts.GetNext(vPos);
    vrVertex vv = GetLocalMatrix() * (*v);
    box.Include(vv);
  }
  
  return box;
}

//static CMapPtrToPtr *map=NULL;

void vrSolid::AllocateColorData(SFInt32 where, SFInt32 type)
{
	// This is a convienience routine if you already know where
	// normals and texture coords will be stored
	SFInt32 size = GetDataSize(type);
	switch (where)
	{
	case PER_FACE:
		{
			ASSERT(0);
			// Disabled until we really need it -- we can just use the
			// face normal for normal
		}
		break;
	case PER_VERTEX:
		{
			LISTPOS vPos = verts.GetHeadPosition();
			while (vPos)
			{
				vrVertex *v = verts.GetNext(vPos);
				ASSERT(!v->data);
				v->data = (ColorData *)malloc(size);
				v->data->type = type;
			}
		}
		break;
	case PER_VERTEX_PER_FACE:
		{
			LISTPOS fPos = faces.GetHeadPosition();
			while (fPos)
			{
				vrFace *f = faces.GetNext(fPos);
				LISTPOS hPos = f->GetLoopOut()->halfedges.GetHeadPosition();
				while (hPos)
				{
					vrHalfEdge *he = f->GetLoopOut()->halfedges.GetNext(hPos);
					he->data = (ColorData *)malloc(size);
					he->data->type = type;
				}
			}
		}
		break;
	}
}
*/

void vrSolid::RemoveFaceAtIndex(Uint32 index)
{
	vrFace *f = findFace(index);
	vrHalfEdge *he = f->GetFirstHe();
	lkef(he, he->GetMate());
}

void vrSolid::RemoveVertexAtIndex(Uint32 index)
{
	vrVertex *v = findVertex(index);
	if (v)
	{
		vrHalfEdge *he1 = v->GetHe();
		vrHalfEdge *he2 = he1->GetMate();
		lkev(he1, he2);
	}
}

void vrSolid::RemoveVertexAtPt(const SFVec3f& pos)
{
	LISTPOS vPos = verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = verts.GetNext(vPos);
		if (pos == *v)
		{
			Uint32 index = v->GetIndex();
			Uint32 next  = v->GetHe()->GetMate()->GetVertex()->GetIndex();
			kev(v->GetHe()->GetFace()->GetIndex(), index, next);
		}
	}
}

void vrSolid::SetColor(const SFColor& color)
{
	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *face = faces.GetNext(fPos);
		face->SetColor(color);
	}
}