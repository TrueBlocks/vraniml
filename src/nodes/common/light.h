#ifndef __LIGHT_H3D
#define __LIGHT_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrLight

	This class corresponds to the Light node in VRML.  
	<A href="../spec/part1/nodesRef.html#Light">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Light node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Light">link</a>.</ul>

NOTES
	<ul>
	<li>All node classes share certain aspects which are described <a href="../nodespec.htm">here</a>.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrLight : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Non-VRML field lightID.
	//
	// [default] -1
	//
	SFInt32             	m_LightID;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'on' exposedField.
	//
	// [default] TRUE 
	//
	SFBool              	m_On;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'color' exposedField.
	//
	// [default] vrWhite
	//
	SFColor             	m_Color;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'intensity' exposedField.
	//
	// [default] 1.0
	//
	SFFloat             	m_Intensity;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'ambientIntensity' exposedField.
	//
	// [default] 0.0
	//
	SFFloat             	m_AmbientIntensity;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'attenuation' exposedField.
	//
	// [default] xAxis
	//
	SFVec3f             	m_Attenuation;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrLight(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrLight(const vrLight& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrLight(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrLight& operator=(const vrLight& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_LightID member.
	//
	// [in] lightid: The lightid value.
	//
	void SetLightID(SFInt32 lightid);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_LightID member.
	//
	SFInt32 GetLightID(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_On member.
	//
	// [in] on: The on value.
	//
	void SetOn(SFBool on);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Color member.
	//
	// [in] color: The color value.
	//
	void SetColor(const SFColor& color);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Intensity member.
	//
	// [in] intensity: The intensity value.
	//
	void SetIntensity(SFFloat intensity);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_AmbientIntensity member.
	//
	// [in] ambientintensity: The ambientintensity value.
	//
	void SetAmbientIntensity(SFFloat ambientintensity);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Attenuation member.
	//
	// [in] attenuation: The attenuation value.
	//
	void SetAttenuation(const SFVec3f& attenuation);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_On member.
	//
	SFBool GetOn(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Color member.
	//
	SFColor GetColor(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Intensity member.
	//
	SFFloat GetIntensity(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_AmbientIntensity member.
	//
	SFFloat GetAmbientIntensity(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Attenuation member.
	//
	SFVec3f GetAttenuation(void) const;


	//<nodoc>------------------------------------------------------------
	// <dd>Set the value of a field given the field's name and a value.
	// <dd>Note: Error checking is done on 'fieldName' but cannot be done on 'val',
	// <dd>      so make sure you send the correct type of data to this method.
	//
	// [in] fieldName: The name of the field to set (as specified in the VRML97 specification).
	// [in] val: Void pointer to a field of the type corresponding to fieldName.
	//
	virtual SFBool SetFieldValue(const SFString& fieldName, void *val);


	//<doc>------------------------------------------------------------
	// <dd>Respond to a traversal by an arbitrary traverser.  Note: Normally, nodes just call t->Traverse(this)
	// <dd>to have the traverser handle the traversal.  you may override this method in your derived class to
	// <dd>handle traversals of node types.
	//
	// [in] trav: The vrTraverser requesting the traversal.
	//
	virtual void Traverse(vrTraverser *trav) const;

	//<doc>------------------------------------------------------------
	// <dd>Receive an event during an event cascade or directly from caller.
	//
	// [in] event: The vrEvent to be processed.
	//
	virtual void ReceiveEventIn(vrEvent *event);

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if the node (or a particular field) is in it's default state.
	//
	// [in] fieldName: The field to check for default value.  NULL implies check all fields of this node.
	// [out] field: If non-NULL the value of the field will be returned in field.
	//
	virtual SFBool IsDefault(const SFString& fieldName=nullString, vrField *field=NULL) const;

	//<doc>------------------------------------------------------------
	// <dd>Declare that this node may be runtime typed. [ DECLARE_NODE ]
	//
	DECLARE_NODE(vrLight);

	//------------------------------------------------------------
	// hand coded functions
	SFInt32 AllocateLightID(void) const;
	void FreeLightID(SFInt32 id);
	static SFInt32 lightIDs[8];
	SFColor GetAmbientColor(void) const;
	SFColor GetDiffuseColor(void) const;
	SFColor GetSpecularColor(void) const;
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrLight::SetLightID(SFInt32 lightid)
{
	FreeLightID(m_LightID);
	m_LightID = lightid;
}

inline SFInt32 vrLight::GetLightID(void) const
{
	return m_LightID;
}

// exposedField sets and gets inlines
inline void vrLight::SetOn(SFBool on)
{
	m_On = on;
}

inline void vrLight::SetColor(const SFColor& color)
{
	m_Color = color;
}

inline void vrLight::SetIntensity(SFFloat intensity)
{
	m_Intensity = intensity;
}

inline void vrLight::SetAmbientIntensity(SFFloat ambientintensity)
{
	m_AmbientIntensity = ambientintensity;
}

inline void vrLight::SetAttenuation(const SFVec3f& attenuation)
{
	m_Attenuation = attenuation;
}

inline SFBool vrLight::GetOn(void) const
{
	return m_On;
}

inline SFColor vrLight::GetColor(void) const
{
	return m_Color;
}

inline SFFloat vrLight::GetIntensity(void) const
{
	return m_Intensity;
}

inline SFFloat vrLight::GetAmbientIntensity(void) const
{
	return m_AmbientIntensity;
}

inline SFVec3f vrLight::GetAttenuation(void) const
{
	return m_Attenuation;
}

inline void vrLight::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

