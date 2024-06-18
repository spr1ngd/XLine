#pragma once

struct FXLineBatchElementUserData
{
	FRHIShaderResourceView* PositionBuffer;	
};

class FXLineVertexFactory : public FLocalVertexFactory
{
	DECLARE_VERTEX_FACTORY_TYPE(FXLineVertexFactory);

public:
	FXLineVertexFactory(ERHIFeatureLevel::Type InFeatureLevel, const FPositionVertexBuffer* PositionVertexBuffer);

	static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Paramters);
	
private:

	virtual void InitRHI() override;
	virtual void ReleaseRHI() override;
};