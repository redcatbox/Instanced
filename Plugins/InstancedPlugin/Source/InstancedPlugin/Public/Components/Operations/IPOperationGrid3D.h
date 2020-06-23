// redbox, 2020

#pragma once

#include "IPOperationGrid3DBase.h"
#include "IPOperationGrid3D.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationGrid3D : public UIPOperationGrid3DBase
{
	GENERATED_BODY()

public:
	UIPOperationGrid3D();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif
};
