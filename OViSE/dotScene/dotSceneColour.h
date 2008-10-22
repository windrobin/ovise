#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * Basic-class for colour-classes.
	 * All colour-classes inherit from dotSceneColour.
	 * In C# this class was planned as abstract class.
	 * In C/C++ there is no difference to a normal class anymore.
	 * But readers and interpreters should use the four colour-classes, which
	 * inherit from this dotSceneColour.
	 */
    class dotSceneColour : public dotSceneObject 
    {
	private:
		double _r; /**< Property r. RED colour-value.*/
		double _g; /**< Property g. GREEN colour-value.*/
		double _b; /**< Property b. BLUE colour-value.*/

		void set_r(double value);	/**< Set-method for property r. @param value Value of double.*/
		void set_g(double value);	/**< Set-method for property g. @param value Value of double.*/
		void set_b(double value);	/**< Set-method for property b. @param value Value of double.*/

	public:
		double get_r() const;	/**< Get-method for property r. @return Returns r as double.*/
		double get_g() const;	/**< Get-method for property g. @return Returns g as double.*/
		double get_b() const;	/**< Get-method for property b. @return Returns b as double.*/

		/**
		 * Simple constructor.
		 * It calls the constructor of baseobject.
		 * @param incomingTag Has to be a possible value of dotSceneElementTags.
		 */
		dotSceneColour(dotSceneElementTags); 
		
		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings, representing the RGB-values, will be parsed automatically to double-format.
		 * @param incomingTag Enum-Value of a dotScene-XML-Tag. The tags a defines in dotSceneElementTags.h.
		 * @param str_r r-value in string-format. Will be parsed to double.
		 * @param str_g g-value in string-format. Will be parsed to double.
		 * @param str_b b-value in string-format. Will be parsed to double.
		 */
		dotSceneColour(dotSceneElementTags incomingTag, std::string str_r, std::string str_g, std::string str_b);

		/**
		 * Standard-constructor for double-parameters.
		 * All strings, representing the RGB-values, will be parsed automatically to double-format.
		 * @param incomingTag Enum-Value of a dotScene-XML-Tag. The tags a defines in dotSceneElementTags.h.
		 * @param double_r r-value in double-format.
		 * @param double_g g-value in double-format.
		 * @param double_b b-value in double-format.
		 */
		dotSceneColour(dotSceneElementTags incomingTag, double double_r, double double_g, double double_b);
        
		/**
		 * Simple destructor.
		 */
		~dotSceneColour() { }
    };
}
