void vrText::BuildColors(void)
{
}

void vrText::BuildNormals(void)
{
}

void vrText::BuildTexCoords(void)
{
}

#if 1
void vrText::BuildMesh(void)
{
}
#else
#include "Solid\Vertex.h"
#include "Solid\Solid.h"
static vrVertexArray verts;
void vrText::BuildMesh(void)
{
	SetGeom(NULL);
	m_Geom = new vrSolid;
	m_Geom->Reference();

	m_Geom->SetMark(FACE_SET);

	SFVec3f array[] = {
		SFVec3f(0,0,0),
		SFVec3f(2,0,0),
		SFVec3f(2,2,0),
		SFVec3f(0,2,0),
		SFVec3f(0,0,0),
	};
	for (int i=0;i<5;i++)
	{
		verts.AddValue(new vrVertex(array[i]));
	}
	ASSERT(verts.GetCount() == 5);

	MFInt32 indicies;
	indicies[0] = 0;
	indicies[1] = 1;
	indicies[2] = 2;
	indicies[3] = 3;
	indicies[4] = 0;

	// Convert to a solid
	m_Geom->BuildFromIndexSet(verts, indicies);

	BuildColors();
	BuildNormals();
	BuildTexCoords();
	
	m_Geom->CalcPlaneEquations();

#ifdef _DEBUG
	SFInt32 nVerts = m_Geom->verts.GetCount();
#endif
	m_Geom->Triangulate();
#ifdef _DEBUG
	ASSERT(nVerts == m_Geom->verts.GetCount());
#endif
		
	verts.Clear();
}
#endif