//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Solid.h"

#ifdef _DEBUG
//----------------------------------------------------------------------
/*
 * This whole file disapears when optimized -- also all functions
 * here are const so can not alter thier objects 
 */

#undef PI
#define PI(ptr) ((ptr) ? (SFInt32)ptr->GetIndex() : (SFInt32)-1)
#define PN(ptr) ((ptr->next) ? (SFInt32)ptr->next->GetIndex() : (SFInt32)-1)
#define PP(ptr) ((ptr->prev) ? (SFInt32)ptr->prev->GetIndex() : (SFInt32)-1)

void vrSolid::Show(vrDumpContext& dc) const
{
  dc << "Solid: " << ((m_Mark == SOLID_A) ? "A" : (m_Mark == SOLID_B) ? "B" : "??") << "\n";

	dc.m_Verbose = FALSE;
	
	dc.m_nIndents++;
  dc << "Faces: [" << faces.GetCount() << "]\n----------------\n";
	LISTPOS fPos = faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = faces.GetNext(fPos);
		f->Show(dc);
  }

#if 0
  dc << "\n\nEdges: [" << edges.GetCount() << "]\n----------------\n";
	LISTPOS ePos = edges.GetHeadPosition();
	while (ePos)
	{
		vrEdge *e = edges.GetNext(ePos);
		e->Show(dc);
  }
#endif

  dc.m_Verbose = TRUE;
	dc << "\n\nVerts: [" << verts.GetCount() << "]\n----------------\n";
	LISTPOS vPos = verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = verts.GetNext(vPos);
    dc << dc.Indent();
		v->Show(dc);
    dc << "\n";
  }
	dc.m_nIndents--;

  dc << "\n-----------------------------------------------------------\n";
}

void DoData(vrDumpContext& dc, ColorData *data)
{
	dc << dc.Indent() << "m_ColorData [" << data->type << "] ";

	if (data->type&COLOR)
	{
		dc << "c: " << data->color;
	}
	if (data->type&NORMAL)
	{
		dc << "n: " << data->normal;
	}
	if (data->type&TEXCOORD)
	{
		dc << "t: " << data->texcoord;
	}
	dc << "\n";
}

void vrFace::Show(vrDumpContext& dc) const
{
  dc << dc.Indent() << "[" << (SFInt32)index << "] ";
//	if (dc.m_Verbose)
//	{
//		dc << " (" << mark1 << "=" << mark2 << ")]" << " plane equ: " << m_Normal << "\n";
//  }
//  if (data)
//	{
//		dc << "\n";
//		DoData(dc, data);
//	}

	dc.m_nIndents++;
	LISTPOS pos = loops.GetHeadPosition();
	while (pos)
	{
		vrLoop *loop = loops.GetNext(pos);
		loop->Show(dc);
	}
	dc.m_nIndents--;
	dc << "\n";
}

void vrLoop::Show(vrDumpContext& dc) const
{
  if (this == face->GetLoopOut()) 
    dc << dc.Indent() << "**"; 
  else 
    dc << dc.Indent() << "++";

	LISTPOS hPos = halfedges.GetHeadPosition();
	while (hPos)
	{
		vrHalfEdge *he = halfedges.GetNext(hPos);
		he->Show(dc);
  }

//	if (dc.m_Verbose)
//	{
		dc << "\n";
		hPos = halfedges.GetHeadPosition();
		while (hPos)
		{
			vrHalfEdge *he = halfedges.GetNext(hPos);
			dc << dc.Indent();
			if (he->GetVertex())
			{
				he->GetVertex()->Show(dc);
				dc << "\n";
			}
		}

		dc << "\n";
		hPos = halfedges.GetHeadPosition();
		while (hPos)
		{
			vrHalfEdge *he = halfedges.GetNext(hPos);
			dc << dc.Indent();
			if (he->GetEdge())
			{
				he->GetEdge()->Show(dc);
				dc << "\n";
			}
		}
//	}
}

void vrEdge::Show(vrDumpContext& dc) const
{
  dc << "[" << ((SFInt32)index) << "] m: " << m_Mark << "\n";

  dc.m_nIndents++;
  if (he1 && he1->GetVertex())
	{
		dc << dc.Indent() << "+ ";
		he1->GetVertex()->Show(dc);
		dc << "\n";
	}

  if (he2 && he2->GetVertex())
	{
		dc << dc.Indent() << "- ";
		he2->GetVertex()->Show(dc);
		dc << "\n";
	}

  dc.m_nIndents--;
}

void vrHalfEdge::Show(vrDumpContext& dc) const
{
  dc << PI(this);
//  if (dc.m_Verbose) 
//	{
    dc << "[" << PP(this) << "," << PN(this) << "(";
		((edge) ? dc << ((SFInt32)edge->GetIndex()) : dc << "NULL");
		dc << ")] ";
//    if (he->isNullEdge())
//      dc << "#";
//      if (he->isNullStrut()) {
//        VRTRACE("@");
//      }
//  }
  dc << " ";

  if (dc.m_Verbose && data)
	{
		dc << "\n";
		DoData(dc, data);
	}
}

void vrVertex::Show(vrDumpContext& dc) const
{
  dc << "[" << ((SFInt32)index) << "]: (" << ((SFVec3f)*this) << ")";
//	if (dc.m_Verbose)
//		dc << " m: " << m_Mark << " p: " << ((SFInt32)prevIndex) << " sc: " << scratch;
//	dc << "\n";

  if (dc.m_Verbose)
	{
		if (data)
		{
			dc << "\n";
			DoData(dc, data);
		}
	}
}

void vrIntersectRecord::Show(vrDumpContext& dc) const
{
	//char tt[][5] = { "NO", "FACE", "VERT", "EDGE", "INSD" };
	//VRTRACE("Type: %s(%d)\n", tt[type], type);

	//VRTRACE("Vertex: ");
	if (v) {
		v->Show(dc);
    //VRTRACE("\n");
	} else {
		//VRTRACE("NULL");
	}
	//VRTRACE("\n");

	//VRTRACE("vrHalfEdge: ");
	if (he) {
		he->Show(dc);
	} else {
		//VRTRACE("NULL");
	}
	//VRTRACE("\n");
}
#endif