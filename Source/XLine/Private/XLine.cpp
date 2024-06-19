#include "XLine.h"
#include "XLineComponent.h"

#define LOCTEXT_NAMESPACE "XLineActor"
FName AXLine::XLineComponentName(TEXT("XLineComponent0"));

AXLine::AXLine( const FObjectInitializer& ObjectInitializer ) : Super(ObjectInitializer)
{
	SetCanBeDamaged(false);

	XLineComponent = CreateDefaultSubobject<UXLineComponent>(XLineComponentName);
	XLineComponent->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	XLineComponent->Mobility = EComponentMobility::Movable;
	XLineComponent->SetGenerateOverlapEvents(false);
	XLineComponent->bUseDefaultCollision = false;
	XLineComponent->RegisterComponent();

	RootComponent = XLineComponent;
	bCanBeInCluster = (GetClass() == AXLine::StaticClass());
}

void AXLine::BeginPlay()
{
	Super::BeginPlay();
}

void AXLine::BeginDestroy()
{
	Super::BeginDestroy();
}

void AXLine::SetPoints(const TArray<FVector>& Points)
{
	// 每个位置多补一个点
}
