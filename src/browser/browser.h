#ifndef __BROWSER_H3D
#define __BROWSER_H3D
//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------

#include "Nodes\AllNodes.h"

#define VRANIML_SENSOR (WM_USER+10)

#include "Event.h"
#include "Traversers\RenderTraverser.h"
#include "Traversers\ActionTraverser.h"
#include "UserMessage.h"
#include "Parser/Parser.h"

/*----------------------------------------------------------------------
CLASS
	vrBrowser

	The top of the scene graph.  The generator of timing events.  The
	be-all-end-all VRaniML class.

DESCRIPTION
	<ul>
	The browser class is the basis for the runtime environment of 
	VRaniML.  It serves as the top level of the scene graph providing
	the initial coordinate system for the scene.  The vrBrowser class
	also implements an internal timer to keep track of the passing
	time in the system.  This is used to generate vrTimeSensor events
	if any such nodes exist in the scene graph.
	</ul>

NOTES
	<ul>
	<li>There can only be one active vrBrowser for each vrTraverser
	at any given time.</li>
	<li>The vrBrowser corresponds roughly to the CDocument class 
	in the MFC.  The vrRenderTraverser corresponds to the CView class.</li>
	</ul>

EXAMPLE CODE
	<pre>
	// None.
	</pre>

MEMBERS
----------------------------------------------------------------------*/
class LIBInterface vrBrowser : public vrTransform
{
protected:
	vrTraverserList     m_TraverserList;

	//<doc>------------------------------------------------------------
	// <dd>The grouping node that was picked with the last call to PickScene (or the last mouse down event).
	//
	// [default] NULL
	//
	vrGroupingNode     *m_PickedObject;

public:

	//<doc>------------------------------------------------------------
	// <dd>The number of frames rendered per second
	//
	// [default] 30
	//
	long                m_FramesPerSec;

	//<doc>------------------------------------------------------------
	// <dd>Millionths of a second allowed per frame (1000000 / m_FramesPerSec)
	//
	// [default] 1000000 / 30
	//
	vrTime              m_FrameRate;

	//<doc>------------------------------------------------------------
	// <dd>The time when the last frame was drawn.
	//
	// [default] vrNow()
	//
	vrTime              m_LastFrame;

	//<nodoc>------------------------------------------------------------
	// <dd>The time when the last frame was drawn.
	//
	// [default] vrNow()
	//
	//	vrTime          m_StartTime;

public:
	vrConsole          *m_Console;

	//<nodoc>------------------------------------------------------------
	// <dd>Default Constructor.
	//
	vrBrowser						(void);

	//<doc>------------------------------------------------------------
	// <dd>Constructor.
	//
	// [in] hWnd: Pointer to a HWND object into which to render the scene graph.
	// [in] drawTraverser: The rendering traverser to use to render to the hWnd.  If NULL a vrOGLTraverser is created.
	//
	vrBrowser						(void *hWnd, vrRenderTraverser *drawTraverser=NULL);

	//<doc>------------------------------------------------------------
	// <dd>Destructor.
	//
	virtual             ~vrBrowser						(void);

	//<doc>-------------------------------------------------------
	//<dd> Binds the given node to the Background stack (or unbinds the node).
	//
	// [in] node: The node to bind or unbind.
	// [in] val: TRUE to bind, FALSE to unbind the given node.
	//
	void                Bind								(vrBackground *node, SFBool val);

	//<doc>-------------------------------------------------------
	//<dd> Binds the given node to the Fog stack (or unbinds the node).
	//
	// [in] node: The node to bind or unbind.
	// [in] val: TRUE to bind, FALSE to unbind the given node.
	//
	void                Bind								(vrFog *node, SFBool val);

	//<doc>-------------------------------------------------------
	//<dd> Binds the given node to the Viewpoint stack (or unbinds the node).
	//
	// [in] node: The node to bind or unbind.
	// [in] val: TRUE to bind, FALSE to unbind the given node.
	//
	void                Bind								(vrViewpoint *node, SFBool val);

	//<doc>-------------------------------------------------------
	//<dd> Binds the given node to the NavigationInfo stack (or unbinds the node).
	//
	// [in] node: The node to bind or unbind.
	// [in] val: TRUE to bind, FALSE to unbind the given node.
	//
	void                Bind								(vrNavigationInfo *node, SFBool val);

	//<doc>-------------------------------------------------------
	//<dd> Binds the given node to the approriate stack based on the nodes runtime type (or unbinds the node).
	//
	// [in] node: The node to bind or unbind.
	// [in] val: TRUE to bind, FALSE to unbind the given node.
	//
	void                Bind								(vrBindable *node, SFBool val);

	//<doc>-------------------------------------------------------
	//<dd> Returns the top of the Background stack.
	//
	vrBackground       *GetBackground				(void) const;

	//<doc>-------------------------------------------------------
	//<dd> Returns the top of the Fog stack.
	//
	vrFog              *GetFog							(void) const;

	//<doc>-------------------------------------------------------
	//<dd> Returns the top of the Viewpoint stack.
	//
	vrViewpoint        *GetViewpoint				(void) const;

	//<doc>-------------------------------------------------------
	//<dd> Returns the top of the NavigationInfo stack.
	//
	vrNavigationInfo   *GetNavigationInfo		(void) const;

	//<doc>-------------------------------------------------------
	//<dd> Read a .wrl file.  Returns TRUE on success.
	//
	// [in] filename: The name of the file to read.
	// [in] insertAt: A grouping node into which the file can be added.  If NULL file is added the this browser.
	//
	SFBool              ReadURL		(const SFString& filename, vrGroupingNode *insertAt=NULL);

	//<doc>-------------------------------------------------------
	//<dd> Read a .wrl file.  Returns TRUE on success.
	//
	// [in] fp: FILE * to open.
	// [in] insertAt: A grouping node into which the file can be added.  If NULL file is added the this browser.
	//
	SFBool              ReadURL		(FILE *fp, vrGroupingNode *insertAt=NULL);

	//<doc>-------------------------------------------------------
	//<dd> Add a ROUTE by name (as opposed to by a pointer to the node).
	//
	// [in] srcName: The name of the source node.
	// [in] srcType: The field in the source node to route from.
	// [in] dstName: The name of the destination node.
	// [in] dstType: The field in the destination node to route to.
	//
	vrRoute					   *AddRoute						(const SFString& srcName, const SFString& srcType, const SFString& dstName, const SFString& dstType, SFBool internal=FALSE);

	//<doc>-------------------------------------------------------
	//<dd> Modifies the suggested frame rate.
	//
	// [in] frames: The frame rate.
	//
	void							  SetFrameRate				(SFInt32 frames);

	//<doc>-------------------------------------------------------
	//<dd> Advance the internal clock one tick.  Returns TRUE if application should call Traverse to render the scene).
	//
	// [in] mode: Undocumented.
	//
	SFBool						  Tick								(SFInt32 mode=0);

	//<doc>-------------------------------------------------------
	//<dd> Traverse the scene.  NULL implies render the scene to the window.
	//
	// [in] t: Traverser to use to traverse the scene graph.
	//
	virtual void				Traverse						(vrTraverser *t=NULL) const;

	//<doc>-------------------------------------------------------
	//<dd>Retrieve a traverser by it's position in traverser list.
	//
	// [in] n: The traverser to return.
	//
	vrTraverser        *GetTraverserByNumber (SFInt32 location) const;

	//<doc>-------------------------------------------------------
	//<dd>Retrieve a traverser by it's type.
	//
	// [in] pClass: The type of the traverser to return (first one encountered).
	//
	vrTraverser        *GetTraverserByType (vrRuntimeClass *pClass) const;

	//<doc>-------------------------------------------------------
	//<dd>Add a traverser to the traverser list (at a particular location in the list).
	//
	// [in] t: The traverser to add (-1 means append to end of list).
	//
	vrTraverser        *SetTraverser        (vrTraverser *t, SFInt32 location, SFBool insert);

	//<doc>-------------------------------------------------------
	//<dd>Retrieve the number of traversers attached to this browser
	//
	SFInt32             GetNTraversers (void) const;

	//<doc>-------------------------------------------------------
	//<dd> Called by the application, this method responds to user actions (mouse movements).
	//<dd> Returns TRUE if the message was processed.
	//
	// [in] msg: The user message
	//
	virtual SFBool      ProcessUserMessage	(const vrUserMessage& msg);

	//<doc>-------------------------------------------------------
	//<dd> Moves the current browser viewpoint to a different location (in nFrames steps)
	//
	// [in] newVP: The viewpoint
	// [in] nFrames: The number of frames to display in the process of moving at the current frame rate.
	//
	void                ChangeViewpoint(vrViewpoint *newVP, SFInt32 nFrames=20);

	//<doc>-------------------------------------------------------
	//<dd> Returns the same value as the most recent PickScene function call.
	//
	vrGroupingNode     *GetSelection(void) const;

	//<doc>-------------------------------------------------------
	//<dd> Returns a the grouping node (if any) that occupies the screen space referenced by the point.
	//
	// [in] pt: The screen space point at which to pick (z-component is unused). 
	//
	vrGroupingNode     *PickScene(SFVec3f pt);

	//<nodoc>-------------------------------------------------------
	//<ul> Used internally to set the currently selected grouping node.
	//
	void                SetSelection(vrGroupingNode *s);

	//<doc>-------------------------------------------------------
	//<dd> Clear the browser's memory.
	//
	// [in] resetOnly: If TRUE do not clear memory just reset.
	//
  void                Clear								(SFBool resetOnly);

	//<doc>------------------------------------------------------------
	// <dd>Declare that this node may be runtime typed and dynamically created. [ DECLARE_NODE ]
	//
	DECLARE_NODE(vrBrowser);

public:
	//<nodoc>------------------------------------------------------------
	// <dd>Do not use this field it is going to disappear.
	//
	vrMatrix matrix;
		
private:
	//<nodoc>------------------------------------------------------------
	// <dd>Calls the parser.
	//
	SFBool ParseFile  (FILE *fp);

	//<nodoc>------------------------------------------------------------
	// <dd>Copy Constructor.
	//
	vrBrowser(const vrBrowser& browser)
		{ }

	//<doc>------------------------------------------------------------
	// <dd>The Viewpoint stack
	//
	vrNodeStack<vrViewpoint *>      m_ViewpointStack;

	//<doc>------------------------------------------------------------
	// <dd>The NavigationInfo stack
	//
	vrNodeStack<vrNavigationInfo *> m_NavInfoStack;

	//<doc>------------------------------------------------------------
	// <dd>The Background stack
	//
	vrNodeStack<vrBackground *>     m_BackgroundStack;

	//<doc>------------------------------------------------------------
	// <dd>The Fog stack
	//
	vrNodeStack<vrFog *>            m_FogStack;
};

inline void vrBrowser::SetFrameRate(SFInt32 frames)
{
	m_FramesPerSec = frames;
	m_FrameRate = vrTime(0, (int)(1000000.0/(SFFloat)m_FramesPerSec));
	m_LastFrame = vrNow(); //m_StartTime = vrNow();
}

inline SFBool vrBrowser::Tick(SFInt32 mode)
{
	vrTime nextFrame(m_LastFrame + m_FrameRate);
	vrTime now = vrNow();

	if (now > nextFrame)
	{
		m_LastFrame = now;
		return TRUE;
	}
	return FALSE;
}

inline vrBackground* vrBrowser::GetBackground(void) const
{
	return m_BackgroundStack.Peek();
}

inline vrFog* vrBrowser::GetFog(void) const
{
	return m_FogStack.Peek();
}

inline vrViewpoint *vrBrowser::GetViewpoint(void) const
{
	return m_ViewpointStack.Peek();
}

inline vrNavigationInfo *vrBrowser::GetNavigationInfo(void) const
{
	return m_NavInfoStack.Peek();
}

inline vrGroupingNode *vrBrowser::GetSelection(void) const
{
	return m_PickedObject;
}

inline void vrBrowser::SetSelection(vrGroupingNode *s)
{
	m_PickedObject = s;;
}

#endif
