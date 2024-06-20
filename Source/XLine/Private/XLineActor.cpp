#include "XLineActor.h"
#include "XLineComponent.h"

#define LOCTEXT_NAMESPACE "XLineActor"
FName AXLineActor::XLineComponentName(TEXT("XLineComponent0"));

AXLineActor::AXLineActor( const FObjectInitializer& ObjectInitializer ) : Super(ObjectInitializer)
{
	SetCanBeDamaged(false);

	XLineComponent = CreateDefaultSubobject<UXLineComponent>(XLineComponentName);
	XLineComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	XLineComponent->Mobility = EComponentMobility::Movable;
	XLineComponent->SetGenerateOverlapEvents(false);
	XLineComponent->bUseDefaultCollision = false;
	XLineComponent->RegisterComponent();

	RootComponent = XLineComponent;
	bCanBeInCluster = (GetClass() == AXLineActor::StaticClass());
}

void AXLineActor::BeginPlay()
{
	Super::BeginPlay();
}

void AXLineActor::BeginDestroy()
{
	Super::BeginDestroy();
}

void AXLineActor::SetPoints(const TArray<FVector>& Points)
{
	// 每个位置多补一个点
}

void AXLineActor::PostLoad()
{
	Super::PostLoad();
}
