class vrBox : public vrNode
{
public:
	SFVec3f m_Size;
	vrBox(const SFString& n=nullString)
	{
		m_Size = SFVec3f(2,2,2);
		if (GetRuntimeClass()->m_RefCount==1)
		{
			AddField(SFVEC3F, (SFInt32)"size");
		}
		GetRuntimeClass()->Reference();
		name = n;
	}
	DECLARE_NODE(vrBox);
};

class vrCone : public vrNode
{
public:
	vrCone(const SFString& n=nullString)
	{
		if (GetRuntimeClass()->m_RefCount==1)
		{
			AddField(SFFLOAT, (SFInt32)"bottomRadius");
			AddField(SFFLOAT, (SFInt32)"height");
			AddField(SFBOOL,  (SFInt32)"side");
			AddField(SFBOOL,  (SFInt32)"bottom");
		}
		GetRuntimeClass()->Reference();
		name = n;
	}
	DECLARE_NODE(vrCone);
};

class vrCylinder : public vrNode
{
public:
	vrCylinder(const SFString& n=nullString)
	{
		if (GetRuntimeClass()->m_RefCount==1) // first one
		{
			AddField(SFFLOAT, (SFInt32)"radius");
			AddField(SFFLOAT, (SFInt32)"height");
			AddField(SFBOOL,  (SFInt32)"side");
			AddField(SFBOOL,  (SFInt32)"bottom");
			AddField(SFBOOL,  (SFInt32)"top");
		}
		GetRuntimeClass()->Reference();
		name = n;
	}
	DECLARE_NODE(vrCylinder);
};

IMPLEMENT_NODE(vrBox, vrNode);
IMPLEMENT_NODE(vrCone, vrNode);
IMPLEMENT_NODE(vrCylinder, vrNode);
