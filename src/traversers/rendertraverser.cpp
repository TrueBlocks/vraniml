//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Windows.h"

#include "RenderTraverser.h"
#include "Browser\Browser.h"

IMPLEMENT_NODE(vrRenderTraverser, vrTraverser);

vrRenderTraverser::vrRenderTraverser(vrBrowser *b, void *h) : vrTraverser(b, h)
{
	m_Browser = b;
	m_hWnd  = h;
	m_hDC = NULL;

	currMaterial = NULL;
	m_DrawLights = FALSE;
	m_isPicking = FALSE;

	ASSERT(m_hWnd);
	Init();
}

vrRenderTraverser::~vrRenderTraverser()
{
	Clear();
}

void vrRenderTraverser::Init(void)
{
	vrTraverser::Init();
	
	if (!m_hDC)
		m_hDC = (void *)GetDC((HWND)m_hWnd);

#ifdef SOUND1
	primaryBuffer = NULL;
	listener = NULL;
	lpDS = NULL;
	HRESULT h = DirectSoundCreate(NULL, &lpDS, NULL);
	CHECKDS(h);

	if (lpDS)
	{
		h = lpDS->SetCooperativeLevel((HWND)m_hWnd, DSSCL_NORMAL);
		CHECKDS(h);
		if (h!=DS_OK)
		{
			lpDS->Release();
			lpDS = NULL;
		}

		if (lpDS)
		{
			DSBUFFERDESC dsbdesc;
			memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
			dsbdesc.dwSize        = sizeof(DSBUFFERDESC);
			dsbdesc.dwFlags       = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
			dsbdesc.dwBufferBytes = 0;
			dsbdesc.lpwfxFormat   = NULL;

			h = lpDS->CreateSoundBuffer(&dsbdesc, &primaryBuffer, NULL);
			CHECKDS(h);
			if (h!=DS_OK)
			{
				lpDS->Release();
				lpDS = NULL;
			}
		}
	}
#endif
}

void vrRenderTraverser::Clear()
{
	vrTraverser::Clear();

	if (m_hDC)
		ReleaseDC((HWND)m_hWnd, (HDC)m_hDC);
	m_hDC = NULL;

#ifdef SOUND1
	if (primaryBuffer)
	{
		primaryBuffer->Release();
		primaryBuffer = NULL;
	}

	if (lpDS)
	{
		lpDS->Release();
		lpDS = NULL;
	}
#endif
}


SFVec2f vrRenderTraverser::TransformTexCoord(const SFVec2f& t) const
{
	SFVec3f v = t;
	v = (m_TextureCoordTransform * t);
	return SFVec2f(v.x, v.y);
}

void vrRenderTraverser::PreTraverse(void)
{
}

void vrRenderTraverser::PostTraverse(void)
{
}

void vrRenderTraverser::Traverse(const vrBrowser * b)
{
	TraverseChildren(b);
}


//-------------------------------------------------------------------
SFBool texTransform = FALSE;
void vrRenderTraverser::Traverse(const vrTextureTransform *node)
{
	texTransform = TRUE;

	SFVec3f center = node->GetCenter();
	SFFloat rotation = node->GetRotation();
	SFVec3f scale = node->GetScale();
	SFVec3f trans = node->GetTranslation();

	m_TextureCoordTransform = IdentityMatrix();
	m_TextureCoordTransform = m_TextureCoordTransform * TranslationMatrix(-center);
	m_TextureCoordTransform = m_TextureCoordTransform * ScaleMatrix(scale);
	m_TextureCoordTransform = m_TextureCoordTransform * RotationZMatrix(rotation);
	m_TextureCoordTransform = m_TextureCoordTransform * TranslationMatrix(center);
	m_TextureCoordTransform = m_TextureCoordTransform * TranslationMatrix(trans);
}
//-------------------------------------------------------------------
void vrRenderTraverser::Traverse(const vrAudioClip *node)
{
	if (m_isPicking) return;

	vrAudioClip *aw = (vrAudioClip *)node;

	if (node->IsActive())
	{
		SFInt32 n=0;
		SFBool loaded = FALSE;
		while (n < node->GetNUrls() && !loaded)
		{
			SFString filename = node->GetUrl(n++);
			// PlaySound returns FALSE if a sound is already playing
		SFString copy = filename;
		SFString local = vrCacheFile(copy, 0);
		SFBool wasPlaying = PlaySound((LPCTSTR)(char*)local, NULL, SND_FILENAME|SND_ASYNC|SND_NODEFAULT|SND_NOSTOP); 
//			SFBool wasPlaying = vrPlaySound(filename); 
			if (!wasPlaying)
			{
				if (aw->GetDuration() == -1)
				{
					SFTime now = vrNow();
					SFTime duration = now - aw->GetStartTime();
					aw->SetDuration(duration);
				}
			}
		}
	}

#ifdef SOUND1
	vrAudioClip *aw = (vrAudioClip *)node;

	if (node->IsActive())
	{
		// Note: This test may seem redundant if followed
		// through vrSound node but it's not because it may
		// not come through vrSound
		//
		// if not already loaded....
		if (aw->GetDuration() <= 0)
		{
			// .. then load it
			aw->LoadData(lpDS);
		}

		DWORD dwStatus = 0;
		HRESULT hres = aw->m_Buffer->GetStatus(&dwStatus);

		if ((dwStatus & DSBSTATUS_PLAYING) != DSBSTATUS_PLAYING)
		{
			if (aw->m_Buffer->Play(0, 0, DSBPLAY_LOOPING) != DS_OK)
			{
				// may have lost the buffer so
				// clear it and try again later
				aw->SetDuration(0);
			}
		}
	}
#endif
}

//-------------------------------------------------------------------
void vrRenderTraverser::Traverse(const vrScript *node)
{
	// not implemented
}

//-------------------------------------------------------------------
void vrRenderTraverser::Traverse(const vrSound *node)
{
	if (m_isPicking) return;

	if (node->GetSource())
		Traverse(node->GetSource());
}

//-------------------------------------------------------------------
void vrRenderTraverser::Traverse(const vrAnchor *node)
{
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrRenderTraverser::Traverse(const vrGroup *node)
{
	// do nothing
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrRenderTraverser::Traverse(const vrInline *node)
{
	if (!node->HasChildren())
	{
		ASSERT(node->IsKindOf(GETRUNTIME_CLASS(vrGroupingNode)));
		SFBool loaded=FALSE;
		SFInt32 n = 0;
		while (n < node->GetNUrls() && !loaded)
		{
			SFString filename = node->GetUrl(n++);
			SFString local = vrCacheFile(filename, 0);
			if (!local.Empty())
			{
				loaded = m_Browser->ReadURL(local, (vrGroupingNode*)node);
			}
		}
	}
	TraverseChildren(node);
}

//-------------------------------------------------------------------
void vrRenderTraverser::Traverse(const vrLOD *node)
{
	SFInt32 choice = MIN(node->GetActiveLevel(), node->GetNLevels());
	if (choice != -1)
		node->GetLevel(choice)->Traverse(this);
}

//-------------------------------------------------------------------
void vrRenderTraverser::Traverse(const vrSwitch *node)
{
	SFInt32 choice = node->GetWhichChoice();
	if (choice != -1)
	{
		if (choice < node->GetNChoices())
			node->GetChoice(node->GetWhichChoice())->Traverse(this);
	}
}

// this should be removed
void vrRenderTraverser::Traverse(const vrImageTexture *node)
{
}