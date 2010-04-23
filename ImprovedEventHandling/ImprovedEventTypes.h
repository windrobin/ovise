#pragma once

#include "../ImprovedEventHandling/ImprovedEvent.h"

// Declare events for EventListener
extern const wxEventType EVT_DEFAULT;
// Declare events for OgreObjectListener
extern const wxEventType EVT_OGRE_CHANGED;
extern const wxEventType EVT_OGRE_CONSTRUCTED;
extern const wxEventType EVT_OGRE_DESTRUCTED;
extern const wxEventType EVT_OGRE_RENAMED;
// Declare events for MovableObjectListener
extern const wxEventType EVT_OGRE_MOVABLEOBJECT_SELECTED;
extern const wxEventType EVT_OGRE_MOVABLEOBJECT_UNSELECTED;
// Declare events for CameraListener
//extern const wxEventType EVT_OGRE_CAMERA_CHANGED;
//extern const wxEventType EVT_OGRE_CAMERA_CONSTRUCTED;
//extern const wxEventType EVT_OGRE_CAMERA_DESTRUCTED;
//extern const wxEventType EVT_OGRE_CAMERA_RENAMED;
// Declare events for EntityListener
//extern const wxEventType EVT_OGRE_ENTITY_CHANGED;
//extern const wxEventType EVT_OGRE_ENTITY_CONSTRUCTED;
//extern const wxEventType EVT_OGRE_ENTITY_DESTRUCTED;
//extern const wxEventType EVT_OGRE_ENTITY_RENAMED;
// Declare events for LightListener
//extern const wxEventType EVT_OGRE_LIGHT_CHANGED;
//extern const wxEventType EVT_OGRE_LIGHT_CONSTRUCTED;
//extern const wxEventType EVT_OGRE_LIGHT_DESTRUCTED;
//extern const wxEventType EVT_OGRE_LIGHT_RENAMED;
// Declare events for SceneManagerListener
//extern const wxEventType EVT_OGRE_SCENEMANAGER_CHANGED;
//extern const wxEventType EVT_OGRE_SCENEMANAGER_CONSTRUCTED;
//extern const wxEventType EVT_OGRE_SCENEMANAGER_DESTRUCTED;
//extern const wxEventType EVT_OGRE_SCENEMANAGER_RENAMED;
// Declare events for SceneNodeListener
//extern const wxEventType EVT_OGRE_SCENENODE_CHANGED;
//extern const wxEventType EVT_OGRE_SCENENODE_CONSTRUCTED;
//extern const wxEventType EVT_OGRE_SCENENODE_DESTRUCTED;
//extern const wxEventType EVT_OGRE_SCENENODE_RENAMED;
extern const wxEventType EVT_OGRE_SCENENODE_TRANSLATED;
extern const wxEventType EVT_OGRE_SCENENODE_ROTATED;
extern const wxEventType EVT_OGRE_SCENENODE_SCALED;

