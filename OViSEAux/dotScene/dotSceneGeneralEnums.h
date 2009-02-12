namespace dotSceneEnums
{
	namespace dotSceneGeneralEnums
	{
		enum RelativeTo
		{
			RelativeToLocal,
			RelativeToParent,
			RelativeToWorld,
			RelativeTo_INVALID /**< Zero/invalid/-1 value of this enum. Important for "valid-check"-model */
		};
	}

	namespace dotSceneBillboradSetEnums
	{
		enum BillboardType
		{
			BillboardType_Point,
			BillboardType_OrientedCommon,
            BillboardType_OrientedSelf,
            BillboardType_PerpendicularCommon,
            BillboardType_PerpendicularSelf,
			BillboardType_INVALID
		};

		enum BillboardOrigin
		{
            BillboardOrigin_TopLeft,
            BillboardOrigin_TopCenter,
            BillboardOrigin_TopRight,
            BillboardOrigin_CenterLeft,
            BillboardOrigin_Center,
            BillboardOrigin_CenterRight,
            BillboardOrigin_BottomLeft,
            BillboardOrigin_BottomCenter,
            BillboardOrigin_BottomRight,
			BillboardOrigin_INVALID
		};

		enum BillboardRotationType
		{
            BillboardRotationType_Vertex,
            BillboardRotationType_Texcoord,
			BillboardRotationType_INVALID
		};
	}

	namespace dotSceneLightEnums
	{
		enum LightTypes
		{
			Light_Point,
			Light_Directional,
			Light_SpotLight,
			Light_RadPoint,
			Light_INVALID
		};
	}

	namespace dotSceneShadowConfigEnums
	{
		enum ShadowTechnique
		{
            none,
            stencilModulative,
            stencilAdditive,
            textureModulative,
            textureAdditive,
            textureModulativeIntegrated,
            textureAdditiveIntegrated
		};

		enum PixelFormat
		{
			PF_UNKNOWN,
            PF_L8,
            PF_BYTE_L,
            PF_L16,
            PF_SHORT_L,
            PF_A8,
            PF_BYTE_A,
            PF_A4L4,
            PF_BYTE_LA,
            PF_R5G6B5,
            PF_B5G6R5,
            PF_R3G3B2,
            PF_A4R4G4B4,
            PF_A1R5G5B5,
            PF_R8G8B8,
            PF_B8G8R8,
            PF_A8R8G8B8,
            PF_A8B8G8R8,
            PF_B8G8R8A8,
            PF_R8G8B8A8,
            PF_X8R8G8B8,
            PF_X8B8G8R8,
            PF_BYTE_RGB,
            PF_BYTE_BGR,
            PF_BYTE_BGRA,
            PF_BYTE_RGBA,
            PF_A2R10G10B10,
            PF_A2B10G10R10,
            PF_DXT1,
            PF_DXT2,
            PF_DXT3,
            PF_DXT4,
            PF_DXT5,
            PF_FLOAT16_R,
            PF_FLOAT16_RGB,
            PF_FLOAT16_RGBA,
            PF_FLOAT32_R,
            PF_FLOAT32_RGB,
            PF_FLOAT32_RGBA,
            PF_FLOAT16_GR,
            PF_FLOAT32_GR,
            PF_DEPTH,
            PF_SHORT_RGBA,
            PF_SHORT_GR,
            PF_SHORT_RGB,
            PF_COUNT
		};
	}
}