#ifndef __USERDATA_H3D
#define __USERDATA_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

/*----------------------------------------------------------------------
CLASS
	vrUserData

	A standin class used for adding user defined data to vrNodes.

DESCRIPTION
	<ul>
	A class that may be used to store user defined data in a vrNode.
	</ul>

NOTES
	<ul>
	<li>vrUserData derived classes should be dynamically allocated by the caller
	of the vrNode::SetUserData function but should not be deleted.  vrUserData
	memory is managed by the vrNode class.  This is the reason for the virtual desctructor.
	<li>Because there is no way to copy the user data, the user data is not
	copied as part of a copy constructor or clone operation for a vrNode.
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrUserData
{
public:
	//<doc>------------------------------------------------------------
	// <dd>Default constructor.
	//
  vrUserData(void)
		{ };

	//<doc>------------------------------------------------------------
	// <dd>Virtual destructor.
	//
	virtual     ~vrUserData(void)
		{ };
};

class vrUserDataItem
{
	vrUserData *m_Data;
	SFString    m_ID;
	// private constructors to avoid unwanted copying.
	vrUserDataItem(void)
		{ m_Data = NULL; m_ID = nullString; };
	vrUserDataItem(const vrUserDataItem& data)
		{ };
public:
	vrUserDataItem(const SFString& id, vrUserData *data);
	~vrUserDataItem();

	friend class vrUserDataList;
	friend class vrNode;
};

class vrUserDataList : public vrList<vrUserDataItem*>
{
public:
	~vrUserDataList(void);
	vrUserDataItem *FindItem(const SFString& id);
};

#endif
