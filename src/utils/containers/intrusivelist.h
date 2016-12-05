#ifndef __INTRUSIVELIST_H3D
#define __INTRUSIVELIST_H3D
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
	vrIntrusiveList

	Type-safe templated doubly linked list.

DESCRIPTION
	<ul>
	This class requires that items added to it already posses a 
	next and previous pointer (thus the name Intrusive).  It is modelled
	heavily after the MFC class CList and behaves in much the same way.
	</ul>

NOTES
	<ul>
	<li>This is a templated class.  Data added to a list of this
		type must contain two data items of type TYPE called next and prev
		or be derived from the vrIntrusiveListNode object.</li>
	<li>This class does not own the memory representing the items added to
	the list.  The caller must allocate and de-allocate this memory.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// A simple linked list.  Items added to the vrIntrusiveList must
	// possess next and prev pointers.
	class A
	{
	public:
		A *next;
		A *prev;
		int data;
		A(int d) { data = d; }
	};

	vrIntrusiveList<A*> Alist;
	Alist.AddTail(new A(1));
	Alist.AddTail(new A(2));
	Alist.AddTail(new A(3));

	LISTPOS pos = Alist.GetHeadPosition();
	while (pos)
	{
		A *a = Alist.GetNext(pos);
		printf("%d ", a->data);
	}
	printf("\n");

	// OUTPUT
	// 1 2 3
	</pre>

MEMBERS
----------------------------------------------------------------------*/
template<class TYPE>
class vrIntrusiveList
{
protected:
  vrIntrusiveList(const vrIntrusiveList& l) {}
  vrIntrusiveList& operator=(const vrIntrusiveList& l) { return *this; }

  SFInt32            nextIndex;

protected:
  //<doc>------------------------------------------------------------
  // <dd>Number of items in the list.
	// [default:] NULL
	//
  SFInt32         n;

  //<doc>------------------------------------------------------------
  // <dd>The head of the list.
	// [default:] NULL
	//
  TYPE             m_Head;

  //<doc>------------------------------------------------------------
  // <dd>The tail of the list.
	// [default:] NULL
	//
  TYPE             m_Tail;

public:
  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	vrIntrusiveList     (void);

  //<doc>------------------------------------------------------------
  // <dd>Destructor.
	//
	~vrIntrusiveList     (void)                     { }

  //<doc>------------------------------------------------------------
  // <dd>Add an item to the tail of the list.
	//
  void             AddTail         (TYPE);

  //<doc>------------------------------------------------------------
  // <dd>Add an item to the head of the list.
	//
  void             AddHead         (TYPE);

  //<doc>------------------------------------------------------------
  // <dd>Return the number of items in the list.
	//
  SFInt32           GetCount        (void)               const {  return n;    }

  //<doc>------------------------------------------------------------
  // <dd>Return the head of the list.
	//
  TYPE             GetHead         (void)               const {  return m_Head; }

  //<doc>------------------------------------------------------------
  // <dd>Return the tail of the list.
	//
  TYPE             GetTail         (void)               const {  return m_Tail; }

  //<doc>------------------------------------------------------------
  // <dd>Return the next item (as represented with the rPosition iterator).
	//
	TYPE             GetNext         (LISTPOS& rPosition) const;

  //<doc>------------------------------------------------------------
  // <dd>Return the previous item (as represented with the rPosition iterator).
	//
	TYPE             GetPrev         (LISTPOS& rPosition) const;

  //<doc>------------------------------------------------------------
  // <dd>Return an iteration handle representing the head of the list.
	//
	LISTPOS          GetHeadPosition (void)               const {  return (LISTPOS)GetHead(); }

  //<doc>------------------------------------------------------------
  // <dd>Return an iteration handle representing the tail of the list.
	//
	LISTPOS          GetTailPosition (void)               const {  return (LISTPOS)GetTail(); }

  //<doc>------------------------------------------------------------
  // <dd>Remove the given item from the list.
	//
  void             RemoveAt        (TYPE);

  //<doc>------------------------------------------------------------
  // <dd>Remove all items from the list.
	//
  void             RemoveAll       (void);

  //<doc>------------------------------------------------------------
  // <dd>Generate the next index for the item being added to the list.
	//
  SFInt32           NextIndex       (void)                     {  nextIndex++;  return nextIndex-1;  }

  //<doc>------------------------------------------------------------
  // <dd>Reset the next index generator.
	//
  void             SetNextIndex    (SFInt32 i);

	friend class vrSolid;
};

//---------------------------------------------------------------------
template<class TYPE>
vrIntrusiveList<TYPE>::vrIntrusiveList<TYPE>(void)
{
	m_Head      = (TYPE)NULL;
	m_Tail      = (TYPE)NULL;
	n         = 0; 
	nextIndex = 0; 
}

//---------------------------------------------------------------------
template<class TYPE>
inline void vrIntrusiveList<TYPE>::AddHead(TYPE node)
{
  ASSERT(node);
  ASSERT(!m_Head || m_Head->prev == NULL);
  ASSERT(!m_Tail || m_Tail->next == NULL);

  node->next = m_Head;
  node->prev = NULL;

  if (!m_Head)
	{
    ASSERT(!m_Tail);
    m_Head = m_Tail = node;
  } else
	{
    ASSERT(m_Tail);
    m_Head->prev = node;
    m_Head = node;
  }

  n++;
}

//---------------------------------------------------------------------
template<class TYPE>
inline void vrIntrusiveList<TYPE>::AddTail(TYPE node)
{
  ASSERT(node);
  ASSERT(!m_Head || m_Head->prev == NULL);
  ASSERT(!m_Tail || m_Tail->next == NULL);

  node->next = NULL;
  node->prev = m_Tail;

  if (!m_Head)
	{
    ASSERT(!m_Tail);
    m_Head = m_Tail = node;
  } else
	{
    ASSERT(m_Tail);
    m_Tail->next = node;
    m_Tail = node;
  }

  n++;
}

//---------------------------------------------------------------------
template<class TYPE>
inline TYPE vrIntrusiveList<TYPE>::GetNext(LISTPOS& pos) const
{
	TYPE node = (TYPE)pos;
	ASSERT(node);
	pos = (LISTPOS)((node->next!=m_Head) ? node->next : NULL);

	return node;
}

template<class TYPE>
inline TYPE vrIntrusiveList<TYPE>::GetPrev(LISTPOS& pos) const
{
	TYPE node = (TYPE)pos;
	ASSERT(node);
	pos = (LISTPOS)((node->prev!=m_Tail) ? node->prev : NULL);

	return node;
}

//---------------------------------------------------------------------
template<class TYPE>
void vrIntrusiveList<TYPE>::RemoveAll(void)
{ 
	// User must delete data
	m_Head      = (TYPE)NULL;
	m_Tail      = (TYPE)NULL;
	n         = 0; 
	nextIndex = 0; 
}

template<class TYPE>
inline void vrIntrusiveList<TYPE>::RemoveAt(TYPE node)
{
  ASSERT(node);
  ASSERT(!m_Head || m_Head->prev == NULL);
  ASSERT(!m_Tail || m_Tail->next == NULL);

  if (!m_Head)
	{
    ASSERT(!m_Tail);
    node->next = NULL;
		node->prev = NULL;
    return;
  }
  ASSERT(m_Tail);

  if (m_Head == node)
	{
    m_Head = m_Head->next;
  }

  if (m_Tail == node)
	{
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

  node->next = NULL;
	node->prev = NULL;

  n--;
}

template<class TYPE>
inline void vrIntrusiveList<TYPE>::SetNextIndex(SFInt32 i)
{ 
  nextIndex = i;
}

/*********************************************************************/
//-------------------------------------------------------------------------------------
template <class TYPE>
class vrIntrusiveListNode
{
public:
private:
  vrIntrusiveListNode(const vrIntrusiveListNode& l) {}
  vrIntrusiveListNode& operator=(const vrIntrusiveListNode& l) { return *this; }

public:
  TYPE next;
  TYPE prev;

	      vrIntrusiveListNode (void)  { next = prev = NULL; }
	     ~vrIntrusiveListNode (void)  { }

  TYPE  Next            (void) const { return next; }
  TYPE  Prev            (void) const { return prev; }
};

#include "RingList.h"

#endif
