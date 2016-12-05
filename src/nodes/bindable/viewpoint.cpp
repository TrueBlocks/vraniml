//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Viewpoint.h"
#include "Browser\Browser.h"

IMPLEMENT_NODE(vrViewpoint, vrBindable);

//----------------------------------------------------------------------
vrViewpoint::vrViewpoint(void) : vrBindable()
{
	m_FieldOfView        = 0.785398 ;
	m_Jump               = TRUE;
	m_Orientation        = defRotation;
	m_Position           = zAxis*10;
//	m_Description        = NULL;
	m_BindTime           = 0.0;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFFLOAT, VRML_FIELDOFVIEW_STR);
		AddExposedField(SFBOOL, VRML_JUMP_STR);
		AddExposedField(SFROTATION, VRML_ORIENTATION_STR);
		AddExposedField(SFVEC3F, VRML_POSITION_STR);
		AddEventOut(SFTIME, VRML_BINDTIME_STR);
		AddEventIn(SFBOOL, VRML_SET_BIND_STR);
		AddEventOut(SFBOOL, VRML_ISBOUND_STR);
	  AddField(SFSTRING, VRML_DESCRIPTION_STR);
	}
}

vrViewpoint::vrViewpoint(const vrViewpoint& v) : vrBindable(v)
{
	m_FieldOfView        = v.m_FieldOfView;
	m_Jump               = v.m_Jump;
	m_Orientation        = v.m_Orientation;
	m_Position           = v.m_Position;
	m_Description        = v.m_Description;
	m_BindTime           = v.m_BindTime;
	GetRuntimeClass()->Reference();
}

vrViewpoint::~vrViewpoint(void)
{
	if (m_BoundTo)
	  m_BoundTo->Bind(this, FALSE);
	m_BoundTo = NULL;
	GetRuntimeClass()->Dereference();
}

vrViewpoint& vrViewpoint::operator=(const vrViewpoint& v)
{
	vrBindable::operator=(v);

	m_FieldOfView        = v.m_FieldOfView;
	m_Jump               = v.m_Jump;
	m_Orientation        = v.m_Orientation;
	m_Position           = v.m_Position;
	m_Description        = v.m_Description;
	m_BindTime           = v.m_BindTime;

	return *this;
}

SFNode vrViewpoint::Clone(void) const
{
	return new vrViewpoint(*this);
}

//----------------------------------------------------------------------
void vrViewpoint::SetDescription(const SFString& description)
{
	m_Description = description;
}

void vrViewpoint::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_FIELDOFVIEW_STR)
		{
			SetFieldOfView(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_FIELDOFVIEW_STR, &m_FieldOfView);
		}
	else if (ev->m_FieldID == VRML_JUMP_STR)
		{
			SetJump(*((SFBool *)ev->m_Value));
			SendEventOut(VRML_JUMP_STR, &m_Jump);
		}
	else if (ev->m_FieldID == VRML_ORIENTATION_STR)
		{
			SetOrientation(*((SFRotation *)ev->m_Value));
			SendEventOut(VRML_ORIENTATION_STR, &m_Orientation);
		}
	else if (ev->m_FieldID == VRML_POSITION_STR)
		{
			SetPosition(*((SFVec3f *)ev->m_Value));
			SendEventOut(VRML_POSITION_STR, &m_Position);
		}
	else
		{
			vrBindable::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrViewpoint::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("fieldOfView", m_FieldOfView, (SFFloat)0.785398);
		//if (fieldName == "fieldOfView")
		//	return ((SFFloat)0.785398  == m_FieldOfView);

		CHECK_FIELD("jump", m_Jump, TRUE);
		//if (fieldName == "jump")
		//	return (TRUE == m_Jump);

		CHECK_FIELD("orientation", m_Orientation, defRotation);
		//if (fieldName == "orientation")
		//	return (defRotation == m_Orientation);

		CHECK_FIELD("position", m_Position, zAxis*10);
		//if (fieldName == "position")
		//	return (zAxis*10 == m_Position);

		CHECK_STRING_FIELD("description", m_Description);
		//if (fieldName == "description")
		//	return m_Description.Empty();

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("fieldOfView")) return FALSE;
		if (!IsDefault("jump")) return FALSE;
		if (!IsDefault("orientation")) return FALSE;
		if (!IsDefault("position")) return FALSE;
		if (!IsDefault("description")) return FALSE;
	}

	return vrBindable::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrViewpoint::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "fieldOfView")
	{
		SetFieldOfView(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "jump")
	{
		SetJump(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "orientation")
	{
		SetOrientation(*((SFRotation *)val));
		return TRUE;
	} else if (fieldName == "position")
	{
		SetPosition(*((SFVec3f *)val));
		return TRUE;
	} else if (fieldName == "description")
	{
		SetDescription(((char *)val));
		return TRUE;
	}
	
	return vrBindable::SetFieldValue(fieldName, val);
}

void vrViewpoint::CompleteNode(vrNode *top)
{
	// Let parent complete this node if needed
	vrBindable::CompleteNode(top);

	if (!top || !top->IsKindOf(GETRUNTIME_CLASS(vrBrowser)))
		return;

	vrBrowser *b = (vrBrowser*)top;
	// Only bind the first encountered node
	if (!b->GetViewpoint())
		b->Bind(this, TRUE);
}
