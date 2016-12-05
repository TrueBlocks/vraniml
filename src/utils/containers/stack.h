#ifndef __STACK_H3D
#define __STACK_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

#include "list.h"

/*----------------------------------------------------------------------
CLASS
	vrStack

	A templated type-safe stack class.

DESCRIPTION
	<ul>
	A simple stack class built on top of the vrList.  This class
	is a template class so stacks of any type of object can be built.
	</ul>

NOTES
	<ul>
	<li>None.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// A simple stack of integers.
	vrStack&lt;SFInt32&gt; intStack;
	intStack.Push(1);
	intStack.Push(2);
	intStack.Push(3);

	while (intStack.Peek())
		printf("%d ", intStack.Pop());

	// OUTPUT: 3 2 1
	</pre>

MEMBERS
----------------------------------------------------------------------*/
template<class TYPE>
class vrStack : 
	public vrList < TYPE >
{
public:
  //<doc>------------------------------------------------------------
  // <dd>Push an object of type TYPE onto the stack.
	//
	// [in] node: the item to push.
	//
	void Push (TYPE item);

  //<doc>------------------------------------------------------------
  // <dd>Pop the topmost item off of the stack.
	//
	TYPE Pop  (void);

  //<doc>------------------------------------------------------------
  // <dd>Peek at the item on the top of the stack.
	//
	TYPE Peek (void) const;
};

template<class TYPE>
inline void vrStack<TYPE>::Push(TYPE node)
{
	AddHead(node);
}

template<class TYPE>
inline TYPE vrStack<TYPE>::Pop(void)
{
	return RemoveHead();
}

template<class TYPE>
inline TYPE vrStack<TYPE>::Peek(void) const
{
	return (Empty() ? NULL : GetHead());
}

/*----------------------------------------------------------------------
CLASS
	vrRefCountStack

	A templated stack class that implements reference counting.

DESCRIPTION
	<ul>
	A simple stack class built on top of the vrRefCountList.  This class
	is a template class so stacks of objects can be built
	as long as they implement the Reference and Dereference interfaces.
	</ul>

NOTES
	<ul>
	<li>None.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// A reference counting stack.
	vrRefCountStack&lt;SFNode&gt; nodeStack;
	nodeStack.Push(new vrCone);
	nodeStack.Push(new vrBox);
	nodeStack.Push(new vrSphere);

	// Deletes the Sphere first.
	while (nodeStack.Peek())
		delete nodeStack.Pop();
	</pre>

MEMBERS
----------------------------------------------------------------------*/
template<class TYPE>
class vrRefCountStack : 
	public vrRefCountList < TYPE >
{
public:
  //<doc>------------------------------------------------------------
  // <dd>Push an object of type TYPE onto the stack.
	//
	// [in] node: The node to be pushed.
	//
	void Push (TYPE node);

  //<doc>------------------------------------------------------------
  // <dd>Pop the topmost item off of the stack.
	//
	TYPE Pop  (void);

  //<doc>------------------------------------------------------------
  // <dd>Peek at the item on the top of the stack.
	//
	TYPE Peek (void) const;
};

template<class TYPE>
inline void vrRefCountStack<TYPE>::Push(TYPE node)
{
	AddHead(node);
}

template<class TYPE>
inline TYPE vrRefCountStack<TYPE>::Pop(void)
{
	return RemoveHead();
}

template<class TYPE>
inline TYPE vrRefCountStack<TYPE>::Peek(void) const
{
	return (Empty() ? NULL : GetHead());
}

#endif
