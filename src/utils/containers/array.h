#ifndef __ARRAY_H3D
#define __ARRAY_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

#define CHUNK_SIZE 30

/*----------------------------------------------------------------------
CLASS
	vrArrayBase

	Base class for array classes.

DESCRIPTION
	<ul>
	This class supports the vrArray classes but does not implement the
	+, - or * operators since user may sometimes wish to store items in
	an array for which these operations are not defined (for example strings).
	</ul>

NOTES
	<ul>
	<li>This is a templated class.</li>
	<li>The array will grow in chunks of CHUNK_SIZE items (now defined at
			30 items) whenever necassary.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// This is a basic array class.
	vrArrayBase&lt;SFInt32&gt; intArray;

	intArray[0] = 1;
	intArray[1] = 2;
	intArray[2] = 3;
	for (int i=0;i&lt;intArray.GetCount();i++)
		printf("%d ", intArray[i]);
	printf("\n");

	// OUTPUT: 1 2 3
	</pre>

MEMBERS
----------------------------------------------------------------------*/
template<class TYPE>
class vrArrayBase
{
protected:
  //<doc>------------------------------------------------------------
  // <dd>The current size of the array -- will grow in CHUNK_SIZE increments as array fills up.
	// [default:] CHUNK_SIZE
	//
	SFInt32  m_nSize;

  //<doc>------------------------------------------------------------
  // <dd>The number of values currently stored in the array.
	// [default:] 0
	//
	SFInt32  m_nValues;

  //<doc>------------------------------------------------------------
  // <dd>The actual array of objects of type TYPE.
	// [default:] 0
	//
	TYPE    *m_Values;

public:
  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	vrArrayBase		(void)
		{
			m_nSize = 0;
			m_nValues = 0;
			m_Values = (TYPE*)NULL;
		}

  //<doc>------------------------------------------------------------
  // <dd>Copy constructor.
	//
	vrArrayBase	(const vrArrayBase& ar)
		{
			SFInt32 size = sizeof(TYPE)*ar.m_nSize;
			m_Values = (TYPE *)malloc(size);
			memset(m_Values, 0, size);
			for (int i=0;i<ar.m_nValues;i++)
			{
				m_Values[i] = ar.m_Values[i];
			}
			m_nValues = ar.m_nValues;
			m_nSize   = ar.m_nSize;
		}

  //<doc>------------------------------------------------------------
  // <dd>Desctructor.
	//
	~vrArrayBase		(void)
		{
			Clear();
		}

  //<doc>------------------------------------------------------------
  // <dd>Equals operator.
	//
	vrArrayBase&  operator=	(const vrArrayBase& ar)
		{
			Clear();
			
			SFInt32 size = sizeof(TYPE)*ar.m_nSize;
			m_Values = (TYPE *)malloc(size);
			memset(m_Values, 0, size);
			for (int i=0;i<ar.m_nValues;i++)
			{
				m_Values[i] = ar.m_Values[i];
			}
			m_nValues = ar.m_nValues;
			m_nSize = ar.m_nSize;
			return *this;
		}

  //<doc>------------------------------------------------------------
  // <dd>Clears the array -- does not delete the stored items.
	//
	void Clear(void)
		{
			if (m_Values)
				free(m_Values);
			m_nValues = NULL;
			m_nSize = 0;
			m_Values = NULL;
		}

  //<doc>------------------------------------------------------------
  // <dd>Access the nth item from the array for assignment (will grow if necassary).
	//
	// [in] index: The index of the requested item.
	//
	TYPE&					operator[]		(SFInt32 index)
		{
			if (index >= m_nSize)
			{
				TYPE *a = m_Values;
				if (index >= m_nSize)
				{
					m_nSize += CHUNK_SIZE;
					m_nSize = MAX(m_nSize, index);
					SFInt32 size = sizeof(TYPE)*(m_nSize);
					a = (TYPE *)realloc(m_Values, size);
					// Initialize the newly allocated part only
					SFInt32 newSize = sizeof(TYPE)*CHUNK_SIZE;
					ASSERT(a+size-sizeof(TYPE) == a+(m_nSize-1)*sizeof(TYPE));
					SFInt32 offset = (size-newSize)/sizeof(TYPE);
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

  //<doc>------------------------------------------------------------
  // <dd>Access the nth item from the array (read only).
	//
	// [in] index: The index of the requested item.
	//
	const TYPE&					operator[]		(SFInt32 index) const
		{
			ASSERT(index>=0 && index<=m_nValues);
			return m_Values[index];
		}

  //<doc>------------------------------------------------------------
  // <dd>Returns the number of items in the array.
	//
	SFInt32				GetCount			(void) const
		{
			return m_nValues;
		}

  //<doc>------------------------------------------------------------
  // <dd>Add a value to the array at the next available slot.
	//
	// [in] val: The value to add to the array.
	//
	void					AddValue		  (TYPE val)
		{
			operator[](m_nValues++) = val;
//			m_Values = AddToArray(val, m_Values, m_nValues++);
		}

private:
/*
	TYPE*					AddToArray		(TYPE val, TYPE array[], SFInt32 index)
		{
			TYPE *a = array;
			if (index >= m_nSize)
			{
				m_nSize += CHUNK_SIZE;
				m_nSize = MAX(m_nSize, index);
				SFInt32 size = sizeof(TYPE)*(m_nSize);
				a = (TYPE *)realloc(array, size);
				// Initialize the newly allocated part only
				SFInt32 newSize = sizeof(TYPE)*CHUNK_SIZE;
				ASSERT(a+size-sizeof(TYPE) == a+(m_nSize-1)*sizeof(TYPE));
				memset(a + size - newSize - sizeof(TYPE), 0, newSize);
			}
			a[index] = val;
			return a;
		}
*/
};

/*----------------------------------------------------------------------
CLASS
	vrArray

	Templated arrays that support +, - and * operator (for interpolation for example).

DESCRIPTION
	<ul>
	This class is a vrArrayBase that supports operations needed for interpolation.
	For this reason it is the base class for the multi-valued fields such as
	MFInt32, MFFloat, etc.
	</ul>

NOTES
	<ul>
	<li>Items added to vrArray class must support +, - and * operators or there
	will be a compile time error.</li>
	<li>Future versions of this class will support other operators such as == and !=</li>
	</ul>

EXAMPLE CODE
	<pre>
	// vrArrays can be treated like any C++ data type in that they
	// support the common mathematical operators '+', '-', '*' and '/'.

	// Note: could have used MFFloat instead.
	vrArray&lt;SFFloat&gt; floatArray1;
	floatArray1[0] = 1.0;
	floatArray1[1] = 2.0;
	floatArray1[2] = 3.0;
	for (int i=0;i&lt;floatArray1.GetCount();i++)
		printf("%f ", floatArray1[i]);
	printf("\n");

	// Note: could have used vrArray&lt;SFFloat&gt; instead.
	MFFloat floatArray2;
	floatArray2[0] = 3.0;
	floatArray2[1] = 2.0;
	floatArray2[2] = 1.0;
	for (i=0;i&lt;floatArray2.GetCount();i++)
		printf("%f ", floatArray2[i]);
	printf("\n");

	MFFloat result;
	result = floatArray1 + floatArray2;
	for (i=0;i&lt;result.GetCount();i++)
		printf("%f ", result[i]);
	printf("\n");

	// OUTPUT:
	// 1.0 2.0 3.0
	// 3.0 2.0 1.0
	// 4.0 4.0 4.0
  </pre>

MEMBERS
----------------------------------------------------------------------*/
template<class TYPE>
class vrArray : 
	public vrArrayBase < TYPE >
{
public:
  //<doc>------------------------------------------------------------
  // <dd>Componentwise addition of each item in both arrays.
	//
	// [in] v1: The first array.
	// [in] v2: The second array.
	//
	friend vrArray<TYPE> operator+(const vrArray<TYPE>& v1, const vrArray<TYPE>& v2);

  //<doc>------------------------------------------------------------
  // <dd>Componentwise subtraction of each item in both arrays.
	//
	// [in] v1: The first array.
	// [in] v2: The second array.
	//
  friend vrArray<TYPE> operator-(const vrArray<TYPE>& v1, const vrArray<TYPE>& v2);

  //<doc>------------------------------------------------------------
  // <dd>Componentwise multiplication of each item the array by a scalar.
	//
	// [in] v1: The array.
	// [in] f: The scalar.
	//
  friend vrArray<TYPE> operator*(const vrArray<TYPE>& v,  SFFloat f);

  //<doc>------------------------------------------------------------
  // <dd>Componentwise division of each item the array by a scalar.
	//
	// [in] v1: The array.
	// [in] f: The scalar.
	//
  friend vrArray<TYPE> operator/(const vrArray<TYPE>& v,  SFFloat f);

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if every element of 'array1' is the same as the corresponding element in 'array2'.
	//
	// [in] v1: The first array.
	// [in] v2: The second array.
	//
	friend SFBool operator==(const vrArray<TYPE>& v1, const vrArray<TYPE>& v2);

  //<doc>------------------------------------------------------------
  // <dd>Returns TRUE if any element in 'array1' is different from the corresponding element in 'array2'.
	//
	// [in] v1: The first array.
	// [in] v2: The second array.
	//
	friend SFBool operator!=(const vrArray<TYPE>& v1, const vrArray<TYPE>& v2);

  //<doc>------------------------------------------------------------
  // <dd>Assignment operator.  Note: If the number of items in 'v1' is larger than this array, this array grows, if smaller then only that many items are assigned.
	//
	// [in] v1: The first array.
	// [in] v2: The second array.
	//
	vrArray<TYPE>& operator=(const vrArray<TYPE>& v1);
};

template<class TYPE>
inline vrArray<TYPE> operator+(const vrArray<TYPE>& v1, const vrArray<TYPE>& v2)
{
	vrArray<TYPE> array;
	ASSERT(v1.GetCount() == v2.GetCount());
	for (int i=0;i<v1.GetCount();i++)
	{
		array.AddValue(v1[i] + v2[i]);
	}
	return array;
}

template<class TYPE>
inline vrArray<TYPE> operator-(const vrArray<TYPE>& v1, const vrArray<TYPE>& v2)
{
	vrArray<TYPE> array;
	ASSERT(v1.GetCount() == v2.GetCount());
	for (int i=0;i<v1.GetCount();i++)
	{
		array.AddValue(v1[i] - v2[i]);
	}
	return array;
}

template<class TYPE>
inline vrArray<TYPE> operator*(const vrArray<TYPE>& v,  SFFloat f)
{
	vrArray<TYPE> array;
	for (int i=0;i<v.GetCount();i++)
	{
		array.AddValue(v[i] * f);
	}
	return array;
}

template<class TYPE>
inline vrArray<TYPE> operator/(const vrArray<TYPE>& v,  SFFloat f)
{
	vrArray<TYPE> array;
	for (int i=0;i<v.GetCount();i++)
	{
		array.AddValue(v[i] / f);
	}
	return array;
}

template<class TYPE>
inline SFBool operator==(const vrArray<TYPE>& v1, const vrArray<TYPE>& v2)
{
	if (v1.GetCount() != v2.GetCount())
		return FALSE;

	for (int i=0;i<v1.GetCount();i++)
	{
		if (v1[i] != v2[i])
			return FALSE;
	}
	return TRUE;
}

template<class TYPE>
inline SFBool operator!=(const vrArray<TYPE>& v1, const vrArray<TYPE>& v2)
{
	return (!(operator==(v1, v2)));
}

template<class TYPE>
inline vrArray<TYPE>& vrArray<TYPE>::operator=(const vrArray<TYPE>& v1)
{
	vrArrayBase<TYPE>::operator=(v1);
	return *this;
}

//-------------------------------------------------------------------------
typedef vrArray<SFInt32>    MFInt32;
typedef vrArray<SFFloat>    MFFloat;
typedef vrArray<SFColor>    MFColor;
typedef vrArray<SFVec2f>    MFVec2f;
typedef vrArray<SFVec3f>    MFVec3f;
typedef vrArray<SFRotation> MFRotation;

#endif
