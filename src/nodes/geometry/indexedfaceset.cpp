//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "IndexedFaceSet.h"
#include "Color.h"
#include "Coordinate.h"
#include "Normal.h"
#include "TextureCoordinate.h"

IMPLEMENT_NODE(vrIndexedFaceSet, vrDataSet);

//----------------------------------------------------------------------
vrIndexedFaceSet::vrIndexedFaceSet(void) : vrDataSet()
{
	if (GetRuntimeClass()->Reference()==2)
	{
		AddEventIn(SFINT32, VRML_SET_COLORINDEX_STR);
		AddEventIn(SFINT32, VRML_SET_COORDINDEX_STR);
		AddEventIn(SFINT32, VRML_SET_NORMALINDEX_STR);
		AddEventIn(SFINT32, VRML_SET_TEXCOORDINDEX_STR);
		AddExposedField(SFNODE, VRML_COLOR_STR);
		AddExposedField(SFNODE, VRML_COORD_STR);
		AddExposedField(SFNODE, VRML_NORMAL_STR);
		AddExposedField(SFNODE, VRML_TEXCOORD_STR);
		// undefined events -- to invalidate geometry nodes
		AddEventIn(SFBOOL, VRML_INVALIDATE_STR);

		AddField(SFBOOL, VRML_CCW_STR);
		AddField(SFBOOL, VRML_COLORPERVERTEX_STR);
		AddField(SFFLOAT, VRML_CREASEANGLE_STR);
		AddField(MFFLOAT, VRML_HEIGHT_STR);
		AddField(SFBOOL, VRML_NORMALPERVERTEX_STR);
		AddField(SFBOOL, VRML_SOLID_STR);
		AddField(SFBOOL, VRML_CONVEX_STR);
		AddField(MFINT32, VRML_COLORINDEX_STR);
		AddField(MFINT32, VRML_COORDINDEX_STR);
		AddField(MFINT32, VRML_NORMALINDEX_STR);
		AddField(MFINT32, VRML_TEXCOORDINDEX_STR);
	}
}

vrIndexedFaceSet::vrIndexedFaceSet(const vrIndexedFaceSet& v) : vrDataSet(v)
{
	GetRuntimeClass()->Reference();
}

vrIndexedFaceSet::~vrIndexedFaceSet(void)
{
	GetRuntimeClass()->Dereference();
}

vrIndexedFaceSet& vrIndexedFaceSet::operator=(const vrIndexedFaceSet& v)
{
	vrDataSet::operator=(v);

	return *this;
}

SFNode vrIndexedFaceSet::Clone(void) const
{
	return new vrIndexedFaceSet(*this);
}

//----------------------------------------------------------------------

//----------------------------------------------------------------------
SFBool vrIndexedFaceSet::IsDefault(const SFString& fieldName, vrField *field) const
{
	return vrDataSet::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrIndexedFaceSet::SetFieldValue(const SFString& fieldName, void *val)
{
	return vrDataSet::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "IndexedFaceSet.cxx"
