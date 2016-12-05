#ifndef _H_TESTS
#define _H_TESTS

vrSolid *Inter(vrSolid *s1, vrSolid *s2);
vrSolid *Union(vrSolid *s1, vrSolid *s2);
vrSolid *Diff(vrSolid *s1, vrSolid *s2);

void Trans (vrSolid *s, SFFloat x, SFFloat y, SFFloat z);
void Rotate(vrSolid *s, SFFloat a, int axis);
void RotCenter(vrSolid *s, SFFloat a, int axis);
void Sc    (vrSolid *s, SFFloat x, SFFloat y, SFFloat z);

vrSolid *Ball(long test, long n);
#define LineSegment void
vrSolid *SplitTests(int test, SFBool merge); //vrLine **normal, 

vrSolid *Part(void);
vrSolid *Pedro(void);
vrSolid *Room(void);
vrSolid *Ball1(void);
vrSolid *Plant(void);
vrSolid *Car(void);
vrSolid *Twist(void);
vrSolid *Primitives(void);
vrSolid *BasicTests(void);
vrSolid *SmallLog(void);
vrSolid *MediumLog(void);
vrSolid *BigLog(void);
vrSolid *ReadFromFile(const SFString& filename);
vrSolid *Twist2(void);
vrSolid *Stamps(void);
vrSolid *SolidBevel(void);
vrSolid *RotSweep(void);
vrSolid *TransSweep(void);

vrSolid *SolidPlane(const vrPlane& p);

vrSolid *BoolTst3(void);
vrSolid *Table(void);

vrSolid *FloorPlan(SFInt32 n, SFVec3f vecs[]);
vrSolid *PedroBool(void);

extern vrSolid *SweepIntersect(vrSolid *top, vrSolid *front, vrSolid *right, SFBool merge);

inline SFBool Write(vrSolid *solid, FILE *out, SFBool forward=FALSE)
{
	if (!out)
		out = stdout;
		
	LISTPOS fPos = solid->faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = solid->faces.GetNext(fPos);
		f->CalcEquation();
	}

	CHECK(solid);

  SFColor curcol = vrBlack;
  
	fprintf(out, "#\n# vertex list\n");
	fprintf(out, "#\n# x, y, z, nx, ny, nz, tx, ty\n#\n");
	fprintf(out, "%d\n", solid->verts.GetCount());

  LISTPOS vPos = solid->verts.GetHeadPosition();
	while (vPos)
	{
		vrVertex *v = solid->verts.GetNext(vPos);
		SFVec3f normal = v->GetNormal(SFVec3f(0));
		SFVec2f tCoord = v->GetTextureCoord(SFVec2f(0));
    fprintf(out, "% 5.5f % 5.5f % 5.5f % 5.5f % 5.5f % 5.5f % 5.5f % 5.5f\n", 
				v->x, v->y, v->z, 
				normal.x, normal.y, normal.z, 
				tCoord.x, tCoord.y);
  }

	fprintf(out, "#\n# face list (faces with colors)\n");
	fprintf(out, "#\n# nVerts v1 v2 v3 ... r g b\n#\n");

  fprintf(out, "%d\n", solid->faces.GetCount());
	//long nF=0;
	
	fPos = solid->faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = solid->faces.GetNext(fPos);
		long nLoops=0;
    LISTPOS lPos = f->loops.GetHeadPosition();
		while (lPos)
		{
			nLoops++;
			ASSERT(nLoops==1);

			vrLoop *l = f->loops.GetNext(lPos);
    
			Uint32 nVerts=0;
			LISTPOS hPos = l->halfedges.GetHeadPosition();
			while (hPos) 
			{
				l->halfedges.GetNext(hPos);
				nVerts++;
			}

			fprintf(out, "%d ", nVerts);
			
			if (forward)
			{
				hPos = l->halfedges.GetHeadPosition();
				while (hPos) 
				{
					vrHalfEdge *he = l->halfedges.GetNext(hPos);
					fprintf(out, "%d ", he->GetIndex());
				}
			} else
			{
				hPos = l->halfedges.GetTailPosition();
				while (hPos) 
				{
					vrHalfEdge *he = l->halfedges.GetPrev(hPos);
					fprintf(out, "%d ", he->GetIndex());
				}
			}
    }
    
    SFColor col = f->GetColor(vrBlack);
		SFInt32 r = (col.x*15);
		SFInt32 g = (col.y*15);
		SFInt32 b = (col.z*15);

		SFInt32 color = (r * (1<<8)) + (g * (1<<4)) + b;

		fprintf(out, "0x%x\n", color);
		//(int)(col.x*255), (int)(col.y*255), (int)(col.z*255));
  }

  return TRUE;
}

inline void Trans(vrSolid *s, SFFloat x, SFFloat y, SFFloat z)
{
  s->TransformGeometry(TranslationMatrix(SFVec3f(x, y, z)));
}

#define XXX 1
#define YYY 2
#define ZZZ 3

inline void Rotate(vrSolid *s, SFFloat a, int axis)
{
  vrMatrix m;

  a = vrDeg2Rad(a);

  switch (axis) {
  case XXX:
    m = RotationXMatrix(a); break;
  case YYY:
    m = RotationYMatrix(a); break;
  case ZZZ:
    m = RotationZMatrix(a); break;
  default:
    exit(0);
//    ASSERT(0);
  }
  s->TransformGeometry(m);
}

inline void RotCenter(vrSolid *s, SFFloat a, int axis)
{
  vrMatrix m;

  long n=0;
	SFVec3f center(0.f, 0.f, 0.f);
	LISTPOS fPos = s->faces.GetHeadPosition();
	while (fPos)
	{
		vrFace *f = s->faces.GetNext(fPos);
		center += f->GetCenter();
		n++;
	}
	center /= (SFFloat)n;

	Trans(s, -center.x, -center.y, -center.z);
	
	a = vrDeg2Rad(a);

  switch (axis) {
  case XXX:
    m = RotationXMatrix(a); break;
  case YYY:
    m = RotationYMatrix(a); break;
  case ZZZ:
    m = RotationZMatrix(a); break;
  default:
    exit(0);
//    ASSERT(0);
  }
  s->TransformGeometry(m);

	Trans(s, center.x, center.y, center.z);
}

inline void Sc(vrSolid *s, SFFloat x, SFFloat y, SFFloat z)
{
  s->TransformGeometry(ScaleMatrix(x, y, z));
}

class vrSolidLamina : public vrSolid
{
public:
  vrSolidLamina(void);
  vrSolidLamina(const vrSolidLamina& a);
  vrSolidLamina& operator=(const vrSolidLamina& a);

  vrSolidLamina(Uint32 n, SFVec3f vecs[]);
  ~vrSolidLamina(void);
  vrSolid *Clone(void) const;
};

inline vrSolidLamina::vrSolidLamina(void) : vrSolid()
{
}

inline vrSolidLamina::vrSolidLamina(const vrSolidLamina& a) : vrSolid(a)
{
}

inline vrSolidLamina::vrSolidLamina(Uint32 n, SFVec3f vecs[]) : vrSolid(vecs[0].x, vecs[0].y, vecs[0].z)
{
	for (Uint32 i=1;i<n;i++)
	{
		smev(0, i-1, vecs[i].x, vecs[i].y, vecs[i].z);
	}
	smef(0, n-1, 0);
}

inline vrSolidLamina::~vrSolidLamina(void)
{
}

inline vrSolidLamina& vrSolidLamina::operator=(const vrSolidLamina& a)
{
  ASSERT(0);
  return *this;
}

inline vrSolid *vrSolidLamina::Clone(void) const
{
  return new vrSolidLamina(*this);
}

class vrSolidCircle : public vrSolid
{
public:
  vrSolidCircle(void);
  vrSolidCircle(const vrSolidCircle& a);
  vrSolidCircle& operator=(const vrSolidCircle& a);

	vrSolidCircle(SFFloat cx, SFFloat cy, SFFloat rad, SFFloat h, Uint32 n);
 ~vrSolidCircle(void);
  vrSolid *Clone(void) const;
};

inline vrSolidCircle::vrSolidCircle(void) : vrSolid()
{
}

inline vrSolidCircle::vrSolidCircle(const vrSolidCircle& a) : vrSolid(a)
{
}

inline vrSolidCircle::vrSolidCircle(SFFloat cx, SFFloat cy, SFFloat rad, SFFloat h, Uint32 n) : vrSolid(cx+rad, cy, h)
{
  Arc(0, 0, cx, cy, rad, h, 0.0f, ((n-1)*360.0f/n), n-1);
  smef(0, n-1, 0);
}

inline vrSolidCircle::~vrSolidCircle(void)
{
}

inline vrSolidCircle& vrSolidCircle::operator=(const vrSolidCircle& a)
{
  ASSERT(0);
  return *this;
}

inline vrSolid *vrSolidCircle::Clone(void) const
{
  return new vrSolidCircle(*this);
}

class vrSolidCube : public vrSolid
{
public:
  vrSolidCube(void);
  vrSolidCube(const vrSolidCube& a);
  vrSolidCube& operator=(const vrSolidCube& a);

  vrSolidCube(SFFloat size);
  ~vrSolidCube(void);
  vrSolid *Clone(void) const;
};

inline vrSolidCube::vrSolidCube(void) : vrSolid()
{
}

inline vrSolidCube::vrSolidCube(const vrSolidCube& a) : vrSolid(a)
{
}

inline vrSolidCube::vrSolidCube(SFFloat size) : vrSolid(0.0f, 0.0f, 0.0f)
{
  smev(0, 0, size,   0.0f, 0.0f);
  smev(0, 1, size, size, 0.0f);
  smev(0, 2,  0.0f, size, 0.0f);
  smef(0, 3, 0);
  TranslationalSweep(findFace(1), SFVec3f(0.0f, 0.0f, size));
}

inline vrSolidCube::~vrSolidCube(void)
{
}

inline vrSolidCube& vrSolidCube::operator=(const vrSolidCube& a)
{
  ASSERT(0);
  return *this;
}

inline vrSolid *vrSolidCube::Clone(void) const
{
	return new vrSolidCube(*this);
}

class vrSolidCylinder : public vrSolidCircle
{
public:
                    vrSolidCylinder (void);
                    vrSolidCylinder (const vrSolidCylinder& a);
  vrSolidCylinder&  operator=       (const vrSolidCylinder& a);

										vrSolidCylinder (SFFloat rad, SFFloat height, Uint32 n);
                   ~vrSolidCylinder (void);
  vrSolid        *Clone           (void) const;
};

inline vrSolidCylinder::vrSolidCylinder(void) : vrSolidCircle()
{
}

inline vrSolidCylinder::vrSolidCylinder(const vrSolidCylinder& a) : vrSolidCircle(a)
{
}

inline vrSolidCylinder::vrSolidCylinder(SFFloat rad, SFFloat height, Uint32 n) : vrSolidCircle(0.0f, 0.0f, rad, 0.0f, n)
{
  TranslationalSweep(findFace(1), SFVec3f(0.0f, 0.0f, height));
//	CHECK(this);
}

inline vrSolidCylinder::~vrSolidCylinder(void)
{
}

inline vrSolidCylinder& vrSolidCylinder::operator=(const vrSolidCylinder& a)
{
  ASSERT(0);
  //vrSolidCircle::operator=(a);
  return *this;
}

inline vrSolid *vrSolidCylinder::Clone(void) const
{
  return new vrSolidCylinder(*this);
}

class vrSolidBall : public vrSolid
{
public:
  vrSolidBall(void);
  vrSolidBall(const vrSolidBall& a);
  vrSolidBall& operator=(const vrSolidBall& a);

  vrSolidBall(SFFloat rad, Uint32 nVert, Uint32 nHoriz);
  ~vrSolidBall(void);
  vrSolid *Clone(void) const;
};

inline vrSolidBall::vrSolidBall(void) : vrSolid()
{
}

inline vrSolidBall::vrSolidBall(const vrSolidBall& a) : vrSolid(a)
{
}

inline vrSolidBall::vrSolidBall(SFFloat rad, Uint32 nVert, Uint32 nHoriz) :
	vrSolid(-rad, 0.0f, 0.0f)
{
  Arc(0, 0, 0.0f, 0.0f, rad, 0.0f, 180.0f, 0.0f, nVert);
  RotationalSweep(nHoriz);

//  CHECK(this);
}

inline vrSolidBall::~vrSolidBall(void)
{
}

inline vrSolidBall& vrSolidBall::operator=(const vrSolidBall& a)
{
  ASSERT(0);
	//vrSolid::operator=(a);
  return *this;
}

inline vrSolid *vrSolidBall::Clone(void) const
{
  return new vrSolidBall(*this);
}

class vrSolidTorus : public vrSolidCircle
{
public:
                vrSolidTorus (void);
                vrSolidTorus (const vrSolidTorus& a);
	vrSolidTorus& operator=    (const vrSolidTorus& a);

               ~vrSolidTorus (void);
								vrSolidTorus (SFFloat rd1, SFFloat rd2, Uint32 nf1, Uint32 nf2);
  vrSolid *Clone        (void) const;
};

inline vrSolidTorus::vrSolidTorus(void) : vrSolidCircle()
{
}

inline vrSolidTorus::vrSolidTorus(const vrSolidTorus& a) : vrSolidCircle(a)
{
}

inline vrSolidTorus::vrSolidTorus(SFFloat rd1, SFFloat rd2, Uint32 nf1, Uint32 nf2) : vrSolidCircle(0.0f, rd1, rd2, 0.0f, nf2)
{
  RotationalSweep(nf1);
//  CHECK(this);
}

inline vrSolidTorus::~vrSolidTorus(void)
{
}

inline vrSolidTorus& vrSolidTorus::operator=(const vrSolidTorus& a)
{
  vrSolidCircle::operator=(a);
  return *this;
}

inline vrSolid *vrSolidTorus::Clone(void) const
{
  return new vrSolidTorus(*this);
}
#endif
#include "../BoolTestDialog.h"