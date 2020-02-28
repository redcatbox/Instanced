// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPOperationTransformBase.h"
#include "IPOperationTransformRemove.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationTransformRemove : public UIPOperationTransformBase
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif
};