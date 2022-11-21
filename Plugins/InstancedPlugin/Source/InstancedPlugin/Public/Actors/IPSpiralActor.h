// redbox, 2022

#pragma once

#include "IPInstancedISMActor.h"
#include "Components/Operations/IPOperationTransformMultiply.h"
#include "Components/Operations/IPOperationSpiral.h"
#include "Components/Operations/IPOperationRandomTransform.h"
#include "IPSpiralActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPSpiralActor : public AIPInstancedISMActor
{
	GENERATED_BODY()

public:
	AIPSpiralActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationTransformMultiply* IPOperationTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationSpiral* IPOperationSpiral;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationRandomTransform* IPOperationRandomTransform;
#endif
};
