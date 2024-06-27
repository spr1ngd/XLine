#pragma once
#include "CoreMinimal.h"
#include "XLineComponent.generated.h"

UCLASS(Blueprintable, BlueprintType)
class UXLineComponent : public UStaticMeshComponent
{
	GENERATED_UCLASS_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FVector> MetaPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Width = 1.0f;

	virtual ~UXLineComponent();
	
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;

	UFUNCTION()
	void SetPoints(const TArray<FVector>& Points);

	void UpdateLine();

	virtual void PostLoad() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};