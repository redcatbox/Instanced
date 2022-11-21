// redbox, 2022

#pragma once

#include "IPInstancedISMActor.h"
#include "Components/Operations/IPOperationTransformMultiply.h"
#include "Components/Operations/IPOperationRandomSphere.h"
#include "Components/Operations/IPOperationRandomTransform.h"
#include "Components/Operations/IPOperationAlignFromPoint.h"
#include "IPRandomSphereAlignedActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPRandomSphereAlignedActor : public AIPInstancedISMActor
{
	GENERATED_BODY()

public:
	AIPRandomSphereAlignedActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationTransformMultiply* IPOperationTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationRandomSphere* IPOperationRandomSphere;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationAlignFromPoint* IPOperationAlignFromPoint;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationRandomTransform* IPOperationRandomTransform;
#endif
};
