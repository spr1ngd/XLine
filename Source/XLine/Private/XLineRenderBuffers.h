#pragma once

struct FXLineBatchElementUserData
{
	FRHIShaderResourceView* PositionBuffer;
	uint32 VertexNums;
};

class FXLineVertexFactory : public FLocalVertexFactory
{
	DECLARE_VERTEX_FACTORY_TYPE(FXLineVertexFactory);

public:
	FXLineVertexFactory(ERHIFeatureLevel::Type InFeatureLevel);

	void InitVertexFactory( const FStaticMeshLODResources* LODResources );
	static bool ShouldCompilePermutation(const FVertexFactoryShaderPermutationParameters& Parameters);
	static void ModifyCompilationEnvironment( const FVertexFactoryShaderPermutationParameters& Parameters, FShaderCompilerEnvironment& OutEnvironment );
	
private:

	virtual void InitRHI() override;
	virtual void ReleaseRHI() override;
};