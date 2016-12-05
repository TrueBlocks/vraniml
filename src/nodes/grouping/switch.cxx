SFNode vrSwitch::FindByType(vrRuntimeClass *pClass) const
{
	for (int i=0;i<GetNChoices();i++)
	{
		if (GetChoice(i)->IsKindOf(pClass))
			return ((SFNode)GetChoice(i));
	}

	return vrNode::FindByType(pClass);
}

SFNode vrSwitch::FindByName(const SFString& nodeName) const
{
	SFNode node = NULL;

	for (int i=0;i<GetNChoices();i++)
	{
		if ((node = GetChoice(i)->FindByName(nodeName)) != NULL)
			return node;
	}

	return vrNode::FindByName(nodeName);
}

SFBool vrSwitch::ForEvery(PFBO3V userFn, void *userData, PFBO3V afterFn)
{
	for (int i=0;i<GetNChoices();i++)
	{
		GetChoice(i)->ForEvery(userFn, userData, afterFn);
	}

	return vrNode::ForEvery(userFn, userData, afterFn);
}

