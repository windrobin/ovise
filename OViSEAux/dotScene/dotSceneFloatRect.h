#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class holds Information, used in billboards.
	 */
    class dotSceneFloatRect : virtual public dotSceneObject 
    {
	private:
		double _Left;			/**< Property Left.*/
		double _Top;			/**< Property Top.*/
		double _Right;			/**< Property Right.*/
		double _Bottom;			/**< Property Bottom.*/

	public:
		double get_Left() const;	/**< Get-method for property Left. @return Returns Left as double.*/
		double get_Top() const;		/**< Get-method for property Top. @return Returns Top as double.*/
		double get_Right() const;	/**< Get-method for property Right. @return Returns Right as double.*/
		double get_Bottom() const;	/**< Get-method for property Bottom. @return Returns Bottom as double.*/

		void set_Left(double value);	/**< Set-method for property Left. @param value Value of double.*/
		void set_Top(double value);		/**< Set-method for property Top. @param value Value of double.*/
		void set_Right(double value);	/**< Set-method for property Right. @param value Value of double.*/
		void set_Bottom(double value);	/**< Set-method for property Bottom. @param value Value of double.*/

		void set_Left(std::string value);	/**< Set-method for property Left. @param value Value in std::string-format. Will be parsed to double.*/
		void set_Top(std::string value);	/**< Set-method for property Top. @param value Value in std::string-format. Will be parsed to double.*/
		void set_Right(std::string value);	/**< Set-method for property Right. @param value Value in std::string-format. Will be parsed to double.*/
		void set_Bottom(std::string value);	/**< Set-method for property Bottom. @param value Value in std::string-format. Will be parsed to double.*/

		bool IsValid() const;		/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Simple constructor.
		 */
		dotSceneFloatRect(); 
		
		/**
		 * Standard-constructor for std::string-parameters.
		 * All strings will be parsed automatically to double-format.
		 * @param str_Left Left-value in std::string-format.
		 * @param str_Top Top-value in std::string-format.
		 * @param str_Right Right-value in std::string-format.
		 * @param str_Bottom Bottom-value in std::string-format.
		 */
		dotSceneFloatRect(std::string str_Left, std::string str_Top, std::string str_Right, std::string str_Bottom);

		/**
		 * Standard-constructor for direct value-parameters.
		 * @param double_Left Left-value in double-format.
		 * @param double_Top Top-value in double-format.
		 * @param double_Right Right-value in double-format.
		 * @param double_Bottom Bottom-value in double-format.
		 */
		dotSceneFloatRect(double double_Left, double double_Top, double double_Right, double double_Bottom);
    };
}
