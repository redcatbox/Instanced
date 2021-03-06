// redbox, 2021

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/Operations/IPOperationTransformMultiply.h"
#include "Components/Operations/IPOperationSpiral.h"
#include "Components/Operations/IPOperationRandomTransform.h"
#include "IPSpiralActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPSpiralActor : public AIPInstancedHISMActor
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
