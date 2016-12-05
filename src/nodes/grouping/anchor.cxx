#include "Windows.h"
#include "Browser\Browser.h"

void vrAnchor::PointerEvent(SFInt32 mode, const SFVec3f& pt, vrTraverser *t)
{
	vrBrowser *b = t->m_Browser;

	SFBool loaded=FALSE;
	SFInt32 n = 0;
	while (n < GetNUrls() && !loaded)
	{
		char filename[1000];
		strcpy(filename, GetUrl(n++));
		char *viewpoint = NULL;
		if (strchr(filename, '#'))
		{
			viewpoint = strchr(filename, '#');
			viewpoint++;
			*strchr(filename, '#') = '\0';
		}
		
		if (filename[0])
		{
			if (strstr(filename, ".wrl"))
			{
				SFString str = filename;
				SFString local = vrCacheFile(str, 1);
				if (!local.Empty())
				{
					loaded = b->ReadURL(local);
				}
			} else
			{
				if (b)
				{
					HINSTANCE ret = ShellExecute((HWND)t->m_hWnd, "open", filename, "", "", SW_SHOWMAXIMIZED);
					loaded = (ret >= (HINSTANCE)32);
//						if (ret < (HINSTANCE)32)
//						{
//							MessageBox(NULL, "No viewer found for file type.", "Error", MB_OK);
//						}
				}
			}
		}

		if (viewpoint)
		{
			vrViewpoint *vp = (vrViewpoint *)b->FindByName(viewpoint);
			if (vp)
				b->ChangeViewpoint(vp, 20);
		}
  }
}