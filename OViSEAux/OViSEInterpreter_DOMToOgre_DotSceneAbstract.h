#ifndef OVISE_INTERPRETER_DOM_TO_OGRE_DOTSCENE_ABSTRACT_H_
#define OVISE_INTERPRETER_DOM_TO_OGRE_DOTSCENE_ABSTRACT_H_

// Solution's includes
#ifndef OVISE_UNIQUENAME_GENERATOR_USED
#define OVISE_UNIQUENAME_GENERATOR_USED
#include "../OViSE/OViSEUniqueNameGenerator.h"
#endif

#ifndef OVISE_STRINGCONVERTER_USED
#define OVISE_STRINGCONVERTER_USED
#include "../OViSE/OViSEStringConverter.h"
#endif

#ifndef OVISE_DOTSCENE_MANAGER_CONFIGURATION_USED
#define OVISE_DOTSCENE_MANAGER_CONFIGURATION_USED
#include "./OViSEDotSceneManagerConfiguration.h"
#endif

#ifndef OVISE_SCENENODE_OFFSET_USED
#define OVISE_SCENENODE_OFFSET_USED
#include "./OViSESceneNodeOffset.h"
#endif

#ifndef OVISE_LOGGING_USED
#define OVISE_LOGGING_USED
#include "../OViSE/OViSELogging.h"
#endif

// Include Ogre
#ifndef Ogre_h_
#define Ogre_h_
#include "Ogre.h"
#endif

// Include Xerces
#ifndef XERCESC_UTIL_XMLSTRING_USED
#define XERCESC_UTIL_XMLSTRING_USED
#include <xercesc/util/XMLString.hpp>
#endif

#ifndef XERCESC_SAX_HANDLERBASE_USED
#define XERCESC_SAX_HANDLERBASE_USED
#include <xercesc/sax/HandlerBase.hpp>
#endif

#ifndef XERCES_PARSERS_XERCESDOMPARSER_USED
#define XERCES_PARSERS_XERCESDOMPARSER_USED
#include <xercesc/parsers/XercesDOMParser.hpp>
#endif

#ifndef XERCES_DOM_DOM_USED
#define XERCES_DOM_DOM_USED
#include <xercesc/dom/DOM.hpp>
#endif

#ifndef XERCES_UTIL_XMLFLOAT_USED
#define XERCES_UTIL_XMLFLOAT_USED
#include <xercesc/util/XMLFloat.hpp>
#endif

#ifndef XERCES_CPP_NAMESPACE_USE_USED
#define XERCES_CPP_NAMESPACE_USE_USED
XERCES_CPP_NAMESPACE_USE
#endif

// Include WX
#ifndef WX_STRING_USED
#define WX_STRING_USED
#include <wx/string.h>
#endif

#ifndef WX_FILENAME_USED
#define WX_FILENAME_USED
#include <wx/filename.h>
#endif

class OViSEInterpreter_DOMToOgre_DotSceneAbstract
{
	// IMPORTANT: This class and it's children are not thread-safe! (Because of XML-stuff)
private:
	// All abstract methods
	virtual void Interpretation_Externals(xercesc::DOMElement* DOMElement_externals, wxString UniqueNameOfScene) = 0;
	virtual void Interpretation_Nodes(xercesc::DOMElement* DOMElement_nodes) = 0;
	virtual void Interpretation_Node(xercesc::DOMElement* DOMElement_node, Ogre::SceneNode* ParentNode) = 0;
	virtual void Interpretation_Entity(xercesc::DOMElement* DOMElement_entity, Ogre::SceneNode* AssociateNode) = 0;
	virtual void Interpretation_Camera(xercesc::DOMElement* DOMElement_camera) = 0;
	virtual void Interpretation_Environment(xercesc::DOMElement* DOMElement_environment) = 0;
	virtual Ogre::Vector3 Interpretation_Vector3(xercesc::DOMElement* DOMElement_Vector3) = 0;
	virtual Ogre::Vector4 Interpretation_Vector4(xercesc::DOMElement* DOMElement_Vector4) = 0;
	virtual Ogre::Quaternion Interpretation_Quaternion(xercesc::DOMElement* DOMElement_Quaternion) = 0;

protected:
	// Attributes
	Ogre::SceneNode* AnchorNode;
	OViSEDotSceneManagerConfiguration* Configuration;
	wxString VersionString;

	virtual void SetVersionString(wxString VersionString);

	// Methods
	Ogre::SceneNode* AttachSceneNode(	wxString NotUniqueName,
										Ogre::Vector3 Translation_Relative,
										Ogre::Vector3 Scale_Relative,
										Ogre::Quaternion Rotation_Relative,
										Ogre::SceneNode* ParentNode);
	Ogre::Entity* AttachEntity(	wxString NotUniqueEntityName,
								wxString MeshFile,
								Ogre::SceneNode* AttachToThisNode);
	bool Interpretation_DOMScene(	xercesc::DOMDocument* DOMRepresentationOfScene,
									wxString AttachToNodeWithThisName,
									OViSEDotSceneManagerConfiguration* Configuration);

	// Static methods
	
public:
	// De- & Constructors
	~OViSEInterpreter_DOMToOgre_DotSceneAbstract(void);

	// Static methods
	static wxString GetVersionString( xercesc::DOMDocument *DOMRepresentationOfScene );

	// Inheritable methods
	virtual bool Interpretation(xercesc::DOMDocument* DOMRepresentationOfScene,
								wxString AnchorNodeName,
								OViSEDotSceneManagerConfiguration* Configuration) = 0;
};

#endif // OVISE_INTERPRETER_DOM_TO_OGRE_DOTSCENE_ABSTRACT_H_
