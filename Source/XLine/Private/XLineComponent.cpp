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

	if (CheckPSOPrecachingAndBoostPriority() && GetPSOPrecacheProxyCreationStrategy() == EPSOPrecacheProxyCreationStrategy::DelayUntilPSOPrecached)
	{
		UE_LOG(LogStaticMesh, Verbose, TEXT("Skipping CreateSceneProxy for StaticMeshComponent %s (Static mesh component PSOs are still compiling)"), *GetFullName());
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
	const int32 LODNum = 1;
	FStaticMeshRenderData* RenderData = new FStaticMeshRenderData();
	RenderData->AllocateLODResources(LODNum);
	FStaticMeshLODResources& LOD = RenderData->LODResources[0];
	// TODO: pre-process all points data , write data into different sections
	// LOD.Sections
	UStaticMesh* StaticMesh = NewObject<UStaticMesh>(this);
	StaticMesh->SetRenderData(TUniquePtr<FStaticMeshRenderData>(RenderData));
	this->SetStaticMesh(StaticMesh);
}

