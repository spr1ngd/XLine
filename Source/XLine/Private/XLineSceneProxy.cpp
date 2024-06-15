#include "XLineSceneProxy.h"
#include "XLineComponent.h"

FXLineSceneProxy::FXLineSceneProxy(UXLineComponent* PrimitiveComponent) : FPrimitiveSceneProxy(PrimitiveComponent)
{
	
}

FXLineSceneProxy::~FXLineSceneProxy()
{
	
}

void FXLineSceneProxy::GetDynamicMeshElements(const TArray<const FSceneView*>& Views, const FSceneViewFamily& ViewFamily, uint32 VisibilityMap, FMeshElementCollector& Collector) const
{
	FPrimitiveSceneProxy::GetDynamicMeshElements(Views, ViewFamily, VisibilityMap, Collector);
}

FPrimitiveViewRelevance FXLineSceneProxy::GetViewRelevance(const FSceneView* View) const
{
	return FPrimitiveSceneProxy::GetViewRelevance(View);
}
