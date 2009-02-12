#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneColourDiffuse_h_
#define dotSceneColourDiffuse_h_
#include "dotSceneColourDiffuse.h"
#endif

#ifndef dotSceneShadowTextureConfig_h_
#define dotSceneShadowTextureConfig_h_
#include "dotSceneShadowTextureConfig.h"
#endif

#ifndef dotSceneGeneralEnums_h_
#define dotSceneGeneralEnums_h_
#include "dotSceneGeneralEnums.h"
#endif

#ifndef list_h_
#define list_h_
#include <list>
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;
	using namespace dotSceneEnums::dotSceneShadowConfigEnums;

	/**
	 * This class hold values for all objects, which can occure in node-definition.
	 */
	class dotSceneShadowSettings : virtual public dotSceneObject
    {
	private:
		ShadowTechnique _ShadowTechnique;				/**< Property ShadowTechnique. Untested. Context unknown.*/
		bool			_ShowDebugShadows;				/**< Property ShowDebugShadows. Untested. Context unknown.*/
		double			_ShadowFarDistance;				/**< Property ShadowFarDistance. Untested. Context unknown.*/
		double			_ShadowDirectionalLightExtrusionDistance;	/**< Property ShadowDirectionalLightExtrusionDistance. Untested. Context unknown.*/
		int				_ShadowIndexBufferSize;			/**< Property ShadowIndexBufferSize. Untested. Context unknown.*/
		bool			_ShadowUseInfiniteFarPlane;		/**< Property ShadowUseInfiniteFarPlane. Untested. Context unknown.*/
		int				_ShadowTextureCount;			/**< Property ShadowTextureCount. Untested. Context unknown.*/
		int				_ShadowTextureSize;				/**< Property ShadowTextureSize. Untested. Context unknown.*/
		PixelFormat		_ShadowTexturePixelFormat;		/**< Property ShadowTexturePixelFormat. Untested. Context unknown.*/
		double			_ShadowDirLightTextureOffset;	/**< Property ShadowDirLightTextureOffset. Untested. Context unknown.*/
		double			_ShadowTextureFadeStart;		/**< Property ShadowTextureFadeStart. Untested. Context unknown.*/
		double			_ShadowTextureFadeEnd;			/**< Property ShadowTextureFadeEnd. Untested. Context unknown.*/
		bool			_ShadowTextureSelfShadow;		/**< Property ShadowTextureSelfShadow. Untested. Context unknown.*/
		std::string		_ShadowTextureCasterMaterial;	/**< Property ShadowTextureCasterMaterial. Untested. Context unknown.*/
		std::string		_ShadowTextureReceiverMaterial;	/**< Property ShadowTextureReceiverMaterial. Untested. Context unknown.*/
		bool			_ShadowCasterRenderBackFaces;	/**< Property ShadowCasterRenderBackFaces. Untested. Context unknown.*/

		dotSceneColourDiffuse _ColourDiffuse;			/**< Property ColourDiffuse. Untested. Context unknown.*/

	public:
		std::list<dotSceneShadowTextureConfig> _ListOfShadowTextureConfig;	/**< Property ListOfShadowTextureConfig.*/

		ShadowTechnique get_ShadowTechnique() const;				/**< Get-method for property ShadowTechnique. @return Returns ShadowTechnique as value of "dotSceneEnums::dotSceneShadowConfigEnums::ShadowTechnique"-enum.*/
		bool			get_ShowDebugShadows() const;				/**< Get-method for property ShowDebugShadows. @return Returns ShowDebugShadows as bool.*/
		double			get_ShadowFarDistance() const;				/**< Get-method for property ShadowFarDistance. @return Returns ShadowFarDistance as double.*/
		double			get_ShadowDirectionalLightExtrusionDistance() const;/**< Get-method for property ShadowIndexBufferSize. @return Returns ShadowIndexBufferSize as double.*/
		int				get_ShadowIndexBufferSize() const;			/**< Get-method for property ShadowIndexBufferSize. @return Returns ShadowIndexBufferSize as integer.*/
		bool			get_ShadowUseInfiniteFarPlane() const;		/**< Get-method for property ShadowUseInfiniteFarPlane. @return Returns ShadowUseInfiniteFarPlane as bool.*/
		int				get_ShadowTextureCount() const;				/**< Get-method for property ShadowTextureCount. @return Returns ShadowTextureCount as integer.*/
		int				get_ShadowTextureSize() const;				/**< Get-method for property ShadowTextureSize. @return Returns ShadowTextureSize as integer.*/
		PixelFormat		get_ShadowTexturePixelFormat() const;		/**< Get-method for property ShadowTexturePixelFormat. @return Returns ShadowTexturePixelFormat as value of "dotSceneEnums::dotSceneShadowConfigEnums::PixelFormat"-enum.*/
		double			get_ShadowDirLightTextureOffset() const;	/**< Get-method for property ShadowDirLightTextureOffset. @return Returns ShadowDirLightTextureOffset as double.*/
		double			get_ShadowTextureFadeStart() const;			/**< Get-method for property ShadowTextureFadeStart. @return Returns ShadowTextureFadeStart as double.*/
		double			get_ShadowTextureFadeEnd() const;			/**< Get-method for property ShadowTextureFadeEnd. @return Returns ShadowTextureFadeEnd as double.*/
		bool			get_ShadowTextureSelfShadow() const;		/**< Get-method for property ShadowTextureSelfShadow. @return Returns ShadowTextureSelfShadow as integer.*/
		std::string		get_ShadowTextureCasterMaterial() const;	/**< Get-method for property ShadowTextureCasterMaterial. @return Returns ShadowTextureCasterMaterial as std::string.*/
		std::string		get_ShadowTextureReceiverMaterial() const;	/**< Get-method for property ShadowTextureReceiverMaterial. @return Returns ShadowTextureReceiverMaterial as std::string.*/
		bool			get_ShadowCasterRenderBackFaces() const;	/**< Get-method for property ShadowCasterRenderBackFaces. @return Returns ShadowCasterRenderBackFaces as bool.*/

		dotSceneColourDiffuse get_ColourDiffuse() const;			/**< Get-method for property ColourDiffuse. @return Returns a "dotSceneColourDiffuse"-object.*/

		void set_ShadowTechnique(ShadowTechnique value);			/**< Set-method for property ShadowTechnique. @param value Value of "dotSceneEnums::dotSceneShadowConfigEnums::ShadowTechnique"-enum.*/
		void set_ShowDebugShadows(bool value);						/**< Set-method for property ShowDebugShadows. @param value Value of a bool.*/
		void set_ShadowFarDistance(double value);					/**< Set-method for property ShadowFarDistance. @param value Value of a double.*/
		void set_ShadowDirectionalLightExtrusionDistance(double value);	/**< Set-method for property ShadowIndexBufferSize. @param value Value of a double.*/
		void set_ShadowIndexBufferSize(int value);					/**< Set-method for property ShadowIndexBufferSize. @param value Value of a integer.*/
		void set_ShadowUseInfiniteFarPlane(bool value);				/**< Set-method for property ShadowUseInfiniteFarPlane. @param value Value of a bool.*/
		void set_ShadowTextureCount(int value);						/**< Set-method for property ShadowTextureCount. @param value Value of a integer.*/
		void set_ShadowTextureSize(int value);						/**< Set-method for property ShadowTextureSize. @param value Value of a integer.*/
		void set_ShadowTexturePixelFormat(PixelFormat value);		/**< Set-method for property ShadowTexturePixelFormat. @param value Value of "dotSceneEnums::dotSceneShadowConfigEnums::PixelFormat"-enum.*/
		void set_ShadowDirLightTextureOffset(double value);			/**< Set-method for property ShadowDirLightTextureOffset. @param value Value of a double.*/
		void set_ShadowTextureFadeStart(double value);				/**< Set-method for property ShadowTextureFadeStart. @param value Value of a double.*/
		void set_ShadowTextureFadeEnd(double value);				/**< Set-method for property ShadowTextureFadeEnd. @param value Value of a double.*/
		void set_ShadowTextureSelfShadow(bool value);				/**< Set-method for property ShadowTextureSelfShadow. @param value Value of a bool.*/
		void set_ShadowTextureCasterMaterial(std::string value);	/**< Set-method for property ShadowTextureCasterMaterial. @param value Value of a std::string.*/
		void set_ShadowTextureReceiverMaterial(std::string value);	/**< Set-method for property ShadowTextureReceiverMaterial. @param value Value of a std::string.*/
		void set_ShadowCasterRenderBackFaces(bool value);			/**< Set-method for property ShadowCasterRenderBackFaces. @param value Value of a bool.*/
	
		void set_ColourDiffuse(dotSceneColourDiffuse value);		/**< Set-method for property ColourDiffuse. @param value A "dotSceneColourDiffuse"-object.*/

		void set_ShadowTechnique(std::string value);				/**< Set-method for property ShadowTechnique. @param value Value of std::string.*/
		void set_ShowDebugShadows(std::string value);				/**< Set-method for property ShowDebugShadows. @param value Value of std::string.*/
		void set_ShadowFarDistance(std::string value);				/**< Set-method for property ShadowFarDistance. @param value Value of std::string.*/
		void set_ShadowDirectionalLightExtrusionDistance(std::string value);	/**< Set-method for property ShadowIndexBufferSize. @param value Value of std::string.*/
		void set_ShadowIndexBufferSize(std::string value);			/**< Set-method for property ShadowIndexBufferSize. @param value Value of std::string.*/
		void set_ShadowUseInfiniteFarPlane(std::string value);		/**< Set-method for property ShadowUseInfiniteFarPlane. @param value Value of std::string.*/
		void set_ShadowTextureCount(std::string value);				/**< Set-method for property ShadowTextureCount. @param value Value of std::string.*/
		void set_ShadowTextureSize(std::string value);				/**< Set-method for property ShadowTextureSize. @param value Value of std::string.*/
		void set_ShadowTexturePixelFormat(std::string value);		/**< Set-method for property ShadowTexturePixelFormat. @param value Value of std::string.*/
		void set_ShadowDirLightTextureOffset(std::string value);	/**< Set-method for property ShadowDirLightTextureOffset. @param value Value of std::string.*/
		void set_ShadowTextureFadeStart(std::string value);			/**< Set-method for property ShadowTextureFadeStart. @param value Value of std::string.*/
		void set_ShadowTextureFadeEnd(std::string value);			/**< Set-method for property ShadowTextureFadeEnd. @param value Value of std::string.*/
		void set_ShadowTextureSelfShadow(std::string value);		/**< Set-method for property ShadowTextureSelfShadow. @param value Value of std::string.*/
		void set_ShadowCasterRenderBackFaces(std::string value);	/**< Set-method for property ShadowCasterRenderBackFaces. @param value Value of std::string.*/

		bool IsValid() const;	/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/
		
		/**
		 * This method adds a new dotSceneShadowTextureConfig to list "ListOfShadowTextureConfig".
		 * @param someShadowTextureConfig A "dotSceneShadowTextureConfig"-object.
		 * @return Returns a bool value. TRUE, when no problem occured.
		 */
		bool addShadowTextureConfig(dotSceneShadowTextureConfig someShadowTextureConfig);

        /**
		 * Simple Constructor.
		 */
		dotSceneShadowSettings();

		/**
		 * Full initialisation constructor of dotSceneShadowSettings.
		 * All std::string-values will be parsed automatically.
	 	 * @param str_ShadowTechnique Untested. Context unknown.
		 * @param str_ShowDebugShadows Untested. Context unknown.
		 * @param str_ShadowFarDistance Untested. Context unknown.
		 * @param str_ShadowDirectionalLightExtrusionDistance Untested. Context unknown.
		 * @param str_ShadowIndexBufferSize Untested. Context unknown.
		 * @param str_ShadowUseInfiniteFarPlane Untested. Context unknown.
		 * @param str_ShadowTextureCount Untested. Context unknown.
		 * @param str_ShadowTextureSize Untested. Context unknown.
		 * @param str_ShadowTexturePixelFormat Untested. Context unknown.
		 * @param str_ShadowDirLightTextureOffset Untested. Context unknown.
		 * @param str_ShadowTextureFadeStart Untested. Context unknown.
		 * @param str_ShadowTextureFadeEnd Untested. Context unknown.
		 * @param str_ShadowTextureSelfShadow Untested. Context unknown.
		 * @param str_ShadowTextureCasterMaterial Untested. Context unknown.
		 * @param str_ShadowTextureReceiverMaterial Untested. Context unknown.
		 * @param str_ShadowCasterRenderBackFaces Untested. Context unknown.
		 * @param dotSceneColourDiffuse obj_ColourDiffuse A pre-constructed "dotSceneColourDiffuse"-object. Context unknown.
		 */
		dotSceneShadowSettings(
			std::string str_ShadowTechnique,
			std::string str_ShowDebugShadows,
			std::string str_ShadowFarDistance,
			std::string str_ShadowDirectionalLightExtrusionDistance,
			std::string	str_ShadowIndexBufferSize,
			std::string str_ShadowUseInfiniteFarPlane,
			std::string	str_ShadowTextureCount,
			std::string	str_ShadowTextureSize,
			std::string str_ShadowTexturePixelFormat,
			std::string str_ShadowDirLightTextureOffset,
			std::string str_ShadowTextureFadeStart,
			std::string str_ShadowTextureFadeEnd,
			std::string str_ShadowTextureSelfShadow,
			std::string	str_ShadowTextureCasterMaterial,
			std::string	str_ShadowTextureReceiverMaterial,
			std::string str_ShadowCasterRenderBackFaces,
			dotSceneColourDiffuse obj_ColourDiffuse);

		/**
		 * Full initialisation constructor of dotSceneShadowSettings.
		 * @param enum_ShadowTechnique Untested. Context unknown.
		 * @param bool_ShowDebugShadows Untested. Context unknown.
		 * @param double_ShadowFarDistance Untested. Context unknown.
		 * @param double_ShadowDirectionalLightExtrusionDistance Untested. Context unknown.
		 * @param int_ShadowIndexBufferSize Untested. Context unknown.
		 * @param bool_ShadowUseInfiniteFarPlane Untested. Context unknown.
		 * @param int_ShadowTextureCount Untested. Context unknown.
		 * @param int_ShadowTextureSize Untested. Context unknown.
		 * @param enum_ShadowTexturePixelFormat Untested. Context unknown.
		 * @param double_ShadowDirLightTextureOffset Untested. Context unknown.
		 * @param double_ShadowTextureFadeStart Untested. Context unknown.
		 * @param double_ShadowTextureFadeEnd Untested. Context unknown.
		 * @param bool_ShadowTextureSelfShadow Untested. Context unknown.
		 * @param str_ShadowTextureCasterMaterial Untested. Context unknown.
		 * @param str_ShadowTextureReceiverMaterial Untested. Context unknown.
		 * @param bool_ShadowCasterRenderBackFaces Untested. Context unknown.
		 * @param obj_ColourDiffuse A pre-constructed "dotSceneColourDiffuse"-object. Context unknown.
		 */
		dotSceneShadowSettings(
			ShadowTechnique enum_ShadowTechnique,
			bool bool_ShowDebugShadows,
			double double_ShadowFarDistance,
			double double_ShadowDirectionalLightExtrusionDistance,
			int	int_ShadowIndexBufferSize,
			bool bool_ShadowUseInfiniteFarPlane,
			int	int_ShadowTextureCount,
			int	int_ShadowTextureSize,
			PixelFormat enum_ShadowTexturePixelFormat,
			double double_ShadowDirLightTextureOffset,
			double double_ShadowTextureFadeStart,
			double double_ShadowTextureFadeEnd,
			bool bool_ShadowTextureSelfShadow,
			std::string	str_ShadowTextureCasterMaterial,
			std::string	str_ShadowTextureReceiverMaterial,
			bool bool_ShadowCasterRenderBackFaces,
			dotSceneColourDiffuse obj_ColourDiffuse);
    };
}
