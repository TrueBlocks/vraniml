//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "Utility.h"

#include "BaseNode.h"

vrRuntimeClass vrBaseNode::classvrBaseNode;
static vrBuiltIn _biBaseNode(&vrBaseNode::classvrBaseNode,
	"vrBaseNode", sizeof(vrBaseNode), NULL, NULL);

vrRuntimeClass* vrBaseNode::GetRuntimeClass() const
{
	return &vrBaseNode::classvrBaseNode;
}

SFBool vrBaseNode::IsKindOf(const vrRuntimeClass* pClass) const
{
	vrRuntimeClass* pClassThis = GetRuntimeClass();
	return pClassThis->IsDerivedFrom(pClass);
}

void vrBaseNode::AddField(SFInt32 fieldType, SFInt32 fieldID, const SFString& fieldName)
{
	vrRuntimeClass *pClass = GetRuntimeClass();
	if (fieldName == nullString) // fieldID is actually a pointer to the fieldName
		pClass->AddField((char*)fieldID, fieldType, vrField::field, fieldID);
	else
		pClass->AddField(fieldName, fieldType, vrField::field, fieldID);
}

void vrBaseNode::AddExposedField(SFInt32 fieldType, SFInt32 fieldID, const SFString& fieldName)
{
	vrRuntimeClass *pClass = GetRuntimeClass();
	if (fieldName == nullString) // fieldID is actually a pointer to the fieldName
		pClass->AddField((char*)fieldID, fieldType, vrField::exposedField, fieldID);
	else
		pClass->AddField(fieldName, fieldType, vrField::exposedField, fieldID);
}

void vrBaseNode::AddEventOut(SFInt32 fieldType, SFInt32 fieldID, const SFString& fieldName)
{
	vrRuntimeClass *pClass = GetRuntimeClass();
	if (fieldName == nullString) // fieldID is actually a pointer to the fieldName
		pClass->AddField((char*)fieldID, fieldType, vrField::eventOut, fieldID);
	else
		pClass->AddField(fieldName, fieldType, vrField::eventOut, fieldID);
}

void vrBaseNode::AddEventIn(SFInt32 fieldType, SFInt32 fieldID, const SFString& fieldName)
{
	vrRuntimeClass *pClass = GetRuntimeClass();
	if (fieldName == nullString) // fieldID is actually a pointer to the fieldName
		pClass->AddField((char*)fieldID, fieldType, vrField::eventIn, fieldID);
	else
		pClass->AddField(fieldName, fieldType, vrField::eventIn, fieldID);
}

SFInt32 vrBaseNode::GetEventOutID(const SFString& fieldName) const
{
	vrRuntimeClass *pClass = GetRuntimeClass();
	vrFieldList *list = pClass->GetFieldList();
	if (!list)
		return FALSE;

	LISTPOS pos = list->GetHeadPosition();
	while (pos)
	{
		vrField *field = list->GetNext(pos);
		if (field->GetName() == fieldName)
		{
			// exact match
			return field->GetID();
		} else
		{
			if (field->IsEventType(vrField::exposedField)) // i.e. exposed field
			{
				// fieldName may contain '_changed' test for this
				// by testing the first 'len' items in fieldName for
				// equality with the search string.
				SFString start = fieldName.Left(field->GetName().Length());
				SFString rest  = fieldName.Mid(field->GetName().Length());
				
				if (field->GetName() == start && "_changed" == rest)
					return field->GetID();
			}
		}
	}
	return FALSE;
}

SFInt32 vrBaseNode::GetEventInID(const SFString& fieldName) const
{
	vrRuntimeClass *pClass = GetRuntimeClass();
	vrFieldList *list = pClass->GetFieldList();
	if (!list)
		return 0;

	LISTPOS pos = list->GetHeadPosition();
	while (pos)
	{
		vrField *field = list->GetNext(pos);
		if (field->GetName() == fieldName)
		{
			return field->GetID();
		} else
		{
			if (field->IsEventType(vrField::exposedField)) // i.e. exposed field
			{
				SFString first = fieldName.Left(4);
				SFString rest = fieldName.Mid(4);
				if (first == "set_" && rest == field->GetName())
					return field->GetID();
			}
		}
	}

	return FALSE;
}

SFString vrBaseNode::GetFieldName(SFInt32 eventID) const
{
	vrRuntimeClass *pClass = GetRuntimeClass();
	vrFieldList *list = pClass->GetFieldList();
	if (!list)
		return nullString;

	LISTPOS pos = list->GetHeadPosition();
	while (pos)
	{
		vrField *field = list->GetNext(pos);
		if (field->GetID() == eventID)
			return field->GetName();
	}

	return nullString;
}

SFInt32 vrBaseNode::GetFieldID(const SFString& fieldName) const
{
	SFInt32 id = GetEventInID(fieldName);
	if (!id)
		id = GetEventOutID(fieldName);
	return id;
}

SFInt32 vrBaseNode::GetFieldType(const SFString& fieldName) const
{
	return GetFieldType(GetFieldID(fieldName));
}

SFInt32 vrBaseNode::GetFieldType(SFInt32 eventID) const
{
	vrRuntimeClass *pClass = GetRuntimeClass();
	vrFieldList *list = pClass->GetFieldList();
	if (!list)
		return 0;

	LISTPOS pos = list->GetHeadPosition();
	while (pos)
	{
		vrField *field = list->GetNext(pos);
		if (field->GetID() == eventID)
		{
			return field->GetType();
		}
	}
	return FALSE;
}

SFBool vrBaseNode::SetFieldValue(const SFString& fieldName, void *val)
{
	ASSERT(0);
	return FALSE;
}
