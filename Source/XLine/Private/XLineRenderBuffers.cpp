#include "XLineRenderBuffers.h"
#include "MaterialDomain.h"
#include "MeshDrawShaderBindings.h"
#include "MeshMaterialShader.h"

class FXLineVertexFactoryShaderParameters : public FVertexFactoryShaderParameters
{
	DECLARE_TYPE_LAYOUT(FXLineVertexFactoryShaderParameters, NonVirtual);

public:

	void Bind( const FShaderParameterMap& ParameterMap )
	{
		PositionBuffer.Bind(ParameterMap, TEXT("PositionBuffer"));
		VertexNums.Bind(ParameterMap, TEXT("VertexNums"));
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
		if( UserData )
		{
			if( UserData->PositionBuffer && PositionBuffer.IsBound() )
			{
				ShaderBindings.Add(PositionBuffer, UserData->PositionBuffer);
			}
			if( VertexNums.IsBound() )
			{
				ShaderBindings.Add(VertexNums, UserData->VertexNums);
			}
		}  
	}

private:

	LAYOUT_FIELD(FShaderResourceParameter, PositionBuffer);
	LAYOUT_FIELD(FShaderParameter, VertexNums);
};

FXLineVertexFactory::FXLineVertexFactory(ERHIFeatureLevel::Type InFeatureLevel)
	: FLocalVertexFactory(InFeatureLevel, "FXLineVertexFactory")
{
	
}

void FXLineVertexFactory::InitVertexFactory(const FStaticMeshLODResources* LODResources)
{
	if( IsInRenderingThread() )
    {
    	FLocalVertexFactory::FDataType VertexData;
    	VertexData.PositionComponent = FVertexStreamComponent(
    		&LODResources->VertexBuffers.PositionVertexBuffer,
    		0,
    		LODResources->VertexBuffers.PositionVertexBuffer.GetStride(),
    		VET_Float3,
    		EVertexStreamUsage::Default);
		VertexData.ColorComponent = FVertexStreamComponent(
			&LODResources->VertexBuffers.ColorVertexBuffer,
			0,
			LODResources->VertexBuffers.ColorVertexBuffer.GetStride(),
			VET_Color,
			EVertexStreamUsage::ManualFetch);

		FVertexStreamComponent TexCoord0 = FVertexStreamComponent(
			&LODResources->VertexBuffers.StaticMeshVertexBuffer.TexCoordVertexBuffer,
			0,
			sizeof(FVector2f),
			VET_Float2,
			EVertexStreamUsage::ManualFetch
		);
		VertexData.TextureCoordinates.Emplace(TexCoord0);
		
		SetData(VertexData);
		InitResource();
    }
    else
    {
    	FXLineVertexFactory* VertexFactory = this;
    	ENQUEUE_RENDER_COMMAND(XLineVertexFactoryInit)([VertexFactory, LODResources]( FRHICommandListImmediate& RHICmdList )
    	{
    		VertexFactory->InitVertexFactory(LODResources);
    	});
    }
}

bool FXLineVertexFactory::ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters)
{
	return
		(!Parameters.MaterialParameters.bIsUsedWithInstancedStaticMeshes)
		&& Parameters.MaterialParameters.MaterialDomain == EMaterialDomain::MD_Surface
		|| Parameters.MaterialParameters.bIsDefaultMaterial
		|| Parameters.MaterialParameters.bIsSpecialEngineMaterial;
}

void FXLineVertexFactory::ModifyCompilationEnvironment(const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment)
{
	
}

void FXLineVertexFactory::InitRHI()
{
	// TODO: PositionBuffer 用UserData
	FVertexDeclarationElementList Elements;
	Elements.Add(AccessStreamComponent(Data.PositionComponent, 0));
	Elements.Add(AccessStreamComponent(Data.ColorComponent, 1));
	Elements.Add(AccessStreamComponent(Data.TextureCoordinates[0], 2));
	InitDeclaration(Elements);
}

void FXLineVertexFactory::ReleaseRHI()
{
	FLocalVertexFactory::ReleaseRHI();
}

IMPLEMENT_TYPE_LAYOUT(FXLineVertexFactoryShaderParameters);
IMPLEMENT_VERTEX_FACTORY_PARAMETER_TYPE(FXLineVertexFactory, SF_Vertex, FXLineVertexFactoryShaderParameters);
IMPLEMENT_VERTEX_FACTORY_TYPE(FXLineVertexFactory, "/Plugin/XLine/Private/XLineVertexFactory.ush",
	  EVertexFactoryFlags::UsedWithMaterials
	| EVertexFactoryFlags::SupportsPositionOnly );
