#include "XLineComponent.h"
#include "XLineModule.h"
#include "XLineSceneProxy.h"

UXLineComponent::UXLineComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
}

UXLineComponent::~UXLineComponent()
{
	
}

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
	this->MetaPoints = Points;
	this->UpdateLine();
}

void UXLineComponent::UpdateLine()
{
	if( MetaPoints.Num() < 2 )
	{
		UE_LOG(LogXLine, Warning, TEXT("Points number of XLine could not less than 2."));
		return;
	}
	
	TArray<FStaticMeshBuildVertex> StaticMeshBuildVertices;
	StaticMeshBuildVertices.SetNumUninitialized(MetaPoints.Num() * 2);
	TArray<uint32> StaticMeshIndices;
	StaticMeshIndices.SetNumZeroed((MetaPoints.Num() - 1) * 6);
	
	// generate x-line vertices
	{
		for( int32 Idx = 0; Idx < MetaPoints.Num(); Idx++ )
		{
			FStaticMeshBuildVertex Vertex;
			Vertex.Position = FVector3f(MetaPoints[Idx]);
			// todo: other vertex datas
			StaticMeshBuildVertices[Idx * 2] = Vertex;
			StaticMeshBuildVertices[Idx * 2 + 1] = MoveTemp(Vertex);
		}

		// vertex layout
		// 0 --- 2
		// |  x  |
		// 1 --- 3
		for( int32 Idx = 0; Idx < MetaPoints.Num() - 1; Idx++ )
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

	UStaticMesh* LineMesh;
	{
		LineMesh = NewObject<UStaticMesh>(this);
		LineMesh->SetFlags(RF_Transient | RF_DuplicateTransient);
		LineMesh->NaniteSettings.bEnabled = false;
		LineMesh->SetRenderData(TUniquePtr<FStaticMeshRenderData>(RenderData));
		UMaterialInterface* Material = nullptr;
		LineMesh->AddMaterial(Material);
		LineMesh->InitResources();
		LineMesh->CalculateExtendedBounds();
		LineMesh->GetRenderData()->ScreenSize[0].Default = 1.0; // what's meaning ?
	}
	
	this->SetStaticMesh(LineMesh);
}

void UXLineComponent::PostLoad()
{
	Super::PostLoad();

	InitResources();
}

void UXLineComponent::InitResources()
{
	
}

#if WITH_EDITOR

void UXLineComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FProperty* PropertyThatChanged = PropertyChangedEvent.Property;
	if( PropertyThatChanged )
	{
		auto PropertyName = PropertyThatChanged->GetName();
		if( PropertyName == TEXT("MetaPoints") )
		{
			this->UpdateLine();
		}
	}
	Super::PostEditChangeProperty(PropertyChangedEvent);
}

#endif

