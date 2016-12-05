//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "UserData.h"

vrUserDataList::~vrUserDataList(void)
{
	LISTPOS pos = GetHeadPosition();
	while (pos)
	{
		vrUserDataItem *item = GetNext(pos);
		delete item;
	}
	RemoveAll();
}

vrUserDataItem::vrUserDataItem(const SFString& id, vrUserData *data)
{
	m_Data = data;
	m_ID = id;
}

vrUserDataItem::~vrUserDataItem()
{
	if (m_Data)
		delete m_Data;
}

vrUserDataItem *vrUserDataList::FindItem(const SFString& id)
{
	LISTPOS pos = GetHeadPosition();
	while (pos)
	{
		vrUserDataItem *item = GetNext(pos);
		ASSERT(item);
		if (item->m_ID == id)
			return item;
	}
	return NULL;
}

