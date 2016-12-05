#ifndef __ROUTE_H3D
#define __ROUTE_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Nodes\Node.h"

/*----------------------------------------------------------------------
CLASS
	vrRoute

	The class represents a ROUTE from one field of the source node
	to a field (of the exact same data type) of the destination node.

DESCRIPTION
	<ul>
	This class implements the idea of a VRML ROUTE statement.  More information
	on ROUTE's is available <a href="../spec/part1/concepts.html">here</a>.
	Routes are followed during an event cascade which can be initiated by
	the user (for example by a mouse click over a pointing device sensor) or
	by the system (for example from a TimeSensor).
	</ul>

NOTES
	<ul>
	<li>vrRoute objects are created by the vrNode::AddRoute command.  For this 
	reason you will probably not use the class directly.</li>
	<li>Default constructor, copy constructor and equals operator are private
	so you may not make invalid copies of vrRoutes.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// The following...
	vrTimeSensor ts; 
	ts.SetName("TS");
	
	vrOrientationInterpolator ori; 
	ori.SetName("ORI");

	vrTransform trans;
	trans.SetName("TRANS");

	ts.AddRoute("fraction_changed", &ori, "set_fraction");
	ori.AddRoute("value_changed", &trans, "rotation");

	// ...is equivilant to the VRML code:
	// ROUTE TS.fraction_changed TO ORI.set_fraction
	// ROUTE ORI.value_changed   TO TRANS.rotation
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrRoute
{
private:
	//<doc>------------------------------------------------------------
	//<dd>The source node for the ROUTE.
	//
	// [default] NA
	//
	SFNode      m_Source;

	//<doc>------------------------------------------------------------
	//<dd>The field ID for the source field.
	//
	// [default] NA
	//
	SFInt32     m_SrcFieldID;

	//<doc>------------------------------------------------------------
	//<dd>The destination node for the ROUTE.
	//
	// [default] NA
	//
	SFNode      m_Destination;

	//<doc>------------------------------------------------------------
	//<dd>The field ID for the source field.
	//
	// [default] NA
	//
	SFInt32     m_DstFieldID;

	//<nodoc>------------------------------------------------------------
	//<dd>TRUE if this route is internal (i.e. not defined in VRML spec)
	//
	// [default] FALSE
	//
	SFInt32     m_Internal;

	//<nodoc>------------------------------------------------------------
	//<dd>Assigned by system at runtime (for use in exporting only)
	//
	// [default] NA
	//
	SFInt32     m_RouteID;

	//<nodoc>------------------------------------------------------------
	//<dd>Counts all routes created since application started to uniquely
	//<dd>identify routes so when the are exported they are exported in order of appearance.
	//
	// [default] 0
	//
	static   SFInt32		 m_nRoutes;

public:
	//<doc>------------------------------------------------------------
	//<dd>Constructor.
	//
	// [in] src: Source node.
	// [in] srcFieldID: Source field ID.
	// [in] dst: Destination node.
	// [in] dstFieldID: Destination field ID.
	// [in] intern: TRUE if this ROUTE is system defined (i.e. not defined in VRML spec).
	//
	vrRoute(SFNode src, SFInt32 srcFieldID, SFNode dst, SFInt32 dstFieldID, int intern=FALSE);

	//<doc>------------------------------------------------------------
	//<dd>Destructor.
	//
	~vrRoute(void);

	//<doc>------------------------------------------------------------
	//<dd>Returns TRUE if this is a valid route (as defined in VRML spec).
	//
	SFBool   IsValid      (void) const;

	//<doc>------------------------------------------------------------
	//<dd>Returns the human-readable name of the source or destination field.
	//
	// [in] which: 0 = return source field name, 1 = return destination field name
	//
	SFString GetFieldName (SFInt32 which) const;

	//<doc>------------------------------------------------------------
	//<dd>Returns the data type of the source or destination field.
	//
	// [in] which: 0 = return source field name, 1 = return destination field name
	//
	SFInt32  GetFieldType (SFInt32 which) const;

	//<doc>------------------------------------------------------------
	//<dd>Returns the name of the source or destination node.
	//
	// [in] which: 0 = return source node name, 1 = return destination node name
	//
	SFString GetNodeName  (SFInt32 which) const;

	//<nodoc>------------------------------------------------------------
	//<dd>Returns the route ID.
	//
	SFInt32  GetRouteID (void) const;

	//<nodoc>------------------------------------------------------------
	//<dd>Returns TRUE if this route is internal.
	//
	SFBool   IsInternal (void) const;

	friend class vrNode;
	friend SFBool FillRouteArray(SFNode node, void *data);

private:
	//<nodoc>------------------------------------------------------------
	// Private default constructor, copy constructor and equals
	// operator disallows invalid routes.
	//
	vrRoute()
		{ };
	vrRoute(const vrRoute& route)
		{ };
	vrRoute& operator=(const vrRoute& route)
		{ return *this; };
};

inline SFInt32 vrRoute::GetRouteID(void) const
{
	return m_RouteID;
}

inline SFBool vrRoute::IsInternal(void) const
{
	return m_Internal;
}

//<nodoc>------------------------------------------------------------
// <dd>Add a vrRoute to the specified node.
//
// [in] srcNode: The source node of the route.
// [in] srcField: A vrField name for a node of this type that initiates the route.
// [in] dstNode: The node to which the srcField is routed.
// [in] dstField: The vrField in the dstNode to which the srcField is routed.
//
//inline void AddRoute(SFNode srcNode, const SFString& srcField, SFNode dstNode, const SFString& dstField)
//{
//	if (srcNode)
//		srcNode->AddRoute(srcField, dstNode, dstField);
//}

/*----------------------------------------------------------------------
CLASS
	vrRouteList

	A list of vrRoute pointers.

DESCRIPTION
	<ul>
	This class is used by each vrNode to store a list of all vrRoute
	objects that eminate from it.  Note that to store the entire
	Route graph we only need to store the routes that eminate from
	a particular node.
	</ul>

NOTES
	<ul>
	<li>You may, but probably will not, use this class directly.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class vrRouteList :
	public vrList < vrRoute * >
{
};

#endif