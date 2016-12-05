#include "Utils\Utility.h"

#include "TestNode.h"

IMPLEMENT_NODE(vrNode, vrBaseNode);

vrRefCountList<vrNode*> namedNodes;
void ClearNamedNodes(void)
{
	LISTPOS pos = namedNodes.GetHeadPosition();
	while (pos)
	{
		LISTPOS p = pos;
		vrNode *node = namedNodes.GetNext(pos);
		namedNodes.RemoveAt(p);
		node->Reference();
		vrDELETE(node);
	}
	ASSERT(namedNodes.Empty());
	return;
}

vrNode *FindNode(const SFString& name)
{
	LISTPOS pos = namedNodes.GetHeadPosition();
	while (pos)
	{
		vrNode *node = namedNodes.GetNext(pos);
		if (node->GetName() == name)
			return node;			
	}
	return NULL;
}

vrNode *vrNode::FindByName(const SFString& name) const
{
	return FindNode(name);
}

void vrNode::SetName(const SFString& name)
{
	vrNode *node = FindNode(name);
	if (node)
	{
		LISTPOS pos = namedNodes.Find(node);
		ASSERT(pos);
		namedNodes.RemoveAt(pos);
		node->Reference();
		vrDELETE(node);
	}
	this->name = name;
	namedNodes.AddTail(this);
}

void vrNode::AddChild (vrNode *node)
{
#ifdef _DEBUG
extern vrDumpContext tracer;
	ASSERT(node);
	SFString name  = className;
	SFString name2 = node->className;
	tracer << tracer.Indent() << "adding " + name2 + " to " + name << endl;
#endif
}
