/**
 * This file contains the enum-declaration that describes all possible tags,
 * which can occure in a dotScene-XML-document.
 * Status corresponds to: version 1.0.0
 * This ENUM was created for dotScene 0.2.0 - some Tags from 1.0.0 have been added later
 * to gurantee compatiblity to the BlenderExporter. This ENUM waits for a complete recreation.
 *
 * @author Written by H.R., ITEC TH Karlsruhe, Germany, 2007-2008
 */
namespace dotSceneEnums
{
	enum dotSceneElementTags
	{
		angle_axis, /**< since 1.0.0 */
		axisXYZ,	/**< since 1.0.0 */

		billboard,
		billboardSet,

		camera,
		clipping,	/**< since 1.0.0 */
		colourAmbient,
		colourBackground,
		colourDiffuse,
		colourSpecular,
		commonDirection,	/**< since 1.0.0 */
		commonMovableObjectParams,	/**< since 1.0.0 */
		commonUpVector,	/**< since 1.0.0 */

		direction,	/**< since 1.0.0 */

		entity,
		environment,
		externals,

		file,
		floatRect,	/**< since 1.0.0 */
		fog,

		indexBuffer,
		item,

		light,
		lightAttenuation,
		localDirection,  //<- veraltet? prüfen!!!!!
		localDirectionVector,
		lookTarget,

		materialLODBias,	/**< since 1.0.0 */
		meshLODBias,	/**< since 1.0.0 */

		node,
		nodes,
		normal,

		octGeometry,
		octMaterial,
		octMesh,
		octNode,
		octree,
		offset,
		orientation, /**< since 1.0.0 */

		particleSystem,
		plane,
		position,
		property_tag, /**< _tag because "property" is a keyword here.. deside a workarround later.*/
		
		quaternion,

		scale,
		scene,
		shadowSettings,	/**< since 1.0.0 */
		shadowTextureConfig,	/**< since 1.0.0 */
		skyBox,
		skyDome,
		skyPlane,
		spotLightRange,	/**< since 1.0.0 */

		terrain,
		textureCoords,	/**< since 1.0.0 */
		textureStacksAndSlices,	/**< since 1.0.0 */
		trackTarget,

		upVector,
		userDataReference,

		vertexBuffer,
	   
		INVALID /**< Zero/invalid/-1 value of this enum. Important for "valid-check"-model */
	};
}
//typedef ElementTags dotSceneElementTags;