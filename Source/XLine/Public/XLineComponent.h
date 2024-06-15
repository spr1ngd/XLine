#pragma once
#include "CoreMinimal.h"
#include "XLineComponent.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UXLineComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
};