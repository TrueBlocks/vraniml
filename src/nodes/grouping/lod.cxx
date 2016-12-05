SFNode vrLOD::FindByType(vrRuntimeClass *pClass) const
{
	for (int i=0;i<GetNLevels();i++)
	{
		if (GetLevel(i)->IsKindOf(pClass))
			return ((SFNode)GetLevel(i));
	}

	return vrNode::FindByType(pClass);
}

SFNode vrLOD::FindByName(const SFString& nodeName) const
{
	SFNode node = NULL;

	for (int i=0;i<GetNLevels();i++)
	{
		if ((node = GetLevel(i)->FindByName(nodeName)) != NULL)
			return node;
	}

	return vrNode::FindByName(nodeName);
}

SFBool vrLOD::ForEvery(PFBO3V userFn, void *userData, PFBO3V afterFn)
{
	for (int i=0;i<GetNLevels();i++)
	{
		GetLevel(i)->ForEvery(userFn, userData, afterFn);
	}

	return vrNode::ForEvery(userFn, userData, afterFn);
}

