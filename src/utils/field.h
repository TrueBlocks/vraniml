#ifndef _FIELD_H3D
#define _FIELD_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

#include "Containers/SFString.h"
#include "FieldVal.h"

/*----------------------------------------------------------------------
CLASS
	vrField

	The vrField class represents information about the fields that make up
	a vrRuntimeClass.  Each node stores static information about itself by
	including a pointer to a vrRuntimeClass for that node type.

DESCRIPTION
	<ul>
	The vrField class stores information about a particular field in
	a vrRuntimeClass.  A vrField has data items for fieldType, fieldName, defaultValue 
	and a storage class or eventType.
	</ul>

NOTES
	<ul>
	<li>The vrField class corresponds to the VRML concept of a field which
	are the components of all built-in nodes and Prototypes.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class UL_Interface vrField
{
public:
	_fieldValUnion val;

	//<doc>------------------------------------------------------------
  // <dd>Enumeration for values assigned to m_EventType.
	// <dd>One of [ undefined=-1 | eventOut=1 | eventIn=2 | exposedField=3 | field=4 ]
	//
	typedef enum { undefined=-1, eventOut=1, eventIn=2, exposedField=3, field=4 } vrEventType;

protected:
  //<doc>------------------------------------------------------------
  // <dd>A unique id for this field.
	// [default:] 0
	//
	SFInt32     m_ID;

  //<doc>------------------------------------------------------------
  // <dd>Type of event this field represents.
	// [default:] 0
	// [values:] [undefined|eventOut|eventIn|exposedField|field]
	//
	vrEventType m_EventType;

  //<doc>------------------------------------------------------------
  // <dd>The name of this field.
	// [default:] NULL
	//
	SFString    m_Name;

  //<doc>------------------------------------------------------------
  // <dd>The type of this field.
	// [default:] NULL
	// [values:] [SFBool|SFInt32|SFFloat|SFVec2f|SFVec3f|...|MFInt32|MFFloat|...etc...]
	//
	SFInt32     m_Type;

  //<nodoc>------------------------------------------------------------
  // <dd>The default value for this field.
	// [default:] NULL
	//
	// void       *m_DefVal;

public:
  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	vrField    (void);

  //<doc>------------------------------------------------------------
  // <dd>Copy constructor.
	//
	vrField    (const vrField& field);

  //<doc>------------------------------------------------------------
  // <dd>Destructor.
	//
 ~vrField    (void);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	//	[in] fieldName: The name of this field (may be NULL).
	//	[in] dataType:  The data type of this field.
	//	[in] eventType: The event type of this field.
	//	[in] fieldID:   The unique id of this field.
	//
	vrField    (const SFString& fieldName, SFInt32 dataType, vrEventType eventType=vrField::undefined, SFInt32 fieldID=-1, void *def=NULL);

  //<doc>------------------------------------------------------------
  // <dd>Equals operator.
	//
	vrField&    operator=  (const vrField& field);

  //<doc>------------------------------------------------------------
  // <dd>Return the field name.
	//
	SFString    GetName    (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Return the field type.
	//
	SFInt32     GetType    (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Return the field event type.
	//
	SFInt32     GetEventType    (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Return the field id.
	//
	SFInt32     GetID    (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE is this field has the given event type.
	//
	//	[in] eventType: The event type to query.
	//
	SFBool      IsEventType(vrEventType eventType) const;

	friend void   UL_Interface SetVal    (vrField *field, void *value);
	friend void   UL_Interface GetVal    (const vrField *field, void *value);
	friend void   UL_Interface CopyVal   (const vrField *fromField, vrField *toField);
	friend void   UL_Interface DumpVal   (vrDumpContext& dc, const vrField *field);
	friend SFBool UL_Interface EqualVal  (const vrField *f1, const vrField *f2);
	friend void   UL_Interface DumpName  (vrDumpContext& dc, const vrField *field);
	friend void                SetValEx  (vrField *field, void *value);
	friend void                GetValEx  (const vrField *field, void *value);
	friend void                CopyValEx (const vrField *fromField, vrField *toField);
	friend void                DumpValEx (vrDumpContext& dc, const vrField *field);
	friend SFBool              EqualValEx(const vrField *f1, const vrField *f2);
};
// Syntactic sugar
#define vrEventType vrField::vrEventType

//-------------------------------------------------------------------------
inline SFString vrField::GetName(void) const
{
	return m_Name;
}

inline SFInt32 vrField::GetType(void) const
{
	return m_Type;
}

inline SFInt32 vrField::GetEventType(void) const
{
	return m_EventType;
}

inline SFInt32 vrField::GetID(void) const
{
	return m_ID;
}

inline SFBool vrField::IsEventType(vrEventType et) const
{
	return (m_EventType == et);
}

extern SFInt32  UL_Interface GetEventType     (const SFString& type);
extern SFString UL_Interface GetEventTypeName (SFInt32 type);
extern SFInt32  UL_Interface GetFieldType     (const SFString& type);
extern SFString UL_Interface GetFieldTypeName (SFInt32 type);

/*----------------------------------------------------------------------
CLASS
	vrFieldList

	The linked list of vrField items.  This class is used by the vrRuntimeClass
	class to store its list of fields.

DESCRIPTION
	<ul>
	The linked list of vrField items.  This class is used by the vrRuntimeClass
	class to store its list of fields.
	</ul>

NOTES
	<ul>
	<li>You will probably not use this class directly.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class UL_Interface vrFieldList : 
	public vrList < vrField * >
{
public:
  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	vrFieldList() {}

  //<doc>------------------------------------------------------------
  // <dd>Find a vrField by name.  Return a pointer to the field or NULL.
	//
	vrField *FindByName(const SFString& name) const;
};

#endif