// redbox, 2020

#pragma once

#include "IPOperationTransformBase.h"
#include "IPOperationTransformReplace.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationTransformReplace : public UIPOperationTransformBase
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif
};