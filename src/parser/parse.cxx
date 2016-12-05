#ifdef _DEBUG
extern vrDumpContext tracer;
#define ASSERT_VALIDPS(st) assert(((st)->curField != nullString) && (st)->curNode)
#else
#define ASSERT_VALIDPS(st)
#endif

//------------------------------------------------------------------
void AddSingleFieldImage(Image *img)
{
#ifdef _DEBUG
	tracer << tracer.Indent() << "AddSingleFieldImage()" << endl;
#endif

	if (!img)
		return;
		
/*
	  image 4 4 1 
					0x00 0xDD 0xAA 0xFF
		      0xDD 0x00 0xDD 0x00
		      0xAA 0xDD 0x00 0x00
		      0xFF 0x00 0x00 0x00
*/
	vrNodeStackItem *ns = GetParser()->nodeStack.Peek();
	if (ns)
	{
#ifdef _DEBUG
		tracer << " >Setting value in node<";
#endif
		ASSERT_VALIDPS(ns);
		ASSERT(ns->curField=="image");
		ASSERT(ns->curNode->IsKindOf(GETRUNTIME_CLASS(vrPixelTexture)));
/*
		if (!ns->curNode->SetFieldValue(ns->curField, (void*)img))
		{
			GetParser()->Error("Not able to set field value: " + ns->curField + " in current node: " + ns->curNode->GetRuntimeClass()->ClassName() + endl);
		}
*/
		vrPixelTexture *p = (vrPixelTexture*)ns->curNode;
		SFInt32 w = img->img.m_Width;
		SFInt32 h = img->img.m_Height;
		SFInt32 n = img->img.m_nComponents;
		p->SetWidth(w);
		p->SetHeight(h);
		p->SetNComponents(n);
		for (int i=0;i<img->colors.GetCount();i++)
		{
			long col = img->colors[i];
			p->AddPixel(col);
		}
	} else
	{
		vrRuntimeClass *pClass = GetParser()->protoStack.Peek();
		ASSERT(pClass);
		if (!pClass->SetFieldValue(ns->curField, (void*)img))
		{
			GetParser()->Error("Not able to set field value: " + ns->curField + " in current prototype: " + pClass->ClassName() + endl);
		}
	}
}

//------------------------------------------------------------------
// Add a single field to the current node or prototype
template<class TYPE>
inline void AddSingleField(TYPE *v)
{
#ifdef _DEBUG
	tracer << tracer.Indent() << "...SingleField( TYPE )";
#endif

	if (v)
	{
		vrNodeStackItem *ns = GetParser()->nodeStack.Peek();
		if (ns)
		{
//			ASSERT_VALIDPS(ns);
			ASSERT(ns->curNode);
			if (!ns->curNode->SetFieldValue(ns->curField, (void*)v))
			{
				GetParser()->Error("Not able to set field value: " + ns->curField + " in current node: " + ns->curNode->GetRuntimeClass()->ClassName() + endl);
			}
#ifdef _DEBUG
			tracer << " >Setting value in node<";
#endif
		} else
		{
ASSERT(0);
			vrRuntimeClass *pClass = GetParser()->protoStack.Peek();
			if (!pClass->SetFieldValue(ns->curField, (void*)v))
			{
				GetParser()->Error("Not able to set field value: " + ns->curField + " in current prototype: " + pClass->ClassName() + endl);
			}
#ifdef _DEBUG
			tracer << " >Setting default in proto<";
#endif
		}
	} else
	{
#ifdef _DEBUG
			tracer << " >field empty<";
#endif
	}

#ifdef _DEBUG
	tracer << endl;
#endif
}

//------------------------------------------------------------------
// Add a multi field to the current node or prototype
template<class TYPE>
void AddMultiField(TYPE *array)
{
#ifdef _DEBUG
	tracer << tracer.Indent() << "...MultiField( TYPE )";
#endif

	if (array && array->GetCount())
	{
		vrNodeStackItem *ns = GetParser()->nodeStack.Peek();
		if (ns)
		{
//			ASSERT_VALIDPS(ns);
			ASSERT(ns->curNode);
			if (!ns->curNode->SetFieldValue(ns->curField, (void*)&array->array))
			{
				GetParser()->Error("Not able to set field value: " + ns->curField + " in current node: " + ns->curNode->GetRuntimeClass()->ClassName() + endl);
			}
#ifdef _DEBUG
			tracer << " >Setting value in node<";
#endif
		} else
		{
ASSERT(0);
			vrRuntimeClass *pClass = GetParser()->protoStack.Peek();
			if (!pClass->SetFieldValue(ns->curField, (void*)&array->array))
			{
				GetParser()->Error("Not able to set field value: " + ns->curField + " in current prototype: " + pClass->ClassName() + endl);
			}
#ifdef _DEBUG
			tracer << " >Setting default in proto<";
#endif
		}
	} else
	{
#ifdef _DEBUG
			tracer << " >field empty<";
#endif
	}

#ifdef _DEBUG
	tracer << endl;
#endif
}
