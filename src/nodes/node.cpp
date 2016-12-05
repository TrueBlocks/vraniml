//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Node.h"
#include "Browser\Route.h"
#include "Browser\Browser.h"
#include "Nodes\Appearance\Material.h"
#include "Windows.h"

IMPLEMENT_NODE(vrNode, vrBaseNode);

//--------------------------------------------------------------------
vrNode::vrNode(void)
{
//	m_Name      = NULL;
	m_NodeType    = normalNode;
	m_RouteList   = NULL;
	m_UserDataList = NULL;
	// m_IsMaps = [] // array
	m_ProtoGroup  = nullString;
}

vrNode::vrNode(const vrNode& ob)
{
	m_Name         = ob.m_Name;
	m_NodeType     = ob.m_NodeType;
	m_RouteList    = NULL;
	m_UserDataList = NULL;
	m_IsMaps       = ob.m_IsMaps;
	m_ProtoGroup   = ob.m_ProtoGroup;
	// user data is not copied becuase no way to know how to copy it
	ASSERT(m_UserDataList==NULL);
}

void vrNode::Clear()
{
	m_Name.Clear();
	m_IsMaps.Clear();
	if (m_RouteList)
	{
		LISTPOS ppos = m_RouteList->GetHeadPosition();
		while (ppos)
		{
			vrRoute *route = m_RouteList->GetNext(ppos);
			delete route;
		}
		ASSERT(!m_RouteList); // will have been deleted when last route disapears
	}
	if (m_UserDataList)
		delete m_UserDataList;
	m_UserDataList = NULL;
}

vrNode::~vrNode(void)
{
	Clear();
}

vrNode& vrNode::operator=(const vrNode& ob)
{
	Clear();

	m_Name         = ob.m_Name;
	m_NodeType     = ob.m_NodeType;
	m_RouteList    = NULL;
	m_UserDataList = NULL;
	m_IsMaps       = ob.m_IsMaps;
	m_ProtoGroup   = ob.m_ProtoGroup;
	// user data is not copied becuase no way to know how to copy it
	ASSERT(m_UserDataList==NULL);

	return *this;
}

SFNode vrNode::Clone(void) const
{
	return new vrNode(*this);
}

SFBool vrNode::ForEvery(PFBO3V userFn, void *userData, PFBO3V afterFn)
{
	return userFn(this, userData);
}

//--------------------------------------------------------------------
SFNode vrNode::FindByName(const SFString& nodeName) const
{
	if (m_Name == nodeName)
		return ((SFNode)this);
	return NULL;
}

SFNode vrNode::FindByType(vrRuntimeClass *pClass) const
{
	if (IsKindOf(pClass))
		return ((SFNode)this);	
	return NULL;
}

//--------------------------------------------------------------------
vrBoundingBox vrNode::GetBoundingBox(void) const
{
/*
	if (m_Children)
	{
		vrMatrix mat;
		if (GetParent())
		{
			mat = GetParent()->GetLocalMatrix();
		}
		LISTPOS pos = m_Children->GetHeadPosition();
		while (pos)
		{
			SFNode ob = m_Children->GetNext(pos);
			vrBoundingBox child = ob->GetBoundingBox();
			if (!child.IsDefault())
			{
				child = TransformBox(child, mat);
				((SFNode)this)->m_Bounds.Include(child);
			}
		}
	}
*/
	return m_Bounds;
}

//vrDumpContext dc;

//class BoundsData
//{
//public:
//	int tos;
//	vrMatrix mat[100];
//	vrBoundingBox box;
//};

//SFBool CalcBox(SFNode node, void *data)
//{
/*
	BoundsData *bd = (BoundsData *)data;
	node->m_Bounds = node->GetBoundingBox();
	vrBoundingBox box = TransformBox(box, );
	bd->box.Include(node->box);
*/
//	return TRUE;
//}

//SFBool AfterFunc(SFNode node, void *data)
//{
//	return TRUE;
//}

vrBoundingBox vrNode::CalcBoxes(vrMatrix& matrix)
{
//	BoundsData data;
	//data.matStack.Push(&matrix);
	
//	ForEvery(CalcBox, &data, AfterFunc);
//	return data.box;
	return vrBoundingBox();

#if 0
/*
	dc << "Name: " << m_Name << " matrix: " << matrix << "\n";
	
	vrBoundingBox bb;
	if (m_Children)
	{
		dc << "has children\n";

		LISTPOS pos = m_Children->GetHeadPosition();
		while (pos)
		{
			SFNode ob = m_Children->GetNext(pos);
			vrMatrix p = matrix;
			matrix *= ob->GetLocalMatrix();
	dc << "new matrix: " << matrix << "\n";
			vrBoundingBox childBox = ob->CalcBoxes(matrix);
			matrix = p;
			if (!childBox.IsDefault())
			{
				bb.Include(childBox);
			}
	dc	<< "  ChildBox: " << childBox.GetMin() << "  " << childBox.GetMax() << "\n";
	dc	<< "  bb: " << bb.GetMin() << "  " << bb.GetMax() << "\n";
		}
		m_Bounds = bb;
	} else
	{
		vrBoundingBox box = GetBoundingBox();
	dc	<< "  untrans: " << box.GetMin() << "  " << box.GetMax() << "\n";
		box = TransformBox(box, matrix);
	dc	<< "  trans: " << box.GetMin() << "  " << box.GetMax() << "\n";
		return box;
	}
	dc 
		<< "Name: " 
		<< m_Name 
		<< "  Box: " 
		<< box.GetMin() << "  " << box.GetMax()
		<< "\n";
	return m_Bounds; //TransformBox(box, GetLocalMatrix());
*/
#endif
}

void vrNode::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}

SFBool IsValidName(const SFString& name)
{
	if (name.Empty())
		return TRUE;
	
	SFString copy = name;
	char *s = copy.GetBuffer();
	while (*s)
	{
		if ((int)*s < 0x21)
		{
			return FALSE;
		}
		// Invalid chars in body of name
		switch (*s)
		{
		case '\"': case '\'': case '#': 
		case ',': case '.': case '[': case ']':
		case '\\': case '{': case '}': 
			return FALSE;
		}
		if (s == name)
		{
			// Invalid first char of name
			switch (*s)
			{
			case '0': case '1': case '2': 
			case '3': case '4': case '5': 
			case '6': case '7': case '8': 
			case '9': case '+': case '-':
				return FALSE;
			}
		}
		s++;
	}

	// Reserved keywords
	if (name == "DEF")          return FALSE;
	if (name == "EXTERNPROTO")  return FALSE;
	if (name == "FALSE")        return FALSE;
	if (name == "IS")           return FALSE;
	if (name == "NULL")         return FALSE;
	if (name == "PROTO")        return FALSE;
	if (name == "ROUTE")        return FALSE;
	if (name == "TO")           return FALSE;
	if (name == "TRUE")         return FALSE;
	if (name == "USE")          return FALSE;
	if (name == "eventIn")      return FALSE;
	if (name == "eventOut")     return FALSE;
	if (name == "exposedField") return FALSE;
	if (name == "field")        return FALSE;

	return TRUE;
}

void vrNode::SetName(const SFString& name)
{
	// Warn developer
	ASSERT(IsValidName(name));
	
	// Only change if it's a valid name
	if (IsValidName(name))
		m_Name = name;
}

void vrNode::AddRoute(vrRoute *route)
{
	if (!m_RouteList)
		m_RouteList = new vrRouteList;
	m_RouteList->AddTail(route);
}

vrRouteList *vrNode::GetRouteList(void) const
{
	return m_RouteList;
}

void vrNode::RemoveRoute(vrRoute *route)
{
	if (!m_RouteList || !route)
		return;

	LISTPOS pos = m_RouteList->GetHeadPosition();
	while (pos)
	{
		LISTPOS prev = pos;
		vrRoute *r = m_RouteList->GetNext(pos);
		if (route == r)
		{
			m_RouteList->RemoveAt(prev);
		}
	}

	// count em and remove route list if empty
	int cnt=0;
	pos = m_RouteList->GetHeadPosition();
	while (pos)
	{
		m_RouteList->GetNext(pos);
		cnt++;
	}

	if (!cnt)
	{
		m_RouteList->RemoveAll();
		delete m_RouteList;
		m_RouteList = NULL;
	}
}

vrRoute *vrNode::AddRoute(const SFString& srcTypeStr, SFNode dst, const SFString& dstTypeStr, SFBool internal)
{
	SFInt32 srcType = GetEventOutID(srcTypeStr);
	if (!internal && srcType == 0)
		return NULL;

	SFInt32 dstType = dst->GetEventInID(dstTypeStr);
	if (!internal && dstType == 0)
		return NULL;

	return AddRoute(srcType, dst, dstType, internal);
}

vrRoute *vrNode::AddRoute(SFInt32 srcType, SFNode dst, SFInt32 dstType, SFBool internal)
{
	ASSERT(dst);
	ASSERT(internal || !GetName().Empty());
	ASSERT(internal || !dst->GetName().Empty());

	vrRoute *route = new vrRoute(this, srcType, dst, dstType, internal);
	if (route->IsValid())
	{
		AddRoute(route);
	} else
	{
		// Bad Route
		delete route;
		route = NULL;
	}

	return route;
}

void vrNode::SendEventOut(SFInt32 eventID, void *data)
{
	if (HasRoutes())
	{
		LISTPOS pos = GetRouteList()->GetHeadPosition();
		while (pos)
		{
			vrRoute *route = GetRouteList()->GetNext(pos);
			if (route->m_SrcFieldID == eventID)
			{
				vrEvent event(route->m_Destination, route->m_DstFieldID, data);
				route->m_Destination->ReceiveEventIn(&event);
			}
		}
	}
}

vrRoute *vrNode::FindRoute(const SFString& srcField, SFNode dstNode, const SFString& dstField) const
{
	if (!HasRoutes() || !dstNode)
		return NULL;

	vrRouteList *list = GetRouteList();
	ASSERT(list);

	LISTPOS pos = list->GetHeadPosition();
	while (pos)
	{
		vrRoute *route = list->GetNext(pos);

		SFInt32 id1 = GetEventInID(srcField);
		SFInt32 id2 = GetEventOutID(dstField);

		if ((route->m_Destination == dstNode) &&
				(route->m_SrcFieldID == id1) &&
				(route->m_DstFieldID == id2))
		{
			return route;
		}
	}	
	return NULL;
}

vrUserData *vrNode::GetUserData(const SFString& id) const
{
	if (m_UserDataList)
	{
		vrUserDataItem *item = m_UserDataList->FindItem(id);
		if (item)
			return item->m_Data;
	}
	return NULL;
}

void vrNode::SetUserData(const SFString& id, vrUserData *data)
{
	// Create it if it does not already exist.
	if (!m_UserDataList)
		m_UserDataList = new vrUserDataList;

	ASSERT(m_UserDataList);
	
	// Look for the current id
	vrUserDataItem *item = m_UserDataList->FindItem(id);
	if (item)
	{
		// if found replace data after deletion.
		if (item->m_Data)
			delete item->m_Data;
		item->m_Data = data;
	} else
	{
		// else create it.
		item = new vrUserDataItem(id, data);
		m_UserDataList->AddTail(item);
	}
}

SFBool vrNode::IsIsMapped(const SFString& fieldName) const
{
	for (int i=0;i<m_IsMaps.GetCount();i++)
	{
		SFInt32 find = m_IsMaps[i].Find(" IS");
		ASSERT(find!=-1);
		SFString fieldNm = m_IsMaps[i].Left(find);
		if (fieldNm == fieldName)
			return TRUE;
	}
	return FALSE;
}

SFString vrNode::GetName(void) const
{
	return m_Name;
}

