## Overview ##
Expands on 0.4 with some new features.

## Features ##
  * Object selection via click in 3D view
  * Centralized application context
  * Improvements to camera controls
  * Dragger control for entity manipulation in viewport

## Description ##
Main feature is object selection in the 3D viewport. This is done via Ogre raycasts.

There will be a central application context that holds the state of the application, like selected entity, interaction mode etc.

Current camera controls are a bit sluggish and could be improved. This will also need some rethinking of input handling in general.
In addition to this a new dragger control should allow easy repositioning of entities in the viewport.