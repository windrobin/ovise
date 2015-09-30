# Introduction #

This page explains how you can export 3D models from Blender to be used with OViSE. To do this, you need Blender, the Ogre exporter script and the Ogre XML converter.


# Exporting from Blender #

The process described in this section might be similar in other modeling packages, the specifics might differ slightly though. In general, the exporter scripts generate Ogre XML files which then need to be converted to the binary Ogre mesh format using the XML converter. The Blender exporter also allows export of complete scenes in a specific XML format, which OViSE can also import. More details on this in a later section.

## What you need ##
  * [Blender](http://www.blender3d.org)
  * [Blender Ogre exporter script](http://code.google.com/p/blender2ogre/)
  * [Ogre XML converter](http://www.ogre3d.org/download/tools)

Note: there are several Blender exporters, a deprecated one for Blender version 2.49b and a very limited rewrite of that for the newest Blender version. Currently we recommend the one linked above as it is the most mature and feature complete. If you have built Ogre from source or downloaded the SDK you should already have the OgreXMLConverter binary file.

## Installation of the exporter script ##
Generally you only need to copy the Python script to your Blender scripts folder and then activate the plugin. For more information see [here](http://code.google.com/p/blender2ogre/wiki/Installation).

Activation of the plugin:
http://i61www.ira.uka.de/users/akasper/Misc/BlenderOgreExporterPluginActivation.PNG

Exporting options:
http://i61www.ira.uka.de/users/akasper/Misc/BlenderOgreExportDialog.PNG
Notes:
  * the exporter script can issue the conversion from XML to Ogre binary format using the OgreXMLConverter binary, it needs to know where to find that though, which means you'll most probably have to edit the python script with the correct path
  * coordinate systems of Blender and OViSE are identical with the z-axis pointing up (in contrast to Ogre default where y-axis is up), so no axis swap is need and it should be set to 'xyz'
  * select the things you want to export (scene, only selected meshes, animations)
  * if you want to use stencil shadows (dynamic shadows in OViSE), you need to generate edge lists, so check the box there
  * an often encountered issue is unapplied transformations or modifiers in Blender. Be sure to apply modifiers (except armature) before exporting. Also make sure transformations in object mode are applied (hit Ctrl+A and apply scale/rotation/location)

## Notes on robot models ##
Creating a robot model for use in OViSE is really simple. Create a rig for your model and connect both using an armature modifier. It is advised to use vertex groups for deformation (not bone envelopes). The robot model plugin for OViSE interprets bones to be 1 DOF joints. The bone's y axis is assumed to be the axis of rotation. This means that the rig should be constructed so, that for a joint the corresponding bone is parallel to the rotation axis of the joint. You can check out the blend files for the bundled robots to see how this can be done. Other than that you only need to export the mesh and make sure you have skeletal animation export enabled. This should yield in a .skeleton file that contains the bone setup.

## Exporting scenes ##
The Ogre exporter script can also generate a XML representation of a scene consisting of more than one object. Therein position, orientation, scale and hierarchical relations are saved. OViSE can load these scenes and reconstruct the scene. Note that lamps, cameras and environment settings are not yet supported. Also note that the models contained in the scene need to be available to OViSE (meaning they need to be in a known resource location, see resources.cfg).