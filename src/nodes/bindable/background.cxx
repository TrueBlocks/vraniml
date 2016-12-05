vrPixelTexture *MakeRampTexture(vrBackground *b);

SFBool vrBackground::MakePanorama(const SFVec3f& trans, const SFRotation& rot, const MFString& url)
{
	if (!m_BackgroundGroup)
	{
		m_BackgroundGroup = new vrGroup;
		m_BackgroundGroup->Reference();
	}
	
	vrTransform *t = new vrTransform;
	t->SetTranslation(trans);
	t->SetRotation(rot);
	vrIndexedFaceSet *ifs = new vrIndexedFaceSet;
	
	SFVec3f coords[]    = { SFVec3f(-50, 50, 0), SFVec3f(50, 50, 0), SFVec3f(50, -50, 0), SFVec3f(-50, -50, 0) };
	SFInt32 indicies[]  = { 0, 1, 2, 3, -1 };
	SFVec2f texCoords[] = { SFVec2f(0, 1), SFVec2f(1, 1), SFVec2f(1, 0), SFVec2f(0, 0) };

	ifs->AddChild(new vrCoordinate);
	ifs->AddChild(new vrTextureCoordinate);

	for (int i=0;i<4;i++)
	{
		ifs->AddCoord(coords[i]);
		ifs->AddCoordIndex(indicies[i]);
		ifs->AddTexCoord(texCoords[i]);
		ifs->AddTexCoordIndex(indicies[i]);
	}
	ifs->AddCoordIndex(indicies[i]);
	ifs->AddTexCoordIndex(indicies[i]);

	vrShape *shape = new vrShape;
	vrAppearance *app = new vrAppearance;
	vrImageTexture *it = new vrImageTexture;
	it->SetUrl(url);
	shape->SetAppearance(app);
	app->SetTexture(it);
	shape->SetGeometry(ifs);
	t->AddChild(shape);
	m_BackgroundGroup->AddChild(t);

	return TRUE;
}

void vrBackground::BuildMesh()
{
	if (!IsDefault("groundAngle") || 
				!IsDefault("groundColor") ||
				!IsDefault("skyAngle") ||
				!IsDefault("skyColor"))
	{
		vrShape *m_Sphere = new vrShape;
		vrSphere *sphere = new vrSphere;
		sphere->SetRadius(98.0);
		sphere->SetSolid(FALSE);
		vrGeometryNode *n = sphere;
		m_Sphere->SetGeometry(n);
		vrAppearance *app = new vrAppearance;

		SFInt32 nSkyColors    = GetNSkyColors();

		if (nSkyColors)
		{
			vrPixelTexture *texture = MakeRampTexture(this);
			app->SetTexture(texture);
		} else
		{
			vrMaterial *mat = new vrMaterial;
			app->SetMaterial(mat);
		}
		m_Sphere->SetAppearance(app);

		m_BackgroundGroup = new vrGroup;
		m_BackgroundGroup->Reference();
		m_BackgroundGroup->AddChild(m_Sphere);
	}

	if (!IsDefault("backUrl"))
		MakePanorama(SFVec3f(0, 0, -50), SFRotation( 0, 1, 0, vrDeg2Rad(180.0)), m_BackUrl);

	if (!IsDefault("frontUrl"))
		MakePanorama(SFVec3f(0, 0,  50), SFRotation( 0, 0, 1, vrDeg2Rad(0.0)), m_FrontUrl);

	if (!IsDefault("leftUrl"))
		MakePanorama(SFVec3f(-50, 0, 0), SFRotation( 0,-1, 0, vrDeg2Rad(90.0)), m_LeftUrl);

	if (!IsDefault("rightUrl"))
		MakePanorama(SFVec3f( 50, 0, 0), SFRotation( 0, 1, 0, vrDeg2Rad(90.0)), m_RightUrl);

	if (!IsDefault("bottomUrl"))
		MakePanorama(SFVec3f( 0,-50, 0), SFRotation( 1, 0, 0, vrDeg2Rad(90.0)), m_BottomUrl);

	if (!IsDefault("topUrl"))
		MakePanorama(SFVec3f( 0, 50, 0), SFRotation(-1, 0, 0, vrDeg2Rad(90.0)), m_TopUrl);
}

SFBool BuildUpArrays(vrBackground *b, MFFloat& angles, MFColor& colors)
{
	ASSERT(angles.GetCount()==0);
	ASSERT(colors.GetCount()==0);
	
	SFInt32 nSkyAngles    = b->GetNSkyAngles();
	SFInt32 nSkyColors    = b->GetNSkyColors();
	SFInt32 nGroundAngles = b->GetNGroundAngles();
	SFInt32 nGroundColors = b->GetNGroundColors();

	ASSERT(nSkyAngles>=0);
	ASSERT(nGroundAngles>=0);

	// invalid data
	if (nSkyColors && (nSkyAngles > nSkyColors-1))
		return FALSE;
	if (nGroundColors && (nGroundAngles > nGroundColors-1))
		return FALSE;

	if (nGroundAngles)
	{
		SFBool clamped=FALSE;
		// find insertion point for ground angles (i.e. the place where
		// gound angles should overlay the sky angles
		
		// fill in the sky colors first
		SFFloat angle = 0.0; // 0.0 is north pole
		SFColor color = b->GetSkyColor(0);
		angles.AddValue(angle);
		colors.AddValue(color);
		for (int i=0;i<nSkyAngles;i++)
		{
			angle = b->GetSkyAngle(i);
			color = b->GetSkyColor(i+1);
			if (angle < M_PI/2.)
			{
				angles.AddValue(angle);
				colors.AddValue(color);
				if (angle == M_PI/2.)
					clamped = TRUE;
			} else if (!clamped)
			{
				clamped = TRUE;
				angles.AddValue(M_PI/2.);
				colors.AddValue(color);
			}
		}

		// finish the sky color
		if (angle < M_PI/2.)
		{
			// clamp it sky color to M_PI/2
			angles.AddValue(M_PI/2.);
			colors.AddValue(color);
		}

		// now do ground colors (note: start from end because they are backwards
		// compared to sky colors

		// start by clamping if necassary
		angle = M_PI/2.;
		color = b->GetGroundColor(nGroundColors-1);
		if (b->GetGroundAngle(nGroundAngles-1)<M_PI/2.)
		{
			angles.AddValue(M_PI/2.);
			colors.AddValue(color);
		}
		for (i=nGroundAngles-1;i>=0;i--)
		{
			SFFloat angle = M_PI - b->GetGroundAngle(i);
			SFColor color = b->GetGroundColor(i+1);
			if (angle >= M_PI/2.0)
			{
				angles.AddValue(angle);
				colors.AddValue(color);
			}
		}
		// do the last color
		angle = M_PI;
		color = b->GetGroundColor(0);
		angles.AddValue(angle);
		colors.AddValue(color);
	} else
	{
		if (nSkyColors)
		{
			// sky colors only
			SFFloat angle = 0.0; // 0.0 is north pole
			SFColor color = b->GetSkyColor(0);
			angles.AddValue(angle);
			colors.AddValue(color);
			for (int i=0;i<nSkyAngles;i++)
			{
				angle = b->GetSkyAngle(i);
				color = b->GetSkyColor(i+1);
				angles.AddValue(angle);
				colors.AddValue(color);
			}
		}
		// Note: The color interpolator will fill in remaining colors
	}

	return TRUE;
}

vrPixelTexture *MakeRampTexture(vrBackground *b)
{
	// Note 0x1908 is #defined in gl.h for GL_RGBA
	vrPixelTexture *texture = new vrPixelTexture(128, 128, 4, 0x1908); 
	SFInt32 *p = (SFInt32 *)texture->GetColorBuffer();
	ASSERT(p);

	vrColorInterpolator interp;
	
	MFFloat keys;
	MFColor colors;
	BuildUpArrays(b, keys, colors);
	
	interp.SetKey(keys);
	interp.SetKeyValue(colors);

	SFInt32 m_Width = 128;
	SFInt32 m_Height = 128;
	for (int i=m_Height-1; i >= 0; i--)
	{
		SFFloat fraction = (SFFloat)i/(SFFloat)m_Width * M_PI;
		SFColor color = interp.Evaluate(fraction);
		for (int j=0; j < m_Width; j++)
		{
			*p = RGBA(color);
			p++;
		}
	}
	return texture;
}

SFBool vrBackground::IsClearOnly(void) const
{
	if (GetNGroundAngles()) return FALSE;
	if (GetNGroundColors()) return FALSE;
	if (GetNBackUrls())     return FALSE;
	if (GetNBottomUrls())   return FALSE;
	if (GetNFrontUrls())    return FALSE;
	if (GetNLeftUrls())     return FALSE;
	if (GetNRightUrls())    return FALSE;
	if (GetNTopUrls())      return FALSE;
	if (GetNSkyAngles())    return FALSE;

	return (GetNSkyColors()==1);
}


#include "Browser/Browser.h"
void vrBackground::CompleteNode(vrNode *top)
{
	// Let parent complete this node if needed
	vrBindable::CompleteNode(top);

	if (!top || !top->IsKindOf(GETRUNTIME_CLASS(vrBrowser)))
		return;

	vrBrowser *b = (vrBrowser*)top;
	// Only bind the first encountered node
	if (!b->GetBackground())
		b->Bind(this, TRUE);
}

