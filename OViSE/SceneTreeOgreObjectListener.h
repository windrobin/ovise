#pragma once

// Solution's includes
#include "../ImprovedEventHandling/OgreObjectListener.h"
#include "../OViSE/SceneTree.h"

class SceneTreeOgreObjectListener :
	public OgreObjectListener
{
private:
	SceneTree* mSceneTree;
public:
	SceneTreeOgreObjectListener(void);
	~SceneTreeOgreObjectListener(void);

	// Get/Set Attributes
	void SetSceneTree(SceneTree* pSceneTree);

	// Management of listener, sealed
	void StartListening();
	wxString GetListenerTypeName();

	// Methods of parent events, sealed
	void OnChanged(ImprovedEvent &event);
	void OnConstructed(ImprovedEvent &event);
	void OnDestructed(ImprovedEvent &event);
	void OnRenamed(ImprovedEvent &event);
	void OnSelected(ImprovedEvent &event);
	void OnUnselected(ImprovedEvent &event);
};