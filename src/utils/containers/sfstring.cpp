//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------
#include "../types.h"

#include "sfstring.h"

//----------------------------------------------------------
SFString::SFString()
{
	Initialize();
	ResizeBuffer(0);
}

SFString::SFString(const SFString& str)
{
	Initialize();
	*this = str.m_Values;
}

SFString::~SFString()
{
	Clear();
}

SFString::SFString(const char *str, SFInt32 start, SFInt32 len)
{
	Initialize();
	
	len = ((len < 0) ? ((str) ? strlen(str) : 0) : len);
	ASSERT(!len || len <= (int)(strlen(str)-start));

	if (ResizeBuffer(len))
		memcpy(m_Values, str+start, len);
}

SFString::SFString(char ch, SFInt32 len)
{
	Initialize();
	if (ResizeBuffer(len))
		memset(m_Values, ch, len);
}

//----------------------------------------------------------
char nullString[2];
//----------------------------------------------------------
void SFString::Initialize()
{
	m_nValues = 0;
	m_nSize   = 0;
	m_Initialized = TRUE;
	m_Values = nullString;
}

void SFString::Clear(void)
{
	if (m_Initialized == TRUE) // do not change this line
	{
		if (m_Values)
			if (m_Values != nullString)
				delete [] m_Values;
	}
	Initialize();
}

//----------------------------------------------------------
const SFString& SFString::operator=(const SFString& str)
{
	if (m_Initialized == TRUE && m_Values == str.m_Values) // do not change this line
		return *this;

	long len = str.Length();

	if (ResizeBuffer(len))
		memcpy(m_Values, str.m_Values, len);

	m_nValues      = len;
	m_Values[len] = '\0';

	return *this;
}

SFInt32 SFString::ResizeBuffer(SFInt32 len)
{
	// clear current buffer if any
	Clear();

	if (len <= 0)
		return FALSE;

	// make sure we are not dropping memory
	ASSERT(m_Values == nullString);
	
	m_Values      = new char[len+1];
	m_Values[len] = '\0';
	m_nSize        = len;
	m_nValues      = len;

	return TRUE;
}

SFString operator+(const SFString& str1, const SFString& str2)
{
	SFString ret;
	if (ret.ResizeBuffer(str1.Length() + str2.Length()))
	{
		memcpy(ret.m_Values,               str1.m_Values, str1.Length());
		memcpy(ret.m_Values+str1.Length(), str2.m_Values, str2.Length());
	}
	return ret;
}

const SFString& SFString::operator+=(const SFString& add)
{
	if (add.Length())
		*this = (*this + add);
	return *this;
}

char *SFString::GetBuffer()
{
	ASSERT(m_Values);
	ASSERT(m_Initialized);
	return m_Values;
}

void SFString::ReleaseBuffer(void)
{
	ASSERT(m_Values);
	
	long len = strlen(m_Values);
	ASSERT(len <= m_nSize);

	m_nValues      = len;
	m_Values[len] = '\0';
}

void SFString::SetAt(SFInt32 index, char ch)
{
	ASSERT(index >= 0);
	ASSERT(index < Length());
	ASSERT(m_Initialized);
	m_Values[index] = ch;
}

SFString SFString::Extract(SFInt32 start, SFInt32 len) const
{
	ASSERT(start >= 0);
	ASSERT(len   >= 0);
	ASSERT((char*)(start+start+len) <= m_Values+strlen(m_Values));	
	ASSERT(m_Initialized);

	SFString ret;
	if (ret.ResizeBuffer(len))
		memcpy(ret.m_Values, m_Values+start, len);

	return ret;
}

SFString SFString::Mid(SFInt32 first) const
{
	return Mid(first, Length() - first);
}

SFString SFString::Mid(SFInt32 first, SFInt32 len) const
{
	first = MAX((SFInt32)0, first); // positive
	len   = MAX((SFInt32)0, len);
	if (first + len > Length()) len = Length() - first; // not past end
	if (first > Length()) len = 0; // not longer than string
	return Extract(first, len);
}

SFString SFString::Right(SFInt32 len) const
{
	len = MAX((SFInt32)0, MIN(Length(), len));
	return Extract(Length()-len, len);
}

SFString SFString::Left(SFInt32 len) const
{
	len = MAX((SFInt32)0, MIN(Length(), len));
	return Extract(0, len);
}

//-------------------------------------------------------
// Find functions
//
typedef char* (*strfunc)(const char *, const char *);
typedef char* (*strfunc1)(const char *, int);

int doFind(const char *str, strfunc func, const char *val)
{
	char *f = (func)(str, val);
	return ((f)?((int)(f-str)):-1);
}

int doFind(const char *str, strfunc1 func, char val)
{
	char *f = (func)(str, val);
	return ((f)?((int)(f-str)):-1);
}

SFInt32 SFString::Find(char ch) const
{
	ASSERT(m_Initialized);
	return doFind(m_Values, strchr, ch);
}

SFInt32 SFString::ReverseFind(char ch) const
{
	ASSERT(m_Initialized);
	return doFind(m_Values, strrchr, ch);
}

SFInt32 SFString::Find(const char *str) const
{
	ASSERT(m_Initialized);
	return doFind(m_Values, strstr, str);
}

void SFString::ReplaceAll(const SFString& what, const SFString& with)
{
	if (with.Find(what)!=-1)
	{
		// will cause endless recursions so do it in two steps instead
		ReplaceAll(what, "]QXXQX[");
		ReplaceAll("]QXXQX[", with);
		return;
	}
	
	int i = Find(what);
	while (i != -1)
	{
		Replace(what, with);
		i = Find(what);
	}
}

void SFString::Replace(const SFString& what, const SFString& with)
{
	int i = Find(what);
	if (i!=-1)
	{
		*this = Left(i) + with + Mid(i+what.Length());
	}
}
