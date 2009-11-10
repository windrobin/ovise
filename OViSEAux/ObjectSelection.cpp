#include "ObjectSelection.h"

ObjectSelection::ObjectSelection() { this->SetSceneManager(OgreAPIMediator::GetSingletonPtr()->GetActiveSceneManager()); }
ObjectSelection::ObjectSelection(QualifiedName qSceneManager) { this->SetSceneManager(qSceneManager); }
ObjectSelection::~ObjectSelection(void) { this->removeAll(); }
bool ObjectSelection::IsValid() { return this->Valid; }
//void ObjectSelection::setUniqueName(wxString UniqueName) { this->UniqueName = UniqueName; }
//wxString ObjectSelection::getUniqueName() { return this->UniqueName; }
bool ObjectSelection::HasMovableObject(QualifiedName qMovableObject)
{
	if (!this->IsValid()) return false;
	if (this->SelectedObjects.count(qMovableObject.UniqueName()) == 1) return true;
	else return false;
}
bool ObjectSelection::AddMovableObject(QualifiedName qMovableObject)
{
	if (!this->IsValid()) return false;
	if (!qMovableObject.IsValid()) return false;
	if (this->HasMovableObject(qMovableObject)) return false;
	this->SelectedObjects[MovableObjectName] = MovableObjectType;
	return true;
}
bool ObjectSelection::removeMovableObject(wxString MovableObjectName)
{
	if (this->SelectedObjects.count(MovableObjectName) == 0) return false;
	this->SelectedObjects.erase(MovableObjectName);
	return true;
}
void ObjectSelection::removeAll() { this->SelectedObjects.clear(); }
wxArrayString ObjectSelection::getAllMovableObjectNames()
{
	wxArrayString AllStringKeys;
	OgreEnums::MovableTypeByStringHashMap::iterator IT;
    for( IT = SelectedObjects.begin(); IT != SelectedObjects.end(); ++IT )
    {
        wxString StringKey = IT->first;
		AllStringKeys.Add(StringKey);
    }
	return AllStringKeys;
}
QualifiedName ObjectSelection::GetSceneManager() { return this->mSceneManager; }
void ObjectSelection::SetSceneManager(QualifiedName qSceneManager)
{
	if (qSceneManager.IsValid())
	{
		this->mSceneManager = qSceneManager;
		this->Valid = true;
	}
	else this->Valid = false;
}
