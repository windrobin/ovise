#pragma once
#include <wx/treectrl.h>
#include <wx/wx.h>
#include <wx/event.h>
#include "../OViSEAux/OgreAPIMediator.h"

#ifndef __APPLE__
#include <Ogre.h>
#else
#include <Ogre/Ogre.h>
#endif

enum OViSESceneTreeDataType
{
	ROOT,
	SCENE_NODE,
	CAMERA,
	LIGHT,
	ENTITY
};

class OViSESceneTreeData : public wxTreeItemData
{
public:
	OViSESceneTreeData(OViSESceneTreeDataType type, void *dataPointer);
	virtual ~OViSESceneTreeData();

	OViSESceneTreeDataType getType();

	void* getDataPointer();

private:
	OViSESceneTreeDataType mType;
	std::string mName;
	void *mData;
};


class OViSESceneTree :
	public wxTreeCtrl
{
public:
	OViSESceneTree(Ogre::SceneManager *manager, wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = wxTR_HAS_BUTTONS, const wxValidator& validator = wxDefaultValidator,
		const wxString& name = wxT("treeCtrl"));
	~OViSESceneTree(void);

	void setSceneManager(Ogre::SceneManager *manager);

	void initTree();

	void updateTreeContents();

	void ConnectOgreAPIMediator();

private:
	void addSceneNodeToTree(Ogre::SceneNode *node, wxTreeItemId parentItemId);

	Ogre::SceneManager *mSceneManager;

	bool mInitialized;

	void OnSelectionChanged( wxCommandEvent& event );
	void OnOgreChanged( wxCommandEvent& event );
};

