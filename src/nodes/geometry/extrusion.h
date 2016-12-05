#ifndef __EXTRUSION_H3D
#define __EXTRUSION_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "GeometryNode.h"

/*----------------------------------------------------------------------
CLASS
	vrExtrusion

	This class corresponds to the Extrusion node in VRML.  
	<A href="../spec/part1/nodesRef.html#Extrusion">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the Extrusion node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#Extrusion">link</a>.</ul>

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
class LIBInterface vrExtrusion : public vrGeometryNode
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'beginCap' field.
	//
	// [default] TRUE
	//
	SFBool              	m_BeginCap;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'endCap' field.
	//
	// [default] TRUE
	//
	SFBool              	m_EndCap;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'crossSection' exposedField.
	//
	// [default] SFVec2f(1,1)
	//
	MFVec2f             	m_CrossSection;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'orientation' exposedField.
	//
	// [default] defRotation
	//
	MFRotation          	m_Orientation;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'scale' exposedField.
	//
	// [default] xy1
	//
	MFVec2f             	m_Scale;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'spine' exposedField.
	//
	// [default] origin
	//
	MFVec3f             	m_Spine;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrExtrusion(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrExtrusion(const vrExtrusion& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrExtrusion(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrExtrusion& operator=(const vrExtrusion& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_BeginCap member.
	//
	// [in] begincap: The begincap value.
	//
	void SetBeginCap(SFBool begincap);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_EndCap member.
	//
	// [in] endcap: The endcap value.
	//
	void SetEndCap(SFBool endcap);

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_BeginCap member.
	//
	SFBool GetBeginCap(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_EndCap member.
	//
	SFBool GetEndCap(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_CrossSection array (grow if needed).
	//
	// [in] crosssection: The value to add to the m_CrossSection array.
	//
	void AddCrossSection(const SFVec2f& crosssection);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_CrossSection member (copies values).
	//
	// [in] crosssection: The m_CrossSection array.
	//
	void SetCrossSection(const MFVec2f& crosssection);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Orientation array (grow if needed).
	//
	// [in] orientation: The value to add to the m_Orientation array.
	//
	void AddOrientation(const SFRotation& orientation);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Orientation member (copies values).
	//
	// [in] orientation: The m_Orientation array.
	//
	void SetOrientation(const MFRotation& orientation);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Scale array (grow if needed).
	//
	// [in] scale: The value to add to the m_Scale array.
	//
	void AddScale(const SFVec2f& scale);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Scale member (copies values).
	//
	// [in] scale: The m_Scale array.
	//
	void SetScale(const MFVec2f& scale);

	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Spine array (grow if needed).
	//
	// [in] spine: The value to add to the m_Spine array.
	//
	void AddSpine(const SFVec3f& spine);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Spine member (copies values).
	//
	// [in] spine: The m_Spine array.
	//
	void SetSpine(const MFVec3f& spine);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_CrossSection member.
	//
	SFInt32 GetNCrossSections(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_CrossSection member.
	//
	// [in] n: The index into the array.
	//
	SFVec2f GetCrossSection(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_CrossSection member.
	//
	const MFVec2f& GetCrossSectionArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Orientation member.
	//
	SFInt32 GetNOrientations(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Orientation member.
	//
	// [in] n: The index into the array.
	//
	SFRotation GetOrientation(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Orientation member.
	//
	const MFRotation& GetOrientationArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Scale member.
	//
	SFInt32 GetNScales(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Scale member.
	//
	// [in] n: The index into the array.
	//
	SFVec2f GetScale(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Scale member.
	//
	const MFVec2f& GetScaleArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Spine member.
	//
	SFInt32 GetNSpines(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Spine member.
	//
	// [in] n: The index into the array.
	//
	SFVec3f GetSpine(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Spine member.
	//
	const MFVec3f& GetSpineArray(void) const;


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
	DECLARE_NODE(vrExtrusion);

	//------------------------------------------------------------
	// hand coded functions
	virtual void BuildMesh(void);
	virtual void BuildColors(void);
	virtual void BuildNormals(void);
	virtual void BuildTexCoords(void);
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrExtrusion::SetBeginCap(SFBool begincap)
{
	m_BeginCap = begincap;
}

inline void vrExtrusion::SetEndCap(SFBool endcap)
{
	m_EndCap = endcap;
}

inline SFBool vrExtrusion::GetBeginCap(void) const
{
	return m_BeginCap;
}

inline SFBool vrExtrusion::GetEndCap(void) const
{
	return m_EndCap;
}

// exposedField sets and gets inlines
inline void vrExtrusion::AddCrossSection(const SFVec2f& crosssection)
{
	m_CrossSection.AddValue(crosssection);
}

inline void vrExtrusion::SetCrossSection(const MFVec2f& crosssection)
{
	m_CrossSection.Clear();
	m_CrossSection = crosssection;
}

inline void vrExtrusion::AddOrientation(const SFRotation& orientation)
{
	m_Orientation.AddValue(orientation);
}

inline void vrExtrusion::SetOrientation(const MFRotation& orientation)
{
	m_Orientation.Clear();
	m_Orientation = orientation;
}

inline void vrExtrusion::AddScale(const SFVec2f& scale)
{
	m_Scale.AddValue(scale);
}

inline void vrExtrusion::SetScale(const MFVec2f& scale)
{
	m_Scale.Clear();
	m_Scale = scale;
}

inline void vrExtrusion::AddSpine(const SFVec3f& spine)
{
	m_Spine.AddValue(spine);
}

inline void vrExtrusion::SetSpine(const MFVec3f& spine)
{
	m_Spine.Clear();
	m_Spine = spine;
}

inline SFInt32 vrExtrusion::GetNCrossSections(void) const
{
	return m_CrossSection.GetCount();
}

inline SFVec2f vrExtrusion::GetCrossSection(SFInt32 n) const
{
	return m_CrossSection[n];
}

inline const MFVec2f& vrExtrusion::GetCrossSectionArray(void) const
{
	return m_CrossSection;
}

inline SFInt32 vrExtrusion::GetNOrientations(void) const
{
	return m_Orientation.GetCount();
}

inline SFRotation vrExtrusion::GetOrientation(SFInt32 n) const
{
	return m_Orientation[n];
}

inline const MFRotation& vrExtrusion::GetOrientationArray(void) const
{
	return m_Orientation;
}

inline SFInt32 vrExtrusion::GetNScales(void) const
{
	return m_Scale.GetCount();
}

inline SFVec2f vrExtrusion::GetScale(SFInt32 n) const
{
	return m_Scale[n];
}

inline const MFVec2f& vrExtrusion::GetScaleArray(void) const
{
	return m_Scale;
}

inline SFInt32 vrExtrusion::GetNSpines(void) const
{
	return m_Spine.GetCount();
}

inline SFVec3f vrExtrusion::GetSpine(SFInt32 n) const
{
	return m_Spine[n];
}

inline const MFVec3f& vrExtrusion::GetSpineArray(void) const
{
	return m_Spine;
}

inline void vrExtrusion::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

