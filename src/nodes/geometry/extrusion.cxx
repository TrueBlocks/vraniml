#include "Traversers\WriteTraverser.h"
#include "Solid\Vertex.h"
#include "Solid\Solid.h"

SFFloat AngleBetween(const SFVec3f& v1, const SFVec3f& v2)
{
	double dot = DotProduct(v1, v2);
	return ((dot == 0.0) ? vrDeg2Rad(90.0) : acos(dot));
}

SFRotation AlignWithTangent(SFVec3f tangent)
{
	if (yAxis == tangent)
		return defRotation;
	if ((-yAxis) == tangent)
		return SFRotation(-defRotation.x, -defRotation.y, -defRotation.z, -defRotation.w);
	SFVec3f cross = CrossProduct(yAxis, tangent);
	SFFloat angle = AngleBetween(yAxis, tangent);
	return SFRotation(Normalize(cross), angle);
}

void vrExtrusion::BuildMesh(void)
{
	SFInt32 nCrossSections = m_CrossSection.GetCount();
	SFInt32 nSpines        = m_Spine.GetCount();
	SFInt32 nScales        = m_Scale.GetCount();
	SFInt32 nOrientations  = m_Orientation.GetCount();

	vrVertexArray verts;
	MFInt32 indicies;

	SFBool crossLoop  = (GetCrossSection(0) == GetCrossSection(nCrossSections-1));
	if (crossLoop)
		nCrossSections--;
	SFBool sameScale  = (GetScale(0)        == GetScale(nScales-1));
	SFBool sameOrient = (GetOrientation(0)  == GetOrientation(nOrientations-1));
	SFBool spineLoop  = (GetSpine(0)        == GetSpine(nSpines-1) && sameScale && sameOrient);

	for (SFInt32 iSpine=0;iSpine<nSpines;iSpine++)
	{
		// spine
		SFVec3f spine = GetSpine(iSpine);
		
		// tangent orientation
		SFRotation tangentOri;
		SFVec3f tangent;
		if (iSpine==0 || iSpine==nSpines-1)
		{
			if (spineLoop)
			{
				tangent = GetSpine(0) - GetSpine(nSpines-2);
			} else
			{
				if (iSpine==0)
				{
					tangent = GetSpine(1) - GetSpine(0);
				} else
				{
					tangent = GetSpine(nSpines-1) - GetSpine(nSpines-2);
				}
			}
		} else
		{
			tangent = GetSpine(iSpine+1) - GetSpine(iSpine-1);
		}
		tangent = Normalize(tangent);
		tangentOri = AlignWithTangent(tangent);

		// orientation
		SFRotation orient = GetOrientation(MIN((SFInt32)(GetNOrientations()-1), iSpine));

		SFVec3f scale = GetScale(MIN((SFInt32)(GetNScales()-1), iSpine));
		vrSwap(scale.y, scale.z); scale.y = 1.0;

		vrMatrix matrix;
		
		matrix = ScaleMatrix(scale);
		matrix *= RotationAxisMatrix(SFVec3f(tangentOri.x, tangentOri.y, tangentOri.z), tangentOri.w);
		matrix *= RotationAxisMatrix(SFVec3f(orient.x,orient.y,orient.z), orient.w);
		matrix *= TranslationMatrix(spine);

		for (SFInt32 j=0;j<nCrossSections;j++)
		{
			SFVec3f vec = GetCrossSection(j);
			vrSwap(vec.y, vec.z); vec.y = 0.0;
			vec = matrix * vec;
			
			// Add every vertex including the last in a crossLoop (even though it is not used
			// because we use the index of the first in the crossLoop so normals are
			// calced correctly.  Including the last makes following math easier.
			verts.AddValue(new vrVertex(vec));
		}

		if (iSpine==0)
		{
			// Add begin cap
			if (GetBeginCap())
			{
				for (SFInt32 iCross=nCrossSections-1;iCross>=0;iCross--)
				{
					indicies.AddValue(iCross);
				}
				if (crossLoop)
				{
					indicies.AddValue(0);
				}
				indicies.AddValue(-1);
			}
		} else
		{
			// Add faces for extruded edges
			for (SFInt32 iCross=0;iCross<nCrossSections-1;iCross++)
			{
				SFInt32 index = (iSpine*nCrossSections)+iCross;

				SFInt32 index1 = index+1-nCrossSections;
				SFInt32 index2 = index+1;
				SFInt32 index3 = index;
				SFInt32 index4 = index-nCrossSections;

				indicies.AddValue(index1);
				indicies.AddValue(index2);
				indicies.AddValue(index3);
				indicies.AddValue(-1);
				indicies.AddValue(index3);
				indicies.AddValue(index4);
				indicies.AddValue(index1);
				indicies.AddValue(-1);
			}
			if (crossLoop)
			{
				SFInt32 index = (iSpine*nCrossSections)+nCrossSections-1;

				SFInt32 index1 = ((index+1)-nCrossSections)-nCrossSections;
				SFInt32 index2 = ((index+1)-nCrossSections);
				SFInt32 index3 = index;
				SFInt32 index4 = index-nCrossSections;

				indicies.AddValue(index1);
				indicies.AddValue(index2);
				indicies.AddValue(index3);
				indicies.AddValue(-1);
				indicies.AddValue(index3);
				indicies.AddValue(index4);
				indicies.AddValue(index1);
				indicies.AddValue(-1);
			}
			
			// Add end cap
			if (iSpine==nSpines-1)
			{
				if (GetEndCap())
				{
					for (SFInt32 iCross=0;iCross<nCrossSections;iCross++)
					{
						if (spineLoop)
						{
							indicies.AddValue(iCross);
						} else
						{
							SFInt32 index = (iSpine*nCrossSections)+iCross;
							indicies.AddValue(index);
						}
					}
					indicies.AddValue(-1);
				}
				if (crossLoop)
				{
					if (spineLoop)
					{
						indicies.AddValue(0);
					} else
					{
						SFInt32 index = (iSpine*nCrossSections);
						indicies.AddValue(index);
					}
				}

			}
		}
	}

	SetGeom(NULL);
		
	m_Geom = new vrSolid;
	m_Geom->Reference();

	m_Geom->SetMark(FACE_SET);

	m_Geom->BuildFromIndexSet(verts, indicies);

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

void vrExtrusion::BuildColors(void)
{
	m_Geom->m_SolidColor = TRUE;
}

void vrExtrusion::BuildNormals(void)
{
	m_Geom->CalcPlaneEquations();
	m_Geom->MarkCreases(m_CreaseAngle);

	LISTPOS vPos = m_Geom->verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = m_Geom->verts.GetNext(vPos);
		v->CalcNormal();
	}
}

void vrExtrusion::BuildTexCoords(void)
{
}
