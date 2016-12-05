// Return the matrix implied by this node
vrMatrix vrTransform::GetLocalMatrix(void) const
{
	vrMatrix ret;

	// apply translation
	ret = ret * TranslationMatrix(GetTranslation());

	// apply center
	ret = ret * TranslationMatrix(GetCenter());

	// apply rotation
	ret = ret * RotationMatrix(GetRotation());

	// apply scale orientation
	ret = ret * RotationMatrix(GetScaleOrientation());

	// apply scale
	ret = ret * ScaleMatrix(GetScale());

	// undo scale orientation
	SFRotation ori = GetScaleOrientation();
	ori.Invert();
	ret = ret * RotationMatrix(ori);

	// undo center
	ret = ret * TranslationMatrix(-GetCenter());

	return ret;
}

