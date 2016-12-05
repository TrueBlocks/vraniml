#include "Color.h"
#include "Coordinate.h"
#include "Solid\Vertex.h"
#include "Solid\Solid.h"

static vrVertexArray verts;
void vrIndexedLineSet::BuildMesh(void)
{
	vrCoordinate *coords = GetCoord();

	SFInt32 nCoordIndicies = m_CoordIndex.GetCount();
	if (!nCoordIndicies)
		return;  // nothing to do

	SetGeom(NULL);
	m_Geom = new vrSolid;
	m_Geom->Reference();

	m_Geom->SetMark(LINE_SET);

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

	// At this point the faces are in order as specified in the
	// index list
	
	BuildColors();
	//BuildNormals();
	//BuildTexCoords();

	verts.Clear();
}

void vrIndexedLineSet::BuildColors(void)
{
	// Assign colors to the appropriate halfedges 
	vrColor   *colors = GetColor();
	if (colors)
	{
		m_Geom->m_SolidColor = FALSE;
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
						ASSERT(coordIndex == colorIndex);
					}
				}
			} else
			{
				//	color node -- colorPerVertex -- no colorIndices (use coord indicies
				for (int i=0;i<nCoordIndicies;i++)
				{
					SFInt32 coordIndex = m_CoordIndex[i];
					SFInt32 colorIndex = MIN(coordIndex, (SFInt32)(nColorIndicies-1));

					if (coordIndex != -1)
					{
						SFColor color = colors->GetColor(colorIndex);
						vrVertex *v = verts[coordIndex];
						v->SetColor(color);
					} else
					{
						ASSERT(coordIndex == colorIndex);
					}
				}
			}
		} else
		{
			// color per line

			SFInt32 nColorIndicies = m_ColorIndex.GetCount();
			SFInt32 nColors = colors->GetNColors();

			if (nColorIndicies)
			{
				//	color node -- colorPerLine -- colorIndices
				SFInt32 nIndex = 0;
				for (int i=0;i<nCoordIndicies;i++)
				{
					SFInt32 colorIndex = m_ColorIndex[MIN((SFInt32)i, (SFInt32)(nColorIndicies-1))];
					ASSERT(colorIndex>=0);
					SFColor lineColor = colors->GetColor(MIN(colorIndex, (SFInt32)(nColors-1)));

					SFInt32 coordIndex = m_CoordIndex[nIndex++];
					while (coordIndex != -1 && nIndex < nCoordIndicies)
					{
						vrVertex *v = verts[coordIndex];
						v->SetColor(lineColor);
						coordIndex = m_CoordIndex[nIndex++];
					}
				}
			} else
			{
				//	color node -- colorPerLine -- no colorIndices
				SFInt32 nIndex = 0;
				for (int i=0;i<nColors;i++)
				{
					SFColor lineColor = colors->GetColor(i);

					SFInt32 coordIndex = m_CoordIndex[nIndex++];
					while (coordIndex != -1 && nIndex < nCoordIndicies)
					{
						vrVertex *v = verts[coordIndex];
						v->SetColor(lineColor);
						coordIndex = m_CoordIndex[nIndex++];
					}
				}
			}
		}
	} else
	{
		// no color node...traverser will assign color to lines
		m_Geom->m_SolidColor = TRUE;
	}
}

void vrIndexedLineSet::BuildNormals(void)
{
	// no normals for line sets
}

void vrIndexedLineSet::BuildTexCoords(void)
{
	// no texture coords for line sets
}
