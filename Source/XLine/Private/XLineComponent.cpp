#include "XLineComponent.h"
#include "..\Public\XLine.h"
#include "XLineSceneProxy.h"

UXLineComponent::UXLineComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);

	{
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultMaterial(TEXT("/XLine/M_XLine"));
		Material = DefaultMaterial.Object;
	}

#if WITH_EDITOR
	{
		MetaPoints.Emplace(FVector3f::ZeroVector);
		MetaPoints.Emplace(FVector3f::ForwardVector * 100.0f);
	}
#endif
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

	return new FXLineSceneProxy(this, GMaxRHIFeatureLevel);
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
	StaticMeshBuildVertices.SetNumUninitialized((MetaPoints.Num() - 1) * 4);
	TArray<uint32> StaticMeshIndices;
	StaticMeshIndices.SetNumZeroed((MetaPoints.Num() - 1) * 6);

	float TotalLength = 0.0f;
	{
		for( int32 Idx = 0; Idx < MetaPoints.Num() - 1; Idx++ )
		{
			float Length = FVector::Dist(MetaPoints[Idx], MetaPoints[Idx + 1]);
			TotalLength += Length;
		}
	}
	
	// generate x-line vertices
	{
		float AccLength = 0.0f;
		for( int32 Idx = 0; Idx < MetaPoints.Num() - 1; Idx++ )
		{
			float StartU = AccLength / TotalLength;
			float EndU = 0.0f;
			float Length = FVector::Dist(MetaPoints[Idx], MetaPoints[Idx + 1]);
			AccLength += Length;
			EndU = AccLength / TotalLength;
			
			FStaticMeshBuildVertex Vertex0;
			Vertex0.Position = FVector3f(MetaPoints[Idx]);
			Vertex0.Color = FColor::White;
			Vertex0.UVs[0] = FVector2f(StartU, 0);
			StaticMeshBuildVertices[Idx * 4] = Vertex0;

			FStaticMeshBuildVertex Vertex1;
			Vertex1.Position = FVector3f(MetaPoints[Idx]);
			Vertex1.Color = FColor::White;
			Vertex1.UVs[0] = FVector2f(StartU, 1);
			StaticMeshBuildVertices[Idx * 4 + 1] = Vertex1;

			FStaticMeshBuildVertex Vertex2;
			Vertex2.Color = FColor::White;
			Vertex2.UVs[0] = FVector2f(EndU, 0);
			Vertex2.Position = FVector3f(MetaPoints[Idx + 1]);
			StaticMeshBuildVertices[Idx * 4 + 2] = Vertex2;

			FStaticMeshBuildVertex Vertex3;
            Vertex3.Color = FColor::White;
			Vertex3.UVs[0] = FVector2f(EndU, 1);
            Vertex3.Position = FVector3f(MetaPoints[Idx + 1]);
            StaticMeshBuildVertices[Idx * 4 + 3] = Vertex3;
		}

		// vertex layout
		// 0 --- 2 4 --- 6
		// |  x  | |  x  |
		// 1 --- 3 5 --- 7
		for( int32 Idx = 0; Idx < MetaPoints.Num() - 1; Idx++ )
		{
			const int32 BaseIndex = Idx * 6;
			const int32 BaseVertexIndex = Idx * 4;
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
	LOD.bHasColorVertexData = true;
	LOD.VertexBuffers.ColorVertexBuffer.Init(StaticMeshBuildVertices, false);

	// index buffer
	{
		LOD.IndexBuffer.SetIndices(StaticMeshIndices,
			StaticMeshBuildVertices.Num() >= std::numeric_limits<uint16>::max()
				? EIndexBufferStride::Type::Force32Bit
				: EIndexBufferStride::Type::Force16Bit);
	}

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
		LineMesh->SetRenderData(TUniquePtr<FStaticMeshRenderData>(RenderData));
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
	this->UpdateLine();
}

#if WITH_EDITOR

void UXLineComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FProperty* PropertyThatChanged = PropertyChangedEvent.MemberProperty;
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

