#pragma once
#include "CoreMinimal.h"
#include "XLine.generated.h"

UCLASS(Blueprintable, BlueprintType)
class AXLine : public AActor
{
	GENERATED_BODY()
public:

	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
};
