#include "XLineRenderBuffers.h"
#include "MeshDrawShaderBindings.h"

class FXLineVertexFactoryShaderParameters : public FVertexFactoryShaderParameters
{
	DECLARE_TYPE_LAYOUT(FXLineVertexFactoryShaderParameters, NonVirtual);

public:

	void Bind( const FShaderParameterMap& ParameterMap )
	{
		PositionBuffer.Bind(ParameterMap, TEXT("PositionBuffer"));
	}

	void GetElementShaderBindings(
		const FSceneInterface* Scene,
		const FSceneView* View,
		const FMeshMaterialShader* Shader,
		const EVertexInputStreamType InputStreamType,
		ERHIFeatureLevel::Type FeatureLevel,
		const FVertexFactory* VertexFactory,
		const FMeshBatchElement& BatchElement,
		FMeshDrawSingleShaderBindings& ShaderBindings,
		FVertexInputStreamArray& VertexStreams) const
	{
		FXLineBatchElementUserData* UserData = (FXLineBatchElementUserData*)BatchElement.UserData;
		if( UserData->PositionBuffer && PositionBuffer.IsBound() )
		{
			ShaderBindings.Add(PositionBuffer, UserData->PositionBuffer);
		}
	}

private:

	LAYOUT_FIELD(FShaderResourceParameter, PositionBuffer);
};

FXLineVertexFactory::FXLineVertexFactory(ERHIFeatureLevel::Type InFeatureLevel)
	: FLocalVertexFactory(InFeatureLevel, "FXLineVertexFactory")
{
	
}

bool FXLineVertexFactory::ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Paramters)
{
	return false;
}

void FXLineVertexFactory::InitRHI()
{
	FLocalVertexFactory::InitRHI();
}

void FXLineVertexFactory::ReleaseRHI()
{
	FLocalVertexFactory::ReleaseRHI();
}

IMPLEMENT_TYPE_LAYOUT(FXLineVertexFactoryShaderParameters);
IMPLEMENT_VERTEX_FACTORY_PARAMETER_TYPE(FXLineVertexFactory, SF_Vertex, FXLineVertexFactoryShaderParameters);
IMPLEMENT_VERTEX_FACTORY_TYPE(FXLineVertexFactory, "/XLine/Shaders/XLineVertexFactory.ush",
	  EVertexFactoryFlags::UsedWithMaterials
	| EVertexFactoryFlags::SupportsPositionOnly
	| EVertexFactoryFlags::SupportsCachingMeshDrawCommands);