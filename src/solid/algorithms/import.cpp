//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Solid\Solid.h"

#include "Map.h"

//XXXXXXXXXXXXX//
typedef vrMap<void*, void*> vrMapPtrToPtr;

vrMapPtrToPtr heMap;

void AddHalfEdge(vrSolid *s, Uint32 next, Uint32 prev, vrHalfEdge *he)
{
	void *x=NULL;
	Uint32 mapIndex = (next*100000)+prev;

	vrEdge *e;
	if (heMap.Lookup((void*)mapIndex, x))
	{
		vrHalfEdge *mate = (vrHalfEdge *)x;
		ASSERT(mate);
		e = mate->GetEdge();
		e->SetHe(HE1, he);
	} else
	{
		e = new vrEdge(s);
		e->SetHe(HE2, he);

		mapIndex = (prev*100000)+next;
		heMap.SetAt((void*)mapIndex, he);
	}
	he->GetVertex()->SetHe(he);
	he->SetEdge(e);
}

void vrSolid::BuildFromIndexSet(const vrVertexArray& verticies, const MFInt32& indicies)
{
	heMap.RemoveAll();

	ASSERT(faces.GetCount()==0);
	ASSERT(verts.GetCount()==0);
	ASSERT(edges.GetCount()==0);
	
	if (indicies.GetCount()<3 || verticies.GetCount()<3)
	{
		return;
	}
	
	vrHalfEdge *he;

	// prepare for the first face
	vrFace *f = new vrFace(this);
	vrLoop *l = new vrLoop(f);
	SFInt32 prev  = indicies[0];
	SFInt32 first = prev;
	SFInt32 next  = -1;

	SFInt32 nIndicies = indicies.GetCount();
	for (int i=1;i<nIndicies;i++)
	{
		next = indicies[i];
		if (next != -1)
		{
			he = new vrHalfEdge(verticies[prev]);
			l->halfedges.AddTail(he);
			he->SetLoop(l);
			AddHalfEdge(this, prev, next, he);
		} else
		{
			he = new vrHalfEdge(verticies[prev]);
			l->halfedges.AddTail(he);
			he->SetLoop(l);
			AddHalfEdge(this, prev, first, he);
			
			// if this is a degenerate face then remove it
			if (f && f->GetLoopOut() && f->GetLoopOut()->halfedges.GetCount()<3)
			{
				faces.RemoveAt(f);
			}

			i++;
			if (i < nIndicies)
			{
				first = next = indicies[i];
				// prepare for the next face
				f = new vrFace(this);
				l = new vrLoop(f);
			} else
			{
				// end of list
				f = NULL;
				l = NULL;
			}
		}
		prev = next;
	}
	
	// last index need not be -1 so finish up
	if (f)
	{
		if (f->GetLoopOut() && f->GetLoopOut()->halfedges.GetCount()>=2)
		{
			// This is a real face so add it
			if (first != -1)
			{
				ASSERT(l);
				he = new vrHalfEdge(verticies[prev]);
				l->halfedges.AddTail(he);
				he->SetLoop(l);
				AddHalfEdge(this, prev, first, he);
			}
		} else
		{
			// This is a degenerate face so remove it
			faces.RemoveAt(f);
			delete f;
		}
	}
//  DEB(this, "Before cleanup");

	Cleanup();
	Renumber();
//  DEB(this, "After cleanup");

	Revert();
// DEB(this, "After revert");
//	CHECK(this);

	heMap.RemoveAll();
}

/*
void vrSolid::Import(FILE *fp)
{
#if 0
  Uint32       nVecs;
	wVectorArray vecs;
  Uint32       nFaces;
  wFaceArray   faceArray;

	vecs.SetSize(1000,1000);
	faceArray.SetSize(1000,1000);
	
	char s[1000];

	// How many verts?
	if (!getnextline(fp, s)) 
	{ 
		// error no verts
		//ASSERT(0); 
		return;
	}
	sscanf(s, "%d\n", &nVecs);
//	sscanf(s, "%d %d", &nVecs, &nFaces);

	// Read them
	vrMatrix spin = RotationXMatrix(vrDeg2Rad(-90.0));
	
	for (Uint32 i=0;i<nVecs;i++)
	{
		if (!getnextline(fp, s))
		{
			// error not enough verts --> must release memory
			//ASSERT(0); 
			return;
		}
		SFFloat x, y, z;
		sscanf(s, "%f %f %f", &x, &y, &z);
		SFVec3f *v = new SFVec3f(x, y, z);
		*v = spin * (*v);
		vecs.SetAtGrow(i, v);
	}  

	// How many faces?
	if (!getnextline(fp, s)) 
	{ 
		// error no faces --> must release memory 
		ASSERT(0); return;
	}
	sscanf(s, "%d\n", &nFaces);

	// Read them
	Uint32 added=0;
	for (i=0;i<nFaces;i++)
	{
		if (!getnextline(fp, s)) 
		{
			// error not enough faces --> must release memory
			ASSERT(0); return;
		}

		wSimpleFace *f = new wSimpleFace;

		// How many indicies?
		//sscanf(s, "%d", &f->nIndicies);
		//ASSERT(f->nIndicies);
		f->nIndicies = 3;

		char *ss = s; //Skip(s);
		for (Uint32 k=0;k<f->nIndicies;k++)
		{
			Uint32 *index = new Uint32;
			sscanf(ss, "%d ", index);
//			// For 'off' index is '1' based
//			*index = (*index)-1;
			*index = (*index);
			ss = Skip(ss);
			f->indexList.AddTail(index);
		}

		// read color
		int col[3];
		for (k=0;k<3;k++)
		{
			sscanf(ss, "%d ", &col[k]);
			ss = Skip(ss);
		}
		f->color.x = (SFFloat)(col[0]/255.f);
		f->color.y = (SFFloat)(col[1]/255.f);
		f->color.z = (SFFloat)(col[2]/255.f);

#if 0
		Uint32 color = 0xfff;
		if (ss[0])
		{
			sscanf(ss, "%x\n", &color);
		}
		f->color.x = ((SFFloat)((color >> 8) & 0xf)/16.f);
		f->color.y = ((SFFloat)((color >> 4) & 0xf)/16.f);
		f->color.z = ((SFFloat)((color) & 0xf)/16.f);
#endif

#if 1
#if 0
		if (AfxGetApp()->GetProfileInt("Debug", "A", FALSE))
		{
			f->color = vrRed;
//			ff->color = vrWhite;
		} else
		{
			f->color = Green;
//			ff->color = Yellow;
		}
#endif

//		ss = strstr(ss, "both");
//		if (ss)
		faceArray.SetAtGrow(added++, f);
		{
//			faceArray.SetAtGrow(added++, (void *)ff);
		}
#else
		wSimpleFace *ff = Reverse(f);

		if (AfxGetApp()->GetProfileInt("Debug", "A", FALSE))
		{
			f->color = vrRed;
			ff->color = vrWhite;
		} else
		{
			f->color = Green;
			ff->color = Yellow;
		}

//		ss = strstr(ss, "both");
//		if (ss)
		faceArray.SetAtGrow(added++, (void *)f);
		{
			faceArray.SetAtGrow(added++, (void *)ff);
		}
#endif
	}  

	BuildFromFaceList(nVecs, vecs, added, faceArray);

//	SetName(filename);

//Revert();

//	CHECK(this);
//	RemoveCoplaneColine();

//afxTraceEnabled=TRUE;
	DEB(this, "After Import");
#endif
}
*/

/*
wSimpleFace *Reverse(wSimpleFace *f)
{
	wSimpleFace *ff = new wSimpleFace;

	// How many indicies?
	ff->nIndicies = f->nIndicies;

	ff->color = f->color;

	POSITION pos = f->indexList.GetTailPosition();
	while (pos)
	{
		Uint32 *ind = f->indexList.GetPrev(pos);
		Uint32 *index = new Uint32(*ind);
		ff->indexList.AddTail(index);
	}
	return ff;
}

inline char *Skip(char *s)
{
	if (!s) return s;
	
	// skip to next white space
	while (*s && (*s != ' ' && *s != '\t'))
		s++;
	// skip over white space
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return s;
}

SFBool getnextline(FILE *fp, char *s)
{
	if (!fgets(s, 1000, fp)) return FALSE;

	// skip over white space
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	
	while (1)
	{
		// Look for a non-blank line starting with a numeral or EOF
		if (isdigit(s[0]) || s[0] == '-')
		{
			return TRUE;
		}
		if (!fgets(s, 1000, fp)) return FALSE;
	}
	ASSERT(0); // never happens
	return FALSE;
}
*/

