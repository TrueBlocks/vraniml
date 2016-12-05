#ifndef _FIELDDEFS_H
#define _FIELDDEFS_H

/* a constant character string for each built-in field name */
extern const char addChildrenStr[];
extern const char ambientIntensityStr[];
extern const char appearanceStr[];
extern const char attenuationStr[];
extern const char autoOffsetStr[];
extern const char avatarSizeStr[];
extern const char axisOfRotationStr[];
extern const char backUrlStr[];
extern const char bboxCenterStr[];
extern const char bboxSizeStr[];
extern const char beamWidthStr[];
extern const char beginCapStr[];
extern const char bindTimeStr[];
extern const char bottomRadiusStr[];
extern const char bottomStr[];
extern const char bottomUrlStr[];
extern const char ccwStr[];
extern const char centerStr[];
extern const char childrenStr[];
extern const char choiceStr[];
extern const char collideStr[];
extern const char collideTimeStr[];
extern const char colorIndexStr[];
extern const char colorPerVertexStr[];
extern const char colorStr[];
extern const char convexStr[];
extern const char coordIndexStr[];
extern const char coordStr[];
extern const char creaseAngleStr[];
extern const char crossSectionStr[];
extern const char cutOffAngleStr[];
extern const char cycleIntervalStr[];
extern const char cycleTimeStr[];
extern const char descriptionStr[];
extern const char diffuseColorStr[];
extern const char directionStr[];
extern const char directOutputStr[];
extern const char diskAngleStr[];
extern const char duration_changedStr[];
extern const char emissiveColorStr[];
extern LIBInterface const char enabledStr[];
extern const char endCapStr[];
extern const char enterTimeStr[];
extern const char exitTimeStr[];
extern const char familyStr[];
extern const char fieldOfViewStr[];
extern const char fogTypeStr[];
extern const char fontStyleStr[];
extern const char fraction_changedStr[];
extern const char frontUrlStr[];
extern const char geometryStr[];
extern const char groundAngleStr[];
extern const char groundColorStr[];
extern const char headlightStr[];
extern const char heightStr[];
extern const char hitNormal_changedStr[];
extern const char hitPoint_changedStr[];
extern const char hitTexCoord_changedStr[];
extern const char horizontalStr[];
extern const char imageStr[];
extern const char infoStr[];
extern const char intensityStr[];
extern const char isActiveStr[];
extern const char isBoundStr[];
extern const char isOverStr[];
extern const char jumpStr[];
extern const char justifyStr[];
extern const char keyStr[];
extern const char keyValueStr[];
extern const char languageStr[];
extern const char leftToRightStr[];
extern const char leftUrlStr[];
extern const char lengthStr[];
extern const char levelStr[];
extern const char locationStr[];
extern const char loopStr[];
extern const char materialStr[];
extern const char maxAngleStr[];
extern const char maxBackStr[];
extern const char maxExtentStr[];
extern const char maxFrontStr[];
extern const char maxPositionStr[];
extern const char minAngleStr[];
extern const char minBackStr[];
extern const char minFrontStr[];
extern const char minPositionStr[];
extern const char mustEvaluateStr[];
extern const char normalIndexStr[];
extern const char normalPerVertexStr[];
extern const char normalStr[];
extern const char offsetStr[];
extern const char onStr[];
extern const char orientation_changedStr[];
extern const char orientationStr[];
extern const char parameterStr[];
extern const char pitchStr[];
extern const char pointStr[];
extern const char position_changedStr[];
extern const char positionStr[];
extern const char priorityStr[];
extern const char proxyStr[];
extern const char radiusStr[];
extern const char rangeStr[];
extern const char removeChildrenStr[];
extern const char repeatSStr[];
extern const char repeatTStr[];
extern const char rightUrlStr[];
extern const char rotation_changedStr[];
extern const char rotationStr[];
extern const char scaleOrientationStr[];
extern const char scaleStr[];
extern const char set_bindStr[];
extern const char set_colorIndexStr[];
extern const char set_coordIndexStr[];
extern const char set_crossSectionStr[];
extern const char set_fractionStr[];
extern const char set_heightStr[];
extern const char set_normalIndexStr[];
extern const char set_orientationStr[];
extern const char set_scaleStr[];
extern const char set_spineStr[];
extern const char set_texCoordIndexStr[];
extern const char shininessStr[];
extern const char sideStr[];
extern const char sizeStr[];
extern const char skyAngleStr[];
extern const char skyColorStr[];
extern const char solidStr[];
extern const char sourceStr[];
extern const char spacingStr[];
extern const char spatializeStr[];
extern const char specularColorStr[];
extern const char speedStr[];
extern const char spineStr[];
extern const char startTimeStr[];
extern const char stopTimeStr[];
extern const char stringStr[];
extern const char styleStr[];
extern const char texCoordIndexStr[];
extern const char texCoordStr[];
extern const char textureStr[];
extern const char textureTransformStr[];
extern const char timeStr[];
extern const char titleStr[];
extern const char topStr[];
extern const char topToBottomStr[];
extern const char topUrlStr[];
extern const char touchTimeStr[];
extern const char trackPoint_changedStr[];
extern const char translationStr[];
extern const char translation_changedStr[];
extern const char transparencyStr[];
extern const char typeStr[];
extern const char urlStr[];
extern const char value_changedStr[];
extern const char vectorStr[];
extern const char visibilityLimitStr[];
extern const char visibilityRangeStr[];
extern const char whichChoiceStr[];
extern const char xDimensionStr[];
extern const char xSpacingStr[];
extern const char zDimensionStr[];
extern const char zSpacingStr[];

extern const char invalidateStr[];

/* and a #define to reference it as a constant */
#define VRML_ADDCHILDREN_STR ((SFInt32)addChildrenStr)
#define VRML_AMBIENTINTENSITY_STR ((SFInt32)ambientIntensityStr)
#define VRML_APPEARANCE_STR ((SFInt32)appearanceStr)
#define VRML_ATTENUATION_STR ((SFInt32)attenuationStr)
#define VRML_AUTOOFFSET_STR ((SFInt32)autoOffsetStr)
#define VRML_AVATARSIZE_STR ((SFInt32)avatarSizeStr)
#define VRML_AXISOFROTATION_STR ((SFInt32)axisOfRotationStr)
#define VRML_BACKURL_STR ((SFInt32)backUrlStr)
#define VRML_BBOXCENTER_STR ((SFInt32)bboxCenterStr)
#define VRML_BBOXSIZE_STR ((SFInt32)bboxSizeStr)
#define VRML_BEAMWIDTH_STR ((SFInt32)beamWidthStr)
#define VRML_BEGINCAP_STR ((SFInt32)beginCapStr)
#define VRML_BINDTIME_STR ((SFInt32)bindTimeStr)
#define VRML_BOTTOM_STR ((SFInt32)bottomStr)
#define VRML_BOTTOMRADIUS_STR ((SFInt32)bottomRadiusStr)
#define VRML_BOTTOMURL_STR ((SFInt32)bottomUrlStr)
#define VRML_CCW_STR ((SFInt32)ccwStr)
#define VRML_CENTER_STR ((SFInt32)centerStr)
#define VRML_CHILDREN_STR ((SFInt32)childrenStr)
#define VRML_CHOICE_STR ((SFInt32)choiceStr)
#define VRML_COLLIDE_STR ((SFInt32)collideStr)
#define VRML_COLLIDETIME_STR ((SFInt32)collideTimeStr)
#define VRML_COLOR_STR ((SFInt32)colorStr)
#define VRML_COLORINDEX_STR ((SFInt32)colorIndexStr)
#define VRML_COLORPERVERTEX_STR ((SFInt32)colorPerVertexStr)
#define VRML_CONVEX_STR ((SFInt32)convexStr)
#define VRML_COORD_STR ((SFInt32)coordStr)
#define VRML_COORDINDEX_STR ((SFInt32)coordIndexStr)
#define VRML_CREASEANGLE_STR ((SFInt32)creaseAngleStr)
#define VRML_CROSSSECTION_STR ((SFInt32)crossSectionStr)
#define VRML_CUTOFFANGLE_STR ((SFInt32)cutOffAngleStr)
#define VRML_CYCLEINTERVAL_STR ((SFInt32)cycleIntervalStr)
#define VRML_CYCLETIME_STR ((SFInt32)cycleTimeStr)
#define VRML_DESCRIPTION_STR ((SFInt32)descriptionStr)
#define VRML_DIFFUSECOLOR_STR ((SFInt32)diffuseColorStr)
#define VRML_DIRECTION_STR ((SFInt32)directionStr)
#define VRML_DIRECTOUTPUT_STR ((SFInt32)directOutputStr)
#define VRML_DISKANGLE_STR ((SFInt32)diskAngleStr)
#define VRML_DURATION_CHANGED_STR ((SFInt32)duration_changedStr)
#define VRML_EMISSIVECOLOR_STR ((SFInt32)emissiveColorStr)
#define VRML_ENABLED_STR ((SFInt32)enabledStr)
#define VRML_ENDCAP_STR ((SFInt32)endCapStr)
#define VRML_ENTERTIME_STR ((SFInt32)enterTimeStr)
#define VRML_EXITTIME_STR ((SFInt32)exitTimeStr)
#define VRML_FAMILY_STR ((SFInt32)familyStr)
#define VRML_FIELDOFVIEW_STR ((SFInt32)fieldOfViewStr)
#define VRML_FOGTYPE_STR ((SFInt32)fogTypeStr)
#define VRML_FONTSTYLE_STR ((SFInt32)fontStyleStr)
#define VRML_FRACTION_CHANGED_STR ((SFInt32)fraction_changedStr)
#define VRML_FRONTURL_STR ((SFInt32)frontUrlStr)
#define VRML_GEOMETRY_STR ((SFInt32)geometryStr)
#define VRML_GROUNDANGLE_STR ((SFInt32)groundAngleStr)
#define VRML_GROUNDCOLOR_STR ((SFInt32)groundColorStr)
#define VRML_HEADLIGHT_STR ((SFInt32)headlightStr)
#define VRML_HEIGHT_STR ((SFInt32)heightStr)
#define VRML_HITNORMAL_CHANGED_STR ((SFInt32)hitNormal_changedStr)
#define VRML_HITPOINT_CHANGED_STR ((SFInt32)hitPoint_changedStr)
#define VRML_HITTEXCOORD_CHANGED_STR ((SFInt32)hitTexCoord_changedStr)
#define VRML_HORIZONTAL_STR ((SFInt32)horizontalStr)
#define VRML_IMAGE_STR ((SFInt32)imageStr)
#define VRML_INFO_STR ((SFInt32)infoStr)
#define VRML_INTENSITY_STR ((SFInt32)intensityStr)
#define VRML_ISACTIVE_STR ((SFInt32)isActiveStr)
#define VRML_ISBOUND_STR ((SFInt32)isBoundStr)
#define VRML_ISOVER_STR ((SFInt32)isOverStr)
#define VRML_JUMP_STR ((SFInt32)jumpStr)
#define VRML_JUSTIFY_STR ((SFInt32)justifyStr)
#define VRML_KEY_STR ((SFInt32)keyStr)
#define VRML_KEYVALUE_STR ((SFInt32)keyValueStr)
#define VRML_LANGUAGE_STR ((SFInt32)languageStr)
#define VRML_LEFTTORIGHT_STR ((SFInt32)leftToRightStr)
#define VRML_LEFTURL_STR ((SFInt32)leftUrlStr)
#define VRML_LENGTH_STR ((SFInt32)lengthStr)
#define VRML_LEVEL_STR ((SFInt32)levelStr)
#define VRML_LOCATION_STR ((SFInt32)locationStr)
#define VRML_LOOP_STR ((SFInt32)loopStr)
#define VRML_MATERIAL_STR ((SFInt32)materialStr)
#define VRML_MAXANGLE_STR ((SFInt32)maxAngleStr)
#define VRML_MAXBACK_STR ((SFInt32)maxBackStr)
#define VRML_MAXEXTENT_STR ((SFInt32)maxExtentStr)
#define VRML_MAXFRONT_STR ((SFInt32)maxFrontStr)
#define VRML_MAXPOSITION_STR ((SFInt32)maxPositionStr)
#define VRML_MINANGLE_STR ((SFInt32)minAngleStr)
#define VRML_MINBACK_STR ((SFInt32)minBackStr)
#define VRML_MINFRONT_STR ((SFInt32)minFrontStr)
#define VRML_MINPOSITION_STR ((SFInt32)minPositionStr)
#define VRML_MUSTEVALUATE_STR ((SFInt32)mustEvaluateStr)
#define VRML_NORMAL_STR ((SFInt32)normalStr)
#define VRML_NORMALINDEX_STR ((SFInt32)normalIndexStr)
#define VRML_NORMALPERVERTEX_STR ((SFInt32)normalPerVertexStr)
#define VRML_OFFSET_STR ((SFInt32)offsetStr)
#define VRML_ON_STR ((SFInt32)onStr)
#define VRML_ORIENTATION_CHANGED_STR ((SFInt32)orientation_changedStr)
#define VRML_ORIENTATION_STR ((SFInt32)orientationStr)
#define VRML_PARAMETER_STR ((SFInt32)parameterStr)
#define VRML_PITCH_STR ((SFInt32)pitchStr)
#define VRML_POINT_STR ((SFInt32)pointStr)
#define VRML_POSITION_CHANGED_STR ((SFInt32)position_changedStr)
#define VRML_POSITION_STR ((SFInt32)positionStr)
#define VRML_PRIORITY_STR ((SFInt32)priorityStr)
#define VRML_PROXY_STR ((SFInt32)proxyStr)
#define VRML_RADIUS_STR ((SFInt32)radiusStr)
#define VRML_RANGE_STR ((SFInt32)rangeStr)
#define VRML_REMOVECHILDREN_STR ((SFInt32)removeChildrenStr)
#define VRML_REPEATS_STR ((SFInt32)repeatSStr)
#define VRML_REPEATT_STR ((SFInt32)repeatTStr)
#define VRML_RIGHTURL_STR ((SFInt32)rightUrlStr)
#define VRML_ROTATION_CHANGED_STR ((SFInt32)rotation_changedStr)
#define VRML_ROTATION_STR ((SFInt32)rotationStr)
#define VRML_SCALE_STR ((SFInt32)scaleStr)
#define VRML_SCALEORIENTATION_STR ((SFInt32)scaleOrientationStr)
#define VRML_SET_BIND_STR ((SFInt32)set_bindStr)
#define VRML_SET_COLORINDEX_STR ((SFInt32)set_colorIndexStr)
#define VRML_SET_COORDINDEX_STR ((SFInt32)set_coordIndexStr)
#define VRML_SET_CROSSSECTION_STR ((SFInt32)set_crossSectionStr)
#define VRML_SET_FRACTION_STR ((SFInt32)set_fractionStr)
#define VRML_SET_HEIGHT_STR ((SFInt32)set_heightStr)
#define VRML_SET_NORMALINDEX_STR ((SFInt32)set_normalIndexStr)
#define VRML_SET_ORIENTATION_STR ((SFInt32)set_orientationStr)
#define VRML_SET_SCALE_STR ((SFInt32)set_scaleStr)
#define VRML_SET_SPINE_STR ((SFInt32)set_spineStr)
#define VRML_SET_TEXCOORDINDEX_STR ((SFInt32)set_texCoordIndexStr)
#define VRML_SHININESS_STR ((SFInt32)shininessStr)
#define VRML_SIDE_STR ((SFInt32)sideStr)
#define VRML_SIZE_STR ((SFInt32)sizeStr)
#define VRML_SKYANGLE_STR ((SFInt32)skyAngleStr)
#define VRML_SKYCOLOR_STR ((SFInt32)skyColorStr)
#define VRML_SOLID_STR ((SFInt32)solidStr)
#define VRML_SOURCE_STR ((SFInt32)sourceStr)
#define VRML_SPACING_STR ((SFInt32)spacingStr)
#define VRML_SPATIALIZE_STR ((SFInt32)spatializeStr)
#define VRML_SPECULARCOLOR_STR ((SFInt32)specularColorStr)
#define VRML_SPEED_STR ((SFInt32)speedStr)
#define VRML_SPINE_STR ((SFInt32)spineStr)
#define VRML_STARTTIME_STR ((SFInt32)startTimeStr)
#define VRML_STOPTIME_STR ((SFInt32)stopTimeStr)
#define VRML_STRING_STR ((SFInt32)stringStr)
#define VRML_STYLE_STR ((SFInt32)styleStr)
#define VRML_TEXCOORD_STR ((SFInt32)texCoordStr)
#define VRML_TEXCOORDINDEX_STR ((SFInt32)texCoordIndexStr)
#define VRML_TEXTURE_STR ((SFInt32)textureStr)
#define VRML_TEXTURETRANSFORM_STR ((SFInt32)textureTransformStr)
#define VRML_TIME_STR ((SFInt32)timeStr)
#define VRML_TITLE_STR ((SFInt32)titleStr)
#define VRML_TOP_STR ((SFInt32)topStr)
#define VRML_TOPTOBOTTOM_STR ((SFInt32)topToBottomStr)
#define VRML_TOPURL_STR ((SFInt32)topUrlStr)
#define VRML_TOUCHTIME_STR ((SFInt32)touchTimeStr)
#define VRML_TRACKPOINT_CHANGED_STR ((SFInt32)trackPoint_changedStr)
#define VRML_TRANSLATION_STR ((SFInt32)translationStr)
#define VRML_TRANSLATION_CHANGED_STR ((SFInt32)translation_changedStr)
#define VRML_TRANSPARENCY_STR ((SFInt32)transparencyStr)
#define VRML_TYPE_STR ((SFInt32)typeStr)
#define VRML_URL_STR ((SFInt32)urlStr)
#define VRML_VALUE_CHANGED_STR ((SFInt32)value_changedStr)
#define VRML_VECTOR_STR ((SFInt32)vectorStr)
#define VRML_VISIBILITYLIMIT_STR ((SFInt32)visibilityLimitStr)
#define VRML_VISIBILITYRANGE_STR ((SFInt32)visibilityRangeStr)
#define VRML_WHICHCHOICE_STR ((SFInt32)whichChoiceStr)
#define VRML_XDIMENSION_STR ((SFInt32)xDimensionStr)
#define VRML_XSPACING_STR ((SFInt32)xSpacingStr)
#define VRML_ZDIMENSION_STR ((SFInt32)zDimensionStr)
#define VRML_ZSPACING_STR ((SFInt32)zSpacingStr)

#define VRML_INVALIDATE_STR ((SFInt32)invalidateStr)

#endif