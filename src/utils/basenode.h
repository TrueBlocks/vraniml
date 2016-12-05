#ifndef __NODE_H3D
#define __NODE_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

#include "RuntimeClass.h"

/*----------------------------------------------------------------------
CLASS
	vrBaseNode

	The vrBaseNode is the base class for all classes that wish to implement
	reference counting and runtime typing.

DESCRIPTION
	<ul>
	Base class for any object added to any container.  Implements reference
	counting and runtime typing.  Future versions of this class will include
	memory debugging.  This class is equivelant to the CObject class in the
	MFC.
	</ul>

NOTES
	<ul>
	<li>If you use the DECLARE_NODE macro in a class
	definition you must add a corresponding IMPLEMENT_NODE macro
	in the class implementation file.</li>

	<li>Use the vrDELETE macro for proper deletion of reference counted objects.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class UL_Interface vrBaseNode
{
private:
  //<doc>------------------------------------------------------------
  // <dd>Count of the number of times this object has been referenced.
	//     The object will not be deleted unless the reference count
	//     reaches 0.
	// [default:] 0
	//
	SFInt32    m_RefCount;

public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
	vrBaseNode (void);

	//<doc>------------------------------------------------------------
	// <dd>Desctructor.
	//
	virtual ~vrBaseNode     (void);

	//<doc>------------------------------------------------------------
	// <dd>Increment the object's reference count.
	//
	void    Reference       (void);

	//<doc>------------------------------------------------------------
	// <dd>Decrement the object's reference count.
	//
	SFInt32 Dereference     (void);

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if the object is referenced.
	//
	SFBool  IsReferenced    (void);

	//<doc>------------------------------------------------------------
	// <dd>Returns TRUE if the object is of the query type or
	//     derived from a class of the query type.
	// <dd>This is used for runtime typing.
	//
	// [in] pClass: A pointer to the query class type.  Use the 
	//       GETRUNTIME_CLASS(className) macro to access the static
	//       vrRuntimeClass pointer for a given class.
	//
	virtual SFBool    IsKindOf     (const vrRuntimeClass* pClass) const;

	//<doc>------------------------------------------------------------
	// <dd>Declare that this node may be runtime typed. [ DECLARE_NODE ]
	//
	DECLARE_NODE(vrBaseNode);

	//<nodoc>------------------------------------------------------------
	// <dd>Add an 'eventIn' field type to a vrBaseNode (either the node's static vrRuntimeClass or directly to the node (as in the vrScript class)).
	//
	virtual void      AddEventIn     (SFInt32 fieldType, SFInt32 fieldId, const SFString& fieldName=nullString);

	//<nodoc>------------------------------------------------------------
	// <dd>Add an 'eventOut' field type to a vrBaseNode (either the node's static vrRuntimeClass or directly to the node (as in the vrScript class)).
	//
	virtual void      AddEventOut    (SFInt32 fieldType, SFInt32 fieldId, const SFString& fieldName=nullString);

	//<nodoc>------------------------------------------------------------
	// <dd>Add an 'exposedField' field type to a vrBaseNode (either the node's static vrRuntimeClass or directly to the node (as in the vrScript class)).
	//
	virtual void      AddExposedField(SFInt32 fieldType, SFInt32 fieldId, const SFString& fieldName=nullString);

	//<nodoc>------------------------------------------------------------
	// <dd>Add an 'field' field type to a vrBaseNode (either the node's static vrRuntimeClass or directly to the node (as in the vrScript class)).
	//
	virtual void      AddField       (SFInt32 fieldType, SFInt32 fieldId, const SFString& fieldName=nullString);

	//<nodoc>------------------------------------------------------------
	// <dd>Undocumented.
	//
	virtual SFInt32   GetEventOutID(const SFString& fieldName) const;

	//<nodoc>------------------------------------------------------------
	// <dd>Undocumented.
	//
	virtual SFInt32   GetEventInID (const SFString& fieldName) const;

	//<nodoc>------------------------------------------------------------
	// <dd>Undocumented.
	//
	virtual SFInt32   GetFieldID   (const SFString& fieldName) const;

	//<nodoc>------------------------------------------------------------
	// <dd>Undocumented.
	//
	virtual SFString  GetFieldName (SFInt32 eventID) const;

	//<nodoc>------------------------------------------------------------
	// <dd>Undocumented.
	//
	virtual SFInt32   GetFieldType (const SFString& fieldName) const;

	//<nodoc>------------------------------------------------------------
	// <dd>Undocumented.
	//
	virtual SFInt32   GetFieldType (SFInt32 eventID) const;

  //<nodoc>------------------------------------------------------------
  // The following are present only as interfaces to the parser.  Any
	// real implementation would override these virtual methods
	//
	virtual SFBool SetFieldValue(const SFString& fieldName, void *val);

	//<nodoc>------------------------------------------------------------
	// <dd>Undocumented.
	//
	virtual vrField *FindField(const SFString& fieldName)
		{
			ASSERT(GetRuntimeClass());
			return GetRuntimeClass()->FindField(fieldName);
		}
};

//<nodoc>------------------------------------------------------------
// All nodes should use this macro to delete themselves
// so that reference counting works.
//
#undef vrDELETE
#define vrDELETE(_nodE) \
	if ((_nodE)) \
		if ((_nodE)->Dereference()) \
			delete (_nodE); \
	(_nodE) = NULL;

inline vrBaseNode::vrBaseNode(void)
{
	m_RefCount = 0;
}

inline vrBaseNode::~vrBaseNode(void)
{
	ASSERT(m_RefCount==0);
}

inline void vrBaseNode::Reference(void)
{
	m_RefCount++;
}

inline SFInt32 vrBaseNode::Dereference(void)
{
	ASSERT(m_RefCount>0);
	m_RefCount--; 
	return (m_RefCount==0);
}

inline SFBool vrBaseNode::IsReferenced(void)
{
	return (m_RefCount);
}

#endif
