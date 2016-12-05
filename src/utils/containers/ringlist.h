#ifndef __RINGLIST_H3D
#define __RINGLIST_H3D
//----------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//----------------------------------------------------------------------

#include "intrusivelist.h"

/*----------------------------------------------------------------------
CLASS
	vrRingList

	A doubly linked list that links its tail to its head allowing
	for iteration begining at any point (a circulator).

DESCRIPTION
	<ul>
	This class is used only in the vrSolid class to implement the
	vrHalfEdge lists in each vrFace.  It may have other user defined
	uses however and is therefor included in this documentation.
	</ul>

NOTES
	<ul>
	<li>This is a templated class.  Data added to a list of this
		type must contain two data items of type TYPE called next and prev
		or be derived from the vrIntrusiveListNode object.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
template <class TYPE>
class vrRingList : 
	public vrIntrusiveList < TYPE >
{
public:
  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	vrRingList() : vrIntrusiveList<TYPE>() {};

  //<doc>------------------------------------------------------------
  // <dd>Destructor.
	//
	~vrRingList() {};

  //<doc>------------------------------------------------------------
  // <dd>Add an item of type TYPE to the tail of the list.
	//
  void             AddTail      (TYPE);

  //<doc>------------------------------------------------------------
  // <dd>Add an item of type TYPE to the head of the list.
	//
  void             AddHead      (TYPE);

  //<doc>------------------------------------------------------------
  // <dd>Mark the given item as the head of the list.
	//
  void             SetHead      (TYPE);

  //<doc>------------------------------------------------------------
  // <dd>Remove the given item from the list.
	//
  void             RemoveAt     (TYPE);

  //<doc>------------------------------------------------------------
  // <dd>Insert the given item in the list following the first item.
	//
  void             InsertNode   (TYPE, TYPE);
};

template <class TYPE>
inline void vrRingList<TYPE>::AddHead(TYPE node)
{
  ASSERT(node);
  ASSERT(!m_Head || m_Head->prev == m_Tail);
  ASSERT(!m_Tail || m_Tail->next == m_Head);

  node->next = m_Head;
  node->prev = m_Tail;

  if (!m_Head)
	{
    ASSERT(!m_Tail);
    m_Head = m_Tail = node;
    m_Head->prev = m_Tail->next = node;
  } else
	{
    ASSERT(m_Tail);
    m_Head->prev = node;
    m_Tail->next = node;
    m_Head = node;
  }

  n++;
}

template <class TYPE>
inline void vrRingList<TYPE>::AddTail(TYPE node)
{
  ASSERT(node);
  ASSERT(!m_Head || m_Head->prev == m_Tail);
  ASSERT(!m_Tail || m_Tail->next == m_Head);

  node->next = m_Head;
  node->prev = m_Tail;

  if (!m_Head)
	{
    ASSERT(!m_Tail);
    m_Head = m_Tail = node;
    m_Head->prev = m_Tail->next = node;
  } else
	{
    ASSERT(m_Tail);
    m_Tail->next = node;
    m_Head->prev = node;
    m_Tail = node;
  }

  n++;
}

template <class TYPE>
inline void vrRingList<TYPE>::SetHead(TYPE newHead)
{
	m_Head = newHead;
  if (m_Head)
	{
    m_Tail = m_Head->prev;
  } else
	{
    m_Tail = NULL;
    n=0;
  }
}

template <class TYPE>
inline void vrRingList<TYPE>::InsertNode(TYPE node, TYPE follows) 
{
  ASSERT(node);
  ASSERT(follows);

  node->next = follows;
  node->prev = follows->prev;

  if (follows->prev)
	{
    follows->prev->next = node;
  }
  follows->prev = node;

  if (m_Head == follows)
	{
    m_Head = node;
  }

  n++;
}

template <class TYPE>
inline void vrRingList<TYPE>::RemoveAt(TYPE node)
{
  ASSERT(node);

  if (!m_Head)
	{
    ASSERT(!m_Tail);
    node->next = node->prev = NULL;
    return;
  }
  ASSERT(m_Tail);

  if (m_Head == node)
	{
    if (m_Head == m_Tail)
		{
      node->next = NULL;
    }
    m_Head = m_Head->next;
  }

  if (m_Tail == node)
	{
    if (m_Head == m_Tail)
		{
      node->prev = NULL;
    }
    m_Tail = m_Tail->prev;
  }

  if (node->prev)
	{
    node->prev->next = node->next;
  }

  if (node->next)
	{
    node->next->prev = node->prev;
  }

  node->next = node->prev = NULL;

  n--;
}

#endif
