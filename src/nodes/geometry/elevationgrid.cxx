#include "Solid\Solid.h"
#include "Color.h"
#include "Coordinate.h"
#include "Normal.h"
#include "TextureCoordinate.h"

static vrVertexArray verts;
void vrElevationGrid::BuildMesh(void)
{
	ASSERT(m_XDimension >= 1);
	ASSERT(m_ZDimension >= 1);
	ASSERT(m_XSpacing >= 0.0);
	ASSERT(m_ZSpacing >= 0.0);

	ASSERT(GetNHeights() >= m_XDimension * m_ZDimension);
	
	vrNormal *normals = GetNormal();
	SFInt32 nNormals = ((normals) ? GetNNormals() : 0);
	ASSERT(!normals || normals->IsKindOf(GETRUNTIME_CLASS(vrNormal)));

	vrTextureCoordinate *texCoord = GetTexCoord();
	SFInt32 nTexCoords = ((texCoord) ? GetNTexCoords() : 0);
	ASSERT(!texCoord || texCoord->IsKindOf(GETRUNTIME_CLASS(vrTextureCoordinate)));

	for (int col=0;col<m_ZDimension;col++)
	{
		SFFloat z = (col * m_ZSpacing);
		for (int row=0;row<m_XDimension;row++)
		{
			SFFloat x = (row * m_XSpacing);
			SFInt32 index = row + m_XDimension * col;
			vrVertex *v = new vrVertex;
			*v = SFVec3f(x, GetHeight(index), z);
			verts.AddValue(v);
			if (normals)
			{
				SFInt32 nIndex = MIN(index, (SFInt32)(nNormals-1));
				v->SetNormal(normals->GetVector(nIndex));
			}
			if (texCoord)
			{
				SFInt32 tIndex = MIN(index, (SFInt32)(nTexCoords-1));
				v->SetTexCoord(texCoord->GetPoint(tIndex));
			}
		}
	}

	for (col=0;col<m_ZDimension-1;col++)
	{
		for (int row=0;row<m_XDimension-1;row++)
		{
			long index1 = row + m_XDimension * col;
			long index2 = index1 + 1;
			long index3 = index2 + m_XDimension;
			long index4 = index1 + m_XDimension;

			m_CoordIndex.AddValue(index1);
			m_CoordIndex.AddValue(index2);
			m_CoordIndex.AddValue(index4);
			m_CoordIndex.AddValue(-1);
			m_CoordIndex.AddValue(index4);
			m_CoordIndex.AddValue(index2);
			m_CoordIndex.AddValue(index3);
			m_CoordIndex.AddValue(-1);
		}
	}

	SetGeom(NULL);
	m_Geom = new vrSolid;
	m_Geom->Reference();

	m_Geom->SetMark(FACE_SET);

	// Convert to a solid
	m_Geom->BuildFromIndexSet(verts, m_CoordIndex);

	BuildColors();
	BuildNormals();
	BuildTexCoords();

	verts.Clear();
}

void vrElevationGrid::BuildColors(void)
{
	// The colorPerVertex field determines whether colors (if specified in 
	// the color field) should be applied to each vertex or each quadrilateral 
	// of the ElevationGrid. If colorPerVertex is FALSE and the color field 
	// is not NULL, then the color field must contain a Color node containing 
	// at least (xDimension-1)*(zDimension-1) colors. If colorPerVertex is TRUE 
	// and the color field is not NULL, then the color field must contain a Color 
	// node containing at least xDimension*zDimension colors. 
	vrColor *colors = GetColor();
	if (colors)
	{
		m_Geom->m_SolidColor = FALSE;
		
		SFInt32 nColors = colors->GetNColors(); 
		if (GetColorPerVertex())
		{
			SFInt32 nVerts = verts.GetCount();
			for (int i=0;i<nVerts;i++)
			{
				verts[i]->SetColor(colors->GetColorArray()[i]);
			}
		} else
		{
			SFInt32 cindex = 0;
			LISTPOS pos = m_Geom->faces.GetTailPosition();
			while (pos)
			{
				cindex = MIN(cindex, (SFInt32)(nColors-1));
				SFColor color = colors->GetColorArray()[cindex++];

				// Each quad makes for two faces -- and they are in order
				vrFace *f = m_Geom->faces.GetPrev(pos);
				f->SetColor(color);
				ASSERT(pos);
				f = m_Geom->faces.GetPrev(pos);
				f->SetColor(color);
			}
		}
	} else
	{
		m_Geom->m_SolidColor = TRUE;
	}
}

void vrElevationGrid::BuildNormals(void)
{
	m_Geom->CalcPlaneEquations();
	// if creaseAngle is zero make it just slightly larger than zero
	m_Geom->MarkCreases((m_CreaseAngle==0.0) ? vrDeg2Rad(1.0) : m_CreaseAngle);
	// ... calc normals and texture coords if needed

	vrNormal *normals = GetNormal();
	//SFInt32 nNormals = ((normals) ? GetNNormals() : 0);
	ASSERT(!normals || normals->IsKindOf(GETRUNTIME_CLASS(vrNormal)));
	if (!normals)
	{
		LISTPOS vPos = m_Geom->verts.GetHeadPosition();
		while (vPos)
		{
			vrVertex *v = m_Geom->verts.GetNext(vPos);
			v->CalcNormal();
		}
	}
}

void vrElevationGrid::BuildTexCoords(void)
{
	vrTextureCoordinate *texCoord = GetTexCoord();
	//SFInt32 nTexCoords = ((texCoord) ? GetNTexCoords() : 0);
	ASSERT(!texCoord || texCoord->IsKindOf(GETRUNTIME_CLASS(vrTextureCoordinate)));

	if (!texCoord)
	{
		m_Bounds = vrBoundingBox();
		LISTPOS vPos = m_Geom->verts.GetHeadPosition();
		while (vPos)
		{
			vrVertex *v = m_Geom->verts.GetNext(vPos);
			m_Bounds.Include(*v);
		}
		SFVec3f min = m_Bounds.GetMin();
		SFVec3f max = m_Bounds.GetMax();
		SFVec3f size = (max-min);
		vPos = m_Geom->verts.GetHeadPosition();
		while (vPos)
		{
			vrVertex *v = m_Geom->verts.GetNext(vPos);
			SFVec3f dist = *v - min;
			SFVec2f t = SFVec2f(dist.x / size.x, dist.z / size.z);
			v->SetTexCoord(t);
		}
	}
}
