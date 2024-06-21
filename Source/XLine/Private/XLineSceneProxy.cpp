#include "XLineSceneProxy.h"
#include "XLineComponent.h"
#include "MaterialDomain.h"

FXLineSceneProxy::FXLineSceneProxy(UXLineComponent* PrimitiveComponent, ERHIFeatureLevel::Type InFeatureLevel)
	: FPrimitiveSceneProxy(PrimitiveComponent)
	, RenderData(PrimitiveComponent->GetStaticMesh()->GetRenderData())
	, XLineVertexFactory(InFeatureLevel)
	, Material(PrimitiveComponent->Material)
{
	
}

FXLineSceneProxy::~FXLineSceneProxy()
{
	
}

void FXLineSceneProxy::DrawStaticElements(FStaticPrimitiveDrawInterface* PDI)
{
	checkSlow(IsInParallelRenderingThread());
	if (!HasViewDependentDPG())
	{
		const int32 ForceLODIndex = 0;
		const FStaticMeshLODResources& LODResource = RenderData->LODResources[ForceLODIndex];
		const FLocalVertexFactory& VertexFactory = XLineVertexFactory;

		// clear 
		{
			for( int32 Idx = 0; Idx < UserDatas.Num(); Idx++ )
			{
				
			}	
		}
		
		const int32 SectionNums = LODResource.Sections.Num();

		
		
		for( int32 SectionIndex = 0; SectionIndex < SectionNums; SectionIndex++ )
		{
			const FStaticMeshSection& Section = LODResource.Sections[SectionIndex];
			auto* UserData = UserDatas[SectionIndex];
			if( Section.NumTriangles == 0 )
			{
				continue;
			}
			FMeshBatch MeshBatch;
			MeshBatch.LODIndex = 0;
			MeshBatch.Type = PT_TriangleList;
			// create mesh batch element
			{
				FMeshBatchElement& MeshBatchElement = MeshBatch.Elements[0];
				UserData->PositionBuffer = VertexFactory.GetPositionsSRV();
				UserData->VertexNums     = Section.MaxVertexIndex + 1;
				MeshBatchElement.UserData = UserData;
				MeshBatchElement.FirstIndex = Section.FirstIndex;
				MeshBatchElement.MaxVertexIndex = Section.MaxVertexIndex;
				MeshBatchElement.IndexBuffer = &LODResource.IndexBuffer;
				MeshBatchElement.NumPrimitives = Section.NumTriangles;
				MeshBatchElement.PrimitiveUniformBuffer = GetUniformBuffer();
			}
			// material render proxy
			{
				MeshBatch.MaterialRenderProxy = Material->GetRenderProxy() == nullptr
					? UMaterial::GetDefaultMaterial(MD_Surface)->GetRenderProxy()
					: Material->GetRenderProxy();
			}
			// MeshBatch.ReverseCulling = IsLocalToWorldDeterminantNegative();
			// MeshBatch.DepthPriorityGroup = SDPG_World;
			// MeshBatch.bCanApplyViewModeOverrides = false;
			// MeshBatch.bDisableBackfaceCulling = false;
			// MeshBatch.CastShadow = false;
			// MeshBatch.bUseAsOccluder = false;
			// MeshBatch.bWireframe = false;
			
			MeshBatch.VertexFactory = &VertexFactory;
			PDI->DrawMesh(MeshBatch, FLT_MAX);
		}
	}
}

FPrimitiveViewRelevance FXLineSceneProxy::GetViewRelevance(const FSceneView* View) const
{
	checkSlow(IsInParallelRenderingThread());
	FPrimitiveViewRelevance Result;
	Result.bDrawRelevance = IsShown(View) && View->Family->EngineShowFlags.StaticMeshes;
	Result.bStaticRelevance = true;
	Result.bDynamicRelevance = false;
	Result.bRenderCustomDepth = ShouldRenderCustomDepth();
	Result.bRenderInMainPass = ShouldRenderInMainPass();
	Result.bRenderInDepthPass = ShouldRenderInDepthPass();
	Result.bUsesLightingChannels = false;
	Result.bTranslucentSelfShadow = false;
	Result.bShadowRelevance = false;
	Result.bVelocityRelevance = DrawsVelocity() && Result.bOpaque && Result.bRenderInMainPass;
	if (!View->Family->EngineShowFlags.Materials)
	{
		Result.bOpaque = true;
	}
	return Result;
}

SIZE_T FXLineSceneProxy::GetTypeHash() const
{
	static size_t UniquePointer;
    return reinterpret_cast<size_t>(&UniquePointer);
}

uint32 FXLineSceneProxy::GetMemoryFootprint() const
{
	return( sizeof( *this ) + GetAllocatedSize() );
}

void FXLineSceneProxy::CreateRenderThreadResources()
{
	const int32 ForceLODIndex = 0;
    const FStaticMeshLODResources& LODResource = RenderData->LODResources[ForceLODIndex];
	XLineVertexFactory.InitVertexFactory(&LODResource);
	XLineVertexFactory.InitResource();
}

void FXLineSceneProxy::DestroyRenderThreadResources()
{
	XLineVertexFactory.ReleaseResource();
}
