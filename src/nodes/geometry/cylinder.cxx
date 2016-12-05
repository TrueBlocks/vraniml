#include "Solid\Solid.h"

#define N 16

void vrCylinder::BuildColors(void)
{
	ASSERT(m_Geom);
	m_Geom->m_SolidColor = TRUE;
}

void vrCylinder::BuildNormals(void)
{
	ASSERT(m_Geom);
	m_Geom->CalcPlaneEquations();
	m_Geom->MarkCreases(vrDeg2Rad(89.0));
	LISTPOS vPos = m_Geom->verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = m_Geom->verts.GetNext(vPos);
		v->CalcNormal();
	}
}

void vrCylinder::BuildTexCoords(void)
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

	vrFace *top = m_Geom->findFace(1);
	pos = top->GetLoopOut()->halfedges.GetHeadPosition();
	while (pos)
	{
		vrHalfEdge *he = top->GetLoopOut()->halfedges.GetNext(pos);
		vrVertex *v = he->GetVertex();
		he->SetTexCoord(SFVec2f((v->x+1.0)/2.0, 1.-(v->z+1.0)/2.0));
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
		t = SFVec2f(x, 1.0);
		next->SetTexCoord(t);

		next = next->Next();
		t = SFVec2f(x+delta, 1.0);
		next->SetTexCoord(t);

		x+=delta;
		he = he->Prev()->GetMate()->Prev();
	} while (he != deepestZ);
}

void vrCylinder::BuildMesh(void)
{
	SetGeom(NULL);
		
	m_Geom = new vrSolid(GetRadius(), 0.0, -GetHeight()/2.0);
	m_Geom->Reference();

	m_Geom->Arc(0, 0, 0.0, 0.0, GetRadius(), -GetHeight()/2.0, 0.0, ((N-1)*360.0f/N), N-1);
	m_Geom->smef(0, N-1, 0);
  m_Geom->TranslationalSweep(m_Geom->findFace(1), SFVec3f(0.0f, 0.0f, GetHeight()));

  m_Geom->TransformGeometry(RotationXMatrix(vrDeg2Rad(-90.0)));

	m_Geom->SetMark(FACE_SET);

	BuildColors();
	BuildNormals();
	BuildTexCoords();

	if (!m_Top || !m_Bottom || !m_Side)
	{
		LISTPOS fPos = m_Geom->faces.GetHeadPosition();
		while (fPos)
		{
			vrFace *f = m_Geom->faces.GetNext(fPos);
			if (f->GetIndex() == 0)
			{
				if (!m_Bottom)
					f->SetMark2(INVISIBLE);
			} else if (f->GetIndex() == 1)
			{
				if (!m_Top)
					f->SetMark2(INVISIBLE);
			} else
			{
				if (!m_Side)
					f->SetMark2(INVISIBLE);
			}
		}
//		m_Solid = FALSE;
	}
}

