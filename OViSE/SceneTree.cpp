#include "SceneTree.h"
#include <memory>
#include <wx/config.h>
#include <wx/imaglist.h>
#include "../OViSEAux/StringConverter.h"

namespace {
// Holder for the associated entity
// Gets insertered as a user object
class EntityTreeData :
	public wxTreeItemData
{
public:
	EntityTreeData( Entity* p=0 ) : mEntity(p) {}

	Entity* mEntity;
};
}

/// ====================================================================================

SceneTree::SceneTree(wxWindow* parent, wxWindowID id, const wxPoint& pos,
							   const wxSize& size, long style, const wxValidator& validator, const wxString& name) :
	wxTreeCtrl(parent, id, pos, size, style, validator, name)
{	
	// Load icons
	LoadImageList();

	this->RootString = ToWxString("Entities");
	wxTreeItemId OgreRootTIID = this->AddRoot(this->RootString, 0, 0, 0);

	this->ExpandAll();

	this->Bind(wxEVT_COMMAND_TREE_SEL_CHANGED, &SceneTree::OnTreeSelectionChanged, this);
	//this->SetInputSource(Gui);
}

void SceneTree::OnEntityInsert( Entity* Object, std::size_t Position )
{
	this->InsertItem( this->GetRootItem(), Position, Object->GetName(), 1, 1, new EntityTreeData(Object) );
}

void SceneTree::OnEntityRemove(Entity *Object, std::size_t Position)
{
	wxTreeItemIdValue Cookie;
	wxTreeItemId Root = this->GetRootItem();

	// Iterate through all level 0 children
	for ( wxTreeItemId Item=this->GetFirstChild(Root,Cookie); Item.IsOk();
		Item=this->GetNextSibling(Item) )
	{
		// Is this the right one?
		if ( dynamic_cast<EntityTreeData*>( this->GetItemData(Item) )->mEntity == Object )
			this->Delete( Item );
	}
}

Entity* SceneTree::GetEntity( wxTreeItemId Item )
{
	EntityTreeData* Data = dynamic_cast<EntityTreeData*>( this->GetItemData(Item) );

	return Data ? Data->mEntity : 0;
}

void SceneTree::LoadImageList()
{
	wxConfig OviseConfig;
	wxString MediaPath=OviseConfig.Read(wxT("MediaDirStr"));

	std::auto_ptr<wxImageList> List(new wxImageList(16, 16, true, 2));
	
	// index 0 = Folder
	wxBitmap nodeIcon(MediaPath+wxT("/data/folder_16.png"), wxBITMAP_TYPE_PNG);
	List->Add(nodeIcon);
	// index 1 = MESH
	wxBitmap meshIcon(MediaPath+wxT("/data/box_16.png"), wxBITMAP_TYPE_PNG);
	List->Add(meshIcon);

	// Transfer ownership to the tree control
	this->AssignImageList(List.release());
}

SceneTree::~SceneTree(void)
{
	this->Unbind(wxEVT_COMMAND_TREE_SEL_CHANGED, &SceneTree::OnTreeSelectionChanged, this);
}

void SceneTree::OnTreeSelectionChanged( wxTreeEvent& event )
{
}

void SceneTree::OnItemActivated( wxTreeEvent& event ) // Double-Click event
{
	// Set Focus here?
	wxString test = ToWxString("DEBUG");
}

