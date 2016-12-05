void DumpFieldList(vrDumpContext& dc, vrFieldList *list, SFBool isExtern, SFBool isScript, const vrNode *node);

void DumpIsMappings(vrDumpContext& dc, const vrNode *node, SFBool showFields=FALSE)
{
	if (node->m_IsMaps.GetCount())
	{
		for (int i=0;i<node->m_IsMaps.GetCount();i++)
		{
			SFString map = node->m_IsMaps[i];
			if (showFields)
			{
				SFInt32 find = map.Find(" IS");
			  ASSERT(find!=-1);
				SFString fieldName = map.Left(find);
				vrField *field = ((vrNode*)node)->FindField(fieldName);
				ASSERT(field);
				dc 
					<< dc.Indent() 
					<< GetEventTypeName(field->GetEventType())
					<< " " 
					<< GetFieldTypeName(field->GetType()) 
					<< " ";
				dc << map << endl;
			} else
			{
			  dc << dc.Indent() << map << endl;
			}
		}
	}
}

#define linebreak(i, nP) ((i%(nP))==(nP-1))
#define indexbreak(i) ((val).GetCount() && (val)[(i)]==-1 && !linebreak(i,20))

#define DO_MULTI(ff, vv, nP, pv, test1, test2) \
{ \
	if ((vv).GetCount()) \
	{ \
		dc << dc.Indent() << (ff) << "\n" << dc.Indent() << "["; \
		dc << "\n"; \
		dc.m_nIndents++; \
		dc << dc.Indent(); \
		for (int i=0;i<(vv).GetCount();i++) \
		{ \
			dc << (pv) << (vv)[(i)] << (pv); \
			int last = (i==(vv).GetCount()-1); \
			if (!last) dc << ","; \
			if ((test1)) \
			{ \
				dc << "\n"; \
				if (!last) dc << dc.Indent(); \
			} else { \
				if (!last) dc << " "; \
			} \
		} \
		if ((test2)) \
			dc << "\n"; \
		dc.m_nIndents--; \
		dc << dc.Indent() << "]\n"; \
	} else \
	{ \
		dc << dc.Indent() << (ff) << " []\n"; \
	} \
}

#define DO_NODE(field, vv) \
{ \
	dc << dc.Indent() << (field) << " "; \
	if (val) \
	{ \
		skipit = TRUE; (vv)->Traverse(this); skipit = FALSE; \
	} else \
		dc << " NULL\n"; \
}

#define DO_SINGLE(field, vv, pv) \
{ \
	dc << dc.Indent() << (field) << " " << (pv) << (vv) << (pv) << "\n"; \
}

void vrWriteTraverser::DumpField(const SFString& fieldName, const MFColor& val, int nPerRow)
{
	DO_MULTI(fieldName, val, nPerRow, "", linebreak(i, nPerRow), !linebreak((i-1), nPerRow));
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const MFFloat& val, int nPerRow)
{
	DO_MULTI(fieldName, val, nPerRow, "", linebreak(i, nPerRow), !linebreak((i-1), nPerRow));
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const MFInt32& val, int nPerRow)
{
	if (!nPerRow)
	{ DO_MULTI(fieldName, val, nPerRow, "", indexbreak(i), !indexbreak((i-1))); }
	else
	{ DO_MULTI(fieldName, val, nPerRow, "", linebreak(i, nPerRow), !linebreak((i-1), nPerRow)); }
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const MFString& val, int nPerRow)
{
	if (val.GetCount()>1)
	{
		DO_MULTI(fieldName, val, nPerRow, "\"", linebreak(i, nPerRow), !linebreak((i-1), nPerRow));
	} else
	{
		if (val.GetCount())
		{
			DO_SINGLE(fieldName, val[0], "\"");
		} else
		{
			DO_SINGLE(fieldName, "[]", "");
		}
	}
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const MFVec2f& val, int nPerRow)
{
	DO_MULTI(fieldName, val, nPerRow, "", linebreak(i, nPerRow), !linebreak((i-1), nPerRow));
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const MFVec3f& val, int nPerRow)
{
	DO_MULTI(fieldName, val, nPerRow, "", linebreak(i, nPerRow), !linebreak((i-1), nPerRow));
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const MFRotation& val, int nPerRow)
{
	DO_MULTI(fieldName, val, nPerRow, "", linebreak(i, nPerRow), !linebreak((i-1), nPerRow));
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const MFNode& val)
{
	dc << dc.Indent() << fieldName << "\n" << dc.Indent() << "[\n";
	dc.m_nIndents++;
	for (int i=0;i<val.GetCount();i++)
	{
		SFNode node = val[i];
		node->Traverse(this);
		dc << "\n";
	}
	dc.m_nIndents--;
	dc << dc.Indent() << "]\n";
}

void vrWriteTraverser::DumpField(const SFString& fieldName, const vrAppearance* val)
{
	DO_NODE(fieldName, val);
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const vrAudioClip* val)
{
	DO_NODE(fieldName, val);
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const vrColor* val)
{
	DO_NODE(fieldName, val);
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const vrCoordinate* val)
{
	DO_NODE(fieldName, val);
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const vrFontStyle* val)
{
	DO_NODE(fieldName, val);
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const vrGeometryNode* val)
{
	DO_NODE(fieldName, val);
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const vrMaterial* val)
{
	DO_NODE(fieldName, val);
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const vrNormal* val)
{
	DO_NODE(fieldName, val);
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const vrPixelTexture* val)
{
	DO_NODE(fieldName, val);
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const vrTextureTransform* val)
{
	DO_NODE(fieldName, val);
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const vrTextureCoordinate* val)
{
	DO_NODE(fieldName, val);
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const SFNode val)
{
	DO_NODE(fieldName, val);
}

void vrWriteTraverser::DumpField(const SFString& fieldName, SFInt32 val)
{
	DO_SINGLE(fieldName, val, "");
}
void vrWriteTraverser::DumpField(const SFString& fieldName, SFBool val)
{
	DO_SINGLE(fieldName, ((val) ? "TRUE" : "FALSE"), "");
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const SFColor& val)
{
	DO_SINGLE(fieldName, val, "");
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const char *val)
{
	SFString v(val);
	DO_SINGLE(fieldName, v, "\"");
}
void vrWriteTraverser::DumpField(const SFString& fieldName, SFFloat val)
{
	DO_SINGLE(fieldName, val, "");
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const SFVec3f& val)
{
	DO_SINGLE(fieldName, val, "");
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const SFVec2f& val)
{
	DO_SINGLE(fieldName, val, "");
}
void vrWriteTraverser::DumpField(const SFString& fieldName, const SFRotation& val)
{
	DO_SINGLE(fieldName, val, "");
}
void vrWriteTraverser::DumpField(const SFString& fieldName, SFTime val)
{
	DO_SINGLE(fieldName, val, "");
}

static int nNames=0;
static SFString names[1024];
SFBool vrWriteTraverser::AddName(char *name)
{
	if (!name)
		return FALSE; // name was not present
	
	for (int i=0;i<nNames;i++)
	{
		if (names[i] == name)
			return TRUE;
	}
	names[nNames++] = name;
	return FALSE; // name was not present
}

//Dictionary *dict=NULL;
/*
SFBool AddName(const SFString& name)
{
	// return TRUE if we've added a new definition

	if (!dict)
		return FALSE;
	
	SFString ss;
	SFString *s = &ss; //char *s = NULL;
	if (dict)
	{
		dict->Lookup(name, s);
		if (!s)
		{
			dict->operator[](name) = strdup("f");
			return TRUE;
		}
	}
	return FALSE;
}
*/

vrNode *GetTop(vrNodeStack<vrGroupingNode *>& stack)
{
	vrNode *top = NULL;
	LISTPOS pos = stack.GetHeadPosition();
	while (pos)
	{	
		top = stack.GetNext(pos);
	}
	return top;
}

class ProtoFind
{
public:
	const vrNode *first;
	vrNode *pro;
};

SFBool FindProtoInstance(vrNode *node, void *data)
{
	if (node->m_NodeType==vrNode::protoGroupInstance)
	{
		ProtoFind *find = (ProtoFind*)data;
		ASSERT(node->IsKindOf(GETRUNTIME_CLASS(vrGroupingNode)));
		vrGroupingNode *group = (vrGroupingNode*)node;
		if (group->GetChildren())
		{
			LISTPOS pos = group->GetChildren()->GetHeadPosition();
			while (pos)
			{
				vrNode *first = group->GetChildren()->GetNext(pos);
				if (first == find->first)
				{
					ASSERT(find->pro == NULL);
					find->pro = group;
					return FALSE;
				}
				pos = NULL;
			}
		}
	}
	return TRUE;
}

extern SFBool IsProtoName(const SFString& nodeName);

SFBool vrWriteTraverser::WriteHead(const vrNode *node)
{
	// Don't write the browser created navigation info
	if (node->GetName() == "_?BROWSER_NAV")
		return TRUE;
	// Don't write the browser created navigation info
	if (node->GetName() == "_?BROWSER_VP")
		return TRUE;

	if (node->m_NodeType==vrNode::protoGroupInstance)
		return TRUE;

	// Don't move without reseting indents
	SFString nodeName = node->GetName();
	SFInt32 find = nodeName.Find("_?");
	if (find!=-1)
		nodeName = nodeName.Left(find);
		
	if (IsProtoName(nodeName))
	{
		ASSERT(node->m_NodeType == vrNode::protoGroup);
extern SFBool DumpPrototype(vrDumpContext& dc, const vrNode *node, vrTraverser *wt);
		SFString save = node->GetName();
		((vrNode*)node)->SetName(nodeName);
		SFBool ret = DumpPrototype(dc, node, this);
		((vrNode*)node)->SetName(save);
		return ret;
	}

	SFInt32 n = dc.m_nIndents;
	if (skipit)
		dc.m_nIndents = 0;

	SFBool found = FALSE;
	if (node->m_NodeType!=vrNode::firstProtoNode)
	{
		if (!nodeName.Empty())
		{
			found = AddName(node->GetName());
			dc << dc.Indent() << ((!found) ? "DEF " : "USE ") << nodeName << " ";
			if (found)
				dc << "\n";
		} else
		{
			dc << dc.Indent();
		}
	}
	dc.m_nIndents = n;
	// USE needs no further work
	if (found)
		return TRUE;

	if (node->m_NodeType==vrNode::firstProtoNode)
	{
		// PROTO instance
//		ASSERT(node->proto);
extern SFBool DumpProtoInstance(vrWriteTraverser *t, vrDumpContext& dc, const vrNode *node);
		vrNode *top = GetTop(parentStack);
		ASSERT(top);
		ProtoFind find;
		find.first = node;
		find.pro = NULL;
		top->ForEvery(FindProtoInstance, &find);
		ASSERT(find.pro);
		found = FALSE;
		nodeName = find.pro->GetName();
		SFInt32 ff = nodeName.Find("_?_");
		if (ff!=-1)
			nodeName = nodeName.Left(ff);
		if (!nodeName.Empty())
		{
			found = AddName(find.pro->GetName());
			dc << dc.Indent() << ((!found) ? "DEF " : "USE ") << nodeName << " ";
			if (found)
				dc << "\n";
		} else
		{
			dc << dc.Indent();
		}
		// USE needs no further work
		if (found)
			return TRUE;
		SFString save = find.pro->GetName();
		((vrNode*)find.pro)->SetName(nodeName);
		SFInt32 ret = DumpProtoInstance(this, dc, find.pro);
		((vrNode*)find.pro)->SetName(save);
		return ret;
	}

	nodeName = node->GetRuntimeClass()->ClassName();
	if (nodeName[0] == 'v' && nodeName[1] == 'r')
		nodeName = nodeName.Mid(2);

	if (m_Verbose || !node->IsDefault() || node->m_IsMaps.GetCount())
	{
		dc << nodeName << endl << dc.Indent() << "{\n";
		// let calling code handle the rest of the node
		return FALSE;
	}

	// default node we are done
	dc << nodeName << " { }\n";
	return TRUE;
}

void vrWriteTraverser::Traverse(const vrEvent *node)
{
}

void vrWriteTraverser::TraverseChildren(const vrGroupingNode *node)
{
	if (node->HasChildren())
	{
		parentStack.Push((vrGroupingNode*)node);

		if (!node->IsKindOf(GETRUNTIME_CLASS(vrBrowser)))
		{
			dc << dc.Indent() << "children\n" << dc.Indent() << "[\n";
		}
		
		dc.m_nIndents++;
		LISTPOS pos = node->GetChildren()->GetHeadPosition();
		while (pos)
		{
			SFNode n = node->GetChildren()->GetNext(pos);
			n->Traverse(this);
			dc << "\n";
		}
		dc.m_nIndents--;

		if (!node->IsKindOf(GETRUNTIME_CLASS(vrBrowser)))
		{
			dc << dc.Indent() << "]\n";
		}

		parentStack.Pop();
	}
}

void vrWriteTraverser::Traverse(const vrBrowser *node)
{
	nNames = 0;
//	if (dict == NULL)
//		dict = new Dictionary;

	dc.m_nIndents--;
	TraverseChildren(node);
	dc.m_nIndents++;

	// Spit out ROUTE's
	DumpRoutes(node, FALSE);

//	if (dict)
//		delete dict;
//	dict = NULL;
}

int sortRoute(const void *rr1, const void *rr2)
{
  vrRoute *r1 = *(vrRoute**)rr1;
  vrRoute *r2 = *(vrRoute**)rr2;
	
	int i = r1->GetRouteID() - r2->GetRouteID();
	return ((i<0) ? -1 : ((i) ? 1 : 0));
}

class RouteArrayData
{
public:
	vrRoute **routes;
	int n;
	SFBool isProto;
	RouteArrayData()
	{
		isProto=FALSE;
		routes = NULL;
		n = 0;
	}
};

SFBool FillRouteArray(SFNode node, void *data)
{
	RouteArrayData *rd = (RouteArrayData*)data;
	vrRouteList *list = node->GetRouteList();
	if (list)
	{
		LISTPOS pos = list->GetHeadPosition();
		while (pos)
		{
			vrRoute *r = list->GetNext(pos);
			SFBool found=FALSE;
			for (int i=0;i<rd->n;i++)
			{
				vrRoute *rr = rd->routes[i];
				if (r == rr)
				{
					// don't double count routes to or from multiply referenced nodes
					found=TRUE;
					break;
				}
			}
			if (!rd->isProto && r->m_Source->m_NodeType!=vrNode::normalNode)
				found=TRUE;
			if (!rd->isProto && r->m_Destination->m_NodeType!=vrNode::normalNode)
				found=TRUE;
			if (!found)
				rd->routes[rd->n++] = r;
		}
	}
	return TRUE;
}

SFBool CountRoutes(SFNode node, void *data)
{
	RouteArrayData *rd = (RouteArrayData*)data;
	vrRouteList *list = node->GetRouteList();
	if (list)
	{
		LISTPOS pos = list->GetHeadPosition();
		while (pos)
		{
			//vrRoute *r = list->GetNext(pos);
			list->GetNext(pos);
			// This overcounts (due to routes of DEF/USE'd nodes,
			// but better to overestimate
			rd->n++;
		}
	}
	return TRUE;
}

void vrWriteTraverser::DumpRoutes(const vrGroupingNode* node, SFBool isProto)
{
// Count routes first
	RouteArrayData data;
	data.isProto = isProto;

	((vrGroupingNode*)node)->ForEvery(CountRoutes, &data);

	data.routes = (vrRoute **)malloc(sizeof(vrRoute*)*data.n);
	
	data.n=0;
	((vrGroupingNode*)node)->ForEvery(FillRouteArray, &data);
	
  // sort the routes as they were read from the original file
	qsort(data.routes, data.n, sizeof(vrRoute*), sortRoute);
	
	for (int i=0;i<data.n;i++)
	{
 		vrRoute *route = data.routes[i];
		if (!route->IsInternal())
		{
			SFString fromName = route->GetNodeName(0);
			if (fromName.Find("_?_")!=-1)
				fromName = fromName.Left(fromName.Find("_?_"));
			ASSERT(!fromName.Empty());
			SFString toName = route->GetNodeName(1);
			if (toName.Find("_?_")!=-1)
				toName = toName.Left(toName.Find("_?_"));
			ASSERT(!toName.Empty());
			dc << dc.Indent() 
				<< "ROUTE " <<  fromName
				<< "." << route->GetFieldName(0)
				<< " TO " << toName
				<< "." << route->GetFieldName(1)
				<< "\n";
		}
	}

	free(data.routes);
}

void vrWriteTraverser::Traverse(const SFNode node)
{
}

void vrWriteTraverser::SetFilename(const SFString& filename)
{
	dc.Close();
	dc.SetFilename(filename);
}

void vrWriteTraverser::SetTabStop(int n, char c)
{
	dc.m_TabStop = n;
	dc.m_TabChar = c;
}