/**
 * This file contains the enum-declaration that describes all possible tags,
 * which can occure in a dotScene-XML-document.
 * Status corresponds to: version 1.0.0
 * This ENUM was created for dotScene 0.2.0 - some Tags from 1.0.0 have been added later
 * to gurantee compatiblity to the BlenderExporter. This ENUM waits for a complete recreation.
 *
 * @author Written by H.R., ITEC TH Karlsruhe, Germany, 2007-2008
 */
enum dotSceneElementTags
{
    billboard, billboardSet,
    camera, colourAmbient, colourBackground, colourDiffuse, colourSpecular,
    entity, environment, externals,
    file, fog,
    indexBuffer, item,
    light, lightAttenuation, localDirection, lightRange, lookTarget,
    node, nodes, normal,
    octGeometry, octMaterial, octMesh, octNode, octree, offset,
    particleSystem, plane, position,
	property_tag, /**< _tag because "property" is a keyword here.. deside a workarround later.*/
    rotation,
    scale, scene,
    skyBox, skyDome, skyPlane,
    terrain, trackTarget,
    upVector, userDataReference,
    vertexBuffer,
   
    clipping /**< since 1.0.0 */
};
//typedef ElementTags dotSceneElementTags;