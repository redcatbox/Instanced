// redbox, 2020

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/Operations/IPOperationTransformMultiply.h"
#include "Components/Operations/IPOperationRandomBox.h"
#include "Components/Operations/IPOperationAlignByDirection.h"
#include "Components/Operations/IPOperationRandomTransform.h"
#include "IPRandomBoxAlignedActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPRandomBoxAlignedActor : public AIPInstancedHISMActor
{
	GENERATED_BODY()

public:
	AIPRandomBoxAlignedActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
		UIPOperationTransformMultiply* IPOperationTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
		UIPOperationRandomBox* IPOperationRandomBox;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
		UIPOperationAlignByDirection* IPOperationAlignByDirection;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
		UIPOperationRandomTransform* IPOperationRandomTransform;
#endif
};
