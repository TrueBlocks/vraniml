#include "Solid\Solid.h"

vrBoundingBox vrBox::GetBoundingBox(void) const
{
	return vrBoundingBox(-m_Size/2, m_Size/2);
}

void vrBox::BuildColors(void)
{
	ASSERT(m_Geom);
	m_Geom->m_SolidColor = TRUE;
}

void vrBox::BuildNormals(void)
{
	ASSERT(m_Geom);

	m_Geom->CalcPlaneEquations();
	m_Geom->MarkCreases(vrDeg2Rad(1.0));
}

void vrBox::BuildTexCoords(void)
{
	ASSERT(m_Geom);
	
	LISTPOS fPos   = m_Geom->faces.GetHeadPosition();
	vrFace *left   = m_Geom->faces.GetNext(fPos);
	{
		vrFace *f = left;
		LISTPOS hPos = f->GetLoopOut()->halfedges.GetHeadPosition();
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(1,1));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(1,0));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(0,0));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(0,1));
	}
	vrFace *bottom = m_Geom->faces.GetNext(fPos);
	{
		vrFace *f = bottom;
		LISTPOS hPos = f->GetLoopOut()->halfedges.GetHeadPosition();
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(0,1));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(1,1));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(1,0));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(0,0));
	}
	vrFace *right  = m_Geom->faces.GetNext(fPos);
	{
		vrFace *f = right;
		LISTPOS hPos = f->GetLoopOut()->halfedges.GetHeadPosition();
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(0,0));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(0,1));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(1,1));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(1,0));
	}
	vrFace *top    = m_Geom->faces.GetNext(fPos);
	{
		vrFace *f = top;
		LISTPOS hPos = f->GetLoopOut()->halfedges.GetHeadPosition();
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(1,0));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(0,0));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(0,1));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(1,1));
	}
	vrFace *front  = m_Geom->faces.GetNext(fPos);
	{
		vrFace *f = front;
		LISTPOS hPos = f->GetLoopOut()->halfedges.GetHeadPosition();
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(0,0));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(0,1));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(1,1));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(1,0));
	}
	vrFace *back   = m_Geom->faces.GetNext(fPos);
	{
		vrFace *f = back;
		LISTPOS hPos = f->GetLoopOut()->halfedges.GetHeadPosition();
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(1,1));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(1,0));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(0,0));
		f->GetLoopOut()->halfedges.GetNext(hPos)->SetTexCoord(SFVec2f(0,1));
	}
}

void vrBox::BuildMesh(void)
{
	SetGeom(NULL);
		
	SFFloat x = GetSize().x / 2.0;
	SFFloat y = GetSize().y / 2.0;
	SFFloat z = GetSize().z / 2.0;

	m_Geom = new vrSolid(-x,  -y,  -z);
	m_Geom->Reference();
	m_Geom->smev(0, 0,    x,  -y,  -z);
  m_Geom->smev(0, 1,    x,   y,  -z);
  m_Geom->smev(0, 2,   -x,   y,  -z);
  m_Geom->smef(0, 3, 0);
  m_Geom->TranslationalSweep(m_Geom->findFace(1), SFVec3f(0.0, 0.0, GetSize().z));

	m_Geom->SetMark(FACE_SET);

	BuildColors();
	BuildNormals();
	BuildTexCoords();

#ifdef _DEBUG
	SFInt32 nVerts = m_Geom->verts.GetCount();
#endif
	m_Geom->Triangulate();
#ifdef _DEBUG
	ASSERT(nVerts == m_Geom->verts.GetCount());
#endif
}

