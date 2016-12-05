#ifndef __MAP_H3D
#define __MAP_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//----------------------------------------------------------------------

#undef VRML_BEFORE_START_POSITION
#define VRML_BEFORE_START_POSITION ((LISTPOS)-1L)

class vrMapItem
{
public:
	vrMapItem* pNext;
	long dwReserved[1];    // align on 8 byte boundary
	void* data() { return this+1; }
	static vrMapItem* Create(vrMapItem*& head, SFInt32 nMax, SFInt32 cbElement);
	void FreeDataChain();
};

template<class KEY_TYPE, class VALUE_TYPE>
class vrMap
{
protected:
	struct vrMapEntry
	{
		KEY_TYPE   key;
		VALUE_TYPE value;
		SFInt32      nHashValue;
		vrMapEntry* pNext;
	};
	SFBool isString;
	
public:
	vrMap(int nBlockSize = 10);
	~vrMap();

	void SetAt(KEY_TYPE key, VALUE_TYPE newValue)
		{
			(*this)[key] = newValue;
		}

	SFInt32 GetCount() const
		{
			return m_nCount;
		}

	SFBool Empty() const
		{
			return m_nCount == 0;
		}

	LISTPOS GetHeadPosition() const
		{
			return (m_nCount == 0) ? NULL : VRML_BEFORE_START_POSITION;
		}

	SFInt32 GetHashTableSize() const
		{
			return m_nHashTableSize;
		}

	SFBool Lookup(KEY_TYPE key, VALUE_TYPE& rValue) const;

	vrMapEntry *GetEntryAt(KEY_TYPE, SFInt32&) const;
	vrMapEntry *NewEntry();
	void       FreeEntry(vrMapEntry*);

	void GetNext(LISTPOS& rNextPosition, KEY_TYPE& rKey, VALUE_TYPE& rValue) const;

	void ResizeHashTable(SFInt32 hashSize, SFBool bAllocNow = TRUE);

	void RemoveAll();
	SFBool RemoveKey(KEY_TYPE key);

	VALUE_TYPE& operator[](KEY_TYPE key);

	SFInt32 HashKey(KEY_TYPE key) const;

protected:
	vrMapEntry   **m_pHashTable;
	SFInt32         m_nHashTableSize;
	int           m_nCount;
	vrMapEntry    *m_pFreeList;
	vrMapItem        *m_pBlocks;
	int           m_nBlockSize;

protected:
	typedef KEY_TYPE BASE_KEY;
	typedef VALUE_TYPE BASE_VALUE;
};

template<class KEY_TYPE, class VALUE_TYPE>
inline vrMap<KEY_TYPE, VALUE_TYPE>::vrMap(int nBlockSize)
{
	ASSERT(nBlockSize > 0);

	m_pHashTable = NULL;
	m_nHashTableSize = 17;
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = nBlockSize;
	isString=FALSE;
}

template<class KEY_TYPE, class VALUE_TYPE>
inline SFInt32 vrMap<KEY_TYPE, VALUE_TYPE>::HashKey(KEY_TYPE key) const
{
	if (isString)
	{
		SFInt32 i=0;
		char *s = (char *)(long)key;
		while (*s)
		{
			i = (i+(SFInt32)*s);
			s++;
		}
		return i;
	} else
	{
		return ((SFInt32)(void*)(long)key) >> 4;
	}
}

template<class KEY_TYPE, class VALUE_TYPE>
inline vrMap<KEY_TYPE, VALUE_TYPE>::~vrMap()
{
	RemoveAll();
	ASSERT(m_nCount == 0);
}

//-----------------------------------------------------------------
template<class KEY_TYPE, class VALUE_TYPE>
inline SFBool vrMap<KEY_TYPE, VALUE_TYPE>::Lookup(KEY_TYPE key, VALUE_TYPE& rValue) const
{
	SFInt32 nHash;
	vrMapEntry* pEntry = GetEntryAt(key, nHash);
	if (pEntry == NULL)
		return FALSE;

	rValue = pEntry->value;
	return TRUE;
}

template<class KEY_TYPE, class VALUE_TYPE>
inline vrMap<KEY_TYPE, VALUE_TYPE>::vrMapEntry *vrMap<KEY_TYPE, VALUE_TYPE>::GetEntryAt(KEY_TYPE key, SFInt32& nHash) const
{
	nHash = HashKey(key) % m_nHashTableSize;
	if (m_pHashTable == NULL)
		return NULL;

	vrMapEntry* pEntry;
	for (pEntry = m_pHashTable[nHash]; pEntry != NULL; pEntry = pEntry->pNext)
	{
		if (isString)
		{
			if (!strcmp((char *)(long)pEntry->key,(char *)(long)key))
				return pEntry;
		} else
		{
			if (pEntry->key == key)
				return pEntry;
		}
	}
	return NULL;
}

template<class KEY_TYPE, class VALUE_TYPE>
inline vrMap<KEY_TYPE, VALUE_TYPE>::vrMapEntry *vrMap<KEY_TYPE, VALUE_TYPE>::NewEntry()
{
	if (m_pFreeList == NULL)
	{
		// add another block
		vrMapItem* newBlock = vrMapItem::Create(m_pBlocks, m_nBlockSize, sizeof(vrMap<KEY_TYPE, VALUE_TYPE>::vrMapEntry));
		// chain them into free list
		vrMap<KEY_TYPE, VALUE_TYPE>::vrMapEntry* pEntry = (vrMap<KEY_TYPE, VALUE_TYPE>::vrMapEntry*)newBlock->data();
		// free in reverse order to make it easier to debug
		pEntry += m_nBlockSize - 1;
		for (int i = m_nBlockSize-1; i >= 0; i--, pEntry--)
		{
			pEntry->pNext = m_pFreeList;
			m_pFreeList = pEntry;
		}
	}
	ASSERT(m_pFreeList != NULL);  // we must have something

	vrMap<KEY_TYPE, VALUE_TYPE>::vrMapEntry* pEntry = m_pFreeList;
	m_pFreeList = m_pFreeList->pNext;
	m_nCount++;

	ASSERT(m_nCount > 0);  // make sure we don't overflow

	pEntry->key   = (KEY_TYPE)0;
	pEntry->value = (VALUE_TYPE)0;

	return pEntry;
}

template<class KEY_TYPE, class VALUE_TYPE>
inline void vrMap<KEY_TYPE, VALUE_TYPE>::FreeEntry(vrMap<KEY_TYPE, VALUE_TYPE>::vrMapEntry* pEntry)
{
	// Note: caller is responsible to delete key and value

	pEntry->pNext = m_pFreeList;
	m_pFreeList = pEntry;
	m_nCount--;
	ASSERT(m_nCount >= 0);  // make sure we don't underflow

	// if no more elements, cleanup completely
	if (m_nCount == 0)
		RemoveAll();
}

template<class KEY_TYPE, class VALUE_TYPE>
inline void vrMap<KEY_TYPE, VALUE_TYPE>::GetNext(LISTPOS& rNextPosition, KEY_TYPE& rKey, VALUE_TYPE& rValue) const
{
	ASSERT(m_pHashTable != NULL);  // never call on empty map

	vrMapEntry* pEntryRet = (vrMapEntry*)rNextPosition;
	ASSERT(pEntryRet != NULL);

	if (pEntryRet == (vrMapEntry*)VRML_BEFORE_START_POSITION)
	{
		// find the first association
		for (SFInt32 nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
			if ((pEntryRet = m_pHashTable[nBucket]) != NULL)
				break;
		ASSERT(pEntryRet != NULL);  // must find something
	}

	// find next association
	vrMapEntry* nextEntry;
	if ((nextEntry = pEntryRet->pNext) == NULL)
	{
		// go to next bucket
		for (SFInt32 nBucket = pEntryRet->nHashValue + 1;
		  nBucket < m_nHashTableSize; nBucket++)
			if ((nextEntry = m_pHashTable[nBucket]) != NULL)
				break;
	}
	rNextPosition = (LISTPOS)nextEntry;

	// fill in return data
	rKey   = pEntryRet->key;
	rValue = pEntryRet->value;
}

template<class KEY_TYPE, class VALUE_TYPE>
inline void vrMap<KEY_TYPE, VALUE_TYPE>::ResizeHashTable(SFInt32 nHashSize, SFBool bAllocNow)
{
	ASSERT(m_nCount == 0);
	ASSERT(nHashSize > 0);

	if (m_pHashTable != NULL)
	{
		delete [] m_pHashTable;
		m_pHashTable = NULL;
	}

	if (bAllocNow)
	{
		m_pHashTable = new vrMapEntry* [nHashSize];
		memset(m_pHashTable, 0, sizeof(vrMapEntry*) * nHashSize);
	}
	m_nHashTableSize = nHashSize;
}

template<class KEY_TYPE, class VALUE_TYPE>
inline void vrMap<KEY_TYPE, VALUE_TYPE>::RemoveAll()
{
	if (isString)
	{
		LISTPOS pos = GetHeadPosition();
		while (pos)
		{
			KEY_TYPE key;
			VALUE_TYPE value;
			GetNext(pos, key, value);
			free((char *)(long)key);
			key=NULL;
			free((char *)(long)value);
			value=NULL;
		}
	}
	
	delete [] m_pHashTable;
	m_pHashTable = NULL;

	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

template<class KEY_TYPE, class VALUE_TYPE>
inline SFBool vrMap<KEY_TYPE, VALUE_TYPE>::RemoveKey(KEY_TYPE key)
{
	if (m_pHashTable == NULL)
		return FALSE;

	vrMapEntry** pBucket;
	pBucket = &m_pHashTable[HashKey(key) % m_nHashTableSize];

	vrMapEntry* pEntry;
	for (pEntry = *pBucket; pEntry != NULL; pEntry = pEntry->pNext)
	{
		if (isString)
		{
			if (!strcmp((char *)(long)pEntry->key,(char *)(long)key))
			{
				*pBucket = pEntry->pNext;
				FreeEntry(pEntry);
				return TRUE;
			}
		} else
		{
			if (pEntry->key == key)
			{
				*pBucket = pEntry->pNext;
				FreeEntry(pEntry);
				return TRUE;
			}
		}
		pBucket = &pEntry->pNext;
	}
	return FALSE;
}

template<class KEY_TYPE, class VALUE_TYPE>
inline VALUE_TYPE& vrMap<KEY_TYPE, VALUE_TYPE>::operator[](KEY_TYPE key)
{
	SFInt32 nHash;

	vrMapEntry* pEntry;
	if ((pEntry = GetEntryAt(key, nHash)) == NULL)
	{
		if (m_pHashTable == NULL)
			ResizeHashTable(m_nHashTableSize);

		pEntry = NewEntry();
		pEntry->nHashValue = nHash;
		if (isString)
		{
			pEntry->key = (KEY_TYPE)(long)strdup((char *)(long)key);
		} else
		{
			pEntry->key = key;
		}
		// 'pEntry->value' is a constructed object, nothing more

		pEntry->pNext = m_pHashTable[nHash];
		m_pHashTable[nHash] = pEntry;
	}
	return pEntry->value;
}

// Typed pointer list
template<class BASE_CLASS, class KEY, class VALUE>
class vrTypedPtrMap : public BASE_CLASS
{
public:
	vrTypedPtrMap(int nBlockSize = 10) : BASE_CLASS(nBlockSize)
		{
		}

	SFBool Lookup(BASE_CLASS::BASE_KEY key, VALUE& rValue) const
		{
			return BASE_CLASS::Lookup(key, (BASE_CLASS::BASE_VALUE&)rValue);
		}

	VALUE& operator[](BASE_CLASS::BASE_KEY key)
		{ 
			return (VALUE&)BASE_CLASS::operator[](key);
		}

	void SetAt(KEY key, VALUE newValue)
		{ 
			BASE_CLASS::SetAt(key, newValue);
		}

	SFBool RemoveKey(KEY key)
		{
			return BASE_CLASS::RemoveKey(key);
		}

	void GetNext(LISTPOS& rPosition, KEY& rKey, VALUE& rValue) const
		{ 
			BASE_CLASS::GetNext(rPosition, 
														(BASE_CLASS::BASE_KEY&)rKey,
														(BASE_CLASS::BASE_VALUE&)rValue);
		}
};

#endif