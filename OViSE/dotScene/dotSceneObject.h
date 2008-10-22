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
		dotSceneElementTags _NameSymbol; /**< Property NameSymbol. This property identifies the kind of dotScene-Object by a dotSceneElementTags-enum.*/
		std::string _Name; /**< Property Name. This property identifies the kind of dotScene-Object by a string.*/

		void set_NameSymbol(dotSceneElementTags value); /**< Set-method for property NameSymbol. @param value A value of enum dotSceneElementTags.*/

		/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
		 * Can't be implemented good in C/C++. In C# that's no problem.				   *
		 * A possible solution for this can be found under:							   *
		 * http:://www.codeguru.com/cpp/cpp/cpp_mfc/article.php/c4067/				   *
		 *																			   *
		 * It can help, but at last that solution bind the implemetation to            *
		 * MS systems again. In that case, you can use a C# implementation anyway ;-)  *
		 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
		//void set_Name(std::string);

	public:
		dotSceneElementTags get_NameSymbol() const; /**< Get-method for property NameSymbol. @return Returns NameSymbol as a value of enum dotSceneElementTags.*/
		std::string get_Name() const;				/**< Get-method for property Name. @return Returns name as std::string.*/

		/**
		 * Constructor for class dotSceneObject.
		 * A simple constuctor without any parameters is not supported.
		 * @param ElementTag Has to be a possible value of dotSceneElementTags.
		 */
		dotSceneObject(dotSceneElementTags ElementTag); 
		// siehe oben !!!
		//dotSceneObject(std::string); // Constructor for class dotSceneObject. A simple constuctor without any parameters is not supported. // <param name="ElementName">string MUST correspond to text of one possiple value of dotSceneElementTags</param>
		//dotSceneObject(dotSceneObject); // Copy-constructor of class dotSceneObject. // <param name="obj">dotSceneObject, where is copied from.</param>
        
		/**
		 * Simple destructor.
		 */
		~dotSceneObject() { }
    };
}
