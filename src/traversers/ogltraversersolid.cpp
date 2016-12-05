//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Windows.h"
#include "gl\gl.h"
#include "gl\glu.h"

#include "OGLTraverser.h"
#include "Nodes\Appearance\Material.h"

#include "Solid\Solid.h"
#include "Solid\Face.h"
#include "Solid\Loop.h"
#include "Solid\Edge.h"
#include "Solid\HalfEdge.h"
#include "Solid\Vertex.h"

//-------------------------------------------------------------------
// Routines for traversing and drawing solid objects
//-------------------------------------------------------------------
#if 1
inline void DrawFaceNormalsTexCoords(vrOGLTraverser *traverser, const vrFace *face)
{
	SFVec3f faceNormal = face->GetNormal();

	glBegin(GL_POLYGON);
	LISTPOS hPos = face->GetLoopOut()->halfedges.GetTailPosition();
	while (hPos)
	{
		vrHalfEdge *he = face->GetLoopOut()->halfedges.GetPrev(hPos);
    SFVec3f v = *he->GetVertex();
    SFVec3f n = he->GetNormal(faceNormal);
    SFVec2f t = traverser->TransformTexCoord(he->GetTextureCoord(SFVec2f(0,0)));

		glTexCoord2fv((SFFloat*)&t);
		glNormal3fv((SFFloat*)&n);
		glVertex3fv((SFFloat*)&v);
  }
	glEnd();
}
#else
static int i=1;

inline void DoIt(vrOGLTraverser *traverser, vrHalfEdge *he, const SFVec3f& normal)
{
	if (he)
	{
		SFVec3f v = *he->GetVertex();
		SFVec3f n = he->GetNormal(normal);
		SFVec2f t = traverser->TransformTexCoord(he->GetTextureCoord(SFVec2f(0,0)));
//glColor3f(1.0, 0.0, 0.0);
		glTexCoord2fv((SFFloat*)&t);
		glNormal3fv((SFFloat*)&n);
		glVertex3fv((SFFloat*)&v);
	}
}

inline void DrawFaceNormalsTexCoords(vrOGLTraverser *traverser, const vrFace *face)
{
	SFVec3f faceNormal = face->GetNormal();

	glColor3f(colorMap[i%MAX_COLORS].x, colorMap[i%MAX_COLORS].y, colorMap[i%MAX_COLORS].z);
	i++;

	glBegin(GL_TRIANGLE_FAN);

	// First vertex
	vrHalfEdge *he = face->GetLoopOut()->halfedges.GetTail();
	DoIt(traverser, he, faceNormal);
	DoIt(traverser, he->Prev(), faceNormal);

	vrHalfEdge *start = he;
	do
	{
		DoIt(traverser, he->Next(), faceNormal);
		he->GetFace()->SetMark1((Uint32)BELOW);
		if (he->GetMate())
			he = he->GetMate()->Next();
		else
			he = NULL;
	} while (he && he != start);

/*
	// Second vertex
	he = he->Prev();
		DoIt(traverser, he, faceNormal);

	SFBool first = TRUE;
	while (face->Marked1(ABOVE))
	{
		// Third and final vertex
		he = he->Prev();
			DoIt(traverser, he, faceNormal);
//	}
		// Visited face1
		((vrFace*)face)->SetMark1((Uint32)BELOW);

		if (!first)
			he = he->Prev();
		he = he->GetMate();
		face = he->GetFace();
		first = FALSE;
	}
*/
	glEnd();
}
#endif

inline void DrawFaceColorsNormalsTexCoords(vrOGLTraverser *traverser, const vrFace *face)
{
	SFVec3f faceNormal = face->GetNormal();

	glBegin(GL_POLYGON);
	LISTPOS hPos = face->GetLoopOut()->halfedges.GetTailPosition();
	while (hPos)
	{
		vrHalfEdge *he = face->GetLoopOut()->halfedges.GetPrev(hPos);
    SFVec3f v = *he->GetVertex();
    SFVec3f n = he->GetNormal(faceNormal);
    SFVec2f t = traverser->TransformTexCoord(he->GetTextureCoord(SFVec2f(0,0)));

		SFColor color = vrBlack;
		if (traverser->currMaterial)
			color = traverser->currMaterial->GetEmissiveColor(); // ...or emmisive color if available

    SFColor   c = he->GetColor(face->GetColor(color));

		glTexCoord2fv((SFFloat*)&t);
		glNormal3fv((SFFloat*)&n);
		glColor3fv((SFFloat*)&c);
		glVertex3fv((SFFloat*)&v);
  }
	glEnd();
}

inline void DrawFaceNoColor(const vrFace *face)
{
	glBegin(GL_LINE_STRIP);
	LISTPOS hPos = face->GetLoopOut()->halfedges.GetTailPosition();
	while (hPos)
	{
		vrHalfEdge *he = face->GetLoopOut()->halfedges.GetPrev(hPos);
    SFVec3f v = *he->GetVertex();
		glVertex3fv((SFFloat*)&v);
  }
	glEnd();
}

inline void DrawFaceWithColor(vrOGLTraverser *traverser, const vrFace *face)
{
	glBegin(GL_LINE_STRIP);
	LISTPOS hPos = face->GetLoopOut()->halfedges.GetTailPosition();
	while (hPos)
	{
		vrHalfEdge *he = face->GetLoopOut()->halfedges.GetPrev(hPos);
    SFVec3f v = *he->GetVertex();

		SFColor color = vrBlack;
		if (traverser->currMaterial)
			color = traverser->currMaterial->GetEmissiveColor(); // ...or emmisive color if available

    SFColor c = he->GetColor(face->GetColor(color));

		glColor3fv((SFFloat*)&c);
		glVertex3fv((SFFloat*)&v);
  }
	glEnd();
}

void vrOGLTraverser::Traverse(const vrSolid *node)
{
  if (!node || !node->verts.GetCount())
		return;
		
	// Do not change the order of these tests
	if (node->Marked(FACE_SET))
	{
		if (node->m_SolidColor)
		{
#if 1
			LISTPOS fPos = node->faces.GetHeadPosition();
			while (fPos)
			{
				vrFace *f = node->faces.GetNext(fPos);
				ASSERT(f->nLoops()==1);
				ASSERT(f->Marked2(CALCED));
			  if (!f->Marked2(INVISIBLE))
					DrawFaceNormalsTexCoords(this, f);
//				else
//				{
//					glPushAttrib(GL_ALL_ATTRIB_BITS);
//					vrMaterial mat;
//					mat.SetTransparency(0.75);
//					mat.SetDiffuseColor(vrYellow);
//					Traverse(&mat);
//					DrawFaceNormalsTexCoords(this, f);
//					glPopAttrib();
//				}
			}
#else
	i=1;
			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

			// Mark all the faces
			LISTPOS fPos = node->faces.GetHeadPosition();
			while (fPos)
			{
				vrFace *f = node->faces.GetNext(fPos);
				ASSERT(f->nLoops()==1);
				ASSERT(f->Marked2(CALCED));
				f->SetMark1(ABOVE);
			}

			// Now draw them
			fPos = node->faces.GetHeadPosition();
			while (fPos)
			{
				vrFace *f = node->faces.GetNext(fPos);
			  if (!f->Marked2(INVISIBLE) && f->Marked1(ABOVE))
					DrawFaceNormalsTexCoords(this, f);
			}
//				else
//				{
//					glPushAttrib(GL_ALL_ATTRIB_BITS);
//					vrMaterial mat;
//					mat.SetTransparency(0.75);
//					mat.SetDiffuseColor(vrYellow);
//					Traverse(&mat);
//					DrawFaceNormalsTexCoords(this, f);
//					glPopAttrib();
//				}
#endif
		} else
		{
			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
			LISTPOS fPos = node->faces.GetHeadPosition();
			while (fPos)
			{
				vrFace *f = node->faces.GetNext(fPos);
				ASSERT(f->nLoops()==1);
				ASSERT(f->Marked2(CALCED));
			  if (!f->Marked2(INVISIBLE))
					DrawFaceColorsNormalsTexCoords(this, f);
			}
			glDisable(GL_COLOR_MATERIAL);
		}
	} else if (node->Marked(LINE_SET))
	{
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		
		if (node->m_SolidColor)
		{
			// no color node so use black or emmisiveColor if available for all lines
			SFColor color = vrBlack;
			if (currMaterial)
				color = currMaterial->GetEmissiveColor(); // ...or emmisive color if available
			glColor3f(color.x, color.y, color.z);
			LISTPOS fPos = node->faces.GetHeadPosition();
			while (fPos)
			{
				vrFace *f = node->faces.GetNext(fPos);
				DrawFaceNoColor(f);
			}
		} else
		{
			LISTPOS fPos = node->faces.GetHeadPosition();
			while (fPos)
			{
				vrFace *f = node->faces.GetNext(fPos);
				DrawFaceWithColor(this, f);
			}
		}
	} else
	{
		ASSERT(node->Marked(POINT_SET));
	}

//	glDisable(GL_LIGHTING);
//	LISTPOS vPos = node->verts.GetHeadPosition();
//	while (vPos)
//	{
//		vrVertex *v = node->verts.GetNext(vPos);
//	  SFColor c = v->GetHe()->GetColor(vrWhite);
//		glColor3fv((SFFloat*)&c);
//		DrawPoint(*v, 0.125, 0);
//	}

  return;
}

void vrOGLTraverser::DrawComplexFace(const vrFace *node)
{
ASSERT(0);
/*
  ASSERT(node);
	
  vrFace *copy = new vrFace(*node);
	vrSolid *s = new vrSolid;

	copy->SetSolid(s);
	s->AddFace(copy);
	s->Cleanup();

  //
   // Find the the he in lout and the he in the interior
   // loop that are closest together 
   ///
	vrHalfEdge *he1, *he2;
  copy->FindTwoClosest(&he1, &he2);

  // and make an edge between them
	s->lmekr(he1, he2);

	Traverse(s);
	delete s;
*/
}

void vrOGLTraverser::DrawSimpleFace(const vrFace *face)
{
ASSERT(0);
/*
  if (face->Marked2(INVISIBLE))
		return;
	
	ASSERT(face->Marked2(CALCED));
	SFVec3f faceNormal = face->GetNormal();

glEnable(GL_COLOR_MATERIAL);
glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glBegin(GL_POLYGON);
	LISTPOS hPos = face->GetLoopOut()->halfedges.GetTailPosition();
	while (hPos)
	{
		vrHalfEdge *he = face->GetLoopOut()->halfedges.GetPrev(hPos);
    SFVec3f v = *he->GetVertex();
    SFVec3f n = he->GetNormal(faceNormal);
    SFVec2f t = TransformTexCoord(he->GetTextureCoord(SFVec2f(0,0)));
    SFColor   c = he->GetVertex()->GetColor(vrWhite);
		glColor3fv((SFFloat*)&c);
		glTexCoord2fv((SFFloat*)&t);
		glNormal3fv((SFFloat*)&n);
		glVertex3fv((SFFloat*)&v);
  }
	glEnd();
*/
}

void vrOGLTraverser::Traverse(const vrFace *node)
{
/*
  if (node->nLoops() != 1)
	{
    DrawComplexFace(node);
  } else
	{
    DrawSimpleFace(node);
  }
*/
}

void DrawPoint(const SFVec3f& pt, SFFloat size, Uint32 state)
{
  vrMatrix T0 = TranslationMatrix(pt);

  glPushMatrix();
  glMultMatrixf(&T0.vals[0][0]);

  GLUquadricObj *newObj = gluNewQuadric();

	gluQuadricDrawStyle(newObj, GLU_FILL);
  gluQuadricNormals   (newObj, GL_SMOOTH); //(state & M_SMOOTH) ? GL_SMOOTH : GL_FLAT);
  gluQuadricDrawStyle (newObj, GL_TRIANGLES); //(state & M_WIREFRAME)  ? GL_LINE_LOOP : GL_TRIANGLES);
	gluQuadricTexture(newObj, GL_FALSE);

  gluSphere(newObj, size, 3, 3);
//  gluBlock(newObj, size, size, size);

  gluDeleteQuadric(newObj);
  
  glPopMatrix();
}

