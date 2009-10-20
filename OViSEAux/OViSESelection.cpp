#include "OViSESelection.h"

OViSESelection::OViSESelection()
{
	wxArrayString AS = OgreAPIMediator::GetSingletonPtr()->getSceneManagerNames();
	if (AS.empty()) this->setSceneManagerName(wxString());
	else this->setSceneManagerName(AS[0]);
	this->Valid = false;
}
OViSESelection::OViSESelection(wxString SceneManagerName)
{
	this->UniqueName = ToWxString("INVALID");
	this->setSceneManagerName(SceneManagerName);
	this->Valid = true;
}
OViSESelection::~OViSESelection(void) { this->removeAll(); }
bool OViSESelection::isValid() { return this->Valid; }
void OViSESelection::setUniqueName(wxString UniqueName) { this->UniqueName = UniqueName; }
wxString OViSESelection::getUniqueName() { return this->UniqueName; }
bool OViSESelection::hasMovableObject(wxString MovableObjectName)
{
	if (!this->isValid()) return false;
	if (this->SelectedObjects.count(MovableObjectName) == 1) return true;
	else return false;
}
bool OViSESelection::addMovableObject(wxString MovableObjectName, OViSEOgreEnums::MovableObject::MovableType MovableObjectType)
{
	if (!this->isValid())
	{
		return false;
	}
	if (this->hasMovableObject(MovableObjectName))
	{
		return false;
	}
	if (!OgreAPIMediator::GetSingletonPtr()->hasMovableObject(this->getSceneManagerName(), MovableObjectName, MovableObjectType))
	{
		return false;
	}
	
	this->SelectedObjects[MovableObjectName] = MovableObjectType;
	return true;
}
bool OViSESelection::removeMovableObject(wxString MovableObjectName)
{
	if (this->SelectedObjects.count(MovableObjectName) == 0) return false;
	this->SelectedObjects.erase(MovableObjectName);
	return true;
}
void OViSESelection::removeAll() { this->SelectedObjects.clear(); }
wxArrayString OViSESelection::getAllMovableObjectNames()
{
	wxArrayString AllStringKeys;
	OViSEOgreEnums::HashMap_Enums_MovableType_ByString::iterator IT;
    for( IT = SelectedObjects.begin(); IT != SelectedObjects.end(); ++IT )
    {
        wxString StringKey = IT->first;
		AllStringKeys.Add(StringKey);
    }
	return AllStringKeys;
}
wxString OViSESelection::getSceneManagerName() { return this->SceneManagerName; }
void OViSESelection::setSceneManagerName(wxString SceneManagerName) { this->SceneManagerName = SceneManagerName; this->Valid = true; }
