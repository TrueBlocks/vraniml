//-------------------------------------------------------------------------
// Copyright (c) 1997-1998 Great Hill Corporation
// All Rights Reserved.
//-------------------------------------------------------------------------
// WARNING: THIS FILE WAS CREATED AUTOMATICALLY
//-------------------------------------------------------------------------
#include "Kramer.h"

#include "Appearance.h"
#include "Material.h"
#include "PixelTexture.h"
#include "TextureTransform.h"

IMPLEMENT_NODE(vrAppearance, vrNode);

//----------------------------------------------------------------------
vrAppearance::vrAppearance(void) : vrNode()
{
	m_Material           = NULL;
	m_Texture            = NULL;
	m_TextureTransform   = NULL;

	if (GetRuntimeClass()->Reference()==2)
	{
		AddExposedField(SFNODE, VRML_MATERIAL_STR);
		AddExposedField(SFNODE, VRML_TEXTURE_STR);
		AddExposedField(SFNODE, VRML_TEXTURETRANSFORM_STR);
	}
}

vrAppearance::vrAppearance(const vrAppearance& v) : vrNode(v)
{
	m_Material=NULL;
	SetMaterial(((v.m_Material) ? (vrMaterial*)v.m_Material->Clone() : NULL));
	m_Texture=NULL;
	SetTexture(((v.m_Texture) ? (vrPixelTexture*)v.m_Texture->Clone() : NULL));
	m_TextureTransform=NULL;
	SetTextureTransform(((v.m_TextureTransform) ? (vrTextureTransform*)v.m_TextureTransform->Clone() : NULL));
	GetRuntimeClass()->Reference();
}

vrAppearance::~vrAppearance(void)
{
	vrDELETE(m_Material);
	vrDELETE(m_Texture);
	vrDELETE(m_TextureTransform);
	GetRuntimeClass()->Dereference();
}

vrAppearance& vrAppearance::operator=(const vrAppearance& v)
{
	vrNode::operator=(v);

	vrDELETE(m_Material);
	SetMaterial(((v.m_Material) ? (vrMaterial*)v.m_Material->Clone() : NULL));
	vrDELETE(m_Texture);
	SetTexture(((v.m_Texture) ? (vrPixelTexture*)v.m_Texture->Clone() : NULL));
	vrDELETE(m_TextureTransform);
	SetTextureTransform(((v.m_TextureTransform) ? (vrTextureTransform*)v.m_TextureTransform->Clone() : NULL));

	return *this;
}

SFNode vrAppearance::Clone(void) const
{
	return new vrAppearance(*this);
}

//----------------------------------------------------------------------
void vrAppearance::SetMaterial(const vrMaterial* material)
{
	vrDELETE(m_Material);
	m_Material = (vrMaterial*)material; //((material) ? (vrMaterial*)material->Clone() : NULL);
	if (m_Material)
		m_Material->Reference();
}

void vrAppearance::SetTexture(const vrPixelTexture* texture)
{
	vrDELETE(m_Texture);
	m_Texture = (vrPixelTexture*)texture; //((texture) ? (vrPixelTexture*)texture->Clone() : NULL);
	if (m_Texture)
		m_Texture->Reference();
}

void vrAppearance::SetTextureTransform(const vrTextureTransform* texturetransform)
{
	vrDELETE(m_TextureTransform);
	m_TextureTransform = (vrTextureTransform*)texturetransform; //((texturetransform) ? (vrTextureTransform*)texturetransform->Clone() : NULL);
	if (m_TextureTransform)
		m_TextureTransform->Reference();
}

void vrAppearance::ReceiveEventIn(vrEvent *ev)
{
	if (ev->m_FieldID == VRML_MATERIAL_STR)
		{
			SetMaterial(*((vrMaterial* *)ev->m_Value));
			SendEventOut(VRML_MATERIAL_STR, &m_Material);
		}
	else if (ev->m_FieldID == VRML_TEXTURE_STR)
		{
			SetTexture(*((vrPixelTexture* *)ev->m_Value));
			SendEventOut(VRML_TEXTURE_STR, &m_Texture);
		}
	else if (ev->m_FieldID == VRML_TEXTURETRANSFORM_STR)
		{
			SetTextureTransform(*((vrTextureTransform* *)ev->m_Value));
			SendEventOut(VRML_TEXTURETRANSFORM_STR, &m_TextureTransform);
		}
}

//----------------------------------------------------------------------
SFNode vrAppearance::FindByType(vrRuntimeClass *pClass) const
{
	if (m_Material && m_Material->IsKindOf(pClass))
		return ((SFNode)m_Material);

	if (m_Texture && m_Texture->IsKindOf(pClass))
		return ((SFNode)m_Texture);

	if (m_TextureTransform && m_TextureTransform->IsKindOf(pClass))
		return ((SFNode)m_TextureTransform);

	return vrNode::FindByType(pClass);
}

SFNode vrAppearance::FindByName(const SFString& nodeName) const
{
	SFNode node = NULL;

	if (m_Material && ((node = m_Material->FindByName(nodeName)) != NULL))
		return (node);

	if (m_Texture && ((node = m_Texture->FindByName(nodeName)) != NULL))
		return (node);

	if (m_TextureTransform && ((node = m_TextureTransform->FindByName(nodeName)) != NULL))
		return (node);

	return vrNode::FindByName(nodeName);
}

SFBool vrAppearance::ForEvery(PFBO3V userFn, void *userData, PFBO3V afterFn)
{
	if (m_Material)
		m_Material->ForEvery(userFn, userData, afterFn);

	if (m_Texture)
		m_Texture->ForEvery(userFn, userData, afterFn);

	if (m_TextureTransform)
		m_TextureTransform->ForEvery(userFn, userData, afterFn);

	return vrNode::ForEvery(userFn, userData, afterFn);
}


//----------------------------------------------------------------------
SFBool vrAppearance::IsDefault(const SFString& fieldName, vrField *field) const
{
	if (!fieldName.Empty())
	{
		CHECK_FIELD("material", m_Material, NULL);
		//if (fieldName == "material")
		//{
		//	if (field)
		//		SetValEx(field, (void*)&m_Material);
		//	return (NULL == m_Material);
		//}

		CHECK_FIELD("texture", m_Texture, NULL);
		//if (fieldName == "texture")
		//{
		//	if (field)
		//		SetValEx(field, (void*)&m_Texture);
		//	return (NULL == m_Texture);
		//}

		CHECK_FIELD("textureTransform", m_TextureTransform, NULL);
		//if (fieldName == "textureTransform")
		//{
		//	if (field)
		//		SetValEx(field, (void*)&m_TextureTransform);
		//	return (NULL == m_TextureTransform);
		//}

		// may be looking for field in parent class so fall through
	} else
	{
		ASSERT(!field);
		// NULL fieldName -- try all fields
		if (!IsDefault("material")) return FALSE;
		if (!IsDefault("texture")) return FALSE;
		if (!IsDefault("textureTransform")) return FALSE;
	}

	// parent class is vrNode...no fields to check
	return TRUE;
}

void vrAppearance::AddChild(SFNode node)
{
	if (node->IsKindOf(GETRUNTIME_CLASS(vrMaterial)))
	{
		SetMaterial((vrMaterial*)node);
	} else if (node->IsKindOf(GETRUNTIME_CLASS(vrPixelTexture)))
	{
		SetTexture((vrPixelTexture*)node);
	} else 
	{
		ASSERT(node->IsKindOf(GETRUNTIME_CLASS(vrTextureTransform)));
		SetTextureTransform((vrTextureTransform*)node);
	}
}

//----------------------------------------------------------------------
SFBool vrAppearance::SetFieldValue(const SFString& fieldName, void *val)
{
	if (FALSE) // use this to make automatic creation of this function easier
	{
	} else if (fieldName == "material")
	{
		AddChild((SFNode)val);
		return TRUE;
	} else if (fieldName == "texture")
	{
		AddChild((SFNode)val);
		return TRUE;
	} else if (fieldName == "textureTransform")
	{
		AddChild((SFNode)val);
		return TRUE;
	}

	ASSERT(0); // Invalid field name
	return FALSE;
}
