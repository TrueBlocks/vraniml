//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "Utility.h"

#include "RuntimeClass.h"

// No constructor because these fields are initilialized by
// the IMPLEMENT macros in the header

//-------------------------------------------------------------------------
vrRuntimeClass::~vrRuntimeClass(void)
{
	ClearFieldList();
	// Should be cleared when last node is deleted
	ASSERT(!m_FieldList);

	if (m_Schema==0xFFFA)
	{
		// This will only happen when the PROTO is read from
		// a file which is not yet supported.
		if (m_ClassName)
			free(m_ClassName);
	}
}

//-------------------------------------------------------------------------
char *vrRuntimeClass::ClassName(void) const
{
	return m_ClassName;
}

SFBool vrRuntimeClass::IsDerivedFrom(const vrRuntimeClass* pBaseClass) const
{
	const vrRuntimeClass* pClassThis = this;
	while (pClassThis != NULL)
	{
		if (pClassThis == pBaseClass)
			return TRUE;
		pClassThis = pClassThis->m_BaseClass;
	}
	return FALSE;
}

//-------------------------------------------------------------------------
// Needed because there is no constructor
void vrRuntimeClass::Initialize(const SFString& protoName)
{
	SFString copy = protoName;
	if (!copy.Empty())
		m_ClassName     = strdup(copy.GetBuffer());

	m_ObjectSize    = 0;
	// Signifies that we were created with Initialize so we can cleanup (i.e. the class is not builtin)
	m_Schema        = 0xFFFA;
	m_BaseClass     = NULL;
	m_FieldList     = NULL;
	m_RefCount      = 0;
	m_CreateFunc    = NULL;
}

void vrRuntimeClass::ClearFieldList(void)
{
	if (m_FieldList)
	{
		LISTPOS p = m_FieldList->GetHeadPosition();
		while (p)
		{
			vrField *field = m_FieldList->GetNext(p);
			delete field;
		}
		m_FieldList->RemoveAll();
		delete m_FieldList;
		m_FieldList = NULL;
	}
}

void vrRuntimeClass::AddField(const SFString& fieldName, SFInt32 dataType, vrEventType eventType, SFInt32 fieldID)
{
	if (!m_FieldList)
	{
		m_FieldList = new vrFieldList;
	}
	ASSERT(m_FieldList);
	m_FieldList->AddTail(new vrField(fieldName, dataType, eventType, fieldID));
}

//-------------------------------------------------------------------------
SFInt32 vrRuntimeClass::Reference(void)
{
	++m_RefCount;
	return m_RefCount;
}

SFInt32 vrRuntimeClass::Dereference(void)
{
	m_RefCount--; 
	ASSERT(m_RefCount>=0); 
	if (!m_RefCount || 
			(m_CreateFunc && m_RefCount==1))
	{
		// Clear the field list for proper PROTO's when last
		// referenced or BuiltIns when only the builtin is still
		// referenced.
		ClearFieldList();
	}
	return (m_RefCount==0);
}

vrClassTypeList vrBuiltIn::m_TypeList;

vrRuntimeClass *vrBuiltIn::Lookup(const SFString& name)
{
	LISTPOS pos = m_TypeList.GetHeadPosition();
	while (pos)
	{
		vrRuntimeClass *pClass = m_TypeList.GetNext(pos);
		if (pClass->ClassName() == name)
			return pClass;
	}
	return NULL;
}

SFBool vrRuntimeClass::SetFieldValue(const SFString& fieldName, void *val)
{
	vrField *field = FindField(fieldName);
	ASSERT(field);
	SetVal(field, val);
	return TRUE;
}

vrBuiltIn::vrBuiltIn(vrRuntimeClass *pClass, 
					char *className, 
					SFInt32 classSize,
					PFNV createFunc,
					vrRuntimeClass *pParent)
{
	ASSERT(pClass);
	pClass->m_ClassName = className;
	pClass->m_ObjectSize = classSize;
	pClass->m_Schema = 0xFFFF;
	pClass->m_CreateFunc = createFunc;
	pClass->m_BaseClass = pParent;
	pClass->m_FieldList = NULL;
	pClass->m_RefCount = 0;
	m_TypeList.AddTail(pClass);
}
