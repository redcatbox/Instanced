// redbox, 2021

#pragma once

#include "IPOperationTransformBase.h"
#include "IPOperationTransformMultiply.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationTransformMultiply : public UIPOperationTransformBase
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif
};
