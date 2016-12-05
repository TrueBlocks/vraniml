#include "Solid\Solid.h"

void vrDataSet::BuildColors()
{
	ASSERT(m_Geom);
}

void vrDataSet::BuildNormals()
{
	ASSERT(m_Geom);
}

void vrDataSet::BuildTexCoords()
{
	ASSERT(m_Geom);
}

void vrDataSet::BuildMesh(void)
{
	// should never happen
	ASSERT(0);
}

//----------------------------------------------------------------------
void vrDataSet::AddColor(const SFColor& color)
{
	vrColor *colorNode = GetColor();
	if (colorNode)
		colorNode->AddColor(color); 
}

void vrDataSet::AddCoord(const SFVec3f& vec3f)
{
	vrCoordinate *coordNode = GetCoord();
	if (coordNode)
		coordNode->AddPoint(vec3f);
}

void vrDataSet::AddNormal(const SFVec3f& vec3f)
{
	vrNormal *normNode = GetNormal();
	if (normNode)
		normNode->AddVector(vec3f);
}

void vrDataSet::AddTexCoord(const SFVec2f& vec2f)
{
	vrTextureCoordinate *coordNode = GetTexCoord();
	if (coordNode)
		coordNode->AddPoint(vec2f);
}

SFInt32 vrDataSet::GetNColors(void) const
{
	vrColor *colorNode = GetColor();
	if (colorNode)
		return colorNode->GetColorArray().GetCount();
	else
		return 0;
}

SFInt32 vrDataSet::GetNCoords(void) const
{
	vrCoordinate *coordNode = GetCoord();
	if (coordNode)
		return coordNode->GetPointArray().GetCount();
	else
		return 0;
}

SFInt32 vrDataSet::GetNNormals(void) const
{
	vrNormal *normNode = GetNormal();
	if (normNode)
		return normNode->GetVectorArray().GetCount();
	else
		return 0;
}

SFInt32 vrDataSet::GetNTexCoords(void) const
{
	vrTextureCoordinate *coordNode = GetTexCoord();
	if (coordNode)
		return coordNode->GetPointArray().GetCount();
	else
		return 0;
}

SFColor vrDataSet::GetColor(SFInt32 n) const
{
	vrColor *colorNode = GetColor();
	if (colorNode) 
		return colorNode->GetColorArray()[n];
	else
		return SFColor(0.0);
}

SFVec3f vrDataSet::GetCoord(SFInt32 n) const
{ 
	vrCoordinate *coordNode = GetCoord();
	if (coordNode) 
		return coordNode->GetPointArray()[n];
	else
		return SFVec3f(0.0);
}

SFVec3f vrDataSet::GetNormal(SFInt32 n) const
{ 
	vrNormal *normNode  = GetNormal();
	if (normNode)
		return normNode->GetVectorArray()[n];
	else
		return SFVec3f(0.0);
}

SFVec2f vrDataSet::GetTexCoord(SFInt32 n) const
{
	vrTextureCoordinate *coordNode = GetTexCoord();
	if (coordNode)
		return coordNode->GetPointArray()[n];
	else
		return SFVec2f(0.0);
}
