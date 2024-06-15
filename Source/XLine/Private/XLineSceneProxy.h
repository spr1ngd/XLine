#pragma once

class UXLineComponent;

class FXLineSceneProxy : public FPrimitiveSceneProxy
{
public:

	FXLineSceneProxy(UXLineComponent* PrimitiveComponent);
	virtual ~FXLineSceneProxy();
};
