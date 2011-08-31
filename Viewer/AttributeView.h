
#ifndef ATTRIBUTE_VIEW_H
#define ATTRIBUTE_VIEW_H

#include "../Core/EntityPool.h"

#include <wx/setup.h>
#include <wx/propgrid/propgrid.h>

/** 
  View for the attributes in an entity.
  Uses a property grid.
*/
class AttributeView :
	public EntityObserver, public EntityPoolObserver
{
public:
	AttributeView( wxWindow* Parent );
	~AttributeView();

	wxPropertyGrid* GetGrid();

	/// Set the entity to display.
	void SetEntity( Entity* Rhs );

	/// Handler for reacting to property changes
	virtual void OnPropertyChange( wxPropertyGridEvent& Rhs );

	/// Handler for insertion of an entity.
	virtual void OnEntityInsert( Entity* Object, std::size_t Index ) {}
	/// Handler for removal of an entity.
	virtual void OnEntityRemove( Entity* Object, std::size_t Index );

protected:
	// Implements the EntityObserver interface
	virtual void OnEntityAttributeChanged( Entity* Rhs, 
		const std::string& Name, const EntityVariantType* Attribute );

	virtual void ShowAttribs();

private:
	wxPropertyGrid* mObjectProperties;
	Entity*         mCurrentEntity;
};

#endif
