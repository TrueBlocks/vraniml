//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Extrusion.h"

IMPLEMENT_NODE(vrExtrusion, vrGeometryNode);

//----------------------------------------------------------------------
vrExtrusion::vrExtrusion(void) : vrGeometryNode()
{
	m_BeginCap           = TRUE;
	m_CrossSection.AddValue(SFVec2f(1,1));
	m_CrossSection.AddValue(SFVec2f(1,-1));
	m_CrossSection.AddValue(SFVec2f(-1,-1));
	m_CrossSection.AddValue(SFVec2f(-1,1));
	m_CrossSection.AddValue(SFVec2f(1,1) );
	m_EndCap             = TRUE;
	m_Orientation.AddValue(defRotation);
	m_Scale.AddValue(xy1);
	m_Spine.AddValue(origin);
	m_Spine.AddValue(yAxis );

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(MFVEC2F, VRML_CROSSSECTION_STR);
		AddExposedField(MFROTATION, VRML_ORIENTATION_STR);
		AddExposedField(MFVEC2F, VRML_SCALE_STR);
		AddExposedField(MFVEC3F, VRML_SPINE_STR);
		// undefined events -- to invalidate geometry nodes
		AddEventIn(SFBOOL, VRML_INVALIDATE_STR);

		AddField(SFBOOL, VRML_BEGINCAP_STR);
		AddField(SFBOOL, VRML_CONVEX_STR);
		AddField(SFBOOL, VRML_ENDCAP_STR);
		AddField(SFBOOL, VRML_CCW_STR);
		AddField(SFFLOAT, VRML_CREASEANGLE_STR);
		AddField(SFBOOL, VRML_SOLID_STR);
	}
}

vrExtrusion::vrExtrusion(const vrExtrusion& v) : vrGeometryNode(v)
{
	m_BeginCap           = v.m_BeginCap;
	m_CrossSection       = v.m_CrossSection;
	m_EndCap             = v.m_EndCap;
	m_Orientation        = v.m_Orientation;
	m_Scale              = v.m_Scale;
	m_Spine              = v.m_Spine;
	GetRuntimeClass()->Reference();
}

vrExtrusion::~vrExtrusion(void)
{
	m_CrossSection.Clear();
	m_Orientation.Clear();
	m_Scale.Clear();
	m_Spine.Clear();

	GetRuntimeClass()->Dereference();
}

vrExtrusion& vrExtrusion::operator=(const vrExtrusion& v)
{
	vrGeometryNode::operator=(v);

	m_BeginCap           = v.m_BeginCap;
	m_CrossSection.Clear();
	m_CrossSection       = v.m_CrossSection;
	m_EndCap             = v.m_EndCap;
	m_Orientation.Clear();
	m_Orientation        = v.m_Orientation;
	m_Scale.Clear();
	m_Scale              = v.m_Scale;
	m_Spine.Clear();
	m_Spine              = v.m_Spine;

	return *this;
}

SFNode vrExtrusion::Clone(void) const
{
	return new vrExtrusion(*this);
}

//----------------------------------------------------------------------
void vrExtrusion::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_CROSSSECTION_STR)
		{
			SetCrossSection(*((MFVec2f *)ev->m_Value));
			SendEventOut(VRML_CROSSSECTION_STR, &m_CrossSection);
			SetGeom(NULL);
		}
	else if (ev->m_FieldID == VRML_ORIENTATION_STR)
		{
			SetOrientation(*((MFRotation *)ev->m_Value));
			SendEventOut(VRML_ORIENTATION_STR, &m_Orientation);
			SetGeom(NULL);
		}
	else if (ev->m_FieldID == VRML_SCALE_STR)
		{
			SetScale(*((MFVec2f *)ev->m_Value));
			SendEventOut(VRML_SCALE_STR, &m_Scale);
			SetGeom(NULL);
		}
	else if (ev->m_FieldID == VRML_SPINE_STR)
		{
			SetSpine(*((MFVec3f *)ev->m_Value));
			SendEventOut(VRML_SPINE_STR, &m_Spine);
			SetGeom(NULL);
		}
	else
		{
			vrGeometryNode::ReceiveEventIn(ev);
		}
}

//----------------------------------------------------------------------
SFBool vrExtrusion::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("beginCap", m_BeginCap, TRUE);
		//if (fieldName == "beginCap")
		//	return (TRUE == m_BeginCap);

		if (fieldName == "crossSection")
		{
			if (field)
				SetVal(field, (void*)&m_CrossSection);
			if (IsIsMapped(fieldName))
				return TRUE;
			if (5 != m_CrossSection.GetCount()) return FALSE;
			if (SFVec2f(1,1)   != GetCrossSection(0)) return FALSE;
			if (SFVec2f(1,-1)  != GetCrossSection(1)) return FALSE;
			if (SFVec2f(-1,-1) != GetCrossSection(2)) return FALSE;
			if (SFVec2f(-1,1)  != GetCrossSection(3)) return FALSE;
			if (SFVec2f(1,1)   != GetCrossSection(4)) return FALSE;
			return TRUE;
		}


		if (fieldName == "endCap")
			return (TRUE == m_EndCap);

		if (fieldName == "orientation")
		{
			if (1 != GetNOrientations()) return FALSE;
			if (defRotation != GetOrientation(0)) return FALSE;
			return TRUE;
		}

		if (fieldName == "scale")
		{
			if (1 != GetNScales()) return FALSE;
			if (xy1 != GetScale(0)) return FALSE; // default: xy1
			return TRUE;
		}

		if (fieldName == "spine")
		{
			if (2 != m_Spine.GetCount()) return FALSE;
			if (origin != GetSpine(0)) return FALSE;
			if (yAxis  != GetSpine(1)) return FALSE;
			return TRUE;
		}

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("beginCap")) return FALSE;
		if (!IsDefault("crossSection")) return FALSE;
		if (!IsDefault("endCap")) return FALSE;
		if (!IsDefault("orientation")) return FALSE;
		if (!IsDefault("scale")) return FALSE;
		if (!IsDefault("spine")) return FALSE;
	}

	return vrGeometryNode::IsDefault(fieldName, field);
}

//----------------------------------------------------------------------
SFBool vrExtrusion::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "beginCap")
	{
		SetBeginCap(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "crossSection")
	{
		SetCrossSection(*((MFVec2f *)val));
		return TRUE;
	} else if (fieldName == "endCap")
	{
		SetEndCap(*((SFBool *)val));
		return TRUE;
	} else if (fieldName == "orientation")
	{
		SetOrientation(*((MFRotation *)val));
		return TRUE;
	} else if (fieldName == "scale")
	{
		SetScale(*((MFVec2f *)val));
		return TRUE;
	} else if (fieldName == "spine")
	{
		SetSpine(*((MFVec3f *)val));
		return TRUE;
	}

	return vrGeometryNode::SetFieldValue(fieldName, val);
}

//----------------------------------------------------------------------
#include "Extrusion.cxx"
