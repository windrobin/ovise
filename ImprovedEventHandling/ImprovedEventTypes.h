#pragma once

#include "../ImprovedEventHandling/ImprovedEvent.h"

// Declare events for EventListener
extern const wxEventType EVT_DEFAULT;
// Declare events for OgreObjectListener
extern const wxEventType EVT_OGRE_OBJECT_CHANGED;
extern const wxEventType EVT_OGRE_OBJECT_CONSTRUCTED;
extern const wxEventType EVT_OGRE_OBJECT_DESTRUCTED;
extern const wxEventType EVT_OGRE_OBJECT_RENAMED;
// Declare events for Selection
extern const wxEventType EVT_OGRE_OBJECT_SELECTED;
extern const wxEventType EVT_OGRE_OBJECT_UNSELECTED;
// Declare events for MovableObjectListener
extern const wxEventType EVT_OGRE_MOVABLEOBJECT_CHANGED;
extern const wxEventType EVT_OGRE_MOVABLEOBJECT_CONSTRUCTED;
extern const wxEventType EVT_OGRE_MOVABLEOBJECT_DESTRUCTED;
extern const wxEventType EVT_OGRE_MOVABLEOBJECT_RENAMED;
// Declare events for CameraListener
extern const wxEventType EVT_OGRE_CAMERA_CHANGED;
extern const wxEventType EVT_OGRE_CAMERA_CONSTRUCTED;
extern const wxEventType EVT_OGRE_CAMERA_DESTRUCTED;
extern const wxEventType EVT_OGRE_CAMERA_RENAMED;
// Declare events for EntityListener
extern const wxEventType EVT_OGRE_ENTITY_CHANGED;
extern const wxEventType EVT_OGRE_ENTITY_CONSTRUCTED;
extern const wxEventType EVT_OGRE_ENTITY_DESTRUCTED;
extern const wxEventType EVT_OGRE_ENTITY_RENAMED;
// Declare events for LightListener
extern const wxEventType EVT_OGRE_LIGHT_CHANGED;
extern const wxEventType EVT_OGRE_LIGHT_CONSTRUCTED;
extern const wxEventType EVT_OGRE_LIGHT_DESTRUCTED;
extern const wxEventType EVT_OGRE_LIGHT_RENAMED;
// Declare events for SceneManagerListener
extern const wxEventType EVT_OGRE_SCENEMANAGER_CHANGED;
extern const wxEventType EVT_OGRE_SCENEMANAGER_CONSTRUCTED;
extern const wxEventType EVT_OGRE_SCENEMANAGER_DESTRUCTED;
extern const wxEventType EVT_OGRE_SCENEMANAGER_RENAMED;
// Declare events for SceneNodeListener
extern const wxEventType EVT_OGRE_SCENENODE_CHANGED;
extern const wxEventType EVT_OGRE_SCENENODE_CONSTRUCTED;
extern const wxEventType EVT_OGRE_SCENENODE_DESTRUCTED;
extern const wxEventType EVT_OGRE_SCENENODE_RENAMED;
extern const wxEventType EVT_OGRE_SCENENODE_MOVED;
extern const wxEventType EVT_OGRE_SCENENODE_ROTATED;
extern const wxEventType EVT_OGRE_SCENENODE_SCALED;

