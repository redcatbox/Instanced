// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPProcedureGrid3DBase.h"
#include "IPProcedureGrid3D.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureGrid3D : public UIPProcedureGrid3DBase
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif
};