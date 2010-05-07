#include "../OViSE/SceneTreeOgreObjectListener.h"

SceneTreeOgreObjectListener::SceneTreeOgreObjectListener() { this->mSceneTree = 0; }
SceneTreeOgreObjectListener::~SceneTreeOgreObjectListener(void) { }
// Get/Set Attributes
void SceneTreeOgreObjectListener::SetSceneTree(SceneTree* pSceneTree) { this->mSceneTree = pSceneTree; }
// Management of listener, sealed
void SceneTreeOgreObjectListener::StartListening() { if (this->mSceneTree != 0) OgreObjectListener::StartListening(); }
wxString SceneTreeOgreObjectListener::GetListenerTypeName() { return ToWxString("SceneTreeOgreObjectListener"); }
// Methods of parent events, sealed
void SceneTreeOgreObjectListener::OnChanged(ImprovedEvent &event)
{
	event.Skip();
}
void SceneTreeOgreObjectListener::OnConstructed(ImprovedEvent &event)
{
	this->mSceneTree->AddOgreObject(event.GetContextInfo());
	event.Skip();
}
void SceneTreeOgreObjectListener::OnDestructed(ImprovedEvent &event)
{
	this->mSceneTree->RemoveOgreObject(event.GetContextInfo());
	event.Skip();
}
void SceneTreeOgreObjectListener::OnRenamed(ImprovedEvent &event)
{
	event.Skip();
}
void SceneTreeOgreObjectListener::OnSelected(ImprovedEvent &event)
{
	// Stop publishing selection-changed-events, while apply selection in SceneTree. Otherwise code walkhrouth in an endless loop!
	this->mSceneTree->SetInputSource(InputSourceInterface::Event);
	
	// Apply SelectItem()
	QualifiedName qName = event.GetContextInfo();
	wxTreeItemId Item = this->mSceneTree->Items[qName.UniqueName()];
	this->mSceneTree->SelectItem(Item);

	// Start publishing selection-changed-events again!
	this->mSceneTree->SetInputSource(InputSourceInterface::Gui);

	// Forwarding event
	event.Skip();
}
void SceneTreeOgreObjectListener::OnUnselected(ImprovedEvent &event)
{
	// Stop publishing selection-changed-events, while apply selection in SceneTree. Otherwise code walkhrouth in an endless loop!
	this->mSceneTree->SetPublishTreeSelectionChanged(false);

	// Apply UnselectItem()
	QualifiedName qName = event.GetContextInfo();
	wxTreeItemId Item = this->mSceneTree->Items[qName.UniqueName()];
	this->mSceneTree->UnselectItem(Item);

	// Start publishing selection-changed-events again!
	this->mSceneTree->SetPublishTreeSelectionChanged(true);

	// Forwarding event
	event.Skip();
}