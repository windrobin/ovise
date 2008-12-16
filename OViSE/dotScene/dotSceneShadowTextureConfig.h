#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneGeneralEnums_h_
#define dotSceneGeneralEnums_h_
#include "dotSceneGeneralEnums.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;
	using namespace dotSceneEnums::dotSceneShadowConfigEnums;

	/**
	 * This class hold values for all objects, which can occure in node-definition.
	 */
	class dotSceneShadowTextureConfig : virtual public dotSceneObject
    {
	private:
		int			_ShadowIndex;	/**< Property ShadowIndex. Untested. Context unknown.*/
		double		_Width;			/**< Property Width. Untested. Context unknown.*/
		double		_Height;		/**< Property Height. Untested. Context unknown.*/
		PixelFormat _PixelFormat;	/**< Property PixelFormat. Untested. Context unknown.*/

	public:
		int			get_ShadowIndex() const;/**< Get-method for property ShadowIndex. @return Returns ShadowIndex as integer.*/
		double		get_Width() const;		/**< Get-method for property Width. @return Returns Width as double.*/
		double		get_Height() const;		/**< Get-method for property Height. @return Returns Height as double.*/
		PixelFormat get_PixelFormat() const;/**< Get-method for property PixelFormat. @return Returns PixelFormat as value of "dotSceneEnums::dotSceneShadowTextureConfigEnums::PixelFormat"-enum.*/

		void		set_ShadowIndex(int value);			/**< Set-method for property ShadowIndex. @param value Value of integer.*/
		void		set_Width(double value);			/**< Set-method for property Width. @param value Value of double.*/
		void		set_Height(double value);			/**< Set-method for property Height. @param value Value of double.*/
		void		set_PixelFormat(PixelFormat value);	/**< Set-method for property PixelFormat. @param value Value of a "dotSceneEnums::dotSceneShadowTextureConfigEnums::PixelFormat"-enum.*/
		
		void		set_ShadowIndex(std::string value);	/**< Set-method for property ShadowIndex. @param value Value of a std::string.*/
		void		set_Width(std::string value);		/**< Set-method for property Width. @param value Value of a std::string.*/
		void		set_Height(std::string value);		/**< Set-method for property Height. @param value Value of a std::string.*/
		void		set_PixelFormat(std::string value);	/**< Set-method for property PixelFormat. @param value Value of a std::string.*/

		bool IsValid() const;	/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/
		
        /**
		 * Simple Constructor.
		 */
		dotSceneShadowTextureConfig();

		/**
		 * Full initialisation constructor of dotSceneShadowTextureConfig.
		 * All std::string-values will be parsed automatically.
		 * @param str_ShadowIndex Untested. Context unknown.
		 * @param str_Width Untested. Context unknown.
		 * @param str_Height Untested. Context unknown.
		 * @param str_PixelFormat Untested. Context unknown.
		 */
		dotSceneShadowTextureConfig(
			std::string str_ShadowIndex,
			std::string str_Width,
			std::string str_Height,
			std::string str_PixelFormat);

		/**
		 * Full initialisation constructor of dotSceneShadowTextureConfig.
		 * @param int_ShadowIndex Untested. Context unknown.
		 * @param double_Width Untested. Context unknown.
		 * @param double_Height Untested. Context unknown.
		 * @param enum_PixelFormat Untested. Context unknown.
		 */
		dotSceneShadowTextureConfig(
			int int_ShadowIndex,
			double double_Width,
			double double_Height,
			PixelFormat enum_PixelFormat);
    };
}
