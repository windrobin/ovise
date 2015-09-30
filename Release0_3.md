# Release 0.3 - gnome #

This release will expand the features of 0.2. This page is currently only a draft, so feature may change before release.

## Features ##
  * SceneTree - hierarchical browser for scene structure
  * Linux support
  * Entity system
  * Plugins for entity visiualization
  * Plugins for network interfaces

## Description ##
For this release OViSE will undergo a major restructuring. This will be the first version of OViSE that will be cross-platform between Windows and Linux. Furthermore it will contain the new entity system that allows to create custom entities with arbitrary attributes. A plugin system allows to write custom visualizations specialized on entity types. The entity pool also allows observers to connect to it to be notified on changes in the pool. Last but no least a plugin framework for network interfaces is created that allows the remote manipulation of the entity pool.

Note: DotScene handling is disabled in this release. It will be back in the next release. Planned is to exchange Xerces with rapidxml to reduce dependencies and slim down the code. There will also be a switch to the new Blender 2.5 exporter and the scene format therein.

**Update**: This version has been released to the Mercurial repository under the tag "v0-3\_gnome".