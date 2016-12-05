#define INITGUID
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Windows.h"
#include "gl\gl.h"
#include "gl\glu.h"

#include "OGLTraverser.h"
#include "Browser\Browser.h"
#include "Nodes\AllNodes.h"
#include "Solid\Solid.h"

IMPLEMENT_NODE(vrOGLTraverser, vrRenderTraverser);

void glCheck(vrBrowser *b);
//#define glCheck(a)

extern SFBool texTransform;
/*
vrMatrix vrOGLTraverser::GetProjectMatrix(const vrBrowser *node)
{
}
*/

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrBrowser *node)
{
 	if (!node) return;
	if (!node->HasChildren())
		return;

	// reset texture coord transform
	m_TextureCoordTransform = IdentityMatrix();

	vrViewpoint *vp = node->GetViewpoint();
	if (!vp)
	{
		vp = new vrViewpoint;
		vp->SetName("_?BROWSER_VP");
		((vrBrowser*)node)->AddChild(vp);
		((vrBrowser*)node)->Bind(vp, TRUE);
	}
	vrNavigationInfo *nav = node->GetNavigationInfo();
	if (!nav)
	{
		nav = new vrNavigationInfo;
		nav->SetName("_?BROWSER_NAV");
		((vrBrowser*)node)->AddChild(nav);
		((vrBrowser*)node)->Bind(nav, TRUE);
	}

	SFVec3f    pos       = vp->GetPosition();
	SFRotation rot       = vp->GetOrientation();
	float      viewAngle = vrRad2Deg(rot.w);
	float      hither    = nav->GetAvatarSize(0);
	float      yon       = nav->GetVisibilityLimit();
	if (yon == 0.0)
		yon = 100.0;
	SFFloat    fov       = vrRad2Deg(vp->GetFieldOfView());

	glPushAttrib(GL_ALL_ATTRIB_BITS);
#ifdef _DEBUG
glCheck(m_Browser);
#endif

	glDisable(GL_TEXTURE_2D);
	glDepthRange(hither, yon);

	GLuint hits[256];
	if (m_isPicking)
	{
		glSelectBuffer(256, hits);
		memset(hits, 0, 256*sizeof(GLuint));
		glRenderMode(GL_SELECT);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (m_isPicking)
	{
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		SFVec3f mouseLoc = GetMousePos();
		gluPickMatrix(mouseLoc.x, (viewport[3]-viewport[1])-mouseLoc.y, 10, 10, viewport); // windows is upside down!
		glInitNames();
	}

	float winAspect = (float)GetViewport().Width() / (float)GetViewport().Height();
	if (winAspect > 1.0f)
		viewAngle /= winAspect;
	gluPerspective(fov, winAspect, hither, yon);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	SFColor clearColor = vrBlack;
	vrBackground *b = m_Browser->GetBackground();

	// Clear the screen if the background does not exist (or
	// if it exists with a clear only
 	if (!b || b->IsClearOnly())
	{ 
		if (b)
		{
			clearColor = b->GetSkyColor(0);
		}
	}
	glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_FOG);
	vrFog *fog = node->GetFog();
	if (fog)
	{
		if (fog->GetVisibilityRange()>0)
		{
			glEnable(GL_FOG);
			if (!strcmp(fog->GetFogType(), "LINEAR"))
			{
				glFogf(GL_FOG_MODE, GL_LINEAR);
			} else
			{
				ASSERT(!strcmp(fog->GetFogType(), "EXPONENTIAL"));
				glFogf(GL_FOG_MODE, GL_EXP);
			}
			glFogf(GL_FOG_END, fog->GetVisibilityRange());
			SFColor fogColor = fog->GetColor();
			glFogfv(GL_FOG_COLOR, (GLfloat*)&fogColor.x);
		}
	}

	((vrBrowser*)node)->SetRotation(SFRotation(zAxis,0));
	((vrBrowser*)node)->SetTranslation(origin);
	((vrBrowser*)node)->SetCenter(origin);

//	glMultMatrixf((GLfloat*)&vp->m_ParentTransform.vals[0][0]);
	glRotatef(-vrRad2Deg(rot.w), rot.x, rot.y, rot.z);
	glTranslatef(-pos.x, -pos.y, -pos.z);

	glDisable(GL_LIGHTING);
	if (nav->GetHeadlight())
	{
		static vrDirectionalLight light;
		light.SetAmbientIntensity(0.5);

		SFBool save = m_DrawLights;
		m_DrawLights = FALSE;
		glEnable(GL_LIGHTING);
		Traverse(&light);	
		m_DrawLights = save;
	}

	Traverse((vrTransform*)node);

	if (m_isPicking) 
	{
		// Check to see if anything was picked
		SFInt32 nHits = glRenderMode(GL_RENDER);
		if (nHits)
		{
			GLuint *ptr = hits;
			GLuint min = (GLuint)-1;
			for (int i=0;i<nHits;i++)
			{
				GLuint cnt = *ptr;
				GLuint m = *(ptr+1);
				if (m < min)
				{
					if (cnt)
					{
						vrGroupingNode *sel = ((vrGroupingNode*)*(ptr+3+cnt-1));
						m_Browser->SetSelection(sel);
						// This will fail (and get caught) if this is an invalide pointer
						VCHECK(sel);
					} else
					{
						m_Browser->SetSelection(NULL);
					}
					min = m;
				}
				ptr += (3 + cnt);
			}
		}
	}

	glPopAttrib();
#ifdef _DEBUG
glCheck(m_Browser);
#endif


	return;
}

//-------------------------------------------------------------------
void vrOGLTraverser::PreTraverse()
{
	if (!m_isPicking && !m_Browser->HasChildren())
	{
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

#ifndef RELEASE
	char str[256];
	SetBkMode((HDC)m_hDC, TRANSPARENT);
	SetTextColor((HDC)m_hDC, RGB(255,255,0));
	sprintf(str, "Powered by VRaniML(tm) SDK");
	TextOut((HDC)m_hDC, 10, m_Viewport.Height()-45, str, strlen(str));

	sprintf(str, "(c) 1998 - Great Hill Corp (http://www.greathill.com)");
	TextOut((HDC)m_hDC, 10, m_Viewport.Height()-25, str, strlen(str));
#endif

	return;
}

void vrOGLTraverser::PostTraverse(void)
{
	if (!m_isPicking)
		SwapBuffers((HDC)m_hDC);
	m_isPicking=FALSE;

#ifndef RELEASE
	char str[256];
	SetBkMode((HDC)m_hDC, TRANSPARENT);
	SetTextColor((HDC)m_hDC, RGB(255,255,0));
	sprintf(str, "Powered by VRaniML(tm) SDK");
	TextOut((HDC)m_hDC, 10, m_Viewport.Height()-45, str, strlen(str));

	sprintf(str, "(c) 1998 - Great Hill Corp (http://www.greathill.com)");
	TextOut((HDC)m_hDC, 10, m_Viewport.Height()-25, str, strlen(str));
#endif
}

void vrOGLTraverser::TraverseChildren(const vrGroupingNode *node)
{
	if (node->GetChildren())
	{
		if (m_isPicking && node->HasSensor())
			glPushName((GLint)node);

		parentStack.Push((vrGroupingNode *)node);

		if (node->HasLight())
		{
			// If there are lights, render lights first
			glPushAttrib(GL_LIGHTING_BIT);
			LISTPOS pos = node->GetChildren()->GetHeadPosition();
			while (pos)
			{
				SFNode ob = node->GetChildren()->GetNext(pos);
				if (ob->IsKindOf(GETRUNTIME_CLASS(vrLight)))
					ob->Traverse(this);
			}

			// then objects
			pos = node->GetChildren()->GetHeadPosition();
			while (pos)
			{
				SFNode ob = node->GetChildren()->GetNext(pos);
				if (!ob->IsKindOf(GETRUNTIME_CLASS(vrLight)))
				{
					ob->Traverse(this);
				}
			}

			if (node->HasLight())
				glPopAttrib();
		} else
		{
			// else, just render everything
			LISTPOS pos = node->GetChildren()->GetHeadPosition();
			while (pos)
			{
				SFNode ob = node->GetChildren()->GetNext(pos);
				ob->Traverse(this);
			}
		}

		parentStack.Pop();

		if (m_isPicking && node->HasSensor())
			glPopName();
	}
}

//-------------------------------------------------------------------
//  NODES - NODES - NODES - NODES - NODES - NODES - NODES - NODES 
//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrAppearance *node)
{
	//
	// The value for each of the fields can be NULL, however if the
	// field is non-NULL then it must contain one node of the correct type
	//
	vrMaterial *mat = node->GetMaterial();
	ASSERT(!mat || mat->IsKindOf(GETRUNTIME_CLASS(vrMaterial)));

	vrPixelTexture *texture = node->GetTexture();
	ASSERT(!texture || texture->IsKindOf(GETRUNTIME_CLASS(vrPixelTexture)));

	vrTextureTransform *trans = node->GetTextureTransform();
	ASSERT(!trans || trans->IsKindOf(GETRUNTIME_CLASS(vrTextureTransform)));

	//
	// Some geometry nodes (such as vrPointSet) may use the material from 
	// the Appearance node for default coloring, so save this state in the
	// traverser
	//
	currMaterial = mat;

	if (mat)
	{
		glEnable(GL_LIGHTING);
		mat->Traverse(this);
	} else
	{
		// If material node is NULL, lighting is off and default color is vrBlack
		glDisable(GL_LIGHTING);
		glColor3f(0.0, 0.0, 0.0);
	}

	if (texture)
	{
		if (mat)
		{
			glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		} else
		{
			glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		}
		glEnable(GL_TEXTURE_2D);
		if (trans)
		{
			// texture transform only has effect if texture node is non-NULL
			trans->Traverse(this);
		}
		texture->Traverse(this);
	} else
	{
		// If texture field is NULL, the object is not textured
		glDisable(GL_TEXTURE_2D);
	}
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrFontStyle *node)
{
	// not implemented
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrImageTexture *node)
{
	if (!node->GetColorBuffer())
	{
		SFBool loaded=FALSE;
		SFInt32 n = 0;
		while (n < node->GetNUrls() && !loaded)
		{
			SFString filename = node->GetUrl(n++);
			SFString local = vrCacheFile(filename, 1);
			if (!local.Empty())
			{
				SFImage image(128, 128);
				loaded = vrReadTextureImage(image, local);
				if (loaded)
				{
					((vrPixelTexture*)node)->SetColorBuffer(image);
					((vrPixelTexture*)node)->SetFormat((image.m_nComponents==3) ? GL_RGB : GL_RGBA);
				}
			}
    }
	}
	Traverse((vrPixelTexture*)node);
}

//-------------------------------------------------------------------
#include "stipple.cxx"
void vrOGLTraverser::Traverse(const vrMaterial *node)
{
	SFColor ambient = node->GetAmbientColor();
	glColor3fv((SFFloat*)&ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,   (SFFloat*)&ambient);

	SFColor color = node->GetDiffuseColor();
//	color.a = node->GetTransparency();
	color.a = 1.0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,   (SFFloat*)&color);

#pragma warning(disable : 4238)
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,  (SFFloat*)&node->GetSpecularColor());

	glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, node->GetShininess() * 128.0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION,  (SFFloat*)&node->GetEmissiveColor());

	// do cheesy screen door transparency
	glDisable (GL_POLYGON_STIPPLE);
  float Alpha = 1.0 - node->GetTransparency();

  if (Alpha < 1.0)
  {
		int stipple = (int) (Alpha * 16.0 + 0.5);
    if (stipple < 16)
		{
			glEnable (GL_POLYGON_STIPPLE);
      glPolygonStipple (mask[stipple < 0 ? 0 : stipple]);
		}
	}
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrMovieTexture *node)
{
	// not implemented
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrPixelTexture *node)
{
	glEnable(GL_TEXTURE_2D);
	
	glTexImage2D(GL_TEXTURE_2D, 0, 
				node->GetNComponents(), node->GetWidth(), node->GetHeight(),
				0, node->GetFormat(), GL_UNSIGNED_BYTE, ((vrPixelTexture*)node)->GetColorBuffer());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     (node->GetRepeatS() ? GL_REPEAT : GL_CLAMP));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     (node->GetRepeatT() ? GL_REPEAT : GL_CLAMP));
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrBackground *node)
{
	SFInt32 pending = node->IsBound();
	if (pending && pending != TRUE)
	{
		ASSERT(pending == PENDING_BIND || pending == PENDING_UNBIND);
		m_Browser->Bind((vrBackground*)node, ((pending == PENDING_BIND) ? TRUE : FALSE));
	}
	
	if (!m_isPicking && node->IsBound() && !node->IsClearOnly())
	{
		glPushAttrib(GL_FOG_BIT);
#ifdef _DEBUG
glCheck(m_Browser);
#endif
		glDisable(GL_FOG);
		glPushMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif
		vrMatrix mat;
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *)&mat.vals[0][0]);
		mat = RotationOnly(mat);
		glLoadMatrixf((GLfloat *)&mat.vals[0][0]);
		if (!node->GetBackgroundGroup())
		{
			((vrBackground*)node)->BuildMesh();
		}
		if (node->GetBackgroundGroup())
			node->GetBackgroundGroup()->Traverse(this);
		glPopMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif

		glPopAttrib();
#ifdef _DEBUG
glCheck(m_Browser);
#endif

	}
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrFog *node)
{
	// see browser traversal
}

vrShape *LightShape(vrGeometryNode *ob, SFColor col)
{
	vrShape *shape = new vrShape;
	vrAppearance *app = new vrAppearance;
	vrMaterial *mat = new vrMaterial;
	mat->SetEmissiveColor(col);
	app->SetMaterial(mat);
	shape->SetAppearance(app);
	shape->SetGeometry(ob);
	return shape;
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrDirectionalLight *node)
{
	if (m_isPicking) return;

	SFInt32 lightID = node->GetLightID();
	SFVec4 dir(-node->GetDirection(), 0.0);
	SFColor dif = node->GetDiffuseColor();

	if (node->GetOn())
	{
		glLightfv(GL_LIGHT0+lightID, GL_POSITION, (SFFloat*)&dir);

		SFColor   amb  = node->GetAmbientColor();
		glLightfv(GL_LIGHT0+lightID, GL_AMBIENT,  (SFFloat*)&amb);
	
	  glLightfv(GL_LIGHT0+lightID, GL_DIFFUSE,  (SFFloat*)&dif);

		SFColor   spec = node->GetSpecularColor();
		glLightfv(GL_LIGHT0+lightID, GL_SPECULAR, (SFFloat*)&spec);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0+lightID);

	} else
	{
		glDisable(GL_LIGHT0+lightID);
	}

  if (m_DrawLights)
	{
		glPushMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif
		glTranslatef(dir.x, dir.y, dir.z);
		vrCone *cone = new vrCone;
		cone->SetBottomRadius(0.1);
		cone->SetHeight(0.3);
		vrShape *shape = LightShape(cone, dif);
		Traverse(shape);
		delete shape;
		glPopMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif

	}
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrPointLight *node)
{
	if (m_isPicking) return;

	SFInt32 lightID = node->GetLightID();
	SFVec4 pos(node->GetLocation(), 1.0);
	SFColor dif = node->GetDiffuseColor();

	if (node->GetOn())
	{
		glLightfv(GL_LIGHT0+lightID, GL_POSITION, (SFFloat*)&pos);

		SFColor   amb  = node->GetAmbientColor();
		glLightfv(GL_LIGHT0+lightID, GL_AMBIENT,  (SFFloat*)&amb);
	
	  glLightfv(GL_LIGHT0+lightID, GL_DIFFUSE,  (SFFloat*)&dif);

		SFColor   spec = node->GetSpecularColor();
		glLightfv(GL_LIGHT0+lightID, GL_SPECULAR, (SFFloat*)&spec);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0+lightID);
	} else
	{
		glDisable(GL_LIGHT0+lightID);
	}

  if (m_DrawLights)
	{
		glPushMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif
		glTranslatef(pos.x, pos.y, pos.z);
		vrSphere *s = new vrSphere;
		s->SetRadius(0.1);
		vrShape *shape = LightShape(s, dif);
		Traverse(shape);
		delete shape;
		glPopMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif

	}
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrShape *node)
{
	glDisable(GL_TEXTURE_2D);
	texTransform = FALSE;

	if (node->GetGeometry())
	{
		if (!m_isPicking)
		{
			glPushAttrib(GL_ALL_ATTRIB_BITS);
#ifdef _DEBUG
glCheck(m_Browser);
#endif
			currMaterial = NULL;
			if (node->GetAppearance()) 
				node->GetAppearance()->Traverse(this);
			else
			{
				vrAppearance app;
				app.Traverse(this);
				glColor3f(1.0,1.0,1.0);
			}
		}

		node->GetGeometry()->Traverse(this);

		if (!m_isPicking)
		{
			currMaterial = NULL;
			glPopAttrib();
#ifdef _DEBUG
glCheck(m_Browser);
#endif

		}
	}
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrSpotLight *node)
{
	if (m_isPicking) return;

	SFInt32 lightID = node->GetLightID();

	if (node->GetOn())
	{
		SFVec4 pos(node->GetLocation(), 1.0);
		glLightfv(GL_LIGHT0+lightID, GL_POSITION, (SFFloat*)&pos);

		SFColor   amb  = node->GetAmbientColor();
		glLightfv(GL_LIGHT0+lightID, GL_AMBIENT,  (SFFloat*)&amb);
	
		SFColor   dif  = node->GetDiffuseColor();
	  glLightfv(GL_LIGHT0+lightID, GL_DIFFUSE,  (SFFloat*)&dif);

		SFColor   spec = node->GetSpecularColor();
		glLightfv(GL_LIGHT0+lightID, GL_SPECULAR, (SFFloat*)&spec);

		SFVec4 dir(node->GetDirection(), 0.0);
    glLightfv(GL_LIGHT0+lightID, GL_SPOT_DIRECTION, (SFFloat *)&dir);

    glLightf(GL_LIGHT0+lightID, GL_SPOT_CUTOFF, vrRad2Deg(node->GetCutOffAngle()));

// what about radius?
#define CONE_INTENSITY 0.95
    SFFloat exp = log(cos(node->GetBeamWidth()/2))/log(CONE_INTENSITY);
    glLightf(GL_LIGHT0+lightID, GL_SPOT_EXPONENT, exp);

    SFVec3f atten = node->GetAttenuation();
		glLightf(GL_LIGHT0+lightID, GL_CONSTANT_ATTENUATION,  atten.x);
    glLightf(GL_LIGHT0+lightID, GL_LINEAR_ATTENUATION,    atten.y);
    glLightf(GL_LIGHT0+lightID, GL_QUADRATIC_ATTENUATION, atten.z);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0+lightID);
	} else
	{
		glDisable(GL_LIGHT0+lightID);
	}

  if (m_DrawLights)
	{
	}
}

//-------------------------------------------------------------------
void buildRot(float theta, const SFVec3f& axis, float m[16])
{
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	float d = x*x + y*y + z*z;
  float ct = cosf(vrDeg2Rad(theta)), st = sinf(vrDeg2Rad(theta));

  /* normalize */
  if (d > 0)
	{
		d = 1/d;
		x *= d;
		y *= d;
		z *= d;
  }

  m[ 0] = 1; m[ 1] = 0; m[ 2] = 0; m[ 3] = 0;
  m[ 4] = 0; m[ 5] = 1; m[ 6] = 0; m[ 7] = 0;
  m[ 8] = 0; m[ 9] = 0; m[10] = 1; m[11] = 0;
  m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;

	/* R = uu' + cos(theta)*(I-uu') + sin(theta)*S
	 *
	 * S =  0  -z   y    u' = (x, y, z)
	 *	    z   0  -x
	 *	   -y   x   0
	 */

	 m[0] = x*x + ct*(1-x*x) + st*0;
	 m[4] = x*y + ct*(0-x*y) + st*-z;
	 m[8] = x*z + ct*(0-x*z) + st*y;

	 m[1] = y*x + ct*(0-y*x) + st*z;
	 m[5] = y*y + ct*(1-y*y) + st*0;
	 m[9] = y*z + ct*(0-y*z) + st*-x;

	 m[2] = z*x + ct*(0-z*x) + st*-y;
	 m[6] = z*y + ct*(0-z*y) + st*x;
	 m[10]= z*z + ct*(1-z*z) + st*0;
}

void vrOGLTraverser::Traverse(const vrBillboard *node)
{
	glPushMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif
		float mat[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, mat);
		buildRot(-180*atan2f(mat[8], mat[10])/M_PI, node->GetAxisOfRotation(), mat);
		glMultMatrixf(mat);
		TraverseChildren(node);
  glPopMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif

}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrCollision *node)
{
	// not implemented
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrTransform *node)
{
	if (node->IsKindOf(GETRUNTIME_CLASS(vrBrowser)))
	{
		glPushMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif
		glTranslatef(node->GetTranslation().x, node->GetTranslation().y, node->GetTranslation().z);

		glTranslatef(node->GetCenter().x, node->GetCenter().y, node->GetCenter().z);

		glRotatef(vrRad2Deg(node->GetRotation().w), node->GetRotation().x, node->GetRotation().y, node->GetRotation().z);

		glMultMatrixf((GLfloat*)&((vrBrowser*)node)->matrix.vals[0][0]);

		glRotatef(vrRad2Deg(node->GetScaleOrientation().w), node->GetScaleOrientation().x, node->GetScaleOrientation().y, node->GetScaleOrientation().z);

		glScalef(node->GetScale().x, node->GetScale().y, node->GetScale().z);

		glRotatef(vrRad2Deg(node->GetScaleOrientation().w), -node->GetScaleOrientation().x, -node->GetScaleOrientation().y, -node->GetScaleOrientation().z);

		glTranslatef(-node->GetCenter().x, -node->GetCenter().y, -node->GetCenter().z);

		TraverseChildren(node);

		glPopMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif

	} else
	{
		glPushMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif
			glTranslatef(node->GetTranslation().x, node->GetTranslation().y, node->GetTranslation().z);
			glTranslatef(node->GetCenter().x, node->GetCenter().y, node->GetCenter().z);

			glRotatef(vrRad2Deg(node->GetRotation().w), node->GetRotation().x, node->GetRotation().y, node->GetRotation().z);

			glRotatef(vrRad2Deg(node->GetScaleOrientation().w), node->GetScaleOrientation().x, node->GetScaleOrientation().y, node->GetScaleOrientation().z);

			glScalef(node->GetScale().x, node->GetScale().y, node->GetScale().z);

			glRotatef(vrRad2Deg(node->GetScaleOrientation().w), -node->GetScaleOrientation().x, -node->GetScaleOrientation().y, -node->GetScaleOrientation().z);

			glTranslatef(-node->GetCenter().x, -node->GetCenter().y, -node->GetCenter().z);

			TraverseChildren(node);

		glPopMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif

	}
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrGeometryNode *node)
{
	if (!node->GetGeom() || ((Uint32)node->GetGeom()) < 0x10)
	{
		((vrGeometryNode*)node)->BuildMesh();
	}

	if (node->GetSolid())
	{
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
		glEnable(GL_CULL_FACE);
	} else
	{
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		glDisable(GL_CULL_FACE);
	}

	Traverse(node->GetGeom());
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrBox *node)
{
	if (node->GetNative())
	{
		SFVec3f size = node->GetSize();
		
		double x0, x1, y0, y1, z0, z1;
		x0 = -(float)size.x/2.; x1 = (float)size.x/2.;
		y0 = -(float)size.y/2.; y1 = (float)size.y/2.;
		z0 = -(float)size.z/2.; z1 = (float)size.z/2.;

		static GLdouble n[6][3] =
		{
			{-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
			{0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0}
		};
		static GLint faces[6][4] =
		{
			{ 0, 1, 2, 3 }, { 3, 2, 6, 7 }, { 7, 6, 5, 4 },
			{ 4, 5, 1, 0 }, { 5, 6, 2, 1 }, { 7, 4, 0, 3 }
		};
		static GLfloat tex[6][4][2] =
		{
			{ { 0.f, 0.f }, { 1.f, 0.f }, { 1.f, 1.f }, { 0.f, 1.f } }, // left
			{ { 0.f, 1.f }, { 0.f, 0.f }, { 1.f, 0.f }, { 1.f, 1.f } }, // top
			{ { 1.f, 1.f }, { 0.f, 1.f }, { 0.f, 0.f }, { 1.f, 0.f } }, // right
			{ { 1.f, 0.f }, { 1.f, 1.f }, { 0.f, 1.f }, { 0.f, 0.f } }, // bottom
			{ { 1.f, 0.f }, { 1.f, 1.f }, { 0.f, 1.f }, { 0.f, 0.f } }, // front
			{ { 0.f, 1.f }, { 0.f, 0.f }, { 1.f, 0.f }, { 1.f, 1.f } }  // back
		};
		SFVec2f tt[24];
		for (int k=0;k<6;k++)
			for (int i=0;i<4;i++)
				tt[k*4+i] = TransformTexCoord(SFVec2f(tex[k][i][0], tex[k][i][1]));

		GLdouble v[8][3];

		if (x0 > x1)
			vrSwap(x0, x1);

		if (y0 > y1)
			vrSwap(y0, y1);

		if (z0 > z1)
			vrSwap(z0, z1);

		v[0][0] = v[1][0] = v[2][0] = v[3][0] = x0;
		v[4][0] = v[5][0] = v[6][0] = v[7][0] = x1;
		v[0][1] = v[1][1] = v[4][1] = v[5][1] = y0;
		v[2][1] = v[3][1] = v[6][1] = v[7][1] = y1;
		v[0][2] = v[3][2] = v[4][2] = v[7][2] = z0;
		v[1][2] = v[2][2] = v[5][2] = v[6][2] = z1;

		glEnable(GL_CULL_FACE);

		for (int i = 0; i < 6; i++ )
		{
			glBegin(GL_QUADS);

			glNormal3dv( &n[i][0] );
			glTexCoord2fv( (GLfloat*)&tt[i*4] );
			glVertex3dv( &v[faces[i][0]][0] );

			glNormal3dv( &n[i][0] );
			glTexCoord2fv( (GLfloat*)&tt[i*4+1] );
			glVertex3dv( &v[faces[i][1]][0] );

			glNormal3dv( &n[i][0] );
			glTexCoord2fv( (GLfloat*)&tt[i*4+2] );
			glVertex3dv( &v[faces[i][2]][0] );

			glNormal3dv( &n[i][0] );
			glTexCoord2fv( (GLfloat*)&tt[i*4+3] );
			glVertex3dv( &v[faces[i][3]][0] );

			glEnd();
		}
	} else
	{
		Traverse((vrGeometryNode*)node);
	}
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrCone *node)
{
	if (node->GetNative() && !texTransform)
	{
//		if (node->GetSide() && node->GetBottom())
		glEnable(GL_CULL_FACE);
//		else
//			glDisable(GL_CULL_FACE);

		GLUquadricObj* quadObj = gluNewQuadric();

		if (node->GetSide() || node->GetBottom())
		{
			glPushMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif
				glRotatef(90, -1, 0, 0);
				glTranslatef(0, 0, -node->GetHeight()/2);
				gluQuadricDrawStyle(quadObj, GLU_FILL);
				gluQuadricNormals(quadObj, GLU_SMOOTH);
				gluQuadricTexture(quadObj, GL_TRUE);

				if (node->GetSide())
				{
					gluCylinder(quadObj, node->GetBottomRadius(), 0, node->GetHeight(), 16, 1);
				}
				
				if (node->GetBottom())
				{
					glPushMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif
					glRotatef(180.0, 1.0, 0.0, 0.0);
					gluDisk(quadObj, 0, node->GetBottomRadius(), 16, 2);
					glPopMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif

				}
			glPopMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif

		}

		gluDeleteQuadric(quadObj);
	} else
	{
		Traverse((vrGeometryNode*)node);
	}
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrCylinder *node)
{
	if (node->GetNative() && !texTransform)
	{
//		if(node->GetSide() && node->GetBottom() && node->GetTop())
		glEnable(GL_CULL_FACE);
//		else
//			glDisable(GL_CULL_FACE);

		GLUquadricObj* quadObj = gluNewQuadric();

		if(node->GetSide() || node->GetBottom() || node->GetTop())
		{
			glPushMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif
				glRotatef(90, -1, 0, 0);
				glTranslatef(0, 0, -node->GetHeight()/2);
				gluQuadricDrawStyle(quadObj, GLU_FILL);
				gluQuadricNormals(quadObj, GLU_SMOOTH);
				gluQuadricTexture(quadObj, GL_TRUE);
				if(node->GetSide())
				{
					gluCylinder(quadObj, node->GetRadius(), node->GetRadius(), node->GetHeight(), 16, 1);
				}
    
				if (node->GetBottom())
				{
					glPushMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif
					glRotatef(180.0, 1.0, 0.0, 0.0);
					gluDisk(quadObj, 0, node->GetRadius(), 16, 2);
					glPopMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif

				}

				if (node->GetTop())
				{
					glPushMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif
						glTranslatef(0, 0, node->GetHeight());
						gluDisk(quadObj, 0, node->GetRadius(), 16, 2);
					glPopMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif

				} 
			glPopMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif

		}
		gluDeleteQuadric(quadObj);
	} else
	{
		Traverse((vrGeometryNode*)node);
	}
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrExtrusion *node)
{
	Traverse((vrGeometryNode*)node);
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrSphere *node)
{
	if (node->GetNative() && !texTransform)
	{
		// The sphere is used by the background node and we are
		// inside it.  So sometimes we do not want to cull back
		// facing polys.
		if (node->GetSolid())
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);

		// Note: This does not work if textureTransform is non-identity
		// because MS OpenGL does not support gluQuadricCallback
		glPushMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		GLUquadricObj *obj = gluNewQuadric();
		gluQuadricDrawStyle(obj, GLU_FILL);
		gluQuadricNormals(obj, GLU_SMOOTH);
		gluQuadricTexture(obj, GL_TRUE);
		gluSphere(obj, node->GetRadius(), node->GetSlices(), node->GetStacks());
		gluDeleteQuadric(obj);
		glPopMatrix();
#ifdef _DEBUG
glCheck(m_Browser);
#endif

	} else
	{
		Traverse((vrGeometryNode*)node);
	}
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrText *node)
{
	Traverse((vrGeometryNode*)node);
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrDataSet *node)
{
	Traverse((vrGeometryNode*)node);
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrElevationGrid *node)
{
	VCHECK(node);
	
	Traverse((vrGeometryNode*)node);
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrIndexedFaceSet *node)
{
	((vrIndexedFaceSet*)node)->tempHack=this;
	Traverse((vrGeometryNode*)node);
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrIndexedLineSet *node)
{
	if (node->GetNative())
	{
		// Coordinate and Color nodes and thier counts
		vrCoordinate *coords  = node->GetCoord();
		vrColor   *colors  = node->GetColor();

		SFInt32       nCoords = ((coords) ? coords->GetNPoints() : 0);
		SFInt32       nColors = ((colors) ? colors->GetNColors() : 0);

		ASSERT(!coords || coords->IsKindOf(GETRUNTIME_CLASS(vrCoordinate)));
		ASSERT(!colors || colors->IsKindOf(GETRUNTIME_CLASS(vrColor)));

		if (!coords || !nCoords)
			return;

		// CoordinateIndex and ColorIndex arrays and thier counts
		const MFInt32& coordIndexArray = node->GetCoordIndexArray();
		SFInt32  nCoordIndicies  = coordIndexArray.GetCount();
		if (!nCoordIndicies)
			return;
		const MFInt32& colorIndexArray = node->GetColorIndexArray();
		SFInt32  nColorIndicies  = colorIndexArray.GetCount();

		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glBegin(GL_LINE_STRIP);

		if (!colors)
		{
			// no Color node so use vrBlack...
			SFColor color = vrBlack;
			if (currMaterial)
				color = currMaterial->GetEmissiveColor(); // ...or emmisive color if available
			glColor3f(color.x, color.y, color.z);
			for (int i=0;i<nCoordIndicies;i++)
			{
				SFInt32 index  = MIN((SFInt32)node->GetCoordIndex(i), (SFInt32)(nCoords-1));
				if (index >= 0)
				{
					glVertex3fv(&coords->GetPointArray()[index][0]);
				} else
				{
					glEnd();
					glBegin(GL_LINE_STRIP);
				}
			}
		} else
		{
			if (node->GetColorPerVertex())
			{
				// Color per vertex
				if (nColorIndicies)
				{
					for (int i=0;i<nCoordIndicies;i++)
					{
						SFInt32 index   = MIN(node->GetCoordIndex(i), (SFInt32)(nCoords-1));
						SFInt32 cindex  = MIN(node->GetColorIndex(i), (SFInt32)(nColors-1));
						if (index >= 0)
						{
							glColor3fv(&colors->GetColorArray()[cindex][0]);
							glVertex3fv(&coords->GetPointArray()[index][0]);
						} else
						{
							glEnd();
							glBegin(GL_LINE_STRIP);
						}
					}
				} else
				{
					for (int i=0;i<nCoordIndicies;i++)
					{
						SFInt32 index  = MIN(node->GetCoordIndex(i), (SFInt32)(nCoords-1));
						SFInt32 cindex = MIN(index, (SFInt32)(nColors-1));
						if (index >= 0)
						{
							glColor3fv(&colors->GetColorArray()[cindex][0]);
							glVertex3fv(&coords->GetPointArray()[index][0]);
						} else
						{
							glEnd();
							glBegin(GL_LINE_STRIP);
						}
					}
				}
			} else
			{
				// Color per line
				if (nColorIndicies)
				{
					SFInt32 indexIndex = 0;
					SFInt32 cindex  = MIN(node->GetColorIndex(indexIndex), (SFInt32)(nColors-1));
					glColor3fv(&colors->GetColorArray()[cindex][0]);
					for (int i=0;i<nCoordIndicies;i++)
					{
						SFInt32 index  = MIN(node->GetCoordIndex(i), (SFInt32)(nCoords-1));
						if (index >= 0)
						{
							glVertex3fv(&coords->GetPointArray()[index][0]);
						} else
						{
							glEnd();
							glBegin(GL_LINE_STRIP);
							indexIndex = MIN(indexIndex+1, nColorIndicies-1);
							cindex = MIN(node->GetColorIndex(indexIndex), (SFInt32)(nColors-1));
							glColor3fv(&colors->GetColorArray()[cindex][0]);
						}
					}
				} else
				{
					SFInt32 cindex = 0;
					glColor3fv(&colors->GetColorArray()[cindex][0]);
					for (int i=0;i<nCoordIndicies;i++)
					{
						SFInt32 index  = MIN(node->GetCoordIndex(i), (SFInt32)(nCoords-1));
						if (index >= 0)
						{
							glVertex3fv(&coords->GetPointArray()[index][0]);
						} else
						{
							glEnd();
							glBegin(GL_LINE_STRIP);
							cindex = MIN(cindex+1, nColors-1);
							glColor3fv(&colors->GetColorArray()[cindex][0]);
						}
					}
				}
			}
		} // if (!color)
		glEnd();
	} else
	{
		Traverse((vrGeometryNode*)node);
	}
}

//-------------------------------------------------------------------
void vrOGLTraverser::Traverse(const vrPointSet *node)
{
	//
	// Note: vrPointSet will not use the vrSolid since it would be inefficient
	//

	vrCoordinate *coords = node->GetCoord();
	ASSERT(!coords || coords->IsKindOf(GETRUNTIME_CLASS(vrCoordinate)));
	if (!coords)
		return;

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	vrColor *colors = node->GetColor();
	ASSERT(!colors || colors->IsKindOf(GETRUNTIME_CLASS(vrColor)));

	SFInt32 nCoords = coords->GetNPoints();
	if (!nCoords)
		return;

	glBegin(GL_POINTS);
	if (colors)
	{
		SFInt32 nColors = colors->GetNColors();
		// ASSERT(nColors >= nCoords);  See note below
		for (SFInt32 i=0; i<nCoords; i++)
		{
			// Note: Undefined behaviour if nColors is less than nCoords.  
			// We choose to clamp the color index so that the last available 
			// color colors all remaining coords
			SFColor c = colors->GetColor(MIN((SFInt32)(nColors-1), i));
			glColor3f(c.x, c.y, c.z);
			SFVec3f v = coords->GetPoint(i);
			glVertex3f(v.x, v.y, v.z);
		}
	} else
	{
		SFColor color = vrBlack;
		if (currMaterial)
			color = currMaterial->GetEmissiveColor(); // ...or emmisive color if available
		glColor3f(color.x, color.y, color.z);
		for (int i=0; i<nCoords; i++)
		{
			SFVec3f v = coords->GetPoint(i);
			glVertex3f(v.x, v.y, v.z);
		}
	}
	glEnd();
}

#ifdef SOUND1
  //todo:
	//check to see if have a direct sound object in lpDS
	//check to see if have a primary buffer
	//check to see if listener has bee released
	//creates the listener if it doesn't already exist
	if (!listener)
	{
		if (primaryBuffer)
		{
			if (DS_OK != primaryBuffer->QueryInterface(IID_IDirectSound3DListener, (void **)&listener))
			{
				primaryBuffer->Release();
				primaryBuffer = NULL;
				lpDS->Release();
				lpDS = NULL;
			}
		}
	}
#endif

void vrOGLTraverser::SetViewport(long x, long y, long w, long h)
{
	vrRenderTraverser::SetViewport(x,y,w,h);
	glViewport(x, y, w, h);
	Reset();
}
