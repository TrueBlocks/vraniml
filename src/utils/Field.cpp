//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "Utility.h"

#include "Field.h"

vrField::vrField(void)
{
	m_ID        = -1;
//	m_Name      = NULL;
	m_Type      = -1;
	m_EventType = vrField::undefined; 
//	m_DefVal    = NULL;
	ASSERT(val.boolVal == NULL);
}

vrField::vrField(const vrField& field)
{
	m_ID        = field.m_ID;
	m_Name      = field.m_Name;
	m_Type      = field.m_Type;
	m_EventType = field.m_EventType; 
	
	// (how to copy void pointers?)
//	ASSERT(0); 
//	m_DefVal    = ((field.m_DefVal) ? NULL;
	CopyVal(&field,this);
}

vrField::~vrField(void)
{
}

vrField::vrField(const SFString& fieldName, SFInt32 dataType, vrEventType eventType, SFInt32 id, void *def)
{
	m_ID        = id;
	m_Name      = fieldName;
	m_Type      = dataType;
	m_EventType = eventType; 
	if (m_Type==-1)
	{
		m_Type = m_ID;
		m_ID = (long)m_Name.GetBuffer();
	}
	if (def)
		SetVal(this,def);
	else
	{
		ASSERT(val.boolVal==NULL);
	}
}

vrField& vrField::operator=(const vrField& field)
{
	m_ID        = field.m_ID;
	m_Name      = field.m_Name;
	m_Type      = field.m_Type;
	m_EventType = field.m_EventType; 

	CopyVal(&field,this);

	return *this;
}

//------------------------------------------------------------------
vrField *vrFieldList::FindByName(const SFString& name) const
{
	LISTPOS pos = GetHeadPosition();
	while (pos)
	{
		vrField *field = GetNext(pos);
		if (field->GetName() == name)
			return field;
	}
	return NULL;
}

SFInt32 GetEventType(const SFString& type)
{
	if (type == "eventIn")      return vrField::eventIn;
	if (type == "eventOut")     return vrField::eventOut;
	if (type == "field")        return vrField::field;
	if (type == "exposedField") return vrField::exposedField;
	return 0;
}

SFString GetEventTypeName(SFInt32 type)
{
	switch (type)
	{
	case vrField::eventIn:      return "eventIn";
	case vrField::eventOut:     return "eventOut";
	case vrField::field:        return "field";
	case vrField::exposedField: return "exposedField";
	}
	return "";
}

//-----------------------------------------------------------------------
SFInt32 GetFieldType(const SFString& type)
{
	if (type[0] == 'S')
	{
		if (type == "SFBool")     return SFBOOL;
		if (type == "SFInt32")    return SFINT32;
		if (type == "SFFloat")    return SFFLOAT;
		if (type == "SFTime")     return SFTIME;
		if (type == "SFString")   return SFSTRING;
		if (type == "SFVec2f")    return SFVEC2F;
		if (type == "SFVec3f")    return SFVEC3F;
		if (type == "SFColor")    return SFCOLOR;
		if (type == "SFRotation") return SFROTATION;
		if (type == "SFImage")    return SFIMAGE;
		if (type == "SFNode")     return SFNODE;
	} else if (type[0] == 'M')
	{
		if (type == "MFInt32")    return MFINT32;
		if (type == "MFFloat")    return MFFLOAT;
		if (type == "MFString")   return MFSTRING;
		if (type == "MFColor")    return MFCOLOR;
		if (type == "MFVec2f")    return MFVEC2F;
		if (type == "MFVec3f")    return MFVEC3F;
		if (type == "MFRotation") return MFROTATION;
		if (type == "MFNode")     return MFNODE;
	}
	return 0; // an error
}

//------------------------------------------------------------------
SFString GetFieldTypeName(SFInt32 type)
{
	switch (type)
	{
	case SFBOOL:     return "SFBool";
	case SFINT32:    return "SFInt32";
	case SFFLOAT:    return "SFFloat";
	case SFTIME:     return "SFTime";
	case SFSTRING:   return "SFString";
	case SFVEC2F:    return "SFVec2f";
	case SFVEC3F:    return "SFVec3f";
	case SFCOLOR:    return "SFColor";
	case SFROTATION: return "SFRotation";
	case SFIMAGE:    return "SFImage";
	case SFNODE:     return "SFNode";
	case MFINT32:    return "MFInt32";
	case MFFLOAT:    return "MFFloat";
	case MFSTRING:   return "MFString";
	case MFCOLOR:    return "MFColor";
	case MFVEC2F:    return "MFVec2f";
	case MFVEC3F:    return "MFVec3f";
	case MFROTATION: return "MFRotation";
	case MFNODE:     return "MFNode";
	default:
		// Error: 'illegal field name: 'type'
		ASSERT(0);
	}
	return "";
}

#define SETIT(a,b) \
	if (field->val.a)   \
		delete field->val.a; \
	if (!val) \
		field->val.a = NULL; \
	else \
	  field->val.a = new b(*(b*)val); \

void SetVal(vrField *field, void *val)
{
	ASSERT(field);
	switch (field->m_Type)
	{
	case SFBOOL:
		SETIT(boolVal, SFBool); break;
	case SFINT32:
		SETIT(intVal, SFInt32); break;
	case SFFLOAT:
		SETIT(floatVal, SFFloat); break;
	case SFTIME:
		SETIT(timeVal, SFTime); break;
	case SFSTRING:
		if (field->val.stringVal)
			delete field->val.stringVal;
		field->val.stringVal = new SFString((char *)val);
		break;
	case SFVEC2F:
		SETIT(vec2Val, SFVec2f); break;
	case SFVEC3F:
		SETIT(vec3Val, SFVec3f); break;
	case SFCOLOR:
		SETIT(colorVal, SFColor); break;
	case SFROTATION:
		SETIT(rotVal, SFRotation); break;
	case SFIMAGE:
		SETIT(imageVal, SFImage); break;
	case MFINT32:
		SETIT(intArray, MFInt32); break;
	case MFFLOAT:
		SETIT(floatArray, MFFloat); break;
	case MFSTRING:
		SETIT(stringArray, MFString); break;
	case MFVEC2F:
		SETIT(vec2Array, MFVec2f); break;
	case MFVEC3F:
		SETIT(vec3Array, MFVec3f); break;
	case MFCOLOR:
		SETIT(colorArray, MFColor); break;
	case MFROTATION:
		SETIT(rotArray, MFRotation); break;
	case SFNODE:
	case MFNODE:
		// must be handled by caller
	default:
		ASSERT(2==1);
	}
}

#define GETIT(a,b) \
	ASSERT(field->val.a); \
	*((b*)val) = *field->val.a;

void GetVal(const vrField *field, void *val)
{
	ASSERT(val);
	ASSERT(field);

	switch (field->m_Type)
	{
	case SFBOOL:
		GETIT(boolVal, SFBool); break;
	case SFINT32:
		GETIT(intVal, SFInt32); break;
	case SFFLOAT:
		GETIT(floatVal, SFFloat); break;
	case SFTIME:
		GETIT(timeVal, SFTime); break;
	case SFSTRING:
		GETIT(stringVal, SFString); break;
	case SFVEC2F:
		GETIT(vec2Val, SFVec2f); break;
	case SFVEC3F:
		GETIT(vec3Val, SFVec3f); break;
	case SFCOLOR:
		GETIT(colorVal, SFColor); break;
	case SFROTATION:
		GETIT(rotVal, SFRotation); break;
	case SFIMAGE:
		GETIT(imageVal, SFImage); break;
	case MFINT32:
		GETIT(intArray, MFInt32); break;
	case MFFLOAT:
		GETIT(floatArray, MFFloat); break;
	case MFSTRING:
		GETIT(stringArray, MFString); break;
	case MFVEC2F:
		GETIT(vec2Array, MFVec2f); break;
	case MFVEC3F:
		GETIT(vec3Array, MFVec3f); break;
	case MFCOLOR:
		GETIT(colorArray, MFColor); break;
	case MFROTATION:
		GETIT(rotArray, MFRotation); break;
	case SFNODE:
	case MFNODE:
		// must be handled by caller
	default:
		ASSERT(3==2);
	}
}

#define COPYIT(TYPE) \
	{ \
		TYPE v; \
		ASSERT(fromField->m_Type == toField->m_Type); \
		GetVal(fromField, &v); \
		SetVal(toField, &v); \
	}

void CopyVal(const vrField *fromField, vrField *toField)
{
	ASSERT(toField);
	ASSERT(fromField);
	ASSERT(toField->m_Type == fromField->m_Type);
	if (toField->val.boolVal == NULL || fromField->val.boolVal == NULL)
		return;

	switch (fromField->m_Type)
	{
	case SFBOOL:
		COPYIT(SFBool); break;
	case SFINT32:
		COPYIT(SFInt32); break;
	case SFFLOAT:
		COPYIT(SFFloat); break;
	case SFTIME:
		COPYIT(SFTime); break;
	case SFSTRING:
		COPYIT(SFString); break;
	case SFVEC2F:
		COPYIT(SFVec2f); break;
	case SFVEC3F:
		COPYIT(SFVec3f); break;
	case SFCOLOR:
		COPYIT(SFColor); break;
	case SFROTATION:
		COPYIT(SFRotation); break;
	case SFIMAGE:
		COPYIT(SFImage); break;
	case MFINT32:
		COPYIT(MFInt32); break;
	case MFFLOAT:
		COPYIT(MFFloat); break;
	case MFSTRING:
		COPYIT(MFString); break;
	case MFVEC2F:
		COPYIT(MFVec2f); break;
	case MFVEC3F:
		COPYIT(MFVec3f); break;
	case MFCOLOR:
		COPYIT(MFColor); break;
	case MFROTATION:
		COPYIT(MFRotation); break;
	case SFNODE:
	case MFNODE:
		// must be handled by caller
	default:
		ASSERT(4==3);
	}
}

#define DO_ARRAY(arr) \
	{ \
		if (field->val.arr) \
		{ \
			for (int i=0;i<field->val.arr->GetCount();i++) \
			{	\
				dc << field->val.arr->operator[](i); \
				if (i<field->val.arr->GetCount()-1) \
					dc << " "; \
			} \
		} \
	}

#define DO_SINGLE(vv) \
	if (field->val.vv) \
		dc << " " << *field->val.vv; \

void DumpName(vrDumpContext& dc, const vrField *field)
{
	dc << field->GetName();
}

void DumpVal(vrDumpContext& dc, const vrField *field)
{
	switch (field->GetType())
	{
	case SFBOOL:
		{
			char vals[][10] = { "FALSE", "TRUE" };
			if (field->val.boolVal)
			{
				ASSERT(*field->val.boolVal>-1&&*field->val.boolVal<2);
				dc << " " << vals[*field->val.boolVal]; \
			}
		}
		break;
	case SFINT32:
		DO_SINGLE(intVal);
		break;
	case SFFLOAT:
		DO_SINGLE(floatVal);
		break;
	case SFTIME:
		DO_SINGLE(timeVal);
		break;
	case SFSTRING:
		if (field->val.stringVal)
			dc << " \"" << *field->val.stringVal << "\"";
		break;
	case SFVEC2F:
		DO_SINGLE(vec2Val);
		break;
	case SFVEC3F:
		DO_SINGLE(vec3Val);
		break;
	case SFCOLOR:
		DO_SINGLE(colorVal);
		break;
	case SFROTATION:
		DO_SINGLE(rotVal);
		break;
	case SFIMAGE:
		DO_SINGLE(imageVal);
		break;
	case MFINT32:
		DO_ARRAY(intArray);
		break;
	case MFFLOAT:
		DO_ARRAY(floatArray);
		break;
	case MFSTRING:
		DO_ARRAY(stringArray);
		break;
	case MFVEC2F:
		DO_ARRAY(vec2Array);
		break;
	case MFVEC3F:
		DO_ARRAY(vec3Array);
		break;
	case MFCOLOR:
		DO_ARRAY(colorArray);
		break;
	case MFROTATION:
		DO_ARRAY(rotArray);
		break;
	case SFNODE:
	case MFNODE:
		// must be handled by caller
	default:
		ASSERT(5==4);
	}
}

#define EQ_SINGLE(vv) \
	(*f1->val.vv == *f2->val.vv);

#define EQ_ARRAY(vv) \
	(FALSE)

SFBool EqualVal(const vrField *f1, const vrField *f2)
{
	if (!f1 || !f1->val.boolVal)
		return FALSE;
	if (!f2 || !f2->val.boolVal)
		return FALSE;
	if (f1->IsEventType(vrField::eventOut))
		return TRUE;
	ASSERT(f1->GetType()==f2->GetType());
	switch (f1->GetType())
	{
	case SFBOOL:
		return EQ_SINGLE(boolVal);
		break;
	case SFINT32:
		return EQ_SINGLE(intVal);
		break;
	case SFFLOAT:
		return EQ_SINGLE(floatVal);
		break;
	case SFTIME:
		return EQ_SINGLE(timeVal);
		break;
	case SFSTRING:
		return EQ_SINGLE(stringVal);
		break;
	case SFVEC2F:
		return EQ_SINGLE(vec2Val);
		break;
	case SFVEC3F:
		return EQ_SINGLE(vec3Val);
		break;
	case SFCOLOR:
		return EQ_SINGLE(colorVal);
		break;
	case SFROTATION:
		return EQ_SINGLE(rotVal);
		break;
	case SFIMAGE:
//		return EQ_SINGLE(imageVal);
		return TRUE;
		break;
	case MFINT32:
		return EQ_ARRAY(intArray);
		break;
	case MFFLOAT:
		return EQ_ARRAY(floatArray);
		break;
	case MFSTRING:
		return EQ_ARRAY(stringArray);
		break;
	case MFVEC2F:
		return EQ_ARRAY(vec2Array);
		break;
	case MFVEC3F:
		return EQ_ARRAY(vec3Array);
		break;
	case MFCOLOR:
		return EQ_ARRAY(colorArray);
		break;
	case MFROTATION:
		return EQ_ARRAY(rotArray);
		break;
	case SFNODE:
	case MFNODE:
		// caller must handle these cases
	default:
		ASSERT(6==5);
	}
	return FALSE;
}
