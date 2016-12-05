//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Map.h"

vrMapItem* vrMapItem::Create(vrMapItem*& pHead, SFInt32 nMax, SFInt32 cbElement)
{
	ASSERT(nMax > 0 && cbElement > 0);
	vrMapItem* p = (vrMapItem*) new char[sizeof(vrMapItem) + nMax * cbElement];
	p->pNext = pHead;
	pHead = p;
	return p;
}

void vrMapItem::FreeDataChain()
{
	vrMapItem* p = this;
	while (p != NULL)
	{
		char* bytes = (char*) p;
		vrMapItem* pNext = p->pNext;
		delete[] bytes;
		p = pNext;
	}
}
