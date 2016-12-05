#include "Solid\Solid.h"

void vrSphere::BuildColors(void)
{
	ASSERT(m_Geom);
//	m_SolidColor = TRUE;
}

void vrSphere::BuildNormals(void)
{
	ASSERT(m_Geom);

	m_Geom->CalcPlaneEquations();
	m_Geom->MarkCreases(vrDeg2Rad(0.0));

	LISTPOS vPos = m_Geom->verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = m_Geom->verts.GetNext(vPos);
		v->SetNormal(Normalize(*v));
	}
}

void vrSphere::BuildTexCoords(void)
{
	// The sphere's normals have y=-1 at the south pole and y = 1 at the north
	// pole, z = -1 at back seem and x = -1 at left seem.  Use this info to 
	// generate texture coords
	LISTPOS vPos = m_Geom->verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = m_Geom->verts.GetNext(vPos);
		SFVec3f n(0);
		n = v->GetNormal(n);
//		ASSERT(Length(n)==1.0);
		float f = DotProduct(SFVec3f(0,0,-1),SFVec3f(n.x,0,n.z));
		if (n.x < 0.0)
		{
			f = acos(f) / (M_PI*2); //(/= 4.0;
		} else
		{
			f = ((M_PI*2) - acos(f)) / (M_PI*2);
		}
		SFVec2f t(f, (n.y+1.0)/2.0);
		v->SetTexCoord(t);
	}
}

void vrSphere::BuildMesh(void)
{
	SetGeom(NULL);
		
	m_Geom = new vrSolid(-m_Radius, 0.0, 0.0);
	m_Geom->Reference();

  m_Geom->Arc(0, 0, 0.0f, 0.0f, m_Radius, 0.0f, 180.0f, 0.0f, m_Slices);
  m_Geom->RotationalSweep(m_Stacks);
	m_Geom->SetMark(FACE_SET);

	// The are no colors, normals and texture coords are generated
	//BuildColors();
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
