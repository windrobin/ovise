#ifndef OVISE_INTERPRETER_OGRE_TO_DOM_DOTSCENE_V1_0_0_H_
#define OVISE_INTERPRETER_OGRE_TO_DOM_DOTSCENE_V1_0_0_H_

// Solution's includes
#ifndef OVISE_INTERPRETER_OGRE_TO_DOM_DOTSCENE_ABSTRACT_USED
#define OVISE_INTERPRETER_OGRE_TO_DOM_DOTSCENE_ABSTRACT_USED
#include "OViSEInterpreter_OgreToDOM_DotSceneAbstract.h"
#endif

class OViSEInterpreter_OgreToDOM_DotSceneV1_0_0 : public OViSEInterpreter_OgreToDOM_DotSceneAbstract
{
private:
	// Inherited methods

	virtual void SetVersionString(wxString VersionString);

	//virtual void Interpretation_Externals(xercesc::DOMElement* DOMElement_externals, wxString UniqueNameOfScene);
	//virtual void Interpretation_Environment(xercesc::DOMElement* DOMElement_environment);
	virtual xercesc::DOMElement* Interpretation_Node(Ogre::SceneNode* actualSceneNode);
	virtual xercesc::DOMElement* Interpretation_Camera(Ogre::Camera* actualCamera);
	virtual xercesc::DOMElement* Interpretation_Entity(Ogre::Entity* actualEntity);
	virtual xercesc::DOMElement* Interpretation_Light(Ogre::Light* actualLight);
	virtual xercesc::DOMElement* Interpretation_Position(Ogre::Vector3 NodePosition);
	virtual xercesc::DOMElement* Interpretation_Quaternion(Ogre::Quaternion NodeQuaternion);
	virtual xercesc::DOMElement* Interpretation_Scale(Ogre::Vector3 NodeScale);
	virtual xercesc::DOMElement* Interpretation_DiffuseColour(Ogre::ColourValue DiffuseColour);
	virtual xercesc::DOMElement* Interpretation_SpecularColour(Ogre::ColourValue SpecularColour);

public:
	OViSEInterpreter_OgreToDOM_DotSceneV1_0_0(void);
	~OViSEInterpreter_OgreToDOM_DotSceneV1_0_0(void);

	// Static methods
	static bool IsValidFormatVersion(wxString VersionStringForExport); // Returns "true" for "1.0.0"

	// Inherited methods
	virtual OViSEScenePrototype* Interpretation(	wxString NotUniquePrototypeName,
													OViSESelectionMap Selection,
													OViSEDotSceneManagerConfiguration* Configuration);
};

#endif /*OVISE_INTERPRETER_OGRE_TO_DOM_DOTSCENE_V1_0_0_H_*/