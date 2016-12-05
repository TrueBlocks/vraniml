#include "Kramer.h"

#include "Nodes/AllNodes.h"

#include "Parser.h"

class Mapper
{
public:
	const vrNode *proto;
//	Mapper(vrNode *p, const SFString& to)
//		{ proto = p; toField = to; node=NULL; fromField=nullString; }
	Mapper(const vrNode *pro, const SFString& to)
		{ proto = pro; toField = to; node=NULL; fromField=nullString; }
	vrNode   *node;
	SFString fromField;
	SFString toField;
};

SFBool FindMappedField(vrNode *node, void *data);
class vrProtoGroup : public vrGroupingNode
{
	vrProtoGroup() {}
public:
	SFBool isExtern;
	SFBool isResolvedExtern;
	MFString externName;
	vrRuntimeClass *pClass;
	vrProtoGroup(vrRuntimeClass *pC)
		{
			isResolvedExtern = FALSE;
			isExtern = FALSE;
			pClass = pC;
			pClass->Reference();
			m_NodeType = vrNode::protoGroup;
		}
	~vrProtoGroup()
		{
			vrDELETE(pClass);
		}
	vrProtoGroup(const vrProtoGroup& grp) : vrGroupingNode(grp)
		{
			isResolvedExtern = grp.isResolvedExtern;
			isExtern = grp.isExtern;
			externName = grp.externName;
			pClass = grp.pClass;
			pClass->Reference();
			m_NodeType = grp.m_NodeType;
		}
	vrNode *Clone(void) const { return new vrProtoGroup(*this); }
	vrRuntimeClass *GetRuntimeClass() const
		{
			return pClass;
		}
	SFBool IsKindOf(const vrRuntimeClass* pC) const
		{
			if (pC==NULL)
				return TRUE;
			vrRuntimeClass *base = pClass->m_BaseClass;
			pClass->m_BaseClass = GETRUNTIME_CLASS(vrGroupingNode);
			if (vrGroupingNode::IsKindOf(pC))
				return TRUE;
			pClass->m_BaseClass = base;
			SFString thisClass = pClass->ClassName();
			SFString thatClass = pC->ClassName();
			return (thisClass == thatClass);
		}
	virtual SFBool SetFieldValue(const SFString& fieldName, void *val)
		{
			if (isExtern && m_NodeType==protoGroup)
			{
				// should only ever happen once.
				ASSERT(!externName.GetCount());
				externName = *(MFString*)val;
				return TRUE;				
			} else
			{
				if (m_NodeType==protoGroup)
				{
					ASSERT(pClass);
					return pClass->SetFieldValue(fieldName, val);
				} else
				{
					ASSERT(m_NodeType==protoGroupInstance);
					Mapper map(this, fieldName);
					ForEvery(FindMappedField, &map);
					if (map.node)
					{
						ASSERT(map.fromField!=nullString);
						map.node->SetFieldValue(map.fromField, val);
					}
					return TRUE;
				}
			}
			ASSERT(0);
			return FALSE;
		}
	virtual void AddChild(SFNode child);
};

SFBool FindMappedField(vrNode *node, void *data)
{
	Mapper *map = (Mapper *)data;
	if (node->m_IsMaps.GetCount())
	{
		for (int i=0;i<node->m_IsMaps.GetCount();i++)
		{
			SFString testStr = " IS " + map->toField;
			SFString mapStr = node->m_IsMaps[i].Right(testStr.Length());
			if (mapStr.Find(testStr)!=-1)
			{
				SFInt32 stop = node->m_IsMaps[i].Find(" IS ");
				ASSERT(stop != -1);
				SFString newField = node->m_IsMaps[i].Left(stop);
				if (FALSE) //node->IsIsMapped(newField))
				{
					Mapper map1(map->proto, newField);
					((vrProtoGroup*)map->proto)->ForEvery(FindMappedField, &map1);
					map->fromField = newField;
					map->node = map1.node;
				} else
				{
					map->fromField = newField;
					map->node = node;
				}
				return FALSE;
			}
		}
	}
	return TRUE;
}

class IsMapFinder
{
public:
	SFBool grabbed;
	vrField *field;
	vrNode *node;
	IsMapFinder() { grabbed = FALSE; field=NULL; node=NULL; }
};

SFBool FindIsMappedField(IsMapFinder *finder, const vrNode *node, const SFString& fieldName)
{
	ASSERT(node->m_NodeType==vrNode::protoGroupInstance);
	Mapper map(node, fieldName);
	((vrProtoGroup*)node)->ForEvery(FindMappedField, &map);
	if (map.node)
	{
		ASSERT(map.fromField!=nullString);
		vrField *field = map.node->FindField(map.fromField);
		// grab the current value of the queried field
		if (!field->val.boolVal)
		{
			map.node->IsDefault(field->GetName(), field);
			finder->grabbed = TRUE;
			finder->field   = field;
			finder->node    = map.node;
		}
		return TRUE;
	}
	return FALSE;
}

void vrProtoGroup::AddChild(SFNode child)
{
	vrNodeStackItem *ns = GetParser()->nodeStack.Peek();
	if (ns->curNode->m_NodeType==vrNode::protoSFNode)
	{
		LISTPOS pos = GetParser()->nodeStack.GetHeadPosition();
		ASSERT(pos);
#pragma warning(disable:4189)
		vrNodeStackItem *cur = GetParser()->nodeStack.GetNext(pos);
		ASSERT(cur->curField==nullString);
		ASSERT(pos);
		vrNodeStackItem *par = GetParser()->nodeStack.GetNext(pos);
		ASSERT(par->curField!=nullString);
		IsMapFinder finder;
		FindIsMappedField(&finder, par->curNode, par->curField);
		ASSERT(finder.field);
		ASSERT(finder.node);
		finder.node->AddChild(child);
	}
	vrGroupingNode::AddChild(child);
}


#ifdef _DEBUG
extern vrDumpContext tracer;
#endif

vrPrototypeList m_PrototypeList;
//------------------------------------------------------------------
// Constructor
//------------------------------------------------------------------
vrParser::vrParser(void)
{
	curLine           = 0;
	fileName          = nullString;
	nextFieldType     = 0;
	multiField        = FALSE;
	needsClear        = FALSE;
	nComponentsFound  = 0;
	nComponentsNeeded = 0;
	top               = NULL;
	lastType          = nullString;
	lastName          = nullString;
	viewpoint         = FALSE;
	console           = NULL;
	nextName          = nullString;
}

SFString GetPrivateProtoName(const SFString& name)
{
	SFString nm = name;
	nm.ToUpper();
//NAMEING	
	return SFString("_BROWSER_"+name+"_PROTO_"); 
	//return SFString(name+"_?BROWSER_PROTO_");
}

//------------------------------------------------------------------
// PROTO or EXTERNPROTO is encountered.  Create a new name space
// and push the new prototype onto the proto stack.
//------------------------------------------------------------------
void vrParser::BeginPrototype(const SFString& protoName, SFBool isExtern)
{
#ifdef _DEBUG
	tracer << endl << tracer.Indent() << "-->>BeginPrototype( \"" << protoName << "\" )" << endl;
	tracer.m_nIndents++;
#endif
	// The parser should not return a non-valid prototype name
	ASSERT(vrIsValidName(protoName));
	
	if (Lookup(protoName))
	{
		// Already exists
		Error("Attempt to define PROTO '" + protoName + "' which is already defined." + endl);
	} else
	{
		protoStack.Push(PushNameSpace(protoName));
	  vrRuntimeClass *pClass = protoStack.Peek();
		ASSERT(pClass);
		// Create somewhere to store the nodes in this proto
		vrProtoGroup *group = new vrProtoGroup(pClass);
		group->isExtern = (isExtern==1);
		group->isResolvedExtern = (isExtern==2);
		group->SetName(GetPrivateProtoName(protoName));
		vrNode *parent = GetCurrentNode();
		ASSERT(parent && parent == GetCurrentNode());
		parent->AddChild(group);
		PushNode(group);
	}
}

//------------------------------------------------------------------
// PROTO or EXTERNPROTO is completed.  Pop the name space and add
// this PROTO to the available types.
//------------------------------------------------------------------
void vrParser::EndPrototype(void)
{
#ifdef _DEBUG
	tracer.m_nIndents--;
	tracer << tracer.Indent() << "<<--EndPrototype()" << endl;
#endif
	if (InProto())
	{
#ifdef _DEBUG
		vrNode *pro = GetCurrentNode();
#endif
		PopNameSpace();
		ASSERT(protoStack.Peek());
		vrRuntimeClass *pClass = protoStack.Pop();
		AddProto(pClass);
		EndNode();
/*
		ASSERT(pro->m_NodeType == vrNode::protoGroup);
		vrProtoGroup *group = (vrProtoGroup*)pro;
		if (group->isExtern)
		{
			ASSERT(0);
		}
*/
	}
}

void AddChild(SFNode parent, SFNode child)
{
	ASSERT(child && child->GetRuntimeClass());
	if (!child->IsKindOf(NULL))
	{
		// built in
		if (GetParser()->InProto())
			child->m_NodeType=vrNode::protoNode;
		if (parent->m_NodeType==vrNode::protoGroupInstance)
		{
			if (child->m_NodeType != vrNode::firstProtoNode)
				child->m_NodeType=vrNode::protoSFNode;
			ASSERT(parent->IsKindOf(NULL));
			vrNodeList *children = ((vrProtoGroup*)parent)->GetChildren();
			if (children)
			{
				vrNode *first = children->GetHead();
				ASSERT(first->m_NodeType==vrNode::firstProtoNode);
				if (first->IsKindOf(GETRUNTIME_CLASS(vrGroupingNode)))
				{
					parent->AddChild(child);
				} else
				{
					first->AddChild(child);
				}
			}
		} else
		{
			parent->AddChild(child);
		}
	} else
	{
		// user defined proto
		ASSERT(child->IsKindOf(GETRUNTIME_CLASS(vrGroupingNode)));
		vrGroupingNode *group = (vrGroupingNode*)child;
		vrNodeList *children = group->GetChildren();
		ASSERT(child->m_NodeType==vrNode::protoGroup ||
						child->m_NodeType==vrNode::protoGroupInstance);
		child->m_NodeType=vrNode::protoGroupInstance;
		SFBool first = TRUE;
		if (children)
		{
			LISTPOS pos = children->GetHeadPosition();
			while (pos)
			{
				vrNode *node = children->GetNext(pos);
				if (first)
				{
					node->m_NodeType=vrNode::firstProtoNode;
					node->m_ProtoGroup = child->GetRuntimeClass()->ClassName();
//NAMEING
					node->SetName(child->GetName());
					parent->AddChild(node);
					first = FALSE;
				} else
				{
					node->m_NodeType=vrNode::subsequentProtoNode;
//NAMEING
					node->SetName(nullString);
				}
			}	
		}
		// Add the child so we can ROUTE to it and
		// the second and subsequent nodes are processed
		// by traversers
		GetParser()->top->AddChild(child);
	}
}

//NAMEINGstatic SFString Stringify(const void *ptr)
//NAMEING{
//NAMEING	char str[20];
//NAMEING	sprintf(str, "0x%X", ptr);
//NAMEING	return SFString(str);
//NAMEING}
//------------------------------------------------------------------
// A node definition is encountered.  May be during the parsing of
// a PROTO or just a regular node.
//------------------------------------------------------------------
void vrParser::BeginNode(const SFString& nodeName)
{
#ifdef _DEBUG
	if (!nodeStack.Peek())
		tracer << endl;
	tracer << tracer.Indent() << "-->>BeginNode( \"" << nodeName << "\" )" << endl;
	tracer.m_nIndents++;
#endif

	vrNode *parent = GetCurrentNode();
	vrNode *child = (vrNode*)CreateNewNode(nodeName);
	ASSERT(parent && parent == GetCurrentNode());
	if (!child)
	{
		Error("Node type: " + nodeName + " not found");
		return;
	}

	ASSERT(child->IsKindOf(GETRUNTIME_CLASS(vrNode)));
	PushNode(child);

	if (nextName != nullString)
//NAMEING	{
//NAMEING		if (InProto())
//NAMEING		{
//NAMEING			child->SetName(nextName); //+"_?PROTO_"+Stringify(parent));
//NAMEING		} else
//NAMEING		{
			child->SetName(nextName);
//NAMEING		}
//NAMEING	}
	nextName = nullString;

	AddChild(parent, child);
}

void vrParser::EndNode(void)
{
#ifdef _DEBUG
	tracer.m_nIndents--;
	tracer << tracer.Indent() << "<<--EndNode()" << endl;
#endif

	vrNode *node = GetCurrentNode();
	ASSERT(node);
	// let the node complete its own creation (i.e. bind for binding nodes)
	node->CompleteNode(top);
	// for error reporting only
	lastType = node->ClassName();
	lastName = node->GetName();

	// Clean up the node state
	if (nodeStack.Peek())
		delete nodeStack.Pop();
}

//-----------------------------------------------------------------------
void vrParser::BeginField(const SFString& fieldName)
{
#ifdef _DEBUG
	tracer << tracer.Indent() << "-->>BeginField( \"" << fieldName << "\" )" << endl;
	tracer.m_nIndents++;
#endif

//if (fieldName == "bottom")
//{
//printf("Hello");
//}

	SetCurrentFieldName(fieldName);

	SFNode node = GetCurrentNode();
	ASSERT(node);
ASSERT(node->FindField(fieldName));
	SFInt32 fieldType = node->GetFieldType(fieldName);

	if (fieldType == 0)
	{
		vrRuntimeClass *pClass = Lookup(node->ClassName());
		if (pClass)
		{
			vrFieldList *list = pClass->GetFieldList();
			if (list)
			{
				LISTPOS pos = list->GetHeadPosition();
				while (pos)
				{
					vrField *field = list->GetNext(pos);
					if (field->GetName() == fieldName)
					{
						fieldType = field->GetType();
					}
				}
			}
			if (fieldType == 0)
				Error("Field type: " + fieldName + " not found in proto: " + node->ClassName());
		} else
			Error("Proto not found: " + node->ClassName());
/*
		if (fieldType == 0)
		{
			ASSERT(node && node->IsKindOf(GETRUNTIME_CLASS(vrScript)));
			if (node && node->IsKindOf(GETRUNTIME_CLASS(vrScript)))
			{
				vrFieldList *list = ((vrScript*)node)->GetFieldList();
				ASSERT(list);
				if (list)
				{
					LISTPOS pos = list->GetHeadPosition();
					while (pos)
					{
						vrField *field = list->GetNext(pos);
						if (field->GetName() == fieldName)
						{
							fieldType = field->GetType();
						}
					}
				}
			}
		}
		if (fieldType == 0)
			Error("Field type not found in proto");
printf("Hello");
*/
	}
	nextFieldType = fieldType;
}

void vrParser::EndField(void)
{
#ifdef _DEBUG
	tracer.m_nIndents--;
	tracer << tracer.Indent() << "<<--EndField()" << endl;
#endif
	// do nothing
}

SFInt32 NewID(void)
{
	static SFInt32 nextID = 1000;
	return (++nextID);
}

//------------------------------------------------------------------
// Currently parsing either a script node or a PROTO or EXTERNPROTO.
// This is called when a interface declaration is encountered.
//------------------------------------------------------------------
SFInt32 vrParser::DeclareInterface(vrEventType eventType, const SFString& fieldType, const SFString& fieldName)
{
#ifdef _DEBUG
	tracer << tracer.Indent() << "AddField( \"" + GetEventTypeName(eventType) + "\", \"" << 
				fieldType << "\", \"" << fieldName << "\" )" << endl;
#endif

	// May return zero if .wrl file has an invalid field type.
	SFInt32 type = ::GetFieldType(fieldType);
	if (type)
	{
		if (IsScript())
		{
			ASSERT(GetCurrentNode());
			ASSERT(GetCurrentNode()->GetRuntimeClass());
			vrField *field = GetCurrentNode()->GetRuntimeClass()->FindField(fieldName);
			if (field)
			{
				Error("Duplicate field ignored: " + fieldName);
				return field->GetType();
			} else
			{
				SetCurrentFieldName(fieldName);
				// This field is being added to a script node
				vrScript *script = (vrScript *)GetCurrentNode();
				ASSERT(script);
				script->AddField(eventType, NewID(), fieldName, type);
			}
		} else if (InProto())
		{
			SetCurrentFieldName(fieldName);
			vrRuntimeClass *pClass = protoStack.Peek();
			ASSERT(pClass);
			pClass->AddField(fieldName, type, eventType, NewID());
		} else
		{
			Error(SFString("Invalid interface declaration: ") + GetEventTypeName(type) + ":" + fieldType + ":" + fieldName);
			type = 0;
		}
	} else
	{
		Error(SFString("Invalid field type: ") + fieldType);
	}
	return type;
}

//-----------------------------------------------------------------------
void vrParser::AddRoute(const SFString& fromNode, const SFString& fromField, const SFString& toNode, const SFString& toField)
{
#ifdef _DEBUG
	static int nRoutes=0;
	if (!nRoutes)
		tracer << endl;
	nRoutes++;
	tracer << tracer.Indent() << "ROUTE " << fromNode << "." << fromField 
					<< " TO " << toNode << "." << toField << endl;
#endif

	SFNode from = top->FindByName(fromNode);
	SFNode to   = top->FindByName(toNode);

	SFBool ok = FALSE;
	
	if (from && to)
		ok = (SFBool)from->AddRoute(fromField, to, toField);

	if (!ok)
		Error("Invalid ROUTE " + 
			fromNode + "." + fromField + " TO " +
			toNode + "." + toField);
}

void vrParser::MapFieldName(const SFString& to)
{
	vrRuntimeClass *pClass = protoStack.Peek();
	ASSERT(pClass);

	vrNodeStackItem *ns = nodeStack.Peek();

	vrField *toField   = ns->curNode->FindField(ns->curField);
	if (!toField)
	{
		Error("IS mapping to non existant field name: " + ns->curField + endl);
		return;
	}
	vrField *fromField = pClass->FindField(to);
	if (!fromField)
	{
		Error("IS mapping to non existant field name: " + to + endl);
		return;
	}
	if (toField->GetType() != fromField->GetType())
	{
		Error("IS mapping to non-identical field types: " + GetFieldTypeName(toField->GetType()) +
			" --> " + GetFieldTypeName(fromField->GetType()));
		return;
	}

	SFString map = toField->GetName() + " IS " + fromField->GetName();
	ns->curNode->m_IsMaps.AddValue(map);
	if (fromField->val.boolVal)
		ns->curNode->SetFieldValue(toField->GetName(), (void*)fromField->val.boolVal);

/*
	// Needs to be smarter (i.e. field mapped to exposed field are
	//	OK? 
	if (toField->GetEventType() != fromField->GetEventType())
	{
		Error("IS mapping to non-identical field class types: " + GetEventTypeName(toField->GetEventType()) +
			" --> " + GetEventTypeName(fromField->GetEventType()));
		return;
	}
*/

#ifdef _DEBUG
	tracer << tracer.Indent() << pClass->ClassName() << ": " 
			<< ns->curField << " IS " << to << endl;
#endif
}

/*ass NameFinder
{
public:
	SFString space;
	ex
};
SFBool FindNameInNameSpace(vrNode *node, void *data)
{
}
*/
SFString indexIt()
{
	static int index=0;
	char thing[10];
	sprintf(thing, "_%d", index++);
	return SFString(thing);
}

void vrParser::DefineCurrentNode(const SFString& name)
{
#ifdef _DEBUG
	tracer << tracer.Indent() << "DefineCurrentNode( \"" << name << "\" )" << endl;
#endif

	ASSERT(top);

	// If this name already exists we must remove the name
	SFNode node = top->FindByName(name);
	if (node)
		node->SetName(node->GetName()+"_?"+indexIt());
	ASSERT(!top->FindByName(name));
	nextName = name;
}

//------------------------------------------------------------------
void vrParser::UseDefinedNode(const SFString& name)
{
#ifdef _DEBUG
	tracer << tracer.Indent() << "UseDefinedNode( \"" << name << "\" )" << endl;
#endif

	ASSERT(top);
	SFNode node = top->FindByName(name);
	if (node)
	{
		SFNode parent = top;
		if (nodeStack.Peek())
			parent = nodeStack.Peek()->curNode;
		ASSERT(parent);
		AddChild(parent, node);
	} else
	{
		Error("USE " + name + " encountered.  No corresponding DEF found.");
	}
}

//-----------------------------------------------------------------------
void vrParser::Error(const SFString& msg)
{
	vrDumpString ds;
	ds.m_nIndents++;

	ds << ds.Indent() << "\nError In File:      " << fileName << endl;
	ds << ds.Indent() << "Error Line Number:  " << curLine+1 << endl;
	ds << ds.Indent() << "Error Message:      " << msg << endl;

	ds << ds.Indent() << "Last Good Node:     " << lastType <<
		"( \"" << lastName << "\" )" << endl;

	vrNodeStackItem *ns = nodeStack.Peek();
	if (ns)
	{
		if (ns->curField != nullString)
		{
			ds << ds.Indent() << "Current Field:      " << ns->curField << endl;
			if (ns->curNode)
				ds << ds.Indent() << "Current Node:       " << ns->curNode->ClassName() << endl;
		} else if (ns->curNode)
		{
			ds << ds.Indent() << "Current Node:       " << ns->curNode->ClassName() << endl;
		}
	}

	if (console)
		console->Error(ds.string);
	
	nextFieldType = 0;
}

void vrParser::Clear(void)
{
	curLine = 1;
	// Anything left in the node stack or parser stack
	// should only be here if there was an error while parsing.
	// We should clean these up
	while (nodeStack.Peek())
		delete nodeStack.Pop();
	while (protoStack.Peek())
	{
		vrRuntimeClass *proto = protoStack.Pop();
		if (!proto->m_RefCount)
			delete proto;
	}
	ASSERT(nodeStack.Empty());
	ASSERT(protoStack.Empty());
	
	LISTPOS pos = m_PrototypeList.GetHeadPosition();
	while (pos)
	{
		// Clean up so these are not available for next parse
		vrRuntimeClass *pClass = m_PrototypeList.GetNext(pos);
		vrDELETE(pClass);
	}
	m_PrototypeList.RemoveAll();
	ASSERT(m_PrototypeList.Empty());
}

SFBool vrParser::IsScript(void) const
{
	if (!IsNode())
		return FALSE;
	ASSERT(nodeStack.Peek());
	ASSERT(nodeStack.Peek()->curNode);
	return (nodeStack.Peek()->curNode->IsKindOf(GETRUNTIME_CLASS(vrScript)));
}


//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
void AddProto(vrRuntimeClass *pClass)
{
	// already defined?
	if (Lookup(pClass->ClassName()))
    return;
  m_PrototypeList.AddHead(pClass);
}

vrRuntimeClass *PushNameSpace(const SFString& className)
{
	m_PrototypeList.AddHead((vrRuntimeClass *)NULL);

	vrRuntimeClass *pClass = vrLookupBuiltin("vr"+className);
	if (pClass)
		return pClass;

  pClass = new vrRuntimeClass(); //vrRuntimeProto(className);
	pClass->Initialize(className);
	return pClass;
}

void PopNameSpace()
{
	LISTPOS pos = m_PrototypeList.GetHeadPosition();
	while (pos)
	{
		LISTPOS p = pos;
		vrRuntimeClass *pClass = m_PrototypeList.GetNext(pos);
    m_PrototypeList.RemoveAt(p);
    if (!pClass)
			break;
		delete pClass;
	}
}

vrRuntimeClass *Lookup(const SFString& name)
{
	// if name does not have 'vr' already try it first by
	// adding 'vr', then without
	
	vrRuntimeClass *pClass = NULL;
	
	if (name.Left(2) == "vr")
		pClass = vrLookupBuiltin(name);
	else
		pClass = vrLookupBuiltin("vr"+name);
	if (pClass)
		return pClass;
	// Try one more time just plain
	pClass = vrLookupBuiltin(name);
	if (pClass)
		return pClass;
		
	// Now look for user defined prototypes
	LISTPOS pos = m_PrototypeList.GetHeadPosition();
	while (pos)
	{
		pClass = m_PrototypeList.GetNext(pos);
    if (pClass && name == pClass->ClassName())
			return pClass;
  }
  return NULL;
}

//------------------------------------------------------------------
// The parser used to parse the file.  Should be a pointer
// that is created and destroyed at each parse to clean up memory.
//------------------------------------------------------------------
static vrParser parser;
vrParser *GetParser(void)
{
	return &parser;
}

static SFString lastName;
static vrNode *tTop=NULL;
vrBaseNode *CreateNode(void)
{
	ASSERT(tTop);
	vrNode *proto = tTop->FindByName(GetPrivateProtoName(lastName));
	tTop=NULL;
	ASSERT(proto);
	vrNode *ret = (vrNode*)proto->Clone();
	ret->SetName(nullString);
	return ret;
}

PFNV FindCreateFunc(const SFString& nodeType)
{
	vrRuntimeClass *pClass = Lookup(nodeType);
	if (!pClass)
		return NULL;
		
	if (pClass->m_CreateFunc)
		return pClass->m_CreateFunc;
	
	lastName = nodeType;
	return CreateNode;
}

vrBaseNode *vrParser::CreateNewNode(const SFString& nodeName)
{
	tTop = top;
	PFNV CreateFunc = FindCreateFunc(nodeName);
	if (CreateFunc)
	{
		return (CreateFunc)();
	}
	return NULL;
}

//NAMEING
SFBool IsProtoName(const SFString& nodeName)
{
	return (nodeName.Left(9)=="_BROWSER_" &&
						nodeName.Right(7)=="_PROTO_");
//	nodeName.Find("_BROWSER")!=-1 && nodeName.Find("_PROTO")!=-1)
}

//NAMEING
SFString StripProtoName(const SFString& nodeName)
{
	ASSERT(IsProtoName(nodeName));
	SFString ret = nodeName;
	ret = ret.Mid(9);
	ret = ret.Left(ret.Length()-7);
	return ret;
}

#include "Traversers\WriteTraverser.h"
void DumpFieldList(vrDumpContext& dc, vrFieldList *list, SFBool isExtern, SFBool isScript, const vrNode *node);
SFBool DumpPrototype(vrDumpContext& dc, const vrNode *node, vrTraverser *wt)
{
	SFInt32 n = dc.m_nIndents;
	SFString nodeName = node->GetName();
	
	// This is a prototype node
//NAMEING
	nodeName = StripProtoName(nodeName);
//	ASSERT(nodeName.Left(9)=="_BROWSER_");
//	ASSERT(nodeName.Right(7)=="_PROTO_");
//	nodeName = nodeName.Mid(9);
//	nodeName = nodeName.Left(nodeName.Length()-7);
//	ASSERT(nodeName.Find("_?")==-1);
	vrProtoGroup *pro = (vrProtoGroup*)node;
	if (pro->isExtern)
		dc << dc.Indent() << "EXTERNPROTO " << nodeName << " [";
	else if (pro->isResolvedExtern)
		dc << dc.Indent() << "EXTERNPROTO " << nodeName << " [";
	else
		dc << dc.Indent() << "PROTO " << nodeName << " [";

	vrRuntimeClass *pClass = node->GetRuntimeClass();
	ASSERT(pClass);
	if (!pClass->GetFieldList())
	{
		dc << " ]";
	} else
	{
		dc << endl;
		dc.m_nIndents++;
		DumpFieldList(dc,pClass->GetFieldList(),(pro->isExtern||pro->isResolvedExtern),FALSE,node);
		dc.m_nIndents--;
		dc << dc.Indent() << "]";
	}

	if (pro->isExtern)
	{
		if (pro->externName.GetCount()>1)
			dc << " [" << endl;
		dc.m_nIndents++;
		for (int i=0;i<pro->externName.GetCount();i++)
		{
			SFString str = pro->externName[i];
			dc << dc.Indent() << "\"" << str << "\"";
			if (i<pro->externName.GetCount()-1)
				dc << ",";
			dc << endl;
		}
		dc.m_nIndents--;
		if (pro->externName.GetCount()>1)
			dc << dc.Indent() << "]" << endl;
	} else if (pro->isResolvedExtern)
	{
		vrField *count = pro->FindField("_?nFilenames");
		ASSERT(count);
		SFInt32 cnt;
		GetValEx(count, &cnt);
		if (cnt>1)
			dc << " [ " << endl;
		dc.m_nIndents++;
		for (int i=0;i<cnt;i++)
		{
			char ss[20];
			sprintf(ss, "_?fileName_%d", i);
			vrField *field = pro->FindField(ss);
			ASSERT(field);
			SFString str;
			GetValEx(field, &str);
			dc << dc.Indent() << "\"" << str << "\"";
			if (i<cnt-1)
				dc << ",";
			dc << endl;
		}
		dc.m_nIndents--;
		if (cnt>1)
			dc << "]" << endl;
	} else
	{
		dc << endl;
		dc.m_nIndents = n;
		ASSERT(node->IsKindOf(GETRUNTIME_CLASS(vrGroupingNode)));
		dc << dc.Indent() << "{\n";
		dc.m_nIndents++;
		vrNodeList *children = ((vrGroupingNode*)node)->GetChildren();
		if (children)
		{
			LISTPOS pos = children->GetHeadPosition();
			while (pos)
			{
				SFNode n = children->GetNext(pos);
				n->Traverse(wt);
				if (pos)
					dc << "\n";
			}
		}
		((vrWriteTraverser*)wt)->DumpRoutes((vrGroupingNode*)node, TRUE);
		dc.m_nIndents--;
		dc << dc.Indent() << "}\n";
	}
	return TRUE;
}

class FindInScriptTextx
{
public:
	SFBool found;
	SFString str;
	vrField *field;
	FindInScriptTextx() { field=NULL; found = FALSE; }
};

SFBool FindInScriptText(vrNode *node, void *data)
{
	FindInScriptTextx *dat = (FindInScriptTextx*)data;
	if (dat->found)
		return FALSE;
	if (node->IsKindOf(GETRUNTIME_CLASS(vrScript)))
	{
		for (int i=0;i<((vrScript*)node)->GetNOrigUrls();i++)
		{
			SFString str = ((vrScript*)node)->GetOrigUrl(i);
			if (str.Find(dat->str)!=-1)
			{
				dat->found=TRUE;
				dat->field = node->FindField(str);
				return FALSE;
			}
		}
	}
	return TRUE;
}

SFBool DumpProtoInstance(vrWriteTraverser *t, vrDumpContext& dc, const vrNode *node)
{
	ASSERT(node->m_NodeType == vrNode::protoGroupInstance);
	vrRuntimeClass *pClass = node->GetRuntimeClass();
	ASSERT(pClass);
	dc << dc.Indent() << pClass->ClassName();

	vrFieldList *list = pClass->GetFieldList();
	if (list)
	{
	  dc << endl << dc.Indent() << "{" << endl;
		dc.m_nIndents++;
		LISTPOS pos = list->GetHeadPosition();
		while (pos)
		{
			vrField *field = list->GetNext(pos);
			if (field->GetName().Find("_?nFilenames")!=-1)
				continue;
			if (field->GetName().Find("_?fileName")!=-1)
				continue;
			if (field->IsEventType(vrField::eventOut))
				continue;
			if (field->IsEventType(vrField::eventIn))
				continue;

			IsMapFinder finder;
			FindIsMappedField(&finder, node, field->GetName());;
			vrField *isMapped = finder.field;

if (!isMapped)
{
	FindInScriptTextx find;
	find.str = field->GetName();
	((vrNode*)node)->ForEvery(FindInScriptText, &find);
	if (find.found)
	{
		// PROTO has field which is referenced only in a script
		ASSERT(0);
	} else
	{
		dc << dc.Indent();
		DumpName(dc, field);
		dc << " ";
		DumpValEx(dc, field);
		dc << endl;
	}
}

			if (isMapped && 
					(isMapped->val.boolVal ||
					 field->GetType()==MFNODE ||
					 field->GetType()==SFNODE) && 
					 !EqualValEx(field, isMapped))
			{
				if (isMapped->GetType()!=SFNODE)
				{
					dc << dc.Indent();
					DumpName(dc, field);
					dc << " ";
				}

				if (isMapped->GetType()==MFNODE)
				{
					ASSERT(isMapped->GetName()=="children");
					ASSERT(node->IsKindOf(GETRUNTIME_CLASS(vrGroupingNode)));
					vrNodeList *list = ((vrGroupingNode*)node)->GetChildren();
					if (list)
					{
						if (!list->GetCount())
							dc << "[ ]" << endl;
						else
						{
							dc << endl;
							dc << dc.Indent() << "[" << endl;
							dc.m_nIndents++;
							LISTPOS pos = list->GetHeadPosition();
							while (pos)
							{
								vrNode *n = list->GetNext(pos);
								if (n->m_NodeType==vrNode::normalNode ||
											n->m_NodeType==vrNode::protoSFNode)
								{
									n->Traverse(t);
								}
							}
							dc.m_nIndents--;
							dc << dc.Indent() << "]" << endl;
						}
					}
				} else if (isMapped->GetType()==SFNODE)
				{
					if (isMapped->val.boolVal)
					{
						dc << dc.Indent();
						DumpName(dc, field);
						dc << " ";
						vrNode *node = (vrNode*)isMapped->val.voidPtr;
						ASSERT(node->m_NodeType==vrNode::protoSFNode);
						node->Traverse(t);
					} else
					{
						ASSERT(node->IsKindOf(NULL));
						vrNodeList *children = ((vrProtoGroup*)node)->GetChildren();
						if (children)
						{	
							vrNode *first = children->GetHead();
							ASSERT(first->m_NodeType==vrNode::firstProtoNode);
	//						if (!first->IsDefault(isMapped->GetName()))
	//						{
								//vrField *field = first->FindField(isMapped->GetName());
								// grab the current value of the queried field
		//	[in] fieldName: The name of this field (may be NULL).
		//	[in] dataType:  The data type of this field.
		//	[in] eventType: The event type of this field.
		//	[in] fieldID:   The unique id of this field.
		//
								vrField  tmp(isMapped->GetName(), 
									SFNODE, vrField::field, -1, NULL);

								finder.grabbed=TRUE;
								first->IsDefault(isMapped->GetName(), &tmp);
								dc << dc.Indent();
								DumpName(dc, &tmp);
								dc << " ";
								vrNode *node = (vrNode*)tmp.val.voidPtr;
								ASSERT(node->m_NodeType==vrNode::protoSFNode);
								node->Traverse(t);
						}
//						}
					}
				} else
				{
					DumpValEx(dc, isMapped);
				}
				dc << endl;
			}
			if (finder.grabbed)
				SetValEx(isMapped, NULL);
		}
		dc.m_nIndents--;
		dc << dc.Indent() << "}" << endl;
	} else
	{
		dc << " { }" << endl;
	}
	return TRUE;
}

void DumpFieldList(vrDumpContext& dc, vrFieldList *list, SFBool isExtern, SFBool isScript, const vrNode *node)
{
	if (list)
	{
		LISTPOS p = list->GetHeadPosition();
		while (p)
		{
			vrField *field = list->GetNext(p);
			if (field->GetName().Find("_?nFilenames")!=-1)
				continue;
			if (field->GetName().Find("_?fileName")!=-1)
				continue;

			SFBool writeIt  = TRUE;
			if (isScript)
			{
				if (node->IsIsMapped(field->GetName()))
				{
					writeIt = FALSE;
				}
			}
			if (writeIt)
			{
				dc 
					<< dc.Indent() 
					<< GetEventTypeName(field->GetEventType())
					<< " " 
					<< GetFieldTypeName(field->GetType()) 
					<< " ";
				DumpName(dc, field);
				if (!isExtern)
				{
					dc << " ";
					DumpValEx(dc, field);
				}
				dc << endl;
			}
		}
	}
}

void SetValEx(vrField *field, void *val)
{
	if (field->GetType()==SFNODE)
	{
//		if (field->val.voidPtr)
//			delete field->val.voidPtr;
		field->val.voidPtr = NULL;
		if (!val)
			return;

		field->val.voidPtr = *(vrNode**)val;

	} else if (field->GetType() == MFNODE)
	{
if (val)
{
ASSERT(0);
}
	} else
	{
		SetVal(field,val);
	}
}

void GetValEx(const vrField *field, void *val)
{
	if (field->GetType()==SFNODE)
	{
	} else if (field->GetType() == MFNODE)
	{
ASSERT(0);
	} else
	{
  	GetVal(field,val);
	}
}

void CopyValEx(const vrField *fromField, vrField *toField)
{
	ASSERT(fromField->GetType()==toField->GetType());
	if (fromField->GetType()==SFNODE)
	{
ASSERT(0);
	} else if (fromField->GetType() == MFNODE)
	{
	} else
	{
  	CopyVal(fromField, toField);
	}
}

void DumpValEx(vrDumpContext& dc, const vrField *field)
{
	if (field->GetType()==SFNODE)
	{
		dc << " NULL";
	} else if (field->GetType()==MFNODE)
	{
		dc << " [ ]";
	} else
	{
		DumpVal(dc, field);
	}
}

SFBool EqualValEx(const vrField *f1, const vrField *f2)
{
	ASSERT(f1->GetType()==f2->GetType());
	if (f1->GetType()==SFNODE)
	{
		return FALSE; // always write out these
	} else if (f1->GetType()==MFNODE)
	{
		return FALSE; // always write out these
	}
 	return EqualVal(f1, f2);
}

