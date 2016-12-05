#include "Utils\Utility.h"

#include "TestParser.h"

#include "Parser.h"
#include "Script.h"

#ifdef _DEBUG
extern vrDumpContext tracer;
#endif

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
	
	protoStack.Push(PushNameSpace(protoName));
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
	PopNameSpace();
  ASSERT(protoStack.Peek());
	AddProto(protoStack.Pop());
}

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

//if (nodeName=="Cone")
//{
//	printf("Hello");
//}
	// Don't move this -- CreateNewNode changes the stack
	vrNode *parent = GetCurrentNode();
	ASSERT(parent);
	vrBaseNode *node = CreateNewNode(nodeName);
	ASSERT(node->IsKindOf(GETRUNTIME_CLASS(vrNode)));
	vrNode *child = (vrNode*)node;
	ASSERT(parent == GetCurrentNode());

	if (child)
	{
		PushNode(child);

		if (nextName != nullString)
			child->SetName(nextName);
		nextName = nullString;

		if (InProto())
		{
			vrRuntimeClass *pClass = protoStack.Peek();
			ASSERT(pClass);
			pClass->AddChild(child);
#ifdef _DEBUG
			tracer << tracer.Indent() << "adding to proto" << endl;
#endif
		} else
		{
			ASSERT(parent);
			ASSERT(parent != child);
			parent->AddChild(child);
		}
	} else
	{
		Error("Node type: " + nodeName + " not found");
	}
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
	SFInt32 fieldType = node->GetFieldType(fieldName);

	if (fieldType == 0)
	{
		vrRuntimeClass *pClass = Lookup(node->ClassName());
		if (pClass)
		{
			vrFieldList *list = pClass->GetFieldList();
			ASSERT(list);
			LISTPOS pos = list->GetHeadPosition();
			while (pos)
			{
				vrField *field = list->GetNext(pos);
				if (field->GetName() == fieldName)
				{
					fieldType = field->GetType();
				}
			}
			if (fieldType == 0)
				printf("Field type not found in proto" + fieldName);
		} else
			printf("No proto found");
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
			SetCurrentFieldName(fieldName);
			// This field is being added to a script node
			vrScript *script = (vrScript *)GetCurrentNode();
			ASSERT(script);
			script->AddField(eventType, type, fieldName, -1);
		} else if (InProto())
		{
			vrRuntimeClass *pClass = protoStack.Peek();
			ASSERT(pClass);
			pClass->AddField(fieldName, type, eventType, -1);
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

	SFBool valid = FALSE;

	SFNode from = top->FindByName(fromNode);
	SFNode to   = top->FindByName(toNode);

	if (from && to)
		valid = (SFBool)from->AddRoute(fromField, to, toField);

	if (!valid)
		Error("Invalid ROUTE " + fromNode + " TO " + toNode);
}

void vrParser::MapFieldName(const SFString& to)
{
	vrRuntimeClass *pClass = protoStack.Peek();
	ASSERT(pClass);

	vrNodeStackItem *ns = nodeStack.Peek();
	//Must chech that IS maps two identical field types.
#ifdef _DEBUG
	tracer << tracer.Indent() << pClass->ClassName() << ": " 
			<< ns->curField << " IS " << to << endl;
#endif
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
		node->SetName(nullString);
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
		parent->AddChild(node);
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
	while (nodeStack.Peek())
		delete nodeStack.Pop();
	while (protoStack.Peek())
		delete protoStack.Pop();
	ASSERT(nodeStack.Empty());
	ASSERT(protoStack.Empty());
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
vrPrototypeList m_PrototypeList;
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

  pClass = new vrRuntimeClass();
	ASSERT(pClass);
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
	vrRuntimeClass *pClass = vrLookupBuiltin("vr"+name);
	if (pClass)
		return pClass;

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

