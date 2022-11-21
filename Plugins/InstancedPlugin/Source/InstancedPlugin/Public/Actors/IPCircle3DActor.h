// redbox, 2022

#pragma once

#include "IPInstancedISMActor.h"
#include "Components/Operations/IPOperationTransformMultiply.h"
#include "Components/Operations/IPOperationCircle3D.h"
#include "Components/Operations/IPOperationRandomTransform.h"
#include "IPCircle3DActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPCircle3DActor : public AIPInstancedISMActor
{
	GENERATED_BODY()

public:
	AIPCircle3DActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationTransformMultiply* IPOperationTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationCircle3D* IPOperationCircle3D;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationRandomTransform* IPOperationRandomTransform;
#endif
};
