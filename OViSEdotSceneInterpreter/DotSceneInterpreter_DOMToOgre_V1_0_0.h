/********************************************************************************
 * Name:      DotSceneInterpreter_DOMToOgre_V1_0_0.h							*
 * Purpose:   This interpreter inherits from abstract class						*
 *			  DotSceneInterpreter_DOMToOgre. It redefines all abstract methods  *
 *			  of its partent, according to the (modified and repaired)			*
 *			  dotScene1.0.0 standard.											*
 * Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
 * Created:   2009-11-16														*
 * Copyright: Henning Renartz,													*
 *			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
 * License:																		*
 ********************************************************************************/

#pragma once

#ifndef DOTSCENE_INTERPRETER_DOM_TO_OGRE_V1_0_0_H_
#define DOTSCENE_INTERPRETER_DOM_TO_OGRE_V1_0_0_H_

// Solution's includes
#include "../OViSEdotSceneBase/DotSceneInterpreter_DOMToOgre.h"

// Special defines for debugging or mode-activations
#define __ALLOW_INTERPRETATION_ASSUMPTIONS__

class DotSceneInterpreter_DOMToOgre_V1_0_0 : public DotSceneInterpreter_DOMToOgre
{
	// IMPORTANT: This class and it's children are not thread-safe! (Because of XML-stuff)
private:
	// Inherited methods
	virtual void Interpretation_Externals(xercesc::DOMElement* DOMElement_externals, QualifiedName qResourceGroup);
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
	DotSceneInterpreter_DOMToOgre_V1_0_0();
	~DotSceneInterpreter_DOMToOgre_V1_0_0();

	// Static methods
	static bool IsValidFormatVersion(xercesc::DOMDocument* DOMRepresentationOfScene); // Returns "true" for "1.0.0"

	// Inherited methods
	virtual bool Interpretation(xercesc::DOMDocument* DOMRepresentationOfScene,
								QualifiedName qAnchorNodeName,
								DotSceneBaseConfiguration* Configuration);
};

#endif // DOTSCENE_INTERPRETER_DOM_TO_OGRE_V1_0_0_H_