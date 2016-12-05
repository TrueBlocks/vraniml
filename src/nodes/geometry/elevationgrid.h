#ifndef __ELEVATIONGRID_H3D
#define __ELEVATIONGRID_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "DataSet.h"

/*----------------------------------------------------------------------
CLASS
	vrElevationGrid

	This class corresponds to the ElevationGrid node in VRML.  
	<A href="../spec/part1/nodesRef.html#ElevationGrid">Further information</a> 
	about this class is available in any VRML related documentation.

DESCRIPTION
	<ul>This node corresponds to the ElevationGrid node as defined in the VRML97 
	specification.  Like all Node Classes this class is better described in the 
	<A href="../spec/index.html">VRML97 Specification</a>.  In particular, at this 
	<A href="../spec/part1/nodesRef.html#ElevationGrid">link</a>.</ul>

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
class LIBInterface vrElevationGrid : public vrDataSet
{
protected:
	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'height' field.
	//
	// [default] []
	//
	MFFloat             	m_Height;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'xDimension' field.
	//
	// [default] 0
	//
	SFInt32             	m_XDimension;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'xSpacing' field.
	//
	// [default] 0.0
	//
	SFFloat             	m_XSpacing;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'zDimension' field.
	//
	// [default] 0
	//
	SFInt32             	m_ZDimension;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'zSpacing' field.
	//
	// [default] 0.0
	//
	SFFloat             	m_ZSpacing;

	//<doc>------------------------------------------------------------
	//<dd>Corresponds to the 'setHeight' eventIn.
	//
	// [default] []
	//
	MFFloat             	m_SetHeight;


public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrElevationGrid(void);

	//<doc>------------------------------------------------------------
	// <dd>Copy constructor.
	//
	vrElevationGrid(const vrElevationGrid& v);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual ~vrElevationGrid(void);

	//<doc>------------------------------------------------------------
	// <dd>Equals operator.
	//
	vrElevationGrid& operator=(const vrElevationGrid& v);

	//<doc>------------------------------------------------------------
	// <dd>Returns an exact copy of the given node.
	//
	virtual SFNode Clone(void) const;


	//<doc>------------------------------------------------------------
	// <dd>Add an item to the m_Height array (grow if needed).
	//
	// [in] height: The value to add to the m_Height array.
	//
	void AddHeight(SFFloat height);

	//<doc>------------------------------------------------------------
	// <dd>Replace the values of the m_Height member (copies values).
	//
	// [in] height: The m_Height array.
	//
	void SetHeight(const MFFloat& height);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_XDimension member.
	//
	// [in] xdimension: The xdimension value.
	//
	void SetXDimension(SFInt32 xdimension);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_XSpacing member.
	//
	// [in] xspacing: The xspacing value.
	//
	void SetXSpacing(SFFloat xspacing);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_ZDimension member.
	//
	// [in] zdimension: The zdimension value.
	//
	void SetZDimension(SFInt32 zdimension);

	//<doc>------------------------------------------------------------
	// <dd>Set the value of the m_ZSpacing member.
	//
	// [in] zspacing: The zspacing value.
	//
	void SetZSpacing(SFFloat zspacing);

	//<doc>------------------------------------------------------------
	// <dd>Return the number of values in the m_Height member.
	//
	SFInt32 GetNHeights(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the nth value in the m_Height member.
	//
	// [in] n: The index into the array.
	//
	SFFloat GetHeight(SFInt32 n) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the m_Height member.
	//
	const MFFloat& GetHeightArray(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_XDimension member.
	//
	SFInt32 GetXDimension(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_XSpacing member.
	//
	SFFloat GetXSpacing(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_ZDimension member.
	//
	SFInt32 GetZDimension(void) const;

	//<doc>------------------------------------------------------------
	// <dd>Return the value of the m_ZSpacing member.
	//
	SFFloat GetZSpacing(void) const;


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
	DECLARE_NODE(vrElevationGrid);

	//------------------------------------------------------------
	// hand coded functions
	virtual void BuildMesh(void);
	virtual void BuildColors(void);
	virtual void BuildNormals(void);
	virtual void BuildTexCoords(void);
};

//----------------------------------------------------------------------
// field sets and gets inlines
inline void vrElevationGrid::AddHeight(SFFloat height)
{
	m_Height.AddValue(height);
}

inline void vrElevationGrid::SetHeight(const MFFloat& height)
{
	m_Height.Clear();
	m_Height = height;
}

inline void vrElevationGrid::SetXDimension(SFInt32 xdimension)
{
	m_XDimension = xdimension;
}

inline void vrElevationGrid::SetXSpacing(SFFloat xspacing)
{
	m_XSpacing = xspacing;
}

inline void vrElevationGrid::SetZDimension(SFInt32 zdimension)
{
	m_ZDimension = zdimension;
}

inline void vrElevationGrid::SetZSpacing(SFFloat zspacing)
{
	m_ZSpacing = zspacing;
}

inline SFInt32 vrElevationGrid::GetNHeights(void) const
{
	return m_Height.GetCount();
}

inline SFFloat vrElevationGrid::GetHeight(SFInt32 n) const
{
	return m_Height[n];
}

inline const MFFloat& vrElevationGrid::GetHeightArray(void) const
{
	return m_Height;
}

inline SFInt32 vrElevationGrid::GetXDimension(void) const
{
	return m_XDimension;
}

inline SFFloat vrElevationGrid::GetXSpacing(void) const
{
	return m_XSpacing;
}

inline SFInt32 vrElevationGrid::GetZDimension(void) const
{
	return m_ZDimension;
}

inline SFFloat vrElevationGrid::GetZSpacing(void) const
{
	return m_ZSpacing;
}

inline void vrElevationGrid::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}
#endif

