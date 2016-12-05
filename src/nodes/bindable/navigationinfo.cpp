//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "NavigationInfo.h"
#include "Browser\Browser.h"

IMPLEMENT_NODE(vrNavigationInfo, vrBindable);

//----------------------------------------------------------------------
vrNavigationInfo::vrNavigationInfo(void) : vrBindable()
{
	m_AvatarSize.AddValue(0.25);
	m_AvatarSize.AddValue(1.6);
	m_AvatarSize.AddValue(0.75 );
	m_Headlight          = TRUE;
	m_Speed              = 1.0 ;
	m_Type.AddValue("WALK");
	m_VisibilityLimit    = 0.0;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(MFFLOAT, VRML_AVATARSIZE_STR);
		AddExposedField(SFBOOL, VRML_HEADLIGHT_STR);
		AddExposedField(SFFLOAT, VRML_SPEED_STR);
		AddExposedField(MFSTRING, VRML_TYPE_STR);
		AddExposedField(SFFLOAT, VRML_VISIBILITYLIMIT_STR);
		AddEventIn(SFBOOL, VRML_SET_BIND_STR);
		AddEventOut(SFBOOL, VRML_ISBOUND_STR);
	}
}

vrNavigationInfo::vrNavigationInfo(const vrNavigationInfo& v) : vrBindable(v)
{
	m_AvatarSize         = v.m_AvatarSize;
	m_Headlight          = v.m_Headlight;
	m_Speed              = v.m_Speed;
	m_Type               = v.m_Type;
	m_VisibilityLimit    = v.m_VisibilityLimit;
	GetRuntimeClass()->Reference();
}

vrNavigationInfo::~vrNavigationInfo(void)
{
	if (m_BoundTo)
	  m_BoundTo->Bind(this, FALSE);
	m_BoundTo = NULL;
	m_AvatarSize.Clear();
	m_Type.Clear();
	GetRuntimeClass()->Dereference();
}

vrNavigationInfo& vrNavigationInfo::operator=(const vrNavigationInfo& v)
{
	vrBindable::operator=(v);

	m_AvatarSize.Clear();
	m_AvatarSize         = v.m_AvatarSize;
	m_Headlight          = v.m_Headlight;
	m_Speed              = v.m_Speed;
	m_Type.Clear();
	m_Type               = v.m_Type;
	m_VisibilityLimit    = v.m_VisibilityLimit;

	return *this;
}

SFNode vrNavigationInfo::Clone(void) const
{
	return new vrNavigationInfo(*this);
}

//----------------------------------------------------------------------
void vrNavigationInfo::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_AVATARSIZE_STR)
		{
			SetAvatarSize(*((MFFloat *)ev->m_Value));
			SendEventOut(VRML_AVATARSIZE_STR, &m_AvatarSize);
		}
	else if (ev->m_FieldID == VRML_HEADLIGHT_STR)
		{
			SetHeadlight(*((SFBool *)ev->m_Value));
			SendEventOut(VRML_HEADLIGHT_STR, &m_Headlight);
		}
	else if (ev->m_FieldID == VRML_SPEED_STR)
		{
			SetSpeed(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_SPEED_STR, &m_Speed);
		}
	else if (ev->m_FieldID == VRML_TYPE_STR)
		{
			SetType(*((MFString *)ev->m_Value));
			SendEventOut(VRML_TYPE_STR, &m_Type);
		}
	else if (ev->m_FieldID == VRML_VISIBILITYLIMIT_STR)
		{
			SetVisibilityLimit(*((SFFloat *)ev->m_Value));
			SendEventOut(VRML_VISIBILITYLIMIT_STR, &m_VisibilityLimit);
		}
	else
		{
			vrBindable::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrNavigationInfo::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		if (fieldName == "avatarSize")
		{
			if (field)
				SetValEx(field, (void*)&m_AvatarSize);
			if (IsIsMapped(fieldName))
				return TRUE;
			if (3 != m_AvatarSize.GetCount()) return FALSE;
			if ((SFFloat)0.25 != GetAvatarSize(0)) return FALSE;
			if ((SFFloat)1.6 != GetAvatarSize(1)) return FALSE;
			if ((SFFloat)0.75  != GetAvatarSize(2)) return FALSE;
			return TRUE;
		}

		CHECK_FIELD("headlight", m_Headlight, TRUE);
		//if (fieldName == "headlight")
		//	return (TRUE == m_Headlight);

		CHECK_FIELD("speed", m_Speed, (SFFloat)1.0);
		//if (fieldName == "speed")
		//	return ((SFFloat)1.0  == m_Speed);

		if (fieldName == "type")
		{
			if (field)
				SetValEx(field, (void*)&m_Type);
			if (IsIsMapped(fieldName))
				return TRUE;
			return (!strcmp("WALK" , GetType(0))); // default: "WALK" 
		}

		CHECK_FIELD("visibilityLimit", m_VisibilityLimit, (SFFloat)0.0);
		//if (fieldName == "visibilityLimit")
		//	return ((SFFloat)0.0 == m_VisibilityLimit);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("avatarSize")) return FALSE;
		if (!IsDefault("headlight")) return FALSE;
		if (!IsDefault("speed")) return FALSE;
		if (!IsDefault("type")) return FALSE;
		if (!IsDefault("visibilityLimit")) return FALSE;
	}

	return vrBindable::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrNavigationInfo::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "avatarSize")
	{
		SetAvatarSize(*((MFFloat *)val));
		return TRUE;
	} else if (fieldName == "headlight")
	{
		SetHeadlight(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "speed")
	{
		SetSpeed(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "type")
	{
		SetType(*((MFString *)val));
		return TRUE;
	} else if (fieldName == "visibilityLimit")
	{
		SetVisibilityLimit(*((SFFloat *)val));
		return TRUE;
	}
	
	return vrBindable::SetFieldValue(fieldName, val);
}

void vrNavigationInfo::CompleteNode(vrNode *top)
{
	// Let parent complete this node if needed
	vrBindable::CompleteNode(top);

	if (!top || !top->IsKindOf(GETRUNTIME_CLASS(vrBrowser)))
		return;

	vrBrowser *b = (vrBrowser*)top;
	// Only bind the first encountered node
	if (!b->GetNavigationInfo())
		b->Bind(this, TRUE);
}
