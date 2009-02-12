namespace dotSceneEnums
{
	namespace dotSceneEntityEnums
	{
		enum BufferUsage
		{
			BufferUsage_static, 
			BufferUsage_dynamic,
			BufferUsage_writeOnly,
			BufferUsage_staticWriteOnly,
			BufferUsage_dynamicWriteOnly,
			BufferUsage_discardable,
			BufferUsage_dynamicWriteOnlyDiscardable,
			BufferUsage_INVALID /**< Zero/invalid/-1 value of this enum. Important for "valid-check"-model */
		};
	}
}