#ifndef dotSceneObject_h_
#define dotSceneObject_h_
#include "dotSceneObject.h"
#endif

#ifndef dotSceneUpVector_h_
#define dotSceneUpVector_h_
#include "dotSceneUpVector.h"
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;

	/**
	 * This class hold values for all objects, which can occure in plane-definition.
	 * There are two element-tag used in dotScene.xsd version 1.0.0, without any definition:
	 * indexBuffer
	 * vertexBuffer
	 * Have an eye on 'em.
	 *   -Nov 08 by H.R.
	 */
	class dotScenePlane : virtual public dotSceneObject
    {
	private:
		std::string _name;		/**< Property name.*/
		std::string _ID;		/**< Property ID.*/
		double _NormalX;		/**< Property NormalX.*/
		double _NormalY;		/**< Property NormalY.*/
		double _NormalZ;		/**< Property NormalZ.*/
		double _Distance;		/**< Property Distance.*/
		double _Height;			/**< Property Height.*/
		double _Width;			/**< Property Width.*/
		int _xSegments;			/**< Property xSegments.*/
		int _ySegments;			/**< Property ySegments.*/
		bool _Normals;			/**< Property Normals.*/
		int _NumTexCoordSets;	/**< Property NumTexCoordSets.*/
		int _UTile;				/**< Property UTile.*/
		int _VTile;				/**< Property VTile.*/

		dotSceneUpVector _UpVector;	/**< Property UpVector.*/
		//dotSceneVertexBuffer _invalid;	// This element ist used, but not defined in version 1.0.0 of dotScene.xsd
		//dotSceneIndexBuffer _invalid;		// This element ist used, but not defined in version 1.0.0 of dotScene.xsd

	public:
		std::string get_name() const;	/**< Get-method for property name. @return Returns name as std::string.*/
		std::string get_ID() const;		/**< Get-method for property ID. @return Returns ID as std::string.*/
		double get_NormalX() const;		/**< Get-method for property NormalX. @return Returns NormalX as double.*/
		double get_NormalY() const;		/**< Get-method for property NormalY. @return Returns NormalY as double.*/			
		double get_NormalZ() const;		/**< Get-method for property NormalZ. @return Returns NormalZ as double.*/
		double get_Distance() const;	/**< Get-method for property Distance. @return Returns Distance as double.*/
		double get_Height() const;		/**< Get-method for property Height. @return Returns Height as double.*/
		double get_Width() const;		/**< Get-method for property Width. @return Returns Width as double.*/
		int get_xSegments() const;		/**< Get-method for property xSegments. @return Returns xSegments as integer.*/
		int get_ySegments() const;		/**< Get-method for property ySegments. @return Returns ySegments as integer.*/
		bool get_Normals() const;		/**< Get-method for property Normals. @return Returns Normals as bool.*/
		int get_NumTexCoordSets() const;/**< Get-method for property NumTexCoordSets. @return Returns NumTexCoordSets as integer.*/
		int get_UTile() const;			/**< Get-method for property UTile. @return Returns UTile as integer.*/
		int get_VTile() const;			/**< Get-method for property VTile. @return Returns VTile as integer.*/

		dotSceneUpVector get_UpVector() const;	/**< Get-method for property UpVector. @return Returns a "UpVector"-object.*/
		// Placeholde & Reminder
		// Placeholde & Reminder

		void set_name(std::string value);	/**< Set-method for property name. @param value Value of a std::string.*/
		void set_ID(std::string value);		/**< Set-method for property ID. @param value Value of a std::string.*/
		void set_NormalX(double value);		/**< Set-method for property NormalX. @param value Value of a double.*/
		void set_NormalY(double value);		/**< Set-method for property NormalY. @param value Value of a double.*/
		void set_NormalZ(double value);		/**< Set-method for property NormalZ. @param value Value of a double.*/
		void set_Distance(double value);	/**< Set-method for property Distance. @param value Value of a double.*/
		void set_Height(double value);		/**< Set-method for property Height. @param value Value of a double.*/
		void set_Width(double value);		/**< Set-method for property Width. @param value Value of a double.*/
		void set_xSegments(int value);		/**< Set-method for property xSegments. @param value Value of a integer.*/
		void set_ySegments(int value);		/**< Set-method for property ySegments. @param value Value of a integer.*/
		void set_Normals(bool value);		/**< Set-method for property Normals. @param value Value of a bool.*/
		void set_NumTexCoordSets(int value);/**< Set-method for property NumTexCoordSets. @param value Value of a integer.*/
		void set_UTile(int value);			/**< Set-method for property UTile. @param value Value of a integer.*/
		void set_VTile(int value);			/**< Set-method for property VTile. @param value Value of a integer.*/

		void set_UpVector(dotSceneUpVector value);	/**< Set-method for property UpVector. @param value A "dotSceneUpVector"-object.*/
		// Placeholde & Reminder
		// Placeholde & Reminder

		void set_NormalX(std::string value);		/**< Set-method for property NormalX. @param value Value of a std::string.*/
		void set_NormalY(std::string value);		/**< Set-method for property NormalY. @param value Value of a std::string.*/
		void set_NormalZ(std::string value);		/**< Set-method for property NormalZ. @param value Value of a std::string.*/
		void set_Distance(std::string value);		/**< Set-method for property Distance. @param value Value of a std::string.*/
		void set_Height(std::string value);			/**< Set-method for property Height. @param value Value of a std::string.*/
		void set_Width(std::string value);			/**< Set-method for property Width. @param value Value of a std::string.*/
		void set_xSegments(std::string value);		/**< Set-method for property xSegments. @param value Value of a std::string.*/
		void set_ySegments(std::string value);		/**< Set-method for property ySegments. @param value Value of a std::string.*/
		void set_Normals(std::string value);		/**< Set-method for property Normals. @param value Value of a std::string.*/
		void set_NumTexCoordSets(std::string value);/**< Set-method for property NumTexCoordSets. @param value Value of a std::string.*/
		void set_UTile(std::string value);			/**< Set-method for property UTile. @param value Value of a std::string.*/
		void set_VTile(std::string value);			/**< Set-method for property VTile. @param value Value of a std::string.*/

		bool IsValid() const;	/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/
		
        /**
		 * Simple Constructor.
		 */
		dotScenePlane();

		/**
		 * Full initialisation constructor of dotScenePlane for std::string-values.
		 * All std::string-values will be parsed automatically.
		 * @param  str_name Name of plane. Untested.
	 	 * @param  str_ID ID of plane. Untested.
		 * @param  str_NormalX Context unknown. Untested.
		 * @param  str_NormalY Context unknown. Untested.
		 * @param  str_NormalZ Context unknown. Untested.
		 * @param  str_Distance Context unknown. Untested.
		 * @param  str_Height Context unknown. Untested.
		 * @param  str_Width Context unknown. Untested.
		 * @param  str_xSegments Context unknown. Untested.
		 * @param  str_ySegments Context unknown. Untested.
		 * @param  str_Normals Context unknown. Untested.
		 * @param  str_NumTexCoordSets Context unknown. Untested.
		 * @param  str_UTile Context unknown. Untested.
		 * @param  str_VTile Context unknown. Untested.
		 * @param  obj_UpVector A pre-constrcted "dotSceneUpVector"-object.
		 */
		dotScenePlane(
			std::string str_name,
			std::string str_ID,
			std::string str_NormalX,
			std::string str_NormalY,
			std::string str_NormalZ,
			std::string str_Distance,
			std::string str_Height,
			std::string str_Width,
			std::string str_xSegments,
			std::string str_ySegments,
			std::string str_Normals,
			std::string str_NumTexCoordSets,
			std::string str_UTile,
			std::string str_VTile,
			dotSceneUpVector obj_UpVector);

		/**
		 * Full initialisation constructor of dotScenePlane.
		 * @param str_name Name of billboardSet. Untested.
		 * @param str_ID ID of billboardSet. Untested.
		 * @param double_NormalX;
		 * @param double_NormalY;
		 * @param double_NormalZ;
		 * @param double_Distance;
		 * @param double_Height;
		 * @param double_Width;
		 * @param int_xSegments;
		 * @param int_ySegments;
		 * @param bool_Normals;
		 * @param int_NumTexCoordSets;
		 * @param int_UTile;
		 * @param int_VTile;
		 * @param obj_UpVector A pre-constrcted "dotSceneUpVector"-object.
		 */
		dotScenePlane(
			std::string str_name,
			std::string str_ID,
			double double_NormalX,
			double double_NormalY,
			double double_NormalZ,
			double double_Distance,
			double double_Height,
			double double_Width,
			int int_xSegments,
			int int_ySegments,
			bool bool_Normals,
			int int_NumTexCoordSets,
			int int_UTile,
			int int_VTile,
			dotSceneUpVector obj_UpVector);

		/**
		 * Copy-Constructor.
		 */
		dotScenePlane(const dotScenePlane& CopyObject);
    };
}
