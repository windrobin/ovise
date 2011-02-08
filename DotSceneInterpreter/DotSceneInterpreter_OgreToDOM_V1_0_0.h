/********************************************************************************
* Name:      DotSceneInterpreter_OgreToDOM_V1_0_0.h							*
* Purpose:   This interpreter inherits from abstract class						*
*			  DotSceneInterpreter_OgreToDOM. It redefines all abstract methods  *
*			  of its partent, according to the (modified and repaired)			*
*			  dotScene1.0.0 standard.											*
* Author:    Henning Renartz (renartz dot henning at student dot kit dot edu )	*
* Created:   2009-11-16														*
* Copyright: Henning Renartz,													*
*			  Alexander Kasper (http://i61www.ira.uka.de/users/akasper)			*
* License:																		*
********************************************************************************/

#pragma once

#ifndef DOTSCENE_INTERPRETER_OGRE_TO_DOM_V1_0_0_H_
#define DOTSCENE_INTERPRETER_OGRE_TO_DOM_V1_0_0_H_

// Solution's includes
#include "../OViSEdotSceneBase/DotSceneInterpreter_OgreToDOM.h"

class DotSceneInterpreter_OgreToDOM_V1_0_0 : public
	DotSceneInterpreter_OgreToDOM
{
private:
	// Inherited methods
	virtual void SetVersionString( wxString VersionString );

	// virtual void Interpretation_Externals(xercesc::DOMElement* DOMElement_externals, wxString UniqueNameOfScene);
	// virtual void Interpretation_Environment(xercesc::DOMElement* DOMElement_environment);
	virtual xercesc::DOMElement* Interpretation_Node(
	        Ogre::SceneNode* actualSceneNode );
	virtual xercesc::DOMElement* Interpretation_Camera(
	        Ogre::Camera* actualCamera );
	virtual xercesc::DOMElement* Interpretation_Entity(
	        Ogre::Entity* actualEntity );
	virtual xercesc::DOMElement* Interpretation_Light(
	        Ogre::Light* actualLight );
	virtual xercesc::DOMElement* Interpretation_Position(
	        Ogre::Vector3 NodePosition );
	virtual xercesc::DOMElement* Interpretation_Quaternion(
	        Ogre::Quaternion NodeQuaternion );
	virtual xercesc::DOMElement* Interpretation_Scale(
	        Ogre::Vector3 NodeScale );
	virtual xercesc::DOMElement* Interpretation_DiffuseColour(
	        Ogre::ColourValue DiffuseColour );
	virtual xercesc::DOMElement* Interpretation_SpecularColour(
	        Ogre::ColourValue SpecularColour );

public:
	DotSceneInterpreter_OgreToDOM_V1_0_0( void );
	~DotSceneInterpreter_OgreToDOM_V1_0_0( void );

	// Static methods
	static bool IsValidFormatVersion( wxString VersionStringForExport ); // Returns "true" for "1.0.0"

	// Inherited methods
	/*virtual ScenePrototype* Interpretation(	wxString NotUniquePrototypeName,
	                                                                                QualifiedNameCollection Selection,
	                                                                                DotSceneBaseConfiguration* Configuration);*/
};

#endif /*DOTSCENE_INTERPRETER_OGRE_TO_DOM_V1_0_0_H_*/
