//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "IndexedLineSet.h"

IMPLEMENT_NODE(vrIndexedLineSet, vrDataSet);

//----------------------------------------------------------------------
vrIndexedLineSet::vrIndexedLineSet(void) : vrDataSet()
{
	if (GetRuntimeClass()->Reference()==2)
	{
		AddEventIn(SFINT32, VRML_SET_COLORINDEX_STR);
		AddEventIn(SFINT32, VRML_SET_COORDINDEX_STR);
		AddExposedField(SFNODE, VRML_COLOR_STR);
		AddExposedField(SFNODE, VRML_COORD_STR);
		// undefined events -- to invalidate geometry nodes
		AddEventIn(SFBOOL, VRML_INVALIDATE_STR);

		AddField(SFBOOL, VRML_COLORPERVERTEX_STR);
		AddField(MFINT32, VRML_COLORINDEX_STR);
		AddField(MFINT32, VRML_COORDINDEX_STR);
	}
}

vrIndexedLineSet::vrIndexedLineSet(const vrIndexedLineSet& v) : vrDataSet(v)
{
	GetRuntimeClass()->Reference();
}

vrIndexedLineSet::~vrIndexedLineSet(void)
{
	GetRuntimeClass()->Dereference();
}

vrIndexedLineSet& vrIndexedLineSet::operator=(const vrIndexedLineSet& v)
{
	vrDataSet::operator=(v);


	return *this;
}

SFNode vrIndexedLineSet::Clone(void) const
{
	return new vrIndexedLineSet(*this);
}

//----------------------------------------------------------------------
//ReceiveEventIn is missing

//----------------------------------------------------------------------
SFBool vrIndexedLineSet::IsDefault(const SFString& fieldName, vrField *field) const
{
	return vrDataSet::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrIndexedLineSet::SetFieldValue(const SFString& fieldName, void *val)
{
	return vrDataSet::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "IndexedLineSet.cxx"
