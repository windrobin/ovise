#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class represets the textureStacksAndSlices xml-element.
	 */
	class dotSceneTextureStacksAndSlices : virtual public dotSceneObject
    {
	private:
		std::string _Stacks; /**< Property Stacks.*/
		std::string _Slices; /**< Property Slices.*/

	public:
		std::string get_Stacks() const;		/**< Get-method for property Stacks. @return Returns Stacks as std::string.*/
		std::string get_Slices() const;		/**< Get-method for property Slices. @return Returns Slices as std::string.*/

		void set_Stacks(std::string value);	/**< Set-method for property Stacks. @param value Value of a std::string.*/
		void set_Slices(std::string value);	/**< Set-method for property Slices. @param value Value of a std::string.*/

		bool IsValid() const;				/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor.
		 */
		dotSceneTextureStacksAndSlices();

		/**
		 * Standard-Constructor for std::string-values.
		 * @param str_Stacks Stacks in std::string-format.
		 * @param str_Slices Slices-value in std::string-format.
		 */
		dotSceneTextureStacksAndSlices(std::string str_Stacks, std::string str_Slices);
    };
}
