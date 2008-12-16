#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class holds additional information about behaveiour of a animationed object in Ogre3D.
	 */
	class dotSceneCommonMovableObjectParams : virtual public dotSceneObject 
    {
	private:
		bool _Static;					/**< Property Static. Default-value is "false".*/
		bool _Visible;					/**< Property Visible. This value turn on/off visiblity of a rendered object. Default-value is "true".*/
		bool _CastShadows;				/**< Property CastShadows. This value turn on/off shadows of a rendered object. Default-value is "true".*/
		double _RenderingDistance;		/**< Property RenderingDistance. Defines maximal distance, where the object fades out. Default-value is "0.0".*/
		std::string _QueryFlags;		/**< Property QueryFlags.*/
		std::string _VisibilityFlags;	/**< Property VisibilityFlags.*/

	public:
		bool get_Static() const;				/**< Get-method for property Static. @return Returns Static as a bool.*/
		bool get_Visible() const;				/**< Get-method for property Visible. @return Returns Visible as a bool.*/
		bool get_CastShadows() const;			/**< Get-method for property CastShadows. @return Returns CastShadows as a bool.*/
		double get_RenderingDistance() const;	/**< Get-method for property RenderingDistance. @return Returns RenderingDistance as a double.*/
		std::string get_QueryFlags() const;		/**< Get-method for property QueryFlags. @return Returns QueryFlags as a std::string.**/
		std::string get_VisibilityFlags() const;/**< Get-method for property VisibilityFlags. @return Returns VisibilityFlags as a std::string.*/

		void set_Static(bool value);					/**< Set-method for property Static. @param value Value of a bool.*/
		void set_Visible(bool value);					/**< Set-method for property Visible. @param value Value of a bool.*/
		void set_CastShadows(bool value);				/**< Set-method for property CastShadows. @param value Value of a bool.*/
		void set_RenderingDistance(double value);		/**< Set-method for property RenderingDistance. @param value Value of a bool.*/
		void set_QueryFlags(std::string value);			/**< Set-method for property QueryFlags. @param value Value of a std::string.*/
		void set_VisibilityFlags(std::string value);	/**< Set-method for property VisibilityFlags.@param value Value of a std::string.*/

		void set_Static(std::string value);				/**< Set-method for property Static. @param value Value of a std::string.*/
		void set_Visible(std::string value);			/**< Set-method for property Visible. @param value Value of a std::string.*/
		void set_CastShadows(std::string value);		/**< Set-method for property CastShadows. @param value Value of a std::string.*/
		void set_RenderingDistance(std::string value);	/**< Set-method for property RenderingDistance. @param value Value of a std::string.*/

		bool IsValid() const;							/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor.
		 * Calls constructor of baseobject.
		 */
		dotSceneCommonMovableObjectParams();

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double & bool(integer) -format.
		 * @param str_Static Context unknown.
		 * @param str_Visible Describes visiblityof  a 3D-object.
		 * @param str_CastShadows Describes shadow-behaviour of a 3D-object.
		 * @param str_RenderingDistance Maximal rendering distance of an 3D-object.
		 * @param str_QueryFlags Context unknown.
		 * @param str_VisibilityFlags Context unknown.
		 */
		dotSceneCommonMovableObjectParams(std::string str_Static, std::string str_Visible, std::string str_CastShadows, std::string str_RenderingDistance, std::string str_QueryFlags, std::string str_VisibilityFlags);
		
		/**
		 * Standard-constructor for direct value-parameters.
		 * @param bool_Static Context unknown.
		 * @param bool_Visible Describes visiblityof  a 3D-object.
		 * @param bool_CastShadows Describes shadow-behaviour of a 3D-object.
		 * @param double_RenderingDistance Maximal rendering distance of an 3D-object.
		 * @param str_QueryFlags Context unknown.
		 * @param str_VisibilityFlags Context unknown.
		 */
		dotSceneCommonMovableObjectParams(bool bool_Static, bool bool_Visible, bool bool_CastShadows, double double_RenderingDistance, std::string str_QueryFlags, std::string str_VisibilityFlags);
    };
}
