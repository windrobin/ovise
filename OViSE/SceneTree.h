#ifndef SCENE_TREE_H
#define SCENE_TREE_H

#include <wx/treectrl.h>
#include <wx/wx.h>
#include <wx/event.h>
#include <wx/hashmap.h>
#include "../OgreMediator/OgreMediator.h"
#include "../OViSE/SelectionManager.h"

#include "../ImprovedEventHandling/EventPublisherInterface.h"

#include "../OViSE/InputSourceInterface.h"

#ifndef __APPLE__
#include <Ogre.h>
#else
#include <Ogre/Ogre.h>
#endif

enum SceneTreeDataType
{
	OGRE_ROOT,
	SCENE_MANAGER,
	SCENE_ROOT,
	SCENE_NODE,
	CAMERA,
	LIGHT,
	ENTITY
};

class SceneTreeData :
	public wxTreeItemData
{
public:
	SceneTreeData(SceneTreeDataType type, void *dataPointer);
	virtual ~SceneTreeData();

	SceneTreeDataType getType();

	void* getDataPointer();

private:
	SceneTreeDataType mType;
	std::string mName;
	void *mData;
};

class SceneTree :
	public wxTreeCtrl,
	public EventPublisherInterface,
	public InputSourceInterface
{
public:

	// A hash map with string keys and wxTreeItemIds values
	WX_DECLARE_STRING_HASH_MAP( wxTreeItemId, HashMap_wxTreeItemId );

	SceneTree(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = wxTR_HAS_BUTTONS, const wxValidator& validator = wxDefaultValidator,
		const wxString& name = wxT("treeCtrl"));
	~SceneTree(void);

	HashMap_wxTreeItemId Items;

	void SetPublishTreeSelectionChanged(bool value);
	bool GetPublishTreeSelectionChanged();

	bool AddOgreObject(QualifiedName qOgreObject);
	bool RemoveOgreObject(QualifiedName qOgreObject);

private:
	wxString OGRE_ROOT_STRING;

	QualifiedName mLastSelectedEntry;
	wxTreeItemId mLastSelectedID;

	void addSceneNodeToTree(Ogre::SceneNode *node, wxTreeItemId parentItemId);

	Ogre::SceneManager *mSceneManager;

	bool mPublishTreeSelectionChanged;

	void OnTreeSelectionChanged( wxTreeEvent& event );
	void OnItemActivated( wxTreeEvent& event );
	void OnOgreChanged( wxCommandEvent& event );
};
#endif SCENE_TREE_H
