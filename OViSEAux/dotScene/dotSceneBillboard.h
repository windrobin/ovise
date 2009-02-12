#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotScenePosition_h_
#define dotScenePosition_h_
#include "dotScenePosition.h"
#endif

#ifndef dotSceneColourDiffuse_h_
#define dotSceneColourDiffuse_h_
#include "dotSceneColourDiffuse.h"
#endif

#ifndef dotSceneTextureCoords_h_
#define dotSceneTextureCoords_h_
#include "dotSceneTextureCoords.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class hold all information, needed for an billboard. (untested)
	 * Billboarding a technique to modify parts of textures. For example, you can't cut parts out of a texture. That's not effective.
	 * But you can define parts to a zero alpha-value. So the described party becomes transparent.
	 * That's more effektive than manipulate a texture.
	 */
	class dotSceneBillboard : virtual public dotSceneObject 
    {
	private:
		std::string _ID;	/**< Property ID.*/
		double _Rotation;	/**< Property Rotation.*/
		double _Width;		/**< Property Width.*/
		double _Height;		/**< Property Height.*/
		int _TexCoordIndex;	/**< Property TexCoordIndex.*/

		dotScenePosition _Position;				/**< Property Position.*/
		dotSceneColourDiffuse _ColourDiffuse;	/**< Property ColourDiffuse.*/
		dotSceneTextureCoords _TextureCoords;	/**< Property TextureCoords.*/

	public:
		std::string get_ID() const;		/**< Get-method for property ID. @return Returns ID as a std::string.*/
		double get_Rotation() const;	/**< Get-method for property Rotation. @return Returns Rotation as a double.*/
		double get_Width() const;		/**< Get-method for property Width. @return Returns Width as a double.*/
		double get_Height() const;		/**< Get-method for property Height. @return Returns Height as a double.*/
		int get_TexCoordIndex() const;	/**< Get-method for property TexCoordIndex. @return Returns TexCoordIndex as an integer.*/

		dotScenePosition get_Position() const;				/**< Get-method for property Position. @return Returns a "dotScenePosition"-object.*/
		dotSceneColourDiffuse get_ColourDiffuse() const;	/**< Get-method for property ColourDiffuse. @return Returns a "dotSceneColourDiffuse"-object.*/
		dotSceneTextureCoords get_TextureCoords() const;	/**< Get-method for property TextureCoords. @return Returns a "dotSceneTextureCoords"-object.*/

		void set_ID(std::string value);		/**< Set-method for property ID. @param value Value of a std::string.*/
		void set_Rotation(double value);	/**< Set-method for property Rotation. @param value Value of a double.*/
		void set_Width(double value);		/**< Set-method for property Width. @param value Value of a double.*/
		void set_Height(double value);		/**< Set-method for property Height. @param value Value of a double.*/
		void set_TexCoordIndex(int value);	/**< Set-method for property TexCoordIndex. @param value Value of a integer.*/

		void set_Position(dotScenePosition value);				/**< Set-method for property Position. @param value A "dotScenePosition"-object.*/
		void set_ColourDiffuse(dotSceneColourDiffuse value);	/**< Set-method for property ColourDiffuse. @param A "dotSceneColourDiffuse"-object.*/
		void set_TextureCoords(dotSceneTextureCoords value);	/**< Set-method for property TextureCoords. @param A "dotSceneTextureCoords"-object.*/

		void set_Rotation(std::string value);		/**< Set-method for property Rotation. @param value Value of a std::string.*/
		void set_Width(std::string value);			/**< Set-method for property Width. @param value Value of a std::string.*/
		void set_Height(std::string value);			/**< Set-method for property Height. @param value Value of a std::string.*/
		void set_TexCoordIndex(std::string value);	/**< Set-method for property TexCoordIndex. @param value Value of a std::string.*/

		bool IsValid() const;				/**< Checks if all fields are valid/contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor.
		 */
		dotSceneBillboard();

		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double & integer -format.
		 * @param str_ID ID in std::string-format.
		 * @param str_Rotation Rotation in in std::string-format. Untestet. Context unknown.
		 * @param str_Width Wigth in in std::string-format. Untestet.
		 * @param str_Height Height in in std::string-format. Untestet.
		 * @param str_TexCoordIndex TexCoordIndex in std::string-format. Describes index of selected FloatRect-object in list of property TextureCoords. Untestet.
		 * @param obj_Position Position Some position of this billboard. Untestet.
		 * @param obj_ColourDiffuse Diffuse colour of this billboard.
		 * @param obj_TextureCoords Texture-coordinates of this billboard.
		 */
		dotSceneBillboard(
			std::string str_ID,
			std::string str_Rotation,
			std::string str_Width,
			std::string str_Height,
			std::string str_TexCoordIndex,
			dotScenePosition obj_Position,
			dotSceneColourDiffuse obj_ColourDiffuse,
			dotSceneTextureCoords obj_TextureCoords);
		
		/**
		 * Standard-constructor for direct value-parameters.
		 * @param str_ID ID in std::string-format.
		 * @param double_Rotation Rotation in double-format. Untestet. Context unknown.
		 * @param double_Width Wigth in double-format. Untestet. Context unknown.
		 * @param double_Height Height in double-format. Untestet. Context unknown.
		 * @param int_TexCoordIndex TexCoordIndex in integer-format. Describes index of selected FloatRect-object in list of property TextureCoords. Untestet.
		 * @param obj_Position Position Some position of this billboard. Untestet.
		 * @param obj_ColourDiffuse Diffuse colour of this billboard.
		 * @param obj_TextureCoords Texture-coordinates of this billboard.
		 */
		dotSceneBillboard(
			std::string str_ID,
			double double_Rotation,
			double double_Width,
			double double_Height,
			int int_TexCoordIndex,
			dotScenePosition obj_Position,
			dotSceneColourDiffuse obj_ColourDiffuse,
			dotSceneTextureCoords obj_TextureCoords);
    };
}
