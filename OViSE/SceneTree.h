#ifndef SCENE_TREE_H
#define SCENE_TREE_H

#include <wx/treectrl.h>
#include <wx/wx.h>
#include <wx/event.h>
#include <wx/hashmap.h>
#include "../OgreMediator/OgreMediator.h"

#ifndef __APPLE__
#include <Ogre.h>
#else
#include <Ogre/Ogre.h>
#endif

enum SceneTreeDataType
{
	ROOT,
	SCENE_NODE,
	CAMERA,
	LIGHT,
	ENTITY
};

class SceneTreeData : public wxTreeItemData
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


class SceneTree : public wxTreeCtrl
{
public:

	// A hash map with string keys and wxTreeItemIds values
	WX_DECLARE_STRING_HASH_MAP( wxTreeItemId, HashMap_wxTreeItemId );

	SceneTree(Ogre::SceneManager *manager, wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = wxTR_HAS_BUTTONS, const wxValidator& validator = wxDefaultValidator,
		const wxString& name = wxT("treeCtrl"));
	~SceneTree(void);

	void setSceneManager(Ogre::SceneManager *manager);

	void initTree();

	void updateTreeContents();

	void ConnectOgreMediator();

	HashMap_wxTreeItemId Items;

private:
	void addSceneNodeToTree(Ogre::SceneNode *node, wxTreeItemId parentItemId);

	Ogre::SceneManager *mSceneManager;

	bool mInitialized;

	void OnSelectionChanged( wxCommandEvent& event );
	void OnOgreChanged( wxCommandEvent& event );
};
#endif SCENE_TREE_H
