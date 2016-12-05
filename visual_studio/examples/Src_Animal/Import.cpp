#include "Stdafx.h"

#include "Import.h"

inline void error(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

inline void lower(char *s)
{
	while (*s)
	{
		*s = tolower(*s);
		s++;
	}
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

inline SFBool getnextline(FILE *fp, char *s)
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

vrNode *MakeIFS(MFVec3f *coords, MFVec3f *normals, MFInt32 *faces, MFColor *colors)
{
	vrIndexedFaceSet *ifs = new vrIndexedFaceSet;

	ASSERT(coords);
	vrCoordinate *cs = new vrCoordinate;
	cs->SetPoint(*coords);
	ifs->AddChild(cs);

	ASSERT(faces);
	ifs->SetCoordIndex(*faces);
	ifs->SetCreaseAngle(0.01);

	vrColor *cols = NULL;
	if (colors)
	{
		cols = new vrColor;
		cols->SetColor(*colors);
		ifs->AddChild(cols);
		ifs->SetColorPerVertex(FALSE);
	}

/*
	vrNormal *norms = NULL;
	if (normals)
	{
		norms = new vrNormal;
		norms->SetVector(*normals);
		ifs->AddChild(norms);
		ifs->SetNormalPerVertex(FALSE);
	}
*/
	
	vrMaterial *mat = new vrMaterial;
	mat->SetShininess(0.1);
	vrAppearance *app = new vrAppearance;
	app->SetMaterial(mat);

	vrShape *shape = new vrShape;
	vrGeometryNode *geom = ifs;
	shape->SetGeometry(geom);
	shape->SetAppearance(app);
	return shape;
}

vrNode *parse_geo(FILE *in, vrAxisAlignedBox& box)
{
  SFInt32      nCoords;
  SFInt32      nFaces;

	SFBool       hasNormals=TRUE;

	MFVec3f      coords;
//	MFVec3f      normals;
  MFInt32      faces;
//	MFColor      colors;

	char s[1000];
	s[0] = '\0';

	// How many verts?
	if (!getnextline(in, s)) 
	{ 
		// error no verts
		//ASSERT(0); 
		return NULL;
	}
	sscanf(s, "%d %d\n", &nCoords, &nFaces);

	for (int i=0;i<nCoords;i++)
	{
		if (!getnextline(in, s))
		{
			// error not enough verts --> must release memory
			//ASSERT(0); 
			return NULL;
		}
		SFFloat x, y, z, nx, ny, nz;
		//int r = sscanf(s, "%f %f %f", &x, &y, &z, &nx, &ny, &nz);
		sscanf(s, "%f %f %f", &x, &y, &z, &nx, &ny, &nz);
		SFVec3f v(x, -y, z);
		box.Include(v);
		SFVec3f n(nx, ny, nz);
//		if (r == 3)
//		{
			hasNormals = FALSE;
			coords.AddValue(v);
//		} else
//		{
//			ASSERT(r==6);
//			coords.AddValue(v);
//			normals.AddValue(n);
//		}
	}  

/*
	// How many faces?
	if (!getnextline(in, s)) 
	{ 
		// error no faces --> must release memory 
		ASSERT(0); return NULL;
	}
	sscanf(s, "%d\n", &nFaces);
*/

	// Read them
	for (i=0;i<nFaces;i++)
	{
		if (!getnextline(in, s)) 
		{
			// error not enough faces --> must release memory
			ASSERT(0); return NULL;
		}

		// How many indicies?
		int nIndicies;
		sscanf(s, "%d", &nIndicies);

		MFInt32 face;
		char *ss = Skip(s);
		for (int k=0;k<nIndicies;k++)
		{
			SFInt32 index;
			sscanf(ss, "%d ", &index);
			ss = Skip(ss);
			face.AddValue(index);
		}
		for (int kk=face.GetCount()-1;kk>=0;kk--)
		{
			faces.AddValue(face[kk]); //.GetValue(kk));
		}
		faces.AddValue(-1);

		// read color
/*
		SFInt32 color = 0xfff;
		if (ss[0])
		{
			sscanf(ss, "%x\n", &color);
		}
		SFColor col;
		col.x = ((SFFloat)((color >> 8) & 0xf)/16.f);
		col.y = ((SFFloat)((color >> 4) & 0xf)/16.f);
		col.z = ((SFFloat)((color) & 0xf)/16.f);
*/
//		colors.AddValue(vrWhite);
	}

	return MakeIFS(&coords, NULL, &faces, NULL);
}

vrNode *parse_tbl(FILE *in, vrAxisAlignedBox& box)
{
	vrGroup *group = new vrGroup;

	char s[1000];
	while (fgets(s, 1000, in))
	{
		if (strchr(s, '\n')) *strchr(s, '\n') = '\0';
		char *ss = Skip(s);
		ss = Skip(ss);
		FILE *fp = fopen(ss, "r");
		if (fp)
		{
			vrNode *n = parse_nff(fp, box);
			if (n)
				group->AddChild(n);
			fclose(fp);
		}
	}
	return group;
}

vrNode *parse_nff(FILE *in, vrAxisAlignedBox& box)
{
  SFInt32      nCoords;
  SFInt32      nFaces;

	SFBool       hasNormals=TRUE;

	MFVec3f      coords;
	MFVec3f      normals;
  MFInt32      faces;
	MFColor      colors;

	char s[1000];
	s[0] = '\0';

	// How many verts?
	if (!getnextline(in, s)) 
	{ 
		// error no verts
		//ASSERT(0); 
		return NULL;
	}
	sscanf(s, "%d\n", &nCoords);

	for (int i=0;i<nCoords;i++)
	{
		if (!getnextline(in, s))
		{
			// error not enough verts --> must release memory
			//ASSERT(0); 
			return NULL;
		}
		SFFloat x, y, z, nx, ny, nz;
		int r = sscanf(s, "%f %f %f %f %f %f", &x, &y, &z, &nx, &ny, &nz);
		SFVec3f v(x, -y, z);
		box.Include(v);
		SFVec3f n(nx, ny, nz);
		if (r == 3)
		{
			hasNormals = FALSE;
			coords.AddValue(v);
		} else
		{
			ASSERT(r==6);
			coords.AddValue(v);
			normals.AddValue(n);
		}
	}  

	// How many faces?
	if (!getnextline(in, s)) 
	{ 
		// error no faces --> must release memory 
		ASSERT(0); return NULL;
	}
	sscanf(s, "%d\n", &nFaces);

	// Read them
	for (i=0;i<nFaces;i++)
	{
		if (!getnextline(in, s)) 
		{
			// error not enough faces --> must release memory
			ASSERT(0); return NULL;
		}

		// How many indicies?
		int nIndicies;
		sscanf(s, "%d", &nIndicies);

		MFInt32 face;
		char *ss = Skip(s);
		for (int k=0;k<nIndicies;k++)
		{
			SFInt32 index;
			sscanf(ss, "%d ", &index);
			ss = Skip(ss);
			face.AddValue(index);
		}
		for (int kk=face.GetCount()-1;kk>=0;kk--)
		{
			faces.AddValue(face[kk]); //.GetValue(kk));
		}
		faces.AddValue(-1);

		// read color
		SFInt32 color = 0xfff;
		if (ss[0])
		{
			sscanf(ss, "%x\n", &color);
		}
		SFColor col;
		col.x = ((SFFloat)((color >> 8) & 0xf)/16.f);
		col.y = ((SFFloat)((color >> 4) & 0xf)/16.f);
		col.z = ((SFFloat)((color) & 0xf)/16.f);
		colors.AddValue(col);
	}

	return MakeIFS(&coords, &normals, &faces, &colors);
}
