#ifndef __CHECKEDTEXTURE_H3D
#define __CHECKEDTEXTURE_H3D

#include "GL\gl.h"

//----------------------------------------------------------------------
//----------------------------------------------------------------------
class vrCheckedTexture : public vrPixelTexture
{
protected:

public:
	// constructors
		       vrCheckedTexture(void);
		       vrCheckedTexture(const vrCheckedTexture& v);
					 vrCheckedTexture(const SFColor& c1, const SFColor& c2);
	virtual ~vrCheckedTexture(void);

	         vrCheckedTexture     & operator=(const vrCheckedTexture& v);
	virtual  SFNode          Clone(void) const;

	virtual  void                Traverse(vrTraverser *t) const;

	DECLARE_NODE(vrCheckedTexture);
};

//----------------------------------------------------------------------
inline void vrCheckedTexture::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}

//----------------------------------------------------------------------
inline vrCheckedTexture::vrCheckedTexture(void) : vrPixelTexture()
{
}

inline vrCheckedTexture::vrCheckedTexture(const vrCheckedTexture& v) : vrPixelTexture(v)
{
}

inline vrCheckedTexture::~vrCheckedTexture(void)
{
}

inline vrCheckedTexture& vrCheckedTexture::operator=(const vrCheckedTexture& v)
{
	vrPixelTexture::operator=(v);


	return *this;
}

inline SFNode vrCheckedTexture::Clone(void) const
{
	return new vrCheckedTexture(*this);
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
class vrRampTexture : public vrPixelTexture
{
protected:

public:
	// constructors
		       vrRampTexture(void);
		       vrRampTexture(const vrRampTexture& v);
					 vrRampTexture(const SFColor& c1, const SFColor& c2);
	virtual ~vrRampTexture(void);

	         vrRampTexture     & operator=(const vrRampTexture& v);
	virtual  SFNode          Clone(void) const;

	virtual  void                Traverse(vrTraverser *t) const;

	DECLARE_NODE(vrRampTexture);
};

//----------------------------------------------------------------------
inline void vrRampTexture::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}

//----------------------------------------------------------------------
inline vrRampTexture::vrRampTexture(void) : vrPixelTexture()
{
}

inline vrRampTexture::vrRampTexture(const vrRampTexture& v) : vrPixelTexture(v)
{
}

inline vrRampTexture::~vrRampTexture(void)
{
}

inline vrRampTexture& vrRampTexture::operator=(const vrRampTexture& v)
{
	vrPixelTexture::operator=(v);


	return *this;
}

inline SFNode vrRampTexture::Clone(void) const
{
	return new vrRampTexture(*this);
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
class vrCircleTexture : public vrPixelTexture
{
protected:

public:
	// constructors
		       vrCircleTexture(void);
		       vrCircleTexture(const vrCircleTexture& v);
					 vrCircleTexture(const SFColor& c1, const SFColor& c2);
	virtual ~vrCircleTexture(void);

	         vrCircleTexture     & operator=(const vrCircleTexture& v);
	virtual  SFNode          Clone(void) const;

	virtual  void                Traverse(vrTraverser *t) const;

	DECLARE_NODE(vrCircleTexture);
};

//----------------------------------------------------------------------
inline void vrCircleTexture::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}

//----------------------------------------------------------------------
inline vrCircleTexture::vrCircleTexture(void) : vrPixelTexture()
{
}

inline vrCircleTexture::vrCircleTexture(const vrCircleTexture& v) : vrPixelTexture(v)
{
}

inline vrCircleTexture::~vrCircleTexture(void)
{
}

inline vrCircleTexture& vrCircleTexture::operator=(const vrCircleTexture& v)
{
	vrPixelTexture::operator=(v);


	return *this;
}

inline SFNode vrCircleTexture::Clone(void) const
{
	return new vrCircleTexture(*this);
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
class vrCrossesTexture : public vrPixelTexture
{
protected:

public:
	// constructors
		       vrCrossesTexture(void);
		       vrCrossesTexture(const vrCrossesTexture& v);
					 vrCrossesTexture(const SFColor& c1, const SFColor& c2);
	virtual ~vrCrossesTexture(void);

	         vrCrossesTexture     & operator=(const vrCrossesTexture& v);
	virtual  SFNode          Clone(void) const;

	virtual  void                Traverse(vrTraverser *t) const;

	DECLARE_NODE(vrCrossesTexture);
};

//----------------------------------------------------------------------
inline void vrCrossesTexture::Traverse(vrTraverser *t) const
{
	t->Traverse(this);
}

//----------------------------------------------------------------------
inline vrCrossesTexture::vrCrossesTexture(void) : vrPixelTexture()
{
}

inline vrCrossesTexture::vrCrossesTexture(const vrCrossesTexture& v) : vrPixelTexture(v)
{
}

inline vrCrossesTexture::~vrCrossesTexture(void)
{
}

inline vrCrossesTexture& vrCrossesTexture::operator=(const vrCrossesTexture& v)
{
	vrPixelTexture::operator=(v);


	return *this;
}

inline SFNode vrCrossesTexture::Clone(void) const
{
	return new vrCrossesTexture(*this);
}

#endif

