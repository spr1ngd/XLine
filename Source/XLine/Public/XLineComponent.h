﻿#pragma once
#include "CoreMinimal.h"
#include "XLineComponent.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UXLineComponent : public UStaticMeshComponent
{
	GENERATED_UCLASS_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FVector> MetaPoints;

	virtual ~UXLineComponent();
	
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

	UFUNCTION()
	void SetPoints(const TArray<FVector>& Points);

	void UpdateLine();

	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:

	void InitResources();
};