#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneNodes_h_
#define dotSceneNodes_h_
#include "dotSceneNodes.h"
#endif

#ifndef dotSceneExternals_h_
#define dotSceneExternals_h_
#include "dotSceneExternals.h"
#endif

#ifndef dotSceneEnvironment_h_
#define dotSceneEnvironment_h_
#include "dotSceneEnvironment.h"
#endif

#pragma once

namespace dotSceneObjects
{
	/**
	 * Class dotScene contains all data, which is need for construction an entire scene.
	 * This class is made to contain a complete description of a dotScene-XML.
	 * dotScene-Version 1.0.0 is used. All classes of the dotSceneObjects-concept are
	 * planned as passive classes. So a XML-reader-class should fill the structure and
	 * a factory should interprete a dotScene-class like a blueprint.
	 */
	class dotScene : public dotSceneObjects::dotSceneObject
	{
	private:
		std::string _formatVersion;			/**< Property formatVersion. Version of dotScene.dtd (dotScene.xsd), used for the contained scene.*/
		dotSceneNodes _nodes;				/**< Property nodes. Contais all nodes of the scene. Including entities, cameras and lights.*/
		dotSceneExternals _externals;		/**< Property externals. Contains all externals, referencing files. For example material-files.*/
		dotSceneEnvironment _environment;	/**< Property environment. Contains information about configuration of environment, like fog, ambient light and so on.*/

		void set_formatVersion(std::string value);		/**< Set-method for property formatVersion. @param value Value of string.*/
		void set_nodes(dotSceneNodes value);			/**< Set-method for property nodes. @param value A dotSceneNodes-object.*/
		void set_externals(dotSceneExternals value);	/**< Set-method for property externals. @param value A dotSceneExternals-object.*/
		void set_environment(dotSceneEnvironment value);/**< Set-method for property environment. @param value A dotSceneEnvironment-object.*/

	public:
		std::string get_formatVersion() const;		/**< Get-method for property formatVersion. @return Returns formatVersion as std::string.*/
		dotSceneNodes get_nodes() const;			/**< Get-method for property nodes. @return Returns a dotSceneNodes-object.*/
		dotSceneExternals get_externals() const;	/**< Get-method for property externals. @return Returns a dotSceneExternals-object.*/
		dotSceneEnvironment get_environment() const;/**< Get-method for property environment. @return Returns a dotSceneEnvironment-object.*/

        /**
		 * Simple constructor.
		 * It calls the constructor of base-object.
		 */
		dotScene();

		/**
		 * Standard-constructor for a dotScene-Object.
		 * The dotScene-objects have to be constructed before.
		 * @param str_formatVersion This string-parameter defines the Version of the dotScene XML-document. For example this Assembly is written for formatVersion "1.0.0".
		 * @param obj_nodes A pre-constrcted dotSceneNodes-object. It contains all dotSceneNode-objects.
		 * @param obj_externals A pre-constrcted dotSceneExternals-object. It contains file-references like ".material".
		 * @param obj_environment A pre-constrcted dotSceneEnvironment-object. It contains the general scene-setting.
		 */
		dotScene(std::string str_formatVersion, dotSceneNodes obj_nodes,  dotSceneExternals obj_externals, dotSceneEnvironment obj_environment); 
        
		/**
		 * Simple destructor.
		 */
		~dotScene();
    };
}
