#ifndef _TESTNODE_H
#define _TESTNODE_H

#define endl "\n"

class vrRoute
{
};

// Test class for Reference counting tests
class vrNode : public vrBaseNode
{
protected:
	SFString name;
	SFString className;
public:
	vrNode(void)
		{
			name = nullString;
		}
	DECLARE_NODE(vrNode);

	SFString ClassName(void) const
		{
			return className;
		}
	void SetClassName(const SFString& name)
		{
			className = name;
		}
	void SetName(const SFString& n);
	SFString GetName(void) const
		{
			return name;
		}
	virtual void CompleteNode(vrNode *top)
		{
			return;
		}
	virtual void AddChild (vrNode *node);
	vrRoute *AddRoute(const SFString& srcField, vrNode *dstNode, const SFString& dstField, SFBool internal=FALSE)
		{ return (vrRoute*)TRUE; }
	virtual vrNode *FindByName(const SFString& nodeName) const;
	vrBoundingBox GetBoundingBox() const
		{
			// a phoney bounding box for testing
			return vrBoundingBox(SFVec3f(-1,-2,-3), SFVec3f(1,2,3));
		}
};
typedef vrNode* SFNode;
typedef SFNode (*PFNNV)(void);

#endif