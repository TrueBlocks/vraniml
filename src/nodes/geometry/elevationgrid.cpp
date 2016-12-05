//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "ElevationGrid.h"

IMPLEMENT_NODE(vrElevationGrid, vrDataSet);

//----------------------------------------------------------------------
vrElevationGrid::vrElevationGrid(void) : vrDataSet()
{
	//m_SetHeight          = array;
	//m_Height             = array;
	m_XDimension         = 0;
	m_XSpacing           = 0.0;
	m_ZDimension         = 0;
	m_ZSpacing           = 0.0;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddEventIn(MFFLOAT, VRML_SET_HEIGHT_STR);
		AddExposedField(SFNODE, VRML_COLOR_STR);
		AddExposedField(SFNODE, VRML_NORMAL_STR);
		AddExposedField(SFNODE, VRML_TEXCOORD_STR);
		AddField(SFBOOL, VRML_CCW_STR);
		AddField(SFBOOL, VRML_COLORPERVERTEX_STR);
		AddField(SFFLOAT, VRML_CREASEANGLE_STR);
		AddField(MFFLOAT, VRML_HEIGHT_STR);
		AddField(SFBOOL, VRML_NORMALPERVERTEX_STR);
		AddField(SFBOOL, VRML_SOLID_STR);
		AddField(SFINT32, VRML_XDIMENSION_STR);
		AddField(SFFLOAT, VRML_XSPACING_STR);
		AddField(SFINT32, VRML_ZDIMENSION_STR);
		AddField(SFFLOAT, VRML_ZSPACING_STR);
	}
}

vrElevationGrid::vrElevationGrid(const vrElevationGrid& v) : vrDataSet(v)
{
	m_SetHeight          = v.m_SetHeight;
	m_Height             = v.m_Height;
	m_XDimension         = v.m_XDimension;
	m_XSpacing           = v.m_XSpacing;
	m_ZDimension         = v.m_ZDimension;
	m_ZSpacing           = v.m_ZSpacing;
	GetRuntimeClass()->Reference();
}

vrElevationGrid::~vrElevationGrid(void)
{
	m_SetHeight.Clear();
	m_Height.Clear();
	GetRuntimeClass()->Dereference();
}

vrElevationGrid& vrElevationGrid::operator=(const vrElevationGrid& v)
{
	vrDataSet::operator=(v);

	m_SetHeight.Clear();
	m_SetHeight          = v.m_SetHeight;
	m_Height.Clear();
	m_Height             = v.m_Height;
	m_XDimension         = v.m_XDimension;
	m_XSpacing           = v.m_XSpacing;
	m_ZDimension         = v.m_ZDimension;
	m_ZSpacing           = v.m_ZSpacing;

	return *this;
}

SFNode vrElevationGrid::Clone(void) const
{
	return new vrElevationGrid(*this);
}

//----------------------------------------------------------------------
void vrElevationGrid::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_SET_HEIGHT_STR)
		{
			SetHeight(*((MFFloat *)ev->m_Value));
			// no event out
		}
	else
		{
			vrDataSet::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrElevationGrid::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_ARRAY_FIELD("height", GetNHeights(), m_Height, 0);
		//if (fieldName == "height")
		//	return (0 == GetNHeights()); // default: []

		CHECK_FIELD("xDimension", m_XDimension, 0);
		//if (fieldName == "xDimension")
		//	return (0 == m_XDimension);

		CHECK_FIELD("xSpacing", m_XSpacing, (SFFloat)0.0);
		//if (fieldName == "xSpacing")
		//	return ((SFFloat)0.0 == m_XSpacing);

		CHECK_FIELD("zDimension", m_ZDimension, 0);
		//if (fieldName == "zDimension")
		//	return (0 == m_ZDimension);

		CHECK_FIELD("zSpacing", m_ZSpacing, (SFFloat)0.0);
		//if (fieldName == "zSpacing")
		//	return ((SFFloat)0.0 == m_ZSpacing);

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("height")) return FALSE;
		if (!IsDefault("xDimension")) return FALSE;
		if (!IsDefault("xSpacing")) return FALSE;
		if (!IsDefault("zDimension")) return FALSE;
		if (!IsDefault("zSpacing")) return FALSE;
	}

	return vrDataSet::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrElevationGrid::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "height")
	{
		SetHeight(*((MFFloat *)val));
		return TRUE;
	} else if (fieldName == "xDimension")
	{
		SetXDimension(*((SFInt32 *)val));
		return TRUE;
	} else if (fieldName == "xSpacing")
	{
		SetXSpacing(*((SFFloat *)val));
		return TRUE;
	} else if (fieldName == "zDimension")
	{
		SetZDimension(*((SFInt32 *)val));
		return TRUE;
	} else if (fieldName == "zSpacing")
	{
		SetZSpacing(*((SFFloat *)val));
		return TRUE;
	}

	return vrDataSet::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "ElevationGrid.cxx"
