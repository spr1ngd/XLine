#pragma once

class UXLineComponent;

class FXLineSceneProxy : public FPrimitiveSceneProxy
{
public:

	FXLineSceneProxy(UXLineComponent* PrimitiveComponent);
	virtual ~FXLineSceneProxy();

	virtual void GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const override;
	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;
};
