#ifndef __MATERIAL_H3D
#define __MATERIAL_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrMaterial

	This class corresponds to the Material node in VRML.  
	<A href="../spec/part1/nodesRef.html#Material">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Material node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Material">link</a>.</ul>

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
class LIBInterface vrMaterial : public vrNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'ambientIntensity' exposedField.
	//
	// [default] 0.2
	//
	SFFloat             	m_AmbientIntensity;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'diffuseColor' exposedField.
	//
	// [default] vrWhite*0.8
	//
	SFColor             	m_DiffuseColor;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'emissiveColor' exposedField.
	//
	// [default] vrBlack
	//
	SFColor             	m_EmissiveColor;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'shininess' exposedField.
	//
	// [default] 0.2
	//
	SFFloat             	m_Shininess;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'specularColor' exposedField.
	//
	// [default] vrBlack
	//
	SFColor             	m_SpecularColor;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'transparency' exposedField.
	//
	// [default] 0.0
	//
	SFFloat             	m_Transparency;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrMaterial(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrMaterial(const vrMaterial& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrMaterial(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrMaterial& operator=(const vrMaterial& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_AmbientIntensity member.
	//
	// [in] ambientintensity: The ambientintensity value.
	//
	void SetAmbientIntensity(SFFloat ambientintensity);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_DiffuseColor member.
	//
	// [in] diffusecolor: The diffusecolor value.
	//
	void SetDiffuseColor(const SFColor& diffusecolor);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_EmissiveColor member.
	//
	// [in] emissivecolor: The emissivecolor value.
	//
	void SetEmissiveColor(const SFColor& emissivecolor);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Shininess member.
	//
	// [in] shininess: The shininess value.
	//
	void SetShininess(SFFloat shininess);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_SpecularColor member.
	//
	// [in] specularcolor: The specularcolor value.
	//
	void SetSpecularColor(const SFColor& specularcolor);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_Transparency member.
	//
	// [in] transparency: The transparency value.
	//
	void SetTransparency(SFFloat transparency);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_AmbientIntensity member.
	//
	SFFloat GetAmbientIntensity(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_DiffuseColor member.
	//
	SFColor GetDiffuseColor(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_EmissiveColor member.
	//
	SFColor GetEmissiveColor(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Shininess member.
	//
	SFFloat GetShininess(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_SpecularColor member.
	//
	SFColor GetSpecularColor(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_Transparency member.
	//
	SFFloat GetTransparency(void) const;


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
	// <dd>Declare that this node may be runtime typed and dynamically created. [ DECLARE_NODE ]
	//
	DECLARE_NODE(vrMaterial);

	//------------------------------------------------------------
	// hand coded functions
	SFColor GetAmbientColor(void) const;
};

//----------------------------------------------------------------------
// exposedField sets and gets inlines
inline void vrMaterial::SetAmbientIntensity(SFFloat ambientintensity)
{
	m_AmbientIntensity = ambientintensity;
}

inline void vrMaterial::SetDiffuseColor(const SFColor& diffusecolor)
{
	m_DiffuseColor = diffusecolor;
}

inline void vrMaterial::SetEmissiveColor(const SFColor& emissivecolor)
{
	m_EmissiveColor = emissivecolor;
}

inline void vrMaterial::SetShininess(SFFloat shininess)
{
	m_Shininess = shininess;
}

inline void vrMaterial::SetSpecularColor(const SFColor& specularcolor)
{
	m_SpecularColor = specularcolor;
}

inline void vrMaterial::SetTransparency(SFFloat transparency)
{
	m_Transparency = transparency;
}

inline SFFloat vrMaterial::GetAmbientIntensity(void) const
{
	return m_AmbientIntensity;
}

inline SFColor vrMaterial::GetDiffuseColor(void) const
{
	return m_DiffuseColor;
}

inline SFColor vrMaterial::GetEmissiveColor(void) const
{
	return m_EmissiveColor;
}

inline SFFloat vrMaterial::GetShininess(void) const
{
	return m_Shininess;
}

inline SFColor vrMaterial::GetSpecularColor(void) const
{
	return m_SpecularColor;
}

inline SFFloat vrMaterial::GetTransparency(void) const
{
	return m_Transparency;
}

inline void vrMaterial::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

