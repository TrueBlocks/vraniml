#ifndef __RUNTIME_H3D
#define __RUNTIME_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------
#include "Field.h"

class   vrNode;
class   vrBaseNode;
typedef vrBaseNode* (*PFNV)(void);

/*----------------------------------------------------------------------
CLASS
	vrRuntimeClass

	Information about a given class's type used for runtime typing and dynamic creation.

DESCRIPTION
	<ul>
	The vrRuntimeClass class corresponds to the MFC class CRuntimeClass.<br><br>
	It provides runtime information about a class.  All classes that
	include a DECLARE_NODE macro in thier
	class definition have a pointer to a static vrRuntimeClass
	for that class.  This pointer is used to determine the runtime 
	type of the node.  The vrRuntimeClass may also be used for dynamic 
	addition of class types as is required to support the PROTO concept
	in VRML.
	</ul>

NOTES
	<ul>
	<li>This class corresponds almost exactly to the CRuntimeClass of the MFC.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// Use the DECLARE and IMPLEMENT macros for a class to create
	// the runtime class type information needed for runtime typeing.
	// For example, in the header file for a class called vrMyClass:
	
	DECLARE_NODE(vrMyClass);
		
	// and in the .cpp file:
	
	IMPLEMENT_NODE(vrMyClass, vrMyBaseClass, schemaNumber);

	// You may also use the DECLARE_NODE and IMPLEMENT_NODE macros in the same way.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class UL_Interface vrRuntimeClass
{
public:
  //<doc>------------------------------------------------------------
  // <dd>The human readable name of this class.
	// [default:] className
	//
	char             *m_ClassName;

  //<nodoc>------------------------------------------------------------
  // <dd>The size in bytes of an object of this type.
	// [default:] sizeof(className)
	//
	SFInt32           m_ObjectSize;

  //<nodoc>------------------------------------------------------------
  // <dd>Unused data.
	// [default:] 0xFFFF
	//
	SFInt32           m_Schema;

  //<doc>------------------------------------------------------------
  // <dd>Pointer to a function that creates objects of this type.
	// [default:] Create[className]
	//
	PFNV              m_CreateFunc;

  //<doc>------------------------------------------------------------
  // <dd>The base class of this type if any.
	// [default:] baseClass
	//
	vrRuntimeClass   *m_BaseClass;

  //<doc>------------------------------------------------------------
  // <dd>A linked list of vrField objects that make up the class type
	// this data type.
	// [default:] empty
	//
	vrFieldList      *m_FieldList;

  //<nodoc>------------------------------------------------------------
  // <dd>A reference count so vrRuntimeClass objects can be added to containers
	// [default:] 0
	//
	SFInt32           m_RefCount;

public:
  //<doc>------------------------------------------------------------
  // <dd>Destructor.
	//
	virtual      ~vrRuntimeClass  (void);

  //<doc>------------------------------------------------------------
  // <dd>Returns the name of the class type.
	//
	char         *ClassName       (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if this class is derived from pBaseClass.
	//
	// [in] pBaseClass: A pointer to the query class type.  Use the 
	//       GETRUNTIME_CLASS(className) macro to access the static
	//       class type pointer for a given class.
	//
	SFBool        IsDerivedFrom   (const vrRuntimeClass* pBaseClass) const;

  //<doc>------------------------------------------------------------
  // <dd>Add a vrField to the field list.
	//
	//	[in] fieldName: The name of this field (may be NULL).
	//	[in] dataType:  The data type of this field.
	//	[in] eventType: The event type of this field.
	//	[in] fieldID:   The unique id of this field.
	//
	void          AddField        (const SFString& fieldName, SFInt32 dataType, vrEventType eventType, SFInt32 fieldID);

  //<doc>------------------------------------------------------------
  // <dd>Release memory contained in and empty the field list.
	//
	void          ClearFieldList  (void);

  //<doc>------------------------------------------------------------
  // <dd>Return a pointer to the field list.
	//
	vrFieldList  *GetFieldList    (void) const { return m_FieldList; }

  //<nodoc>------------------------------------------------------------
  // <dd>Needed so vrRuntimeClass objects can be reference counted.
	//
	SFInt32       Reference       (void);

  //<nodoc>------------------------------------------------------------
  // <dd>Needed so vrRuntimeClass objects can be reference counted.
	//
	SFInt32       Dereference     (void);

  //<nodoc>------------------------------------------------------------
  // <dd>Needs to be called for dynamically created vrRuntimeClassess because
	//     there is no constrcutor.  Used while parsing .wrl files only.
	//
	void          Initialize    (const SFString& protoName);

  //<nodoc>------------------------------------------------------------
  // The following are present only as interfaces to the parser.  Any
	// real implementation would override these virtual methods
	//
	virtual SFBool SetFieldValue(const SFString& fieldName, void *val);

	virtual void AddChild(vrNode *node)
		{	/* do nothing */ }
	virtual vrField *FindField(const SFString& fieldName)
		{
			if (m_FieldList)
			{
				LISTPOS pos = m_FieldList->GetHeadPosition();
				while (pos)
				{
					vrField *field = m_FieldList->GetNext(pos);
					if (field->GetName() == fieldName)
						return field;
				}
			}
			return NULL;
		}
};

typedef vrRefCountList<vrRuntimeClass*> vrClassTypeList;
// One instance of this class is created for each 
// builtin class type (by virtue of including the
// IMPLEMENT_NODE macro below).  The constructor of this
// class adds this class type name and the runtime class
// to a static list of types.
class UL_Interface vrBuiltIn
{
	static vrClassTypeList m_TypeList;
public:
	// Do nothing other than add this class type to the static list of types.
	vrBuiltIn(vrRuntimeClass *pClass, 
							char *className, 
							SFInt32 classSize,
							PFNV createFunc,
							vrRuntimeClass *pParent);
	static vrRuntimeClass *Lookup(const SFString& name);
	static vrClassTypeList *GetClassTypeList(void)
		{
			return &m_TypeList;
		}
};
#define vrLookupBuiltin(name) vrBuiltIn::Lookup(name)
#define vrGetClassTypeList() vrBuiltIn::GetClassTypeList()

//------------------------------------------------------------
// Return the static pointer to the vrRuntimeClass object with this CLASS_NAME.
//
#define GETRUNTIME_CLASS(CLASS_NAME) \
	(&CLASS_NAME::class##CLASS_NAME) \

//------------------------------------------------------------
// Declare an object as runtime typeable and dynamically createable.  
// This code is placed in the header file.
//
#define DECLARE_NODE(CLASS_NAME) \
	public: \
		static vrRuntimeClass class##CLASS_NAME; \
		virtual vrRuntimeClass *GetRuntimeClass() const; \
		friend vrBaseNode *Create##CLASS_NAME(void); \

//------------------------------------------------------------
//<doc>
// <dd>Implement the runtime typing and dynamic creation of an object.  
// This code is placed in the .cpp file.
//
#define IMPLEMENT_NODE(CLASS_NAME, BASECLASS_NAME) \
	vrRuntimeClass CLASS_NAME::class##CLASS_NAME; \
	vrRuntimeClass *CLASS_NAME::GetRuntimeClass() const \
	{ \
		return &CLASS_NAME::class##CLASS_NAME; \
	} \
	vrBaseNode *Create##CLASS_NAME(void) \
	{ \
		return new CLASS_NAME; \
	} \
	static vrBuiltIn \
		_bi##CLASS_NAME(&CLASS_NAME::class##CLASS_NAME, \
		#CLASS_NAME, sizeof(CLASS_NAME), \
		Create##CLASS_NAME, GETRUNTIME_CLASS(BASECLASS_NAME)); \

#endif
