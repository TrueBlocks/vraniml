#ifndef __MFSTRING_H3D
#define __MFSTRING_H3D

#define CHUNK_SIZE 30

#include "SFString.h"

/*----------------------------------------------------------------------
CLASS
	MFString

	An array of SFStrings

DESCRIPTION
	<ul>
	An array of SFStrings.
	</ul>

NOTES
	<ul>
	<li>None.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// This is an array of SFString objects
	MFString *intArray = new MFString;

	(*intArray)[0] = "This";
	(*intArray)[1] = SFString(" is an array");
	
	for (int i=0;i<intArray->GetCount();i++)
		dc << (*intArray)[i];

	MFString copy = *intArray;
	delete intArray;

	copy[1] += '.';

	for (i=0;i<copy.GetCount();i++)
		dc << copy[i];

	dc << endl;

	// OUTPUT
	// This is an array
	// This is an array.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class MFString
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
	SFString *m_Values;

public:
  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	MFString(void);

  //<doc>------------------------------------------------------------
  // <dd>Copy constructor.
	//
	MFString(const MFString& ar);

  //<doc>------------------------------------------------------------
  // <dd>Desctructor.
	//
	~MFString(void);

  //<doc>------------------------------------------------------------
  // <dd>Equals operator.
	//
	MFString& operator=(const MFString& ar);

  //<doc>------------------------------------------------------------
  // <dd>Clears the array -- deletes the stored SFStrings.
	//
	void Clear(void);

  //<doc>------------------------------------------------------------
  // <dd>Access the nth item from the array for assignment (will grow if necassary).
	//
	// [in] index: The index of the requested item.
	//
	SFString& operator[](SFInt32 index);

  //<doc>------------------------------------------------------------
  // <dd>Access the nth item from the array (read only).
	//
	// [in] index: The index of the requested item.
	//
	const SFString& operator[](SFInt32 index) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns the number of items in the array.
	//
	SFInt32 GetCount(void) const;

  //<doc>------------------------------------------------------------
  // <dd>Add a value to the array at the next available slot.
	//
	// [in] val: The value to add to the array.
	//
	void AddValue(SFString val);
};

#endif
