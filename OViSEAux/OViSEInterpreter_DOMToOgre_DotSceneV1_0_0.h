#ifndef OVISE_INTERPRETER_DOM_TO_OGRE_DOTSCENE_V1_0_0_H_
#define OVISE_INTERPRETER_DOM_TO_OGRE_DOTSCENE_V1_0_0_H_

// Solution's includes
#ifndef OVISE_INTERPRETER_DOM_TO_OGRE_DOTSCENE_ABSTRACT_USED
#define OVISE_INTERPRETER_DOM_TO_OGRE_DOTSCENE_ABSTRACT_USED
#include "OViSEInterpreter_DOMToOgre_DotSceneAbstract.h"
#endif

// Special defines for debugging or mode-activations
#define __ALLOW_INTERPRETATION_ASSUMPTIONS__

class OViSEInterpreter_DOMToOgre_DotSceneV1_0_0 : public OViSEInterpreter_DOMToOgre_DotSceneAbstract
{
	// IMPORTANT: This class and it's children are not thread-safe! (Because of XML-stuff)
private:
	// Inherited methods
	virtual void Interpretation_Externals(xercesc::DOMElement* DOMElement_externals, wxString UniqueNameOfScene);
	virtual void Interpretation_Nodes(xercesc::DOMElement* DOMElement_nodes);
	virtual void Interpretation_Node(xercesc::DOMElement* DOMElement_node, Ogre::SceneNode* ParentNode);
	virtual void Interpretation_Entity(xercesc::DOMElement* DOMElement_entity, Ogre::SceneNode* AssociateNode);
	virtual void Interpretation_Camera(xercesc::DOMElement* DOMElement_camera);
	virtual void Interpretation_Environment(xercesc::DOMElement* DOMElement_environment);
	virtual Ogre::Vector3 Interpretation_Vector3(xercesc::DOMElement* DOMElement_Vector3);
	virtual Ogre::Vector4 Interpretation_Vector4(xercesc::DOMElement* DOMElement_Vector4);
	virtual Ogre::Quaternion Interpretation_Quaternion(xercesc::DOMElement* DOMElement_Quaternion);

public:
	// De- & Constructors
	OViSEInterpreter_DOMToOgre_DotSceneV1_0_0();
	~OViSEInterpreter_DOMToOgre_DotSceneV1_0_0();

	// Static methods
	static bool IsValidFormatVersion(xercesc::DOMDocument* DOMRepresentationOfScene); // Returns "true" for "1.0.0"

	// Inherited methods
	virtual bool Interpretation(xercesc::DOMDocument* DOMRepresentationOfScene,
								wxString AnchorNodeName,
								OViSEDotSceneManagerConfiguration* Configuration);
};

#endif // OVISE_INTERPRETER_DOM_TO_OGRE_DOTSCENE_V1_0_0_H_