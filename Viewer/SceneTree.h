#ifndef SCENE_TREE_H
#define SCENE_TREE_H

#include <wx/treectrl.h>
#include <wx/wx.h>
#include <wx/event.h>
#include <wx/hashmap.h>


#include "../Core/EntityPool.h"

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

/**
  Represents the current scene in form of a flat tree.
  Lists all entities currently in the scene.
*/
class SceneTree :
	public wxTreeCtrl,
	public EntityPoolObserver
{
public:

	// A hash map with string keys and wxTreeItemIds values
	// WX_DECLARE_STRING_HASH_MAP( wxTreeItemId, HashMap_wxTreeItemId );

	SceneTree( wxWindow*          parent,
	           wxWindowID         id,
	           const wxPoint&     pos = wxDefaultPosition,
	           const wxSize&      size = wxDefaultSize,
	           long               style = wxTR_HAS_BUTTONS,
	           const wxValidator& validator = wxDefaultValidator,
	           const wxString&    name = wxT( "treeCtrl" ));
	~SceneTree( void );

	Entity* GetEntity( wxTreeItemId Item );

private:

	void OnEntityInsert( Entity* Object, std::size_t Position );
	void OnEntityRemove( Entity* Object, std::size_t Position );

	void    LoadImageList();

	wxString RootString;

	void OnTreeSelectionChanged( wxTreeEvent& event );
	void OnItemActivated( wxTreeEvent& event );
	void OnOgreChanged( wxCommandEvent& event );
};

#endif // SCENE_TREE_H
