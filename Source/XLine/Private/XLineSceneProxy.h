#pragma once
#include "XLineRenderBuffers.h"

class UXLineComponent;

class FXLineSceneProxy : public FPrimitiveSceneProxy
{
public:

	FXLineSceneProxy(UXLineComponent* PrimitiveComponent, ERHIFeatureLevel::Type InFeatureLevel);
	virtual ~FXLineSceneProxy();

	virtual void DrawStaticElements(FStaticPrimitiveDrawInterface* PDI) override;
	virtual FPrimitiveViewRelevance GetViewRelevance(const FSceneView* View) const override;

	virtual SIZE_T GetTypeHash() const override;
	virtual uint32 GetMemoryFootprint() const override;

protected:

	
	virtual void CreateRenderThreadResources() override;
	virtual void DestroyRenderThreadResources() override;

private:

	

	TArray<FXLineBatchElementUserData*> UserDatas;
	FStaticMeshRenderData* RenderData;
	UMaterialInterface* Material; 
	FXLineVertexFactory XLineVertexFactory;
};
