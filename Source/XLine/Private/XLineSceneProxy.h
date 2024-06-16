#pragma once

class UXLineComponent;

class FXLineSceneProxy : public FPrimitiveSceneProxy
{
public:

	FXLineSceneProxy(UXLineComponent* PrimitiveComponent);
	virtual ~FXLineSceneProxy();

	virtual void DrawStaticElements(FStaticPrimitiveDrawInterface* PDI) override;
	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;

	virtual SIZE_T GetTypeHash() const override;
	virtual uint32 GetMemoryFootprint() const override;

private:

	FStaticMeshRenderData* RenderData;
};
