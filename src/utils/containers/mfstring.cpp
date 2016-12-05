//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "../types.h"

#include "mfstring.h"

MFString::MFString(void)
{
	m_nSize   = 0;
	m_nValues = 0;
	m_Values  = NULL;
}

MFString::MFString(const MFString& ar)
{
	SFInt32 size = sizeof(SFString) * ar.m_nSize;
	ASSERT(size);

	m_Values = (SFString *)malloc(size);
	memset(m_Values, 0, size);

	for (int i=0;i<ar.m_nValues;i++)
		m_Values[i] = ar.m_Values[i];
	m_nValues = ar.m_nValues;
	m_nSize   = ar.m_nSize;
}

MFString::~MFString(void)
{
	Clear();
}

MFString& MFString::operator=(const MFString& ar)
{
	Clear();
	
	SFInt32 size = sizeof(SFString) * ar.m_nSize;

	m_Values = (SFString *)malloc(size);
	memset(m_Values, 0, size);
	for (int i=0;i<ar.m_nValues;i++)
		m_Values[i] = ar.m_Values[i];
	m_nValues = ar.m_nValues;
	m_nSize = ar.m_nSize;

	return *this;
}

void MFString::Clear(void)
{
	for (int i=0;i<GetCount();i++)
		m_Values[i].~SFString();
	if (m_Values)
		free(m_Values);
	m_nValues = NULL;
	m_nSize = 0;
	m_Values = NULL;
}

SFString& MFString::operator[](SFInt32 index)
{
	if (index >= m_nSize)
	{
		SFString *a = m_Values;
		if (index >= m_nSize)
		{
			m_nSize += CHUNK_SIZE;
			m_nSize = MAX(m_nSize, index);
			SFInt32 size = sizeof(SFString) * (m_nSize);
			a = (SFString *)realloc(m_Values, size);
			// Initialize the newly allocated part only
			SFInt32 newSize = sizeof(SFString) * CHUNK_SIZE;
			ASSERT(a+size-sizeof(SFString) == a+(m_nSize-1)*sizeof(SFString));
			SFInt32 offset = (size-newSize)/sizeof(SFString);
			memset(a + offset, 0, newSize);
		}
		m_Values = a;
	}
	ASSERT(m_Values);
	if (index >= m_nValues)
	{
		m_nValues = index+1;
	}
	ASSERT(index>=0 && index<=m_nSize && index<=m_nValues);
	return m_Values[index];
}

const SFString& MFString::operator[](SFInt32 index) const
{
	ASSERT(index>=0 && index<=m_nValues);
	return m_Values[index];
}

SFInt32 MFString::GetCount(void) const
{
	return m_nValues;
}

void MFString::AddValue(SFString val)
{
	operator[](m_nValues++) = val;
}
