#ifndef _SFSTRING_H
#define _SFSTRING_H
//-------------------------------------------------------------------------
//  Copyright (c) 1997-1998 Great Hill Corporation
//  All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------

/*----------------------------------------------------------------------
CLASS
	SFString

	A string class.

DESCRIPTION
	<ul>
	This is a basic C++ string class supporting most of the functionality
	available for strings.
	</ul>

NOTES
	<ul>
	All SFString class instances refer to the 'nullString' object
	by default.
	</ul>

EXAMPLE CODE
	<pre>
	// Use SFStrings as you would any string class
	SFString string = "This is a string";
	// Find returns -1 if search string is not found.
	ASSERT(string.Find(".")==-1);

	// Add a period.
	string += ".";
	// Now it is found.
	ASSERT(string.Find(".")!=-1);

	// Assignment
	SFString str1 = string;
	// Equality (many other operators are available also).
	ASSERT(str1 == string);

	// Use 'nullString' or Empty to test for empty strings
	SFString defaultString;
	ASSERT(defaultString == nullString);
	ASSERT(defaultString.Empty());
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class SFString
{
protected:
  //<doc>------------------------------------------------------------
  // <dd>The actual characters for this string.
	// [default:] NULL
	//
	char    *m_Values;

  //<doc>------------------------------------------------------------
  // <dd>The number of characters in the string including trailing '\0'.
	// [default:] 0
	//
	SFInt32  m_nValues;

  //<doc>------------------------------------------------------------
  // <dd>The size of the string buffer (usually the same as m_nValues)
	// [default:] 0
	//
	SFInt32  m_nSize;

public:
  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	SFString  (void);

  //<doc>------------------------------------------------------------
  // <dd>Copy constructor.
	//
	SFString  (const SFString& str);

  //<doc>------------------------------------------------------------
  // <dd>Destructor.
	//
	~SFString (void);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] ch: A character to use to initialize the string.
	// [in] reps: The number of times to repeat the character.
	//
	SFString  (char ch, SFInt32 reps=1);

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	// [in] str: A charater string to promote to this SFString.
	// [in] start: The starting position from which to start copying (defaults to 0).
	// [in] len: The number of characters to copy starting at start (defaults to rest of string).
	//
	SFString  (const char *str, SFInt32 start=0, SFInt32 len=-1);

  //<doc>------------------------------------------------------------
  // <dd>Clear string memory and reset the string (same as default construction).
	//
	void            Clear         (void);

  //<doc>------------------------------------------------------------
  // <dd>Assignment operator from another SFString.
	//
	const SFString& operator=     (const SFString& str);

  //<doc>------------------------------------------------------------
  // <dd>Assignment operator from a character.
	//
	const SFString& operator=     (char ch);

  //<doc>------------------------------------------------------------
  // <dd>Assignment operator from a character string.
	//
	const SFString& operator=     (const char *str);

  //<doc>------------------------------------------------------------
  // <dd>Append operator from an SFString.
	//
	const SFString& operator+=    (const SFString& str);

  //<doc>------------------------------------------------------------
  // <dd>Append operator from a character.
	//
	const SFString& operator+=    (char ch);

  //<doc>------------------------------------------------------------
  // <dd>Append operator from a character string.
	//
	const SFString& operator+=    (const char *str);

  //<doc>------------------------------------------------------------
  // <dd>Access operator for a particular character.
	//
	// [in] index: The character to return.
	//
	char            GetAt         (SFInt32 index) const;

  //<doc>------------------------------------------------------------
  // <dd>Set a particular character
	//
	// [in] index: The character to set.
	// [in] ch: The character data.
	//
	void            SetAt         (SFInt32 index, char ch);

  //<doc>------------------------------------------------------------
  // <dd>Access operator for a particular character (same as GetAt).
	//
	// [in] index: The character to return.
	//
	char            operator[]    (int index) const;

  //<doc>------------------------------------------------------------
  // <dd>Casts the string to a const char *
	//
	operator        const char *  (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Casts the string to a char *
	//
	operator        char *        (void);

  //<doc>------------------------------------------------------------
  // <dd>Returns the character pointer data member for direct manipulation.
	//
	char           *GetBuffer     (void);

  //<doc>------------------------------------------------------------
  // <dd>Releases the character buffer and resizes the array.
	//
	void            ReleaseBuffer (void);

  //<doc>------------------------------------------------------------
  // <dd>Return the length of this string.
	//
	SFInt32         Length        (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if this string is empty (i.e. Length() == 0).
	//
	SFBool          Empty         (void) const;

  //<doc>------------------------------------------------------------
  // <dd>Case sensitive compare this string to the given string.  Returns -1 if 'str' is less than, 0 if equal and 1 if 'str' is greater than this string.
	//
	// [in] str: The string to compare.
	//
	SFInt32         Compare       (const char *str) const;

  //<doc>------------------------------------------------------------
  // <dd>Case in-sensitive compare this string to the given string.  Returns -1 if 'str' is less than, 0 if equal and 1 if 'str' is greater than this string.
	//
	// [in] str: The string to compare.
	//
	SFInt32         ICompare      (const char *str) const;

  //<doc>------------------------------------------------------------
  // <dd>Extract a substring from the middle of this string.
	//
	// [in] first: The starting character to extract.
	// [in] len: The number of characters to extract from start.
	//
	SFString        Mid           (SFInt32 first, SFInt32 len) const;

  //<doc>------------------------------------------------------------
  // <dd>Extract a substring from the middle of this string to the end.
	//
	// [in] first: The starting character to extract.
	//
	SFString        Mid           (SFInt32 first) const;

  //<doc>------------------------------------------------------------
  // <dd>Extract the leftmost 'len' characters from this string.
	//
	// [in] len: The number of characters to extract.
	//
	SFString        Left          (SFInt32 len) const;

  //<doc>------------------------------------------------------------
  // <dd>Extract the rightmost 'len' characters from this string.
	//
	// [in] len: The number of characters to extract.
	//
	SFString        Right         (SFInt32 len) const;

  //<doc>------------------------------------------------------------
  // <dd>Convert this string to all upper case.
	//
	void            ToUpper       (void);

  //<doc>------------------------------------------------------------
  // <dd>Convert this string to all lower case.
	//
	void            ToLower       (void);

  //<doc>------------------------------------------------------------
  // <dd>Reverse this string.
	//
	void            Reverse       (void);

  //<doc>------------------------------------------------------------
  // <dd>Returns -1 if 'ch' is not found, the position of 'ch' if it is found.
	//
	// [in] ch: The character to search for.
	//
	SFInt32         Find          (char ch) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns -1 if 'str' is not found, the starting position of 'str' if it is found.
	//
	// [in] str: The substring to search for.
	//
	SFInt32         Find          (const char *str) const;

  //<doc>------------------------------------------------------------
  // <dd>Search for 'ch' from the end of this string.  Returns -1 if 'ch' is not found, the position of 'ch' if it is found.
	//
	// [in] ch: The character to search for.
	//
	SFInt32         ReverseFind   (char ch) const;

  //<doc>------------------------------------------------------------
  // <dd>Replace all occurences of 'what' with 'with' in this string
	//
	// [in] what: The substring to be replace
	// [in] what: The substring to replace 'what' with.
	//
	void ReplaceAll(const SFString& what, const SFString& with);

  //<doc>------------------------------------------------------------
  // <dd>Replace the first occurence of 'what' with 'with' in this string
	//
	// [in] what: The substring to be replace
	// [in] what: The substring to replace 'what' with.
	//
	void Replace(const SFString& what, const SFString& with);

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if this string contains 'search'
	//
	// [in] search: The substring to search for.
	//
	SFBool Contains(const SFString& search) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if this string contains 'search'
	//
	// [in] search: The substring to search for.
	//
	SFBool Contains(char search) const;

  //<doc>------------------------------------------------------------
  // <dd>Return str2 concatinated to str1.
	//
	friend SFString operator+(const SFString& str1, const SFString& str2);

  //<doc>------------------------------------------------------------
  // <dd>Return ch concatinated to str.
	//
	friend SFString operator+(const SFString& str,  char ch);

  //<doc>------------------------------------------------------------
  // <dd>Return str concatinated to ch.
	//
	friend SFString operator+(char ch,              const SFString& str);

  //<doc>------------------------------------------------------------
  // <dd>Return str2 concatinated to str1.
	//
	friend SFString operator+(const SFString& str1, const char *str2);

  //<doc>------------------------------------------------------------
  // <dd>Return str2 concatinated to str1.
	//
	friend SFString operator+(const char *str1,     const SFString& str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if the two strings are the same.
	//
	friend SFBool   operator== (const SFString& str1, const SFString& str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if the two strings are the same.
	//
	friend SFBool   operator== (const SFString& str1, const char *str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if the two strings are the same.
	//
	friend SFBool   operator== (const char *str1, const SFString& str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if the two strings are the same.
	//
	friend SFBool   operator== (const SFString& str1, char ch);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if the two strings are the same.
	//
	friend SFBool   operator== (char ch, const SFString& str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if the two strings are not the same.
	//
	friend SFBool   operator!= (const SFString& str1, const SFString& str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if the two strings are not the same.
	//
	friend SFBool   operator!= (const SFString& str1, const char *str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if the two strings are not the same.
	//
	friend SFBool   operator!= (const char *str1, const SFString& str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if str1 is strictly less than str2.
	//
	friend SFBool   operator<  (const SFString& str1, const SFString& str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if str1 is strictly less than str2.
	//
	friend SFBool   operator<  (const SFString& str1, const char *str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if str1 is strictly less than str2.
	//
	friend SFBool   operator<  (const char *str1, const SFString& str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if str1 is strictly greater than str2.
	//
	friend SFBool   operator>  (const SFString& str1, const SFString& str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if str1 is strictly greater than str2.
	//
	friend SFBool   operator>  (const SFString& str1, const char *str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if str1 is strictly greater than str2.
	//
	friend SFBool   operator>  (const char *str1, const SFString& str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if str1 is less than or equal to str2.
	//
	friend SFBool   operator<= (const SFString& str1, const SFString& str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if str1 is less than or equal to str2.
	//
	friend SFBool   operator<= (const SFString& str1, const char *str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if str1 is less than or equal to str2.
	//
	friend SFBool   operator<= (const char *str1, const SFString& str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if str1 is greater than or equal to str2.
	//
	friend SFBool   operator>= (const SFString& str1, const SFString& str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if str1 is greater than or equal to str2.
	//
	friend SFBool   operator>= (const SFString& str1, const char *str2);

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if str1 is greater than or equal to str2.
	//
	friend SFBool   operator>= (const char *str1, const SFString& str2);

protected:
  //<nodoc>------------------------------------------------------------
  // <dd>Reinitialize the string.
	//
	void            Initialize    (void);

  //<nodoc>------------------------------------------------------------
  // <dd>Grow or shrink the buffer to length.  Returns the size of the buffer.
	//
	// [in] nLen: The length of the string buffer.
	//
	SFInt32         ResizeBuffer  (SFInt32 nLen);

  //<nodoc>------------------------------------------------------------
  // <dd>Extract a substring from this string (used by Mid, Left and Right).
	//
	// [in] first: The starting character to extract.
	// [in] len: The number of characters to extract from start.
	//
	SFString        Extract       (long first, long len) const;

private:
  //<nodoc>------------------------------------------------------------
  // <dd>TRUE if the string has been properly intialized
	// [default:] FALSE
	//
	SFBool          m_Initialized;
};

extern char nullString[];

//----------------------------------------------------------
inline const SFString& SFString::operator=(const char *str)
{
	*this = SFString(str);
	return *this;
}

inline const SFString& SFString::operator=(char ch)
{
	*this = SFString(ch);
	return *this;
}

inline const SFString& SFString::operator+=(const char *str)
{
	return operator+=(SFString(str));
}

inline const SFString& SFString::operator+=(char ch)
{
	return operator+=(SFString(ch));
}

inline SFInt32 SFString::Length() const
{
	return m_nValues;
}

inline SFBool SFString::Empty() const
{
	return !Length();
}

inline char SFString::GetAt(SFInt32 index) const
{
	ASSERT(index >= 0);
	ASSERT(index < Length());
	return m_Values[index];
}

inline char SFString::operator[](int index) const
{
	return GetAt(index);
}

inline SFString::operator const char *() const
{
	return m_Values;
}

inline SFString::operator char *()
{
	return m_Values;
}

inline SFInt32 SFString::Compare(const char *str) const
{
	return strcmp(m_Values, str);
}

inline SFInt32 SFString::ICompare(const char *str) const
{
	return stricmp(m_Values, str);
}

inline void SFString::ToUpper()
{
	_strupr(m_Values);
}

inline void SFString::ToLower()
{
	_strlwr(m_Values);
}

inline void SFString::Reverse()
{
	_strrev(m_Values);
}

inline SFBool SFString::Contains(const SFString& search) const
{
	return (Find(search)!=-1);
}

inline SFBool SFString::Contains(char ch) const
{
	return (Find(ch)!=-1);
}

//----------------------------------------------------------
// Friends and family
inline SFString operator+(const SFString& str1, const char *str2)
{
	return operator+(str1, SFString(str2));
}

inline SFString operator+(const char *str1, const SFString& str2)
{
	return operator+(SFString(str1), str2);
}

//----------------------------------------------------------
// comparison friends
inline SFBool operator==(const SFString& str1, const SFString& str2)
{
	return str1.Compare(str2) == 0;
}

inline SFBool operator==(const SFString& str1, const char *str2)
{
	return str1.Compare(str2) == 0;
}

inline SFBool operator==(const char *str1, const SFString& str2)
{
	return str2.Compare(str1) == 0;
}

inline SFBool operator==(const SFString& str1, char ch)
{
	return str1.Compare(SFString(ch)) == 0;
}

inline SFBool operator==(char ch, const SFString& str2)
{
	return str2.Compare(SFString(ch)) == 0;
}

inline SFBool operator!=(const SFString& str1, const SFString& str2)
{
	return str1.Compare(str2) != 0;
}

inline SFBool operator!=(const SFString& str1, const char *str2)
{
	return str1.Compare(str2) != 0;
}

inline SFBool operator!=(const char *str1, const SFString& str2)
{
	return str2.Compare(str1) != 0;
}

inline SFBool operator<(const SFString& str1, const SFString& str2)
{
	return str1.Compare(str2) < 0;
}

inline SFBool operator<(const SFString& str1, const char *str2)
{
	return str1.Compare(str2) < 0;
}

inline SFBool operator<(const char *str1, const SFString& str2)
{
	return str2.Compare(str1) > 0;
}

inline SFBool operator>(const SFString& str1, const SFString& str2)
{
	return str1.Compare(str2) > 0;
}

inline SFBool operator>(const SFString& str1, const char *str2)
{
	return str1.Compare(str2) > 0;
}

inline SFBool operator>(const char *str1, const SFString& str2)
{
	return str2.Compare(str1) < 0;
}

inline SFBool operator<=(const SFString& str1, const SFString& str2)
{
	return str1.Compare(str2) <= 0;
}

inline SFBool operator<=(const SFString& str1, const char *str2)
{
	return str1.Compare(str2) <= 0;
}

inline SFBool operator<=(const char *str1, const SFString& str2)
{
	return str2.Compare(str1) >= 0;
}

inline SFBool operator>=(const SFString& str1, const SFString& str2)
{
	return str1.Compare(str2) >= 0;
}

inline SFBool operator>=(const SFString& str1, const char *str2)
{
	return str1.Compare(str2) >= 0;
}

inline SFBool operator>=(const char *str1, const SFString& str2)
{
	return str2.Compare(str1) <= 0;
}

#endif
