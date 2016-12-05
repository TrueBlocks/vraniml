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

//-----------------------------------------------------------------------
// construction
//-----------------------------------------------------------------------
vrOGLTraverser::vrOGLTraverser(vrBrowser *b, void *h) : vrRenderTraverser(b, h)
{
	m_hGLRC = NULL;
	Init();
}

vrOGLTraverser::~vrOGLTraverser()
{
	Clear();
}

//-------------------------------------------------------------------
// initialization
//-------------------------------------------------------------------
void vrOGLTraverser::Init()
{
	vrRenderTraverser::Init();

	ASSERT(m_hDC);

	// Should call Clear first if you are re-initializing
	ASSERT(!m_hGLRC);
	
	SetupDC();
	SetupPalette();

	m_hGLRC = (void *)wglCreateContext((HDC)m_hDC);
	wglMakeCurrent((HDC)m_hDC, (HGLRC)m_hGLRC);

	glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //GL_MODULATE); //GL_REPLACE );

	glEnable(GL_DITHER);

	glShadeModel(GL_SMOOTH);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_NORMALIZE);

	glEnable(GL_DEPTH_TEST);
	glDrawBuffer(GL_BACK);
}

void vrOGLTraverser::Clear(void)
{
	// make the rendering context not current 
	wglMakeCurrent(NULL, NULL) ; 

	// delete the rendering context 
	if (m_hGLRC)
		wglDeleteContext((HGLRC)m_hGLRC); 
	m_hGLRC = NULL;

	vrRenderTraverser::Clear();
}

void vrOGLTraverser::SetupPalette(void)
{
	HDC hDC = (HDC)m_hDC;

  PIXELFORMATDESCRIPTOR pfd;
  LOGPALETTE* pPal;
  int pixelFormat = GetPixelFormat(hDC);
  int paletteSize;

  DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

  if (!(pfd.dwFlags & PFD_NEED_PALETTE || pfd.iPixelType == PFD_TYPE_COLORINDEX))
	{
		return;
  }

	paletteSize = 1 << pfd.cColorBits;
	pPal = (LOGPALETTE*)
	malloc(sizeof(LOGPALETTE) + paletteSize * sizeof(PALETTEENTRY));
	pPal->palVersion = 0x300;
	pPal->palNumEntries = paletteSize;

  /* start with a copy of the current system palette */
  GetSystemPaletteEntries(hDC, 0, paletteSize, &pPal->palPalEntry[0]);

  if (pfd.iPixelType == PFD_TYPE_RGBA)
	{
		/* fill in an RGBA color palette */
		int redMask = (1 << pfd.cRedBits) - 1;
		int greenMask = (1 << pfd.cGreenBits) - 1;
		int blueMask = (1 << pfd.cBlueBits) - 1;
		int i;

		for (i=0; i<paletteSize; ++i)
		{
	    pPal->palPalEntry[i].peRed =
		    (((i >> pfd.cRedShift) & redMask) * 255) / redMask;
	    pPal->palPalEntry[i].peGreen =
		    (((i >> pfd.cGreenShift) & greenMask) * 255) / greenMask;
	    pPal->palPalEntry[i].peBlue =
		    (((i >> pfd.cBlueShift) & blueMask) * 255) / blueMask;
	    pPal->palPalEntry[i].peFlags = 0;
		}
  } else
	{
assert(0);
/*
		// fill in a Color Index ramp color palette
		int numRamps = 4; //NUM_COLORS;
		int rampSize = (paletteSize - 20) / numRamps;
		int extra = (paletteSize - 20) - (numRamps * rampSize);
		int i, r;

		for (r=0; r<numRamps; ++r)
		{
			int rampBase = r * rampSize + 10;
			PALETTEENTRY *pe = &pPal->palPalEntry[rampBase];
			int diffSize = (int) (rampSize * colors[r].ratio);
			int specSize = rampSize - diffSize;

			for (i=0; i<rampSize; ++i)
			{
				SFFloat *c0, *c1;
				GLint a;

				if (i < diffSize)
				{
						c0 = colors[r].amb;
						c1 = colors[r].diff;
						a = (i * 255) / (diffSize - 1);
				} else
				{
						c0 = colors[r].diff;
						c1 = colors[r].spec;
						a = ((i - diffSize) * 255) / (specSize - 1);
				}

				pe[i].peRed = (BYTE) (a * (c1[0] - c0[0]) + 255 * c0[0]);
				pe[i].peGreen = (BYTE) (a * (c1[1] - c0[1]) + 255 * c0[1]);
				pe[i].peBlue = (BYTE) (a * (c1[2] - c0[2]) + 255 * c0[2]);
				pe[i].peFlags = PC_NOCOLLAPSE;
			}

			colors[r].indexes[0] = rampBase;
			colors[r].indexes[1] = rampBase + (diffSize-1);
			colors[r].indexes[2] = rampBase + (rampSize-1);
		}

		lit_tex_indexes[0] = 0;
		lit_tex_indexes[1] = (GLint)(rampSize*colors[0].ratio)-1;
		lit_tex_indexes[2] = rampSize-1;

		for (i=0; i<extra; ++i)
		{
	    int index = numRamps*rampSize+10+i;
	    PALETTEENTRY *pe = &pPal->palPalEntry[index];

	    pe->peRed = (BYTE) 0;
	    pe->peGreen = (BYTE) 0;
	    pe->peBlue = (BYTE) 0;
	    pe->peFlags = PC_NOCOLLAPSE;
		}
*/
  }

	HPALETTE hPalette;
  hPalette = CreatePalette(pPal);
  free(pPal);
	pPal=NULL;

  if (hPalette)
	{
		SelectPalette(hDC, hPalette, FALSE);
		RealizePalette(hDC);
  }
}

void vrOGLTraverser::SetupDC(void)
{
	HDC hDC = (HDC)m_hDC;
  char pixelType = PFD_TYPE_RGBA;
  PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),	/* size of this pfd */
		1,				/* version num */
		PFD_DRAW_TO_WINDOW |		/* support window */
		PFD_SUPPORT_OPENGL |		/* support OpenGL */
		PFD_DOUBLEBUFFER,		/* support double buffering */
		pixelType,			/* RGBA type */
		24,				/* 8-bit color depth */
		0, 0, 0, 0, 0, 0,		/* color bits (ignored) */
		0,				/* no alpha buffer */
		0,				/* alpha bits (ignored) */
		0,				/* no accumulation buffer */
		0, 0, 0, 0,			/* accum bits (ignored) */
		16,				/* 16-bit depth buffer */
		0,				/* no stencil buffer */
		0,				/* no auxiliary buffers */
		PFD_MAIN_PLANE,			/* main layer */
		0,				/* reserved */
		0, 0, 0,			/* no layer, visible, damage masks */
  };

	int SelectedPixelFormat;
	BOOL retVal;

	SelectedPixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (SelectedPixelFormat == 0)
	{
		MessageBox((HWND)m_hWnd, "Failed to find acceptable pixel format.", "OpenGL application error", MB_ICONERROR | MB_OK);
		exit(1);
	}

	retVal = SetPixelFormat(hDC, SelectedPixelFormat, &pfd);
	if (retVal != TRUE)
	{
		MessageBox((HWND)m_hWnd, "Failed to set pixel format.", "OpenGL application error", MB_ICONERROR | MB_OK);
		exit(1);
	}
}

// Silly little function gives meaningful error messages from HRESULT's
/*
void ShowDSError(HWND hWnd, HRESULT hr)
{
#ifdef SOUND1
	char error[256];
	
	switch(hr)
	{
	case DSERR_ALLOCATED:
		strcpy(error, "DSERR_ALLOCATED"); break;

	case DSERR_CONTROLUNAVAIL:
		strcpy(error, "DSERR_CONTROLUNAVAIL"); break;

	case DSERR_INVALIDPARAM:
		strcpy(error, "DSERR_INVALIDPARAM"); break;

	case DSERR_INVALIDCALL:
		strcpy(error, "DSERR_INVALIDCALL"); break;

	case DSERR_GENERIC:
		strcpy(error, "DSERR_GENERIC"); break;

	case DSERR_PRIOLEVELNEEDED:
		strcpy(error, "DSERR_PRIOLEVELNEEDED"); break;

	case DSERR_OUTOFMEMORY:
		strcpy(error, "DSERR_OUTOFMEMORY"); break;

	case DSERR_BADFORMAT:
		strcpy(error, "DSERR_BADFORMAT"); break;

	case DSERR_UNSUPPORTED:
		strcpy(error, "DSERR_UNSUPPORTED"); break;

	case DSERR_NODRIVER:
		strcpy(error, "DSERR_NODRIVER"); break;

	case DSERR_ALREADYINITIALIZED:
		strcpy(error, "DSERR_ALREADYINITIALIZED"); break;

	case DSERR_NOAGGREGATION:
		strcpy(error, "DSERR_NOAGGREGATION"); break;

	case DSERR_BUFFERLOST:
		strcpy(error, "DSERR_BUFFERLOST"); break;

	case DSERR_OTHERAPPHASPRIO:
		strcpy(error, "DSERR_OTHERAPPHASPRIO"); break;

	case DSERR_UNINITIALIZED:
		strcpy(error, "DSERR_UNINITIALIZED"); break;

	default:
		strcpy(error, "Unknown HRESULT"); break;
	}

	MessageBox(hWnd, error, "Direct Sound Error", MB_OK);
#endif
}
*/

void glCheck(vrBrowser *b)
{
	GLint error = glGetError();
	if (error!=GL_NO_ERROR)
	{
		char s[1000];
		sprintf(s, "%s", gluErrorString(error));
//		MessageBox(NULL, s, "GL Error", MB_OK);
	}
}

