#include "XLineComponent.h"
#include "XLineSceneProxy.h"

FPrimitiveSceneProxy* UXLineComponent::CreateSceneProxy()
{
	if (GetStaticMesh() == nullptr)
	{
		UE_LOG(LogStaticMesh, Verbose, TEXT("Skipping CreateSceneProxy for StaticMeshComponent %s (StaticMesh is null)"), *GetFullName());
		return nullptr;
	}

	// Prevent accessing the RenderData during async compilation. The RenderState will be recreated when compilation finishes.
	if (GetStaticMesh()->IsCompiling())
	{
		UE_LOG(LogStaticMesh, Verbose, TEXT("Skipping CreateSceneProxy for StaticMeshComponent %s (StaticMesh is not ready)"), *GetFullName());
		return nullptr;
	}

	if (GetStaticMesh()->GetRenderData() == nullptr)
	{
		UE_LOG(LogStaticMesh, Verbose, TEXT("Skipping CreateSceneProxy for StaticMeshComponent %s (RenderData is null)"), *GetFullName());
		return nullptr;
	}

	if (!GetStaticMesh()->GetRenderData()->IsInitialized())
	{
		UE_LOG(LogStaticMesh, Verbose, TEXT("Skipping CreateSceneProxy for StaticMeshComponent %s (RenderData is not initialized)"), *GetFullName());
		return nullptr;
	}
	
	const FStaticMeshLODResourcesArray& LODResources = GetStaticMesh()->GetRenderData()->LODResources;
	if (LODResources.Num() == 0	|| LODResources[0].VertexBuffers.StaticMeshVertexBuffer.GetNumVertices() == 0)
	{
		UE_LOG(LogStaticMesh, Verbose, TEXT("Skipping CreateSceneProxy for StaticMeshComponent %s (LOD problems)"), *GetFullName());
		return nullptr;
	}

	return new FXLineSceneProxy(this);
}

void UXLineComponent::SetPoints(const TArray<FVector>& Points)
{
	TArray<FStaticMeshBuildVertex> StaticMeshBuildVertices;
	StaticMeshBuildVertices.SetNumUninitialized(Points.Num() * 2);
	TArray<uint32> StaticMeshIndices;
	StaticMeshIndices.SetNumZeroed((Points.Num() - 1) * 4);
	
	// generate x-line vertices
	{
		for( int32 Idx = 0; Idx < Points.Num(); Idx++ )
		{
			FStaticMeshBuildVertex Vertex;
			Vertex.Position = FVector3f(Points[Idx]);
			// todo: other vertex datas
			StaticMeshBuildVertices[Idx * 2] = Vertex;
			StaticMeshBuildVertices[Idx * 2 + 1] = MoveTemp(Vertex);
		}

		// vertex layout
		// 0 --- 2
		// |  x  |
		// 1 --- 3
		for( int32 Idx = 0; Idx < Points.Num() - 1; Idx++ )
		{
			const int32 BaseIndex = Idx * 6;
			const int32 BaseVertexIndex = Idx * 2;
			StaticMeshIndices[BaseIndex + 0] = BaseVertexIndex + 0;
			StaticMeshIndices[BaseIndex + 1] = BaseVertexIndex + 1;
			StaticMeshIndices[BaseIndex + 2] = BaseVertexIndex + 3;
			StaticMeshIndices[BaseIndex + 3] = BaseVertexIndex + 3;
            StaticMeshIndices[BaseIndex + 4] = BaseVertexIndex + 2;
            StaticMeshIndices[BaseIndex + 5] = BaseVertexIndex + 0;
		}
	}
	
	const int32 LODNum = 1;
	FStaticMeshRenderData* RenderData = new FStaticMeshRenderData();
	RenderData->AllocateLODResources(LODNum);
	FStaticMeshLODResources& LOD = RenderData->LODResources[0];
	LOD.VertexBuffers.StaticMeshVertexBuffer.SetUseFullPrecisionUVs(true);
	LOD.VertexBuffers.PositionVertexBuffer.Init(StaticMeshBuildVertices, false);
	const int32 InNumTexCoords = 1;
	LOD.VertexBuffers.StaticMeshVertexBuffer.Init(StaticMeshBuildVertices, InNumTexCoords, false);

	FStaticMeshSectionArray& Sections = LOD.Sections;
    FStaticMeshSection& Section = Sections.AddDefaulted_GetRef();
	Section.NumTriangles = StaticMeshIndices.Num() / 3;
	Section.FirstIndex = 0;
	Section.MinVertexIndex = 0;
	Section.MaxVertexIndex = StaticMeshBuildVertices.Num() - 1;
	Section.bEnableCollision = false;
	Section.bCastShadow = false;
	Section.MaterialIndex = 0;
	
	UStaticMesh* NewStaticMesh = NewObject<UStaticMesh>(this);
	NewStaticMesh->SetRenderData(TUniquePtr<FStaticMeshRenderData>(RenderData));
	this->SetStaticMesh(NewStaticMesh);
}

