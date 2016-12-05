#ifndef __NONINTRUSIVELIST_H3D
#define __NONINTRUSIVELIST_H3D
//-------------------------------------------------------------------------
//	Copyright (c) 1997-1998 Great Hill Corporation
//	All Rights Reserved.
//
//  For conditions of distribution and use of this software,
//  please see copyright notice in utility.h
//-------------------------------------------------------------------------

struct xLISTPOS__ { int unused; };
typedef xLISTPOS__* LISTPOS;

/*----------------------------------------------------------------------
CLASS
	vrListNode

	A wrapper class for items added to a vrList.

DESCRIPTION
	<ul>
	This class contains the next and previous pointers that allow us
	to add items to a vrList without requiring any modifications
	to the object added (that is a non-intrusive list).
	</ul>

NOTES
	<ul>
	<li>You will probably not use this class directly.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
template<class TYPE>
class vrListNode
{
private:
	// Don't allow default construction, copy construction or assignment
	vrListNode(void) {}
	vrListNode(const vrListNode& node) {}
	vrListNode& operator=(const vrListNode& node) { return *this; }

public:
  //<doc>------------------------------------------------------------
  // <dd>Pointer to the next item in the linked list.
	// [default:] NULL
	//
	vrListNode *m_Next;

  //<doc>------------------------------------------------------------
  // <dd>Pointer to the previous item in the linked list.
	// [default:] NULL
	//
	vrListNode *m_Prev;

  //<doc>------------------------------------------------------------
  // <dd>Pointer to the data being stored at this node.
	// [default:] NULL
	//
	TYPE m_Data;

  //<doc>------------------------------------------------------------
  // <dd>Constructor.
	//
	vrListNode(TYPE d)
		{ 
			m_Next = NULL;
			m_Prev = NULL; 
			m_Data = d;
		}

  //<doc>------------------------------------------------------------
  // <dd>Destructor.
	//
 ~vrListNode(void)
		{
			m_Next = NULL;
			m_Prev = NULL; 
		}

  //<doc>------------------------------------------------------------
  // <dd>Returns the next pointer.
	//
	vrListNode *Next (void) const
		{ return m_Next; }

  //<doc>------------------------------------------------------------
  // <dd>Returns the prev pointer.
	//
	vrListNode *Prev (void) const
		{ return m_Prev; }
};

/*----------------------------------------------------------------------
CLASS
	vrList

	A type-safe templated doubly linked list.

DESCRIPTION
	<ul>
	A doubly linked list that requires nothing (i.e. is NonIntrusive)
	of the nodes that are inserted in it.  This class is modelled
	very much after the MFC class CList and behaves in much the same way.
	</ul>

NOTES
	<ul>
	<li>The list itself does not own any of the memory for the object being stored.
	The caller must allocate and delete the memory for the stored object.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// This is just a basic linked list class:
	vrList&lt;SFInt32&gt; intList;

	intList.AddTail(1);
	intList.AddTail(2);
	intList.AddTail(3);

	// Iteration is accomplished identically to the MFC.
	LISTPOS pos = intList.GetHeadPosition();
	while (pos)
	{
		SFInt32 i = intList.GetNext(pos);
		printf("%d ", i);
	}
	printf("\n");

	// OUTPUT: 1 2 3
	</pre>

MEMBERS
----------------------------------------------------------------------*/
template<class TYPE>
class vrList
{
protected:
  //<doc>------------------------------------------------------------
  // <dd>Number of items in the list.
	// [default:] 0
	//
  long              m_Count;

  //<doc>------------------------------------------------------------
  // <dd>The head of the linked list.
	// [default:] NULL
	//
  vrListNode<TYPE> *m_Head;

  //<doc>------------------------------------------------------------
  // <dd>The tail of the linked list.
	// [default:] NULL
	//
  vrListNode<TYPE> *m_Tail;

public:
  //<doc>------------------------------------------------------------
  // <dd>Default constructor.
	//
	vrList (void);

  //<doc>------------------------------------------------------------
  // <dd>Copy constructor.
	//
	vrList (const vrList& l);

  //<doc>------------------------------------------------------------
  // <dd>Destructor.
	//
	~vrList (void);

  //<doc>------------------------------------------------------------
  // <dd>Equals operator.
	//
	vrList& operator= (const vrList& l);

  //<doc>------------------------------------------------------------
  // <dd>Returns the number of items in the list.
	//
  long           GetCount        (void)               const
		{ return m_Count; }

  //<doc>------------------------------------------------------------
  // <dd>Returns the head of the list.
	//
  TYPE           GetHead         (void)               const
		{ return (TYPE)(m_Head->m_Data); }

  //<doc>------------------------------------------------------------
  // <dd>Returns the tail of the list.
	//
  TYPE           GetTail         (void)               const
		{ return (TYPE)(m_Tail->m_Data); }

  //<doc>------------------------------------------------------------
  // <dd>Returns the next item in the iteration represented by rPosition.
	//
	// [in] rPosition: reference to the LISTPOS used for iteration.
	//
	TYPE           GetNext         (LISTPOS& rPosition) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns the previous item in the iteration represented by rPosition.
	//
	// [in] rPosition: reference to the LISTPOS used for iteration.
	//
	TYPE           GetPrev         (LISTPOS& rPosition) const;

  //<doc>------------------------------------------------------------
  // <dd>Returns an iteration handle representing the head of the list.
	//
	LISTPOS        GetHeadPosition (void)               const
		{ return (LISTPOS)m_Head; }

  //<doc>------------------------------------------------------------
  // <dd>Returns an iteration handle representing the tail of the list.
	//
	LISTPOS        GetTailPosition (void)               const
		{ return (LISTPOS)m_Tail; }

  //<doc>------------------------------------------------------------
  // <dd>Find the given item in the list.
	//
	// [in] item: The item to find.
	//
	TYPE           FindAt          (TYPE item)          const;

  //<doc>------------------------------------------------------------
  // <dd>Find the given item in the list by iteration handle.
	//
	// [in] pos: LISTPOS used for iteration or searching.
	//
	TYPE           FindAt          (LISTPOS pos)        const;

  //<doc>------------------------------------------------------------
  // <dd>Same as FindAt but returns a LISTPOS.
	//
	// [in] item: The item to find.
	//
	LISTPOS        Find            (TYPE item)          const;

  //<doc>------------------------------------------------------------
  // <dd>Return TRUE if the list is empty.
	//
	SFBool         Empty           (void)               const
		{ return (m_Head==NULL); }

  //<doc>------------------------------------------------------------
  // <dd>Add an object to the list at the tail.
	//
	// [in] item: The item to add.
	//
  void           AddToList       (TYPE item)
		{ AddTail(item); }

  //<doc>------------------------------------------------------------
  // <dd>Add a list of objects to the list at the tail.
	//
	// [in] l: List of items to add.
	//
  void           AddToList       (const vrList& l);

  //<doc>------------------------------------------------------------
  // <dd>Add an object to the list at the tail.
	//
	// [in] item: The item to add.
	//
  void           AddTail         (TYPE item);

  //<doc>------------------------------------------------------------
  // <dd>Add an object to the list at the head.
	//
	// [in] item: The item to add.
	//
  void           AddHead         (TYPE item);

  //<doc>------------------------------------------------------------
  // <dd>Remove an object from the list given its position.
	//
	// [in] pos: LISTPOS of item to remove.
	//
  TYPE           RemoveAt        (LISTPOS pos);

  //<doc>------------------------------------------------------------
  // <dd>Remove all objects from the list.
	//
  void           RemoveAll       (void);

  //<doc>------------------------------------------------------------
  // <dd>Remove the head of the list.
	//
  TYPE           RemoveHead      (void);

  //<doc>------------------------------------------------------------
  // <dd>Remove the tail of the list.
	//
  TYPE           RemoveTail      (void);
};

//---------------------------------------------------------------------
template<class TYPE>
inline vrList<TYPE>::vrList(void)
{
	m_Head  = NULL;
	m_Tail  = NULL;
	m_Count = 0; 
}

template<class TYPE>
vrList<TYPE>::vrList(const vrList<TYPE>& l)
{
	m_Head  = NULL;
	m_Tail  = NULL;
	m_Count = 0; 

	LISTPOS pos = l.GetHeadPosition();
	while (pos)
	{
		TYPE ob = l.GetNext(pos);
		AddTail(ob);
	}
}

template<class TYPE>
inline vrList<TYPE>::~vrList(void)
{
	RemoveAll();
}

template<class TYPE>
vrList<TYPE>& vrList<TYPE>::operator=(const vrList<TYPE>& l)
{
	RemoveAll();
	
	LISTPOS pos = l.GetHeadPosition();
	while (pos)
	{
		TYPE ob = l.GetNext(pos);
		AddTail(ob);
	}
  return *this;
}

//---------------------------------------------------------------------
template<class TYPE>
TYPE vrList<TYPE>::FindAt(TYPE probe) const
{
	LISTPOS pos = GetHeadPosition();
	while (pos)
	{
		TYPE ob = GetNext(pos);
		if (ob == probe)
			return ob;
	}
	return NULL;
}

template<class TYPE>
TYPE vrList<TYPE>::FindAt(LISTPOS probe) const
{
	LISTPOS pos = GetHeadPosition();
	while (pos)
	{
		LISTPOS prev = pos;
		TYPE ob = GetNext(pos);
		if (prev == probe)
			return ob;
	}
	return NULL;
}

template<class TYPE>
LISTPOS vrList<TYPE>::Find(TYPE probe) const
{
	LISTPOS pos = GetHeadPosition();
	while (pos)
	{
		LISTPOS last = pos;
		TYPE ob = GetNext(pos);
		if (ob == probe)
			return last;
	}
	return NULL;
}

//---------------------------------------------------------------------
template<class TYPE>
inline void vrList<TYPE>::AddHead(TYPE data)
{
	vrListNode<TYPE> *node = new vrListNode<TYPE>(data);
	
	ASSERT(node);
  ASSERT(!m_Head || m_Head->m_Prev == NULL);
  ASSERT(!m_Tail || m_Tail->m_Next == NULL);

  node->m_Next = m_Head;
  node->m_Prev = NULL;

  if (!m_Head)
	{
    ASSERT(!m_Tail);
    m_Head = m_Tail = node;
  } else
	{
    ASSERT(m_Tail);
    m_Head->m_Prev = node;
    m_Head = node;
  }

  m_Count++;
}

//---------------------------------------------------------------------
template<class TYPE>
inline void vrList<TYPE>::AddTail(TYPE data)
{
  vrListNode<TYPE> *node = new vrListNode<TYPE>(data);

  ASSERT(node);
  ASSERT(!m_Head || m_Head->m_Prev == NULL);
  ASSERT(!m_Tail || m_Tail->m_Next == NULL);

  node->m_Next = NULL;
  node->m_Prev = m_Tail;

  if (!m_Head)
	{
    ASSERT(!m_Tail);
    m_Head = m_Tail = node;
  } else
	{
    ASSERT(m_Tail);
    m_Tail->m_Next = node;
    m_Tail = node;
  }

  m_Count++;
}

template<class TYPE> 
void vrList<TYPE>::AddToList(const vrList<TYPE>& l)
{
	LISTPOS pos = l.GetHeadPosition();
	while (pos)
	{
		TYPE ob = l.GetNext(pos);
		AddToList(ob);
	}
}

//---------------------------------------------------------------------
template<class TYPE>
inline TYPE vrList<TYPE>::GetNext(LISTPOS& pos) const
{
	vrListNode<TYPE> *node = (vrListNode<TYPE> *)pos;
	ASSERT(node);
	pos = (LISTPOS)((node->m_Next!=m_Head) ? node->m_Next : NULL);

	return (TYPE)(node->m_Data);
}

template<class TYPE>
inline TYPE vrList<TYPE>::GetPrev(LISTPOS& pos) const
{
	vrListNode<TYPE> *node = (vrListNode<TYPE> *)pos;
	ASSERT(node);
	pos = (LISTPOS)((node->m_Prev!=m_Tail) ? node->m_Prev : NULL);

	return (TYPE)(node->m_Data);
}

//---------------------------------------------------------------------
template<class TYPE>
inline void vrList<TYPE>::RemoveAll(void)
{ 
	vrListNode<TYPE> *node = m_Head;
	while (node)
	{
		vrListNode<TYPE> *n = ((node->m_Next!=m_Head) ? node->m_Next : NULL);
		if (node == m_Head)
			m_Head = NULL;
		delete node;
		node = n;
	}
	m_Head      = NULL;
	m_Tail      = NULL;
	m_Count     = 0; 
}

template<class TYPE>
inline TYPE vrList<TYPE>::RemoveAt(LISTPOS pos)
{
	vrListNode<TYPE> *node = (vrListNode<TYPE> *)pos;

  ASSERT(node);
  ASSERT(!m_Head || m_Head->m_Prev == NULL);
  ASSERT(!m_Tail || m_Tail->m_Next == NULL);

  TYPE data = (TYPE)(node->m_Data);
	
	if (!m_Head)
	{
    ASSERT(!m_Tail);
		delete node;
    return data;
  }
  ASSERT(m_Tail);

  if (m_Head == node)
    m_Head = m_Head->m_Next;

  if (m_Tail == node)
    m_Tail = m_Tail->m_Prev;

  if (node->m_Prev)
    node->m_Prev->m_Next = node->m_Next;

  if (node->m_Next)
    node->m_Next->m_Prev = node->m_Prev;

  m_Count--;

	delete node;

	return data;
}

// stack use
template<class TYPE>
inline TYPE vrList<TYPE>::RemoveHead(void)
{
	return RemoveAt((LISTPOS)m_Head);
};

// queue use
template<class TYPE>
inline TYPE vrList<TYPE>::RemoveTail(void)
{
	return RemoveAt((LISTPOS)m_Tail);
};

/*----------------------------------------------------------------------
CLASS
	vrRefCountList

	A type-safe templated doubly linked list that reference counts
	objects added to it.

DESCRIPTION
	<ul>
	A doubly linked list that reference counts objects added to it.
	Either the added objects should be derived from the vrBaseNode class
	(such as all the VRML nodes) or implement the Reference and
	Dereference interfaces.
	</ul>

NOTES
	<ul>
	<li>The list itself does not own any of the memory for the object being stored.
	The caller must allocate and delete the memory for the stored object.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// This is just a basic linked list class for reference counted objects:
	vrRefCountList&lt;SFNode&gt; nodeList;

	nodeList.AddTail(new vrCone);
	nodeList.AddTail(new vrCylinder);
	nodeList.AddTail(new vrBox);

	// Iteration is accomplished identically to the MFC.
	LISTPOS pos = nodeList.GetHeadPosition();
	while (pos)
	{
		SFNode node = nodeList.GetNext(pos);
		// apply an operation to the node
		ApplyOperation(node);
	}

	// To cleanup the list use the vrDELETE macro:
	pos = nodeList.GetHeadPosition();
	while (pos)
	{
		vrBaseNode *node = nodeList.GetNext(pos);
		vrDELETE(node);
	}
	nodeList.RemoveAll();
	</pre>

MEMBERS
----------------------------------------------------------------------*/
template<class TYPE>
class vrRefCountList :
	public vrList < TYPE >
{
public:
  //<doc>------------------------------------------------------------
  // <dd>Add an object to the list at the tail and reference count.
	//
	// [in] item: The item to add.
	//
  void           AddTail         (TYPE item);

  //<doc>------------------------------------------------------------
  // <dd>Add an object to the list at the head.
	//
	// [in] item: The item to add.
	//
  void           AddHead         (TYPE item);

  //<doc>------------------------------------------------------------
  // <dd>Remove an object from the list given its position.
	//
	// [in] pos: LISTPOS of item to remove.
	//
  TYPE           RemoveAt        (LISTPOS pos);

  //<doc>------------------------------------------------------------
  // <dd>Remove the head of the list.
	//
  TYPE           RemoveHead      (void);

  //<doc>------------------------------------------------------------
  // <dd>Remove the tail of the list.
	//
  TYPE           RemoveTail      (void);
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
template<class TYPE>
inline void vrRefCountList<TYPE>::AddHead(TYPE data)
{
	vrList<TYPE>::AddHead(data);
	if (data)
		data->Reference();
}

//---------------------------------------------------------------------
template<class TYPE>
inline void vrRefCountList<TYPE>::AddTail(TYPE data)
{
  vrList<TYPE>::AddTail(data);
	if (data)
		data->Reference();
}

template<class TYPE>
inline TYPE vrRefCountList<TYPE>::RemoveAt(LISTPOS pos)
{
	TYPE data = vrList<TYPE>::RemoveAt(pos);
	if (data)
		data->Dereference();
	return data;
}

// stack use
template<class TYPE>
inline TYPE vrRefCountList<TYPE>::RemoveHead(void)
{
	return RemoveAt((LISTPOS)m_Head);
};

// queue use
template<class TYPE>
inline TYPE vrRefCountList<TYPE>::RemoveTail(void)
{
	return RemoveAt((LISTPOS)m_Tail);
};

#endif
