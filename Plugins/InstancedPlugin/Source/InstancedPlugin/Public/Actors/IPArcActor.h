// redbox, 2022

#pragma once

#include "IPInstancedISMActor.h"
#include "Components/Operations/IPOperationTransformMultiply.h"
#include "Components/Operations/IPOperationArc.h"
#include "Components/Operations/IPOperationRandomTransform.h"
#include "IPArcActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPArcActor : public AIPInstancedISMActor
{
	GENERATED_BODY()

public:
	AIPArcActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationTransformMultiply* IPOperationTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationArc* IPOperationArc;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationRandomTransform* IPOperationRandomTransform;
#endif
};
