#pragma once
#include "CoreMinimal.h"
#include "XLineActor.generated.h"

UCLASS(Blueprintable, BlueprintType)
class AXLineActor : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<class UXLineComponent> XLineComponent;

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

	UFUNCTION()
	void SetPoints(const TArray<FVector>& Points);

	virtual void PostLoad() override;

	static FName XLineComponentName;
};
