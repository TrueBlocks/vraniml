#include "Solid\Vertex.h"
#include "Solid\Solid.h"

static vrVertexArray verts;
void vrIndexedFaceSet::BuildMesh(void)
{
	vrCoordinate *coords = GetCoord();

	SFInt32 nCoordIndicies = m_CoordIndex.GetCount();
	if (!nCoordIndicies)
		return;  // nothing to do

	SetGeom(NULL);
	m_Geom = new vrSolid;
	m_Geom->Reference();

	m_Geom->SetMark(FACE_SET);

	// Build an array of verticies
	const MFVec3f coordArray = coords->GetPointArray();
	SFInt32 nCoords = coordArray.GetCount();
	
	for (int i=0;i<nCoords;i++)
	{
		verts.AddValue(new vrVertex(coordArray[i]));
	}
	ASSERT(verts.GetCount() == nCoords);

	// Convert to a solid
	m_Geom->BuildFromIndexSet(verts, m_CoordIndex);

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
		
	verts.Clear();
}

void vrIndexedFaceSet::BuildColors(void)
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
		//SFInt32 nVerts = verts.GetCount();
		SFInt32 nCoordIndicies = m_CoordIndex.GetCount();

		if (m_ColorPerVertex)
		{
			// color per vertex
			
			SFInt32 nColorIndicies = m_ColorIndex.GetCount();
			if (nColorIndicies)
			{
				//	color node -- colorPerVertex -- colorIndices
				for (int i=0;i<nCoordIndicies;i++)
				{
					SFInt32 coordIndex = m_CoordIndex[i];
					SFInt32 colorIndex = m_ColorIndex[MIN((SFInt32)i, (SFInt32)(nColorIndicies-1))];

					if (coordIndex != -1)
					{
						SFColor color = colors->GetColor(colorIndex);
						vrVertex *v = verts[coordIndex];
						v->SetColor(color);
					} else
					{
//						ASSERT(coordIndex == colorIndex);
					}
				}
			} else
			{
				//	color node -- colorPerVertex -- no colorIndices (use coord indicies)
				for (int i=0;i<nCoordIndicies;i++)
				{
					SFInt32 coordIndex = m_CoordIndex[i];
					SFInt32 colorIndex = MIN(coordIndex, (SFInt32)(nColors-1));

					if (coordIndex != -1)
					{
						SFColor color = colors->GetColor(colorIndex);
						vrVertex *v = verts[coordIndex];
						v->SetColor(color);
					} else
					{
//						ASSERT(coordIndex == colorIndex);
					}
				}
			}
		} else
		{
			// color per face

			SFInt32 nColorIndicies = m_ColorIndex.GetCount();
			if (nColorIndicies)
			{
				//	color node -- colorPerFace -- colorIndices
				SFInt32 nIndex = 0;
				LISTPOS fPos = m_Geom->faces.GetTailPosition();
				while (fPos)
				{
					vrFace *f = m_Geom->faces.GetPrev(fPos);
					nIndex = MIN(nIndex, (SFInt32)(nColorIndicies-1));
					SFInt32 colorIndex = m_ColorIndex[nIndex++]; 
					SFColor faceColor = colors->GetColor(colorIndex);
					f->SetColor(faceColor);
				}
			} else
			{
				//	color node -- colorPerFace -- no colorIndices
				SFInt32 nIndex = 0;
				LISTPOS fPos = m_Geom->faces.GetTailPosition();
				while (fPos)
				{
					vrFace *f = m_Geom->faces.GetPrev(fPos);
					nIndex = MIN(nIndex, (SFInt32)(nColors-1));
					SFColor faceColor = colors->GetColor(nIndex++);
					f->SetColor(faceColor);
				}
			}
		}
	} else
	{
		// no color node...traverser will assign color to lines
		m_Geom->m_SolidColor = TRUE;
	}
}

void vrIndexedFaceSet::BuildNormals(void)
{
	m_Geom->CalcPlaneEquations();
	m_Geom->MarkCreases(m_CreaseAngle);

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
	} else
	{
		// Normals are ignored in indexed face sets
		ASSERT(0);
	}
}

void vrIndexedFaceSet::BuildTexCoords(void)
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
	} else
	{
		SFInt32 nTexCoords = texCoord->GetNPoints();
		//SFInt32 nVerts = verts.GetCount();
		SFInt32 nCoordIndicies = m_CoordIndex.GetCount();

		for (int i=0;i<nCoordIndicies;i++)
		{
			SFInt32 coordIndex = m_CoordIndex[i];
			SFInt32 texIndex = MIN(coordIndex, (SFInt32)(nTexCoords-1));

			if (coordIndex != -1)
			{
				SFVec2f tCoord = texCoord->GetPoint(texIndex);
				vrVertex *v = verts[coordIndex];
				v->SetTexCoord(tCoord);
			} else
			{
				ASSERT(coordIndex == texIndex);
			}
		}
	}
}

