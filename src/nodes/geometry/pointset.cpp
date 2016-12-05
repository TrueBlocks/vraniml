//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "PointSet.h"

IMPLEMENT_NODE(vrPointSet, vrDataSet);

//----------------------------------------------------------------------
vrPointSet::vrPointSet(void) : vrDataSet()
{
	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFNODE, VRML_COLOR_STR);
		AddExposedField(SFNODE, VRML_COORD_STR);
	}
}

vrPointSet::vrPointSet(const vrPointSet& v) : vrDataSet(v)
{
	GetRuntimeClass()->Reference();
}

vrPointSet::~vrPointSet(void)
{
	GetRuntimeClass()->Dereference();
}

vrPointSet& vrPointSet::operator=(const vrPointSet& v)
{
	vrDataSet::operator=(v);


	return *this;
}

SFNode vrPointSet::Clone(void) const
{
	return new vrPointSet(*this);
}

//----------------------------------------------------------------------
//ReceiveEventIn() is missing;

//----------------------------------------------------------------------
SFBool vrPointSet::IsDefault(const SFString& fieldName, vrField *field) const
{
	return vrDataSet::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrPointSet::SetFieldValue(const SFString& fieldName, void *val)
{
	return vrDataSet::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "PointSet.cxx"
