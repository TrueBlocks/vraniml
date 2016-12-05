vrFieldList *vrScript::GetFieldList(void) const
{
	return m_FieldList;
}

void vrScript::AddField(SFInt32 fieldType, SFInt32 fieldID, const SFString& fieldName)
{
ASSERT(fieldName != nullString);
//	ASSERT(!strcmp((char *)fieldID, fieldName));
//	if (fieldName==nullString)
//		AddField(vrEventType::field, fieldID, (char *)fieldID, fieldType);
//	else
		AddField(vrEventType::field, fieldID, fieldName, fieldType);
}

void vrScript::AddExposedField(SFInt32 fieldType, SFInt32 fieldID, const SFString& fieldName)
{
ASSERT(fieldName != nullString);
//	ASSERT(!strcmp((char *)fieldID, fieldName));
//	if (fieldName==nullString)
//		AddField(vrEventType::exposedField, fieldID, (char *)fieldID, fieldType);
//	else
		AddField(vrEventType::exposedField, fieldID, fieldName, fieldType);
}

void vrScript::AddEventOut(SFInt32 fieldType, SFInt32 fieldID, const SFString& fieldName)
{
ASSERT(fieldName != nullString);
//	ASSERT(!strcmp((char *)fieldID, fieldName));
//	if (fieldName==nullString)
//		AddField(vrEventType::eventIn, fieldID, (char *)fieldID, fieldType);
//	else
		AddField(vrEventType::eventIn, fieldID, fieldName, fieldType);
}

void vrScript::AddEventIn(SFInt32 fieldType, SFInt32 fieldID, const SFString& fieldName)
{
ASSERT(fieldName != nullString);
//	ASSERT(!strcmp((char *)fieldID, fieldName));
//	if (fieldName==nullString)
//		AddField(vrEventType::eventOut, fieldID, (char *)fieldID, fieldType);
//	else
		AddField(vrEventType::eventOut, fieldID, fieldName, fieldType);
}

void vrScript::AddField(vrEventType eventType, SFInt32 fieldID, const SFString& fieldName, SFInt32 fieldType)
{
	if (!m_FieldList)
		m_FieldList = new vrFieldList;
	ASSERT(m_FieldList);
	m_FieldList->AddTail(new vrField(fieldName, fieldType, eventType, fieldID));
}

void vrScript::ClearFieldList(void)
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

SFInt32 vrScript::GetEventOutID(const SFString& fieldName) const
{
	SFInt32 id = vrNode::GetEventOutID(fieldName);
	if (!id)
	{
		vrFieldList *list = GetFieldList();
		if (list)
		{
			LISTPOS pos = list->GetHeadPosition();
			while (pos)
			{
				vrField *field = list->GetNext(pos);
				// must be an exact match
				if (fieldName == field->GetName())
					return field->GetID();
			}
		}
	}
	return id;
}

SFInt32 vrScript::GetEventInID(const SFString& fieldName) const
{
	SFInt32 id = vrNode::GetEventInID(fieldName);
	if (!id)
	{
		vrFieldList *list = GetFieldList();
		if (list)
		{
			LISTPOS pos = list->GetHeadPosition();
			while (pos)
			{
				vrField *field = list->GetNext(pos);
				// looking for dest events (eventIns)
				// must be an exact match
				if (fieldName == field->GetName())
					return field->GetID();
			}
		}
	}
	return id;
}

SFString vrScript::GetFieldName(SFInt32 eventID) const
{
	SFString name = vrNode::GetFieldName(eventID);
	if (name == nullString)
	{
		vrFieldList *list = GetFieldList();
		if (list)
		{
			LISTPOS pos = list->GetHeadPosition();
			while (pos)
			{
				vrField *field = list->GetNext(pos);
				if (field->GetID() == eventID)
					return field->GetName();
			}
		}
	}
	return name;
}

SFInt32 vrScript::GetFieldType(SFInt32 eventID) const
{
	SFInt32 type = vrNode::GetFieldType(eventID);
	if (!type)
	{
		vrFieldList *list = GetFieldList();
		if (list)
		{
			LISTPOS pos = list->GetHeadPosition();
			while (pos)
			{
				vrField *field = list->GetNext(pos);
				if (field->GetID() == eventID)
					return field->GetType();
			}
		}
	}
	return type;
}
