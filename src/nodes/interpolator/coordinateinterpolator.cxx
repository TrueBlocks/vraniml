MFVec3f vrCoordinateInterpolator::Evaluate(SFFloat t) const
{
	int nKeys   = m_Key.GetCount();
	int nValues = m_KeyValue.GetCount();
	ASSERT(nKeys <= nValues);
	ASSERT(!(nValues%nKeys));  // exact multiple
	int nRetValues = nValues / nKeys;
	
	if (t < m_Key[0])
	{
		MFVec3f arrayRet;
		for (int i=0;i<nRetValues;i++)
		{
			arrayRet.AddValue(m_KeyValue[i]);
		}
		return arrayRet;
	}
		
	if (t > m_Key[nKeys-1])
	{
		MFVec3f arrayRet;
		for (int i=0;i<nRetValues;i++)
		{
			SFInt32 index = (nKeys-1)*nRetValues+i;
			arrayRet.AddValue(m_KeyValue[index]);
		}
		return arrayRet;
	}
		
	// should use binary search
	for (int i=0;i<nKeys;i++)
	{
		if (t == m_Key[i])
		{
			MFVec3f arrayRet;
			for (int j=0;j<nRetValues;j++)
			{
				SFInt32 index = i*nRetValues+j;
				arrayRet.AddValue(m_KeyValue[index]);
			}
			return arrayRet;
		}
		if (m_Key[i] > t)
			break;
	}
	ASSERT(i<nKeys);
	ASSERT(i>0);

	MFVec3f arrayFrom;
	MFVec3f arrayTo;
	for (int j=0;j<nRetValues;j++)
	{
		SFInt32 fromIndex = (i-1)*nRetValues+j;
		SFInt32 toIndex   = i*nRetValues+j;
		arrayFrom.AddValue(m_KeyValue[fromIndex]);
		arrayTo.AddValue(m_KeyValue[toIndex]);
	}

	return vrInterpolate(arrayFrom, arrayTo,
											m_Key[i-1], m_Key[i],
											t);
}
