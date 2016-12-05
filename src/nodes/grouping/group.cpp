//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Group.h"

IMPLEMENT_NODE(vrGroup, vrGroupingNode);

//----------------------------------------------------------------------
vrGroup::vrGroup(void) : vrGroupingNode()
{
	if (GetRuntimeClass()->Reference()==2)
	{
		AddEventIn(MFNODE, VRML_ADDCHILDREN_STR);
		AddEventIn(MFNODE, VRML_REMOVECHILDREN_STR);
		AddExposedField(MFNODE, VRML_CHILDREN_STR);
		AddField(SFVEC3F, VRML_BBOXCENTER_STR);
		AddField(SFVEC3F, VRML_BBOXSIZE_STR);
	}
}

vrGroup::vrGroup(const vrGroup& v) : vrGroupingNode(v)
{
	GetRuntimeClass()->Reference();
}

vrGroup::~vrGroup(void)
{
	GetRuntimeClass()->Dereference();
}

vrGroup& vrGroup::operator=(const vrGroup& v)
{
	vrGroupingNode::operator=(v);


	return *this;
}

SFNode vrGroup::Clone(void) const
{
	return new vrGroup(*this);
}

//----------------------------------------------------------------------

//----------------------------------------------------------------------
SFBool vrGroup::IsDefault(const SFString& fieldName, vrField *field) const
{
	return vrGroupingNode::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrGroup::SetFieldValue(const SFString& fieldName, void *val)
{
	return vrGroupingNode::SetFieldValue(fieldName, val);
}
