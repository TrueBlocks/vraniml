#include "Solid\Solid.h"

#define N 16

void vrCone::BuildColors(void)
{
	ASSERT(m_Geom);
	m_Geom->m_SolidColor = TRUE;
}

static vrVertex *top=NULL;
void vrCone::BuildNormals(void)
{
	ASSERT(m_Geom);
	m_Geom->CalcPlaneEquations();
	m_Geom->MarkCreases(vrDeg2Rad(90.0));
	LISTPOS vPos = m_Geom->verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = m_Geom->verts.GetNext(vPos);
		v->CalcNormal();
	}

	ASSERT(top);
	vrHalfEdge *he = top->GetHe();
	vrHalfEdge *start = he;
	do
	{
		SFVec3f n1 = he->GetFace()->GetNormal();
		SFVec3f n2 = he->GetMate()->GetFace()->GetNormal();
		he->SetNormal(Normalize((n1+n2)/2.0));
		he = he->GetMate()->Next();
	} while (he != start);
	if (top->data)
	{
		delete top->data;
		top->data = NULL;
	}
	
}

void vrCone::BuildTexCoords(void)
{
	// Assign the bottom faces texCoords, find the furthest away in z for the sides faces
	vrHalfEdge *deepestZ = NULL;
	
	vrFace *bottom = m_Geom->findFace(0);
	LISTPOS pos = bottom->GetLoopOut()->halfedges.GetHeadPosition();
	while (pos)
	{
		vrHalfEdge *he = bottom->GetLoopOut()->halfedges.GetNext(pos);
		vrVertex *v = he->GetVertex();
		he->SetTexCoord(SFVec2f((v->x+1.0)/2.0, (v->z+1.0)/2.0));
		if (!deepestZ || deepestZ->GetVertex()->z > v->z)
		{
			deepestZ = he->GetMate()->Next()->GetMate()->Next();
		}
	}

	// Now, starting with the deepestZ halfedge, go around the side faces and
	// assign texture coords (note: each step is N/2*PI)
	SFFloat delta = (1.0 / N);
	SFFloat x = -delta;
	vrHalfEdge *he = deepestZ;
	do
	{
		SFVec2f t = SFVec2f(x+delta, 0.0);
		he->SetTexCoord(t);
		vrHalfEdge *next = he->Next();
		t = SFVec2f(x, 0.0);
		next->SetTexCoord(t);
		next = next->Next();
		t = SFVec2f(x+(delta/2), 1.0);
		next->SetTexCoord(t);
		x+=delta;
		he = he->Prev()->GetMate()->Prev();
	} while (he != deepestZ);
}

void vrCone::BuildMesh(void)
{
	SetGeom(NULL);
		
	m_Geom = new vrSolid(GetBottomRadius(), 0.0, -GetHeight()/2.0);
	m_Geom->Reference();

	m_Geom->Arc(0, 0, 0.0, 0.0, GetBottomRadius(), -GetHeight()/2.0, 0.0, ((N-1)*360.0/N), N-1);
	m_Geom->smef(0, N-1, 0);
  m_Geom->TranslationalSweep(m_Geom->findFace(1), SFVec3f(0.0, 0.0, GetHeight()));

	vrVertex *v = m_Geom->findVertex(N*2-1);
	ASSERT(v);
	m_Geom->CollapseFace(m_Geom->findFace(1));

	ASSERT(!v->IsMarked(DELETED));
	v->SetLocation(SFVec3f(0.0, 0.0, GetHeight()/2.0));

  m_Geom->TransformGeometry(RotationXMatrix(vrDeg2Rad(-90.0)));
	
	m_Geom->SetMark(FACE_SET);

	BuildColors();
	top = v;
	BuildNormals();
	top = NULL;
	BuildTexCoords();
	
//	if (v->data)
//	{
//		SFVec2f t = v->data->GetTexCoord();
//		delete v->data;
//		v->data = NULL;
//		v->SetTexCoord(t);
//	}

	if (!m_Bottom || !m_Side)
	{
		LISTPOS fPos = m_Geom->faces.GetHeadPosition();
		while (fPos)
		{
			vrFace *f = m_Geom->faces.GetNext(fPos);
			if (f->GetIndex() == 0)
			{
				if (!m_Bottom)
					f->SetMark2(INVISIBLE);
			} else
			{
				if (!m_Side)
					f->SetMark2(INVISIBLE);
			}
		}
//		m_Solid=FALSE;
	}
}

