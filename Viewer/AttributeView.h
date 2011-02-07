
#ifndef ATTRIBUTE_VIEW_H
#define ATTRIBUTE_VIEW_H

#include "../Core/Entity.h"

#include <wx/setup.h>
#include <wx/propgrid/propgrid.h>

/** View for the attributes in an entity.
        Uses a property grid.
 */
class AttributeView :
	public EntityObserver
{
public:
	AttributeView( wxWindow* Parent );
	~AttributeView();

	wxPropertyGrid*                 GetGrid();

	void                                    SetEntity( Entity* Rhs );

	virtual void                    OnPropertyChange(
	        wxPropertyGridEvent& Rhs );
protected:
	// Implements the EntityObserver interface
	virtual void                    OnEntityAttributeChanged(
	        Entity*            Rhs,
	        const std::string& Name,
	        const
	        EntityVariantType* Attribute );

	virtual void                    ShowAttribs();

private:
	wxPropertyGrid* mObjectProperties;
	Entity*         mCurrentEntity;
};

#endif
