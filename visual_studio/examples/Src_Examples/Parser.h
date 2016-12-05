#ifndef _PARSESUPPORT_H
#define _PARSESUPPORT_H

#include "Utils\Utility.h"
#include "TestNode.h"
#include "ParseTypes.h"

class vrNodeStackItem
{
public:
	vrNodeStackItem()
		{
			curField = nullString;
			curNode  = NULL;
		}
	vrNode       *curNode;
  SFString      curField;
};

// Does nothing -- gobbles up all messages
class vrConsole
{
public:
	vrConsole()
		{}
	virtual ~vrConsole()
		{}
	virtual void Message(const SFString& msg)
		{ printf("%s", (const char *)msg); }
	virtual void Error(const SFString& msg)
		{ fprintf(stderr, "%s", (const char *)msg); }
};

typedef vrRefCountStack<vrRuntimeClass *> vrProtoStack;
typedef vrRefCountList<vrRuntimeClass *>  vrPrototypeList;
typedef vrStack<vrNodeStackItem *>        vrNodeItemStack;

class vrParser
{
public:
	SFString        fileName;
	SFInt32         nextFieldType;
	SFInt32         curLine;
	SFBool          multiField;
	SFBool          needsClear;
	SFInt32         nComponentsFound;
	SFInt32         nComponentsNeeded;
	SFInt32         viewpoint;
	vrNode         *top;
	SFString        lastType;
	SFString        lastName;
	vrConsole      *console;
	SFString        nextName;
	
	vrNodeItemStack nodeStack;
	vrProtoStack    protoStack;

public:
	vrParser(void);

	// PROTO or EXTERNPROTO encountered
	void    BeginPrototype    (const SFString& protoName, SFBool isExtern);
	// PROTO or EXTERNPROTO completed
	void    EndPrototype      (void);
	// A field in the PROTO or EXTERNPROTO interface definition is encountered
	SFInt32 DeclareInterface(vrEventType eventType, const SFString& fieldType, const SFString& fieldName);

	// A node is encounted (either in a PROTO or not)
	void    BeginNode         (const SFString& nodeName);
	// the node is completed
	void    EndNode           (void);

	// a field is encountered
	void    BeginField        (const SFString& fieldName);
	// a field is completed
	void    EndField          (void);

	// the most recently completed node is DEF'd
	void DefineCurrentNode (const SFString& nodeName);
	// a previously DEF'd node is USE'd
	void UseDefinedNode    (const SFString& nodeName);

	// A ROUTE is added
	void    AddRoute               (const SFString& fromNode,
																	const SFString& fromField,
																	const SFString& toNode,
																	const SFString& toField);

	// An IS field is encountered
	void MapFieldName(const SFString& to);
	
	// Support routines
	void Error(const SFString& msg);
	void Clear(void);

	SFBool  IsScript      (void) const;
	SFBool  InProto       (void) const;
	SFBool  IsNode        (void) const;
	vrNode *GetCurrentNode(void) const;
	vrBaseNode *CreateNewNode (const SFString& nodeName);
	void    PushNode      (vrNode *node);
	void SetCurrentFieldName(const SFString& fieldName);
};
extern vrParser *GetParser(void);

// Prototype name space management
extern void            AddProto      (vrRuntimeClass *);
extern vrRuntimeClass *PushNameSpace (const SFString& protoName);
extern void            PopNameSpace  (void);
extern vrRuntimeClass *Lookup        (const SFString& name);

inline SFBool vrParser::InProto(void) const
{
	return (protoStack.Peek() != NULL);
}

inline SFBool vrParser::IsNode(void) const
{
	// If node stack is not empty it is pointing to a node
	ASSERT(!nodeStack.Peek() || nodeStack.Peek()->curNode);
	return (nodeStack.Peek() != NULL);
}

inline vrNode *vrParser::GetCurrentNode(void) const
{
	vrNode *ret = top;
	if (nodeStack.Peek())
		ret = nodeStack.Peek()->curNode;
	ASSERT(ret);
	return ret;
}

inline void vrParser::PushNode(vrNode *node)
{
	vrNodeStackItem *ns = new vrNodeStackItem();
	nodeStack.Push(ns);
	ns->curNode = node;
}

inline void vrParser::SetCurrentFieldName(const SFString& fieldName)
{
	ASSERT(nodeStack.Peek());
	nodeStack.Peek()->curField = fieldName;
}

#pragma warning(disable : 4505)

#endif
