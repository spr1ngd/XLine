#include "XLine.h"

void AXLine::BeginPlay()
{
	Super::BeginPlay();
}

void AXLine::BeginDestroy()
{
	Super::BeginDestroy();
}

void AXLine::SetPoints(const TArray<FVector>& Points)
{
	// 每个位置多补一个点
}
