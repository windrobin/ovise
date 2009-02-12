#ifndef dotSceneGeneralEnums_h_
#define dotSceneGeneralEnums_h_
#include "dotSceneGeneralEnums.h"
#endif

#ifndef dotSceneCommonMovableObjectParams_h_
#define dotSceneCommonMovableObjectParams_h_
#include "dotSceneCommonMovableObjectParams.h"
#endif

#ifndef dotSceneCommonDirection_h_
#define dotSceneCommonDirection_h_
#include "dotSceneCommonDirection.h"
#endif

#ifndef dotSceneCommonUpVector_h_
#define dotSceneCommonUpVector_h_
#include "dotSceneCommonUpVector.h"
#endif

#ifndef dotSceneBillboard_h_
#define dotSceneBillboard_h_
#include "dotSceneBillboard.h"
#endif

#ifndef dotSceneTextureCoords_h_
#define dotSceneTextureCoords_h_
#include "dotSceneTextureCoords.h"
#endif

#ifndef dotSceneTextureStacksAndSlices_h_
#define dotSceneTextureStacksAndSlices_h_
#include "dotSceneTextureStacksAndSlices.h"
#endif

#ifndef list_h_
#define list_h_
#include <list>
#endif

#pragma once

namespace dotSceneObjects
{
	using namespace dotSceneObjects;
	using namespace dotSceneEnums::dotSceneBillboradSetEnums;

	/**
	 * This class hold values for all objects, which can occure in pillboardSet-definition.
	 */
	class dotSceneBillboardSet : virtual public dotSceneObject
    {
	private:
		std::string _name;								/**< Property name.*/
		std::string _ID;								/**< Property ID.*/
		int _PoolSize;									/**< Property PoolSize.*/
		bool _Autoextend;								/**< Property Autoextend.*/
		std::string _MaterialName;						/**< Property MaterialName.*/
		double _DefaultWidth;							/**< Property DefaultWidth.*/
		double _DefaultHeight;							/**< Property DefaultHeight.*/
		BillboardType _BillboardType;					/**< Property BillboardType.*/
		BillboardOrigin _BillboardOrigin;				/**< Property BillboardOrigin.*/
		BillboardRotationType _BillboardRotationType;	/**< Property BillboardRotationType.*/
		bool _SortingEnabled;							/**< Property SortingEnabled.*/
		bool _CullIndividually;							/**< Property CullIndividually.*/
		bool _AccurateFacing;							/**< Property AccurateFacing.*/
		bool _BillboardsInWorldSpace;					/**< Property BillboardsInWorldSpace.*/
		bool _PointRenderingEnabled;					/**< Property PointRenderingEnabled.*/

		dotSceneCommonMovableObjectParams _CommonMovableObjectParams;	/**< Property CommonMovableObjectParams.*/
		dotSceneCommonDirection _CommonDirection;						/**< Property CommonDirection.*/
		dotSceneCommonUpVector _CommonUpVector;							/**< Property CommonUpVector.*/
		dotSceneTextureCoords _TextureCoords;							/**< Property TextureCoords.*/
		dotSceneTextureStacksAndSlices _TextureStacksAndSlices;			/**< Property TextureStacksAndSlices.*/

	public:
		// lists
		std::list<dotSceneBillboard> _BillboardList;			/**< dotSceneBillboards of current dotSceneBillboardSet.*/

		std::string get_name() const;							/**< Get-method for property name. @return Returns name as std::string.*/
		std::string get_ID() const;								/**< Get-method for property ID. @return Returns ID as std::string.*/
		int get_PoolSize() const;								/**< Get-method for property PoolSize. @return Returns PoolSize as integer.*/
		bool get_Autoextend() const;							/**< Get-method for property Autoextend. @return Returns Autoextend as bool.*/
		std::string get_MaterialName() const;					/**< Get-method for property MaterialName. @return Returns MaterialName as std::string.*/
		double get_DefaultWidth() const;						/**< Get-method for property DefaultWidth. @return Returns DefaultWidth as double.*/
		double get_DefaultHeight() const;						/**< Get-method for property DefaultHeight. @return Returns DefaultHeight as double.*/
		BillboardType get_BillboardType() const;				/**< Get-method for property BillboardType. @return Returns BillboardType as a value of dotSceneEnums::dotSceneBillboradSetEnums::BillboardType.*/
		BillboardOrigin get_BillboardOrigin() const;			/**< Get-method for property BillboardOrigin. @return Returns BillboardOrigin as a value of dotSceneEnums::dotSceneBillboradSetEnums::BillboardOrigin.*/
		BillboardRotationType get_BillboardRotationType() const;/**< Get-method for property BillboardRotationType. @return Returns BillboardRotationType as a value of dotSceneEnums::dotSceneBillboradSetEnums::BillboardRotationType.*/
		bool get_SortingEnabled() const;						/**< Get-method for property SortingEnabled. @return Returns SortingEnabled as bool.*/
		bool get_CullIndividually() const;						/**< Get-method for property CullIndividually. @return Returns CullIndividually as bool.*/
		bool get_AccurateFacing() const;						/**< Get-method for property AccurateFacing. @return Returns AccurateFacing as bool.*/
		bool get_BillboardsInWorldSpace() const;				/**< Get-method for property BillboardsInWorldSpace. @return Returns BillboardsInWorldSpace as bool.*/
		bool get_PointRenderingEnabled() const;					/**< Get-method for property PointRenderingEnabled. @return Returns PointRenderingEnabled as bool.*/

		dotSceneCommonMovableObjectParams get_CommonMovableObjectParams() const;/**< Get-method for property CommonMovableObjectParams. @return Returns a "dotSceneCommonMovableObjectParams"-object.*/
		dotSceneCommonDirection get_CommonDirection() const;					/**< Get-method for property CommonDirection. @return Returns a "dotSceneCommonDirection"-object.*/
		dotSceneCommonUpVector get_CommonUpVector() const;						/**< Get-method for property CommonUpVector. @return Returns a "dotSceneCommonUpVector"-object.*/
		dotSceneTextureCoords get_TextureCoords() const;						/**< Get-method for property TextureCoords. @return Returns a "dotSceneTextureCoords"-object.*/
		dotSceneTextureStacksAndSlices get_TextureStacksAndSlices() const;		/**< Get-method for property TextureStacksAndSlices. @return Returns a "dotSceneTextureStacksAndSlices"-object.*/

		void set_name(std::string value);							/**< Set-method for property name. @param value Value of a std::string.*/
		void set_ID(std::string value);								/**< Set-method for property ID. @param value Value of a std::string.*/
		void set_PoolSize(int value);								/**< Set-method for property PoolSize. @param value Value of a integer.*/
		void set_Autoextend(bool value);							/**< Set-method for property Autoextend. @param value Value of a bool.*/
		void set_MaterialName(std::string value);					/**< Set-method for property MaterialName. @param value Value of a std::string.*/
		void set_DefaultWidth(double value);						/**< Set-method for property DefaultWidth. @param value Value of a double.*/
		void set_DefaultHeight(double value);						/**< Set-method for property DefaultHeight. @param value Value of a double.*/
		void set_BillboardType(BillboardType value);				/**< Set-method for property BillboardType. @param value Value of dotSceneEnums::dotSceneBillboradSetEnums::BillboardType.*/
		void set_BillboardOrigin(BillboardOrigin value);			/**< Set-method for property BillboardOrigin. @param value Value of dotSceneEnums::dotSceneBillboradSetEnums::BillboardOrigin.*/
		void set_BillboardRotationType(BillboardRotationType value);/**< Set-method for property BillboardRotationType. @param value Value of dotSceneEnums::dotSceneBillboradSetEnums::BillboardRotationType.*/

		void set_SortingEnabled(bool value);						/**< Set-method for property SortingEnabled. @param value Value of a bool.*/
		void set_CullIndividually(bool value);						/**< Set-method for property CullIndividually. @param value Value of a bool.*/
		void set_AccurateFacing(bool value);						/**< Set-method for property AccurateFacing. @param value Value of a bool.*/
		void set_BillboardsInWorldSpace(bool value);				/**< Set-method for property BillboardsInWorldSpace. @param value Value of a bool.*/
		void set_PointRenderingEnabled(bool value);					/**< Set-method for property PointRenderingEnabled. @param value Value of a bool.*/

		void set_CommonMovableObjectParams(dotSceneCommonMovableObjectParams value);/**< Set-method for property CommonMovableObjectParams. @param value A "dotSceneCommonMovableObjectParams"-object.*/
		void set_CommonDirection(dotSceneCommonDirection value);					/**< Set-method for property CommonDirection. @param value A "dotSceneCommonDirection"-object.*/
		void set_CommonUpVector(dotSceneCommonUpVector value);						/**< Set-method for property CommonUpVector. @param value A "dotSceneCommonUpVector"-object.*/
		void set_TextureCoords(dotSceneTextureCoords value);						/**< Set-method for property TextureCoords. @param value A "dotSceneTextureCoords"-object.*/
		void set_TextureStacksAndSlices(dotSceneTextureStacksAndSlices value);		/**< Set-method for property TextureStacksAndSlices. @param value A "dotSceneTextureStacksAndSlices"-object.*/

		void set_PoolSize(std::string value);						/**< Set-method for property PoolSize. @param value Value of a std::string.*/
		void set_Autoextend(std::string value);						/**< Set-method for property Autoextend. @param value Value of a std::string.*/
		void set_DefaultWidth(std::string value);					/**< Set-method for property DefaultWidth. @param value Value of a std::string.*/
		void set_DefaultHeight(std::string value);					/**< Set-method for property DefaultHeight. @param value Value of a std::string.*/
		void set_BillboardType(std::string value);					/**< Set-method for property BillboardType. @param value Value of std::string.*/
		void set_BillboardOrigin(std::string value);				/**< Set-method for property BillboardOrigin. @param value Value of std::string.*/
		void set_BillboardRotationType(std::string value);			/**< Set-method for property BillboardRotationType. @param value Value of std::string.*/
		void set_SortingEnabled(std::string value);					/**< Set-method for property SortingEnabled. @param value Value of a std::string.*/
		void set_CullIndividually(std::string value);				/**< Set-method for property CullIndividually. @param value Value of a std::string.*/
		void set_AccurateFacing(std::string value);					/**< Set-method for property AccurateFacing. @param value Value of a std::string.*/
		void set_BillboardsInWorldSpace(std::string value);			/**< Set-method for property BillboardsInWorldSpace. @param value Value of a std::string.*/
		void set_PointRenderingEnabled(std::string value);			/**< Set-method for property PointRenderingEnabled. @param value Value of a std::string.*/

		bool IsValid() const;	/**< Checks if all data-field contain data. @return Returns TRUE, if all fields contain data. Else FALSE.*/
		
		/**
		 * This function adds a new dotSceneBillboard to the list "BillboardList".
		 * A formatted grow of a container is a better than a direct access.
		 * At last, a proctected acess is not fully implemented.
		 * @param node A "dotSceneBillboard"-object.
		 * @return Returns a bool value. TRUE, when there was no problem.
		 */
		bool addBillboard(dotSceneBillboard someBillboard);

        /**
		 * Simple Constructor.
		 */
		dotSceneBillboardSet();

		/**
		 * Full initialisation constructor of dotSceneBillboardSet for std::string-values.
		 * All std::string-values will be parsed automatically.
		 * @param  str_name Name of billboardSet. Untested.
	 	 * @param  str_ID ID of billboardSet. Untested.
		 * @param  str_PoolSize Context not investigated. Untested.
		 * @param  str_Autoextend Context not investigated. Untested.
		 * @param  str_MaterialName Name of material, used for billboarding. Context not investigated. Untested.
		 * @param  str_DefaultWidth Context not investigated. Untested.
		 * @param  str_DefaultHeight Context not investigated. Untested.
		 * @param  str_BillboardType Context not investigated. Untested.
		 * @param  str_BillboardOrigin Context not investigated. Untested.
		 * @param  str_BillboardRotationType Context not investigated. Untested.
		 * @param  str_SortingEnabled Context not investigated. Untested.
		 * @param  str_CullIndividually Context not investigated. Untested.
		 * @param  str_AccurateFacing Context not investigated. Untested.
		 * @param  str_BillboardsInWorldSpace Context not investigated. Untested.
		 * @param  str_PointRenderingEnabled Context not investigated. Untested.
		 * @param  obj_CommonMovableObjectParams A pre-constrcted "dotSceneCommonMovableObjectParams"-object.
		 * @param  obj_CommonDirection A pre-constrcted "dotSceneCommonDirection"-object.
		 * @param  obj_CommonUpVector A pre-constrcted "dotSceneCommonUpVector"-object.
		 */
		dotSceneBillboardSet(
			std::string str_name,
			std::string str_ID,
			std::string str_PoolSize,
			std::string str_Autoextend,
			std::string str_MaterialName,
			std::string str_DefaultWidth,
			std::string str_DefaultHeight,
			std::string str_BillboardType,
			std::string str_BillboardOrigin,
			std::string str_BillboardRotationType,
			std::string str_SortingEnabled,
			std::string str_CullIndividually,
			std::string str_AccurateFacing,
			std::string str_BillboardsInWorldSpace,
			std::string str_PointRenderingEnabled,
			dotSceneCommonMovableObjectParams obj_CommonMovableObjectParams,
			dotSceneCommonDirection obj_CommonDirection,
			dotSceneCommonUpVector obj_CommonUpVector);

		/**
		 * Full initialisation constructor of dotSceneBillboardSet.
		 * @param str_name Name of billboardSet. Untested.
		 * @param str_ID ID of billboardSet. Untested.
		 * @param int_PoolSize Context not investigated. Untested.
		 * @param bool_Autoextend Context not investigated. Untested.
		 * @param str_MaterialName Name of material, used for billboarding. Context not investigated. Untested.
		 * @param bool_DefaultWidth Context not investigated. Untested.
		 * @param bool_DefaultHeight Context not investigated. Untested.
		 * @param enum_BillboardType Context not investigated. Untested.
		 * @param enum_BillboardOrigin Context not investigated. Untested.
		 * @param enum_BillboardRotationType Context not investigated. Untested.
		 * @param bool_SortingEnabled Context not investigated. Untested.
		 * @param bool_CullIndividually Context not investigated. Untested.
		 * @param bool_AccurateFacing Context not investigated. Untested.
		 * @param bool_BillboardsInWorldSpace Context not investigated. Untested.
		 * @param bool_PointRenderingEnabled Context not investigated. Untested.
		 * @param obj_CommonMovableObjectParams A pre-constrcted "dotSceneCommonMovableObjectParams"-object.
		 * @param obj_CommonDirection A pre-constrcted "dotSceneCommonDirection"-object.
		 * @param obj_CommonUpVector A pre-constrcted "dotSceneCommonUpVector"-object.
		 */
		dotSceneBillboardSet(
			std::string str_name,
			std::string str_ID,
			int int_PoolSize,
			bool bool_Autoextend,
			std::string str_MaterialName,
			double bool_DefaultWidth,
			double bool_DefaultHeight,
			BillboardType enum_BillboardType,
			BillboardOrigin enum_BillboardOrigin,
			BillboardRotationType enum_BillboardRotationType,
			bool bool_SortingEnabled,
			bool bool_CullIndividually,
			bool bool_AccurateFacing,
			bool bool_BillboardsInWorldSpace,
			bool bool_PointRenderingEnabled,
			dotSceneCommonMovableObjectParams obj_CommonMovableObjectParams,
			dotSceneCommonDirection obj_CommonDirection,
			dotSceneCommonUpVector obj_CommonUpVector);

		/**
		 * Copy-Constructor.
		 */
		dotSceneBillboardSet(const dotSceneBillboardSet& CopyObject);
    };
}
