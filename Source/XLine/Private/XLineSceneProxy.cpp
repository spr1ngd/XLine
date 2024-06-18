#include "XLineSceneProxy.h"
#include "XLineComponent.h"
#include "XLineModule.h"

FXLineSceneProxy::FXLineSceneProxy(UXLineComponent* PrimitiveComponent)
	: FPrimitiveSceneProxy(PrimitiveComponent)
	, RenderData(PrimitiveComponent->GetStaticMesh()->GetRenderData())
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
		const FStaticMeshVertexFactories& XLineVFs = RenderData->LODVertexFactories[ForceLODIndex];
		const FLocalVertexFactory& VertexFactory = XLineVFs.VertexFactory;
		
		const int32 SectionNums = LODResource.Sections.Num();
		for( int32 SectionIndex = 0; SectionIndex < SectionNums; SectionIndex++ )
		{
			const FStaticMeshSection& Section = LODResource.Sections[SectionIndex];
			if( Section.NumTriangles == 0 )
			{
				UE_LOG(LogXLine, Warning, TEXT("Section %d triangles number is zero "), SectionIndex);
				continue;
			}
			FMeshBatch MeshBatch;
			MeshBatch.Type = PT_TriangleList;
			// create mesh batch element
			{
				FMeshBatchElement& MeshBatchElement = MeshBatch.Elements[0];
#if WITH_EDITORONLY_DATA
				
#endif
				MeshBatchElement.UserData = VertexFactory.GetPositionsSRV();
				MeshBatchElement.FirstIndex = Section.FirstIndex;
				MeshBatchElement.IndexBuffer = &LODResource.IndexBuffer;
				MeshBatchElement.NumPrimitives = Section.NumTriangles;
			}
			MeshBatch.VertexFactory = &XLineVFs.VertexFactory;
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
