// This file contains data-containers for pharsed data form dotScene-XML-documents.
// All instanceable objects work through their constructor.
// The inheritance of the classes represents the structure of dotScene-XML-documents.
// Written by H.R., ITEC TH Karlsruhe, Germany, 2007-2008

#include <string>

#ifndef list_h_
#define list_h_
#include <list>
#endif

#ifndef dotSceneElementTags_h_
#define dotSceneElementTags_h_
#include "dotSceneElementTags.h"
#endif

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * Abstract basic-class. All other dotSceneObjects inherit from it. 
	 */
	class dotSceneObject
    {    
	private:
		dotSceneEnums::dotSceneElementTags _NameSymbol; /**< Property NameSymbol. This property identifies the kind of dotScene-Object by a dotSceneElementTags-enum.*/
		std::string _Name; /**< Property Name. This property identifies the kind of dotScene-Object by a string.*/

	public:
		bool set_NameSymbol(dotSceneEnums::dotSceneElementTags value); /**< Set-method for property NameSymbol. @param value A value of enum dotSceneElementTags.*/
		
		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		 * set_Name() can't be implemented good in C/C++. In C# that's no problem. *
		 * A possible solution for this can be found under:						   *
		 * http:://www.codeguru.com/cpp/cpp/cpp_mfc/article.php/c4067/			   *
		 *																		   *
		 * It can help, but at last that solution bind the implemetation to		   *
		 * MS systems again. In that case, but you can use std::string anyway	   *
		 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		bool set_Name(std::string value);							/**< Set-method for property Name. @param value A std::string.*/

		dotSceneEnums::dotSceneElementTags get_NameSymbol() const;	/**< Get-method for property NameSymbol. @return Returns NameSymbol as a value of enum dotSceneElementTags.*/
		std::string get_Name() const;								/**< Get-method for property Name. @return Returns name as std::string.*/
		virtual bool IsValid() const;										/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/

		/**
		 * Default-constructor.
		 */
		//dotSceneObject(); 

		/**
		 * Constructor for class dotSceneObject.
		 * A simple constuctor without any parameters is not supported.
		 * @param ElementTag Has to be a possible value of dotSceneElementTags.
		 */
		dotSceneObject(dotSceneEnums::dotSceneElementTags ElementTag); 
		
		/**
		 * Constructor for class dotSceneObject.
		 * A simple constuctor without any parameters is not supported.
		 * @param ElementTag String MUST correspond to text of one possiple value of dotSceneElementTags.
		 */
		dotSceneObject(std::string ElementName);
		
		/**
		 * Copy-constructor of class dotSceneObject.
		 * A simple constuctor without any parameters is not supported.
		 * @param Another instance of dotSceneObject.
		 */
		dotSceneObject(const dotSceneObject& obj);
        
		/**
		 * Simple destructor.
		 */
		~dotSceneObject() { }
    };
}
