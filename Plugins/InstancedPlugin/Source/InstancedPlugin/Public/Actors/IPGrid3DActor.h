// redbox, 2020

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/Operations/IPOperationTransformMultiply.h"
#include "Components/Operations/IPOperationGrid3D.h"
#include "Components/Operations/IPOperationRandomTransform.h"
#include "IPGrid3DActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPGrid3DActor : public AIPInstancedHISMActor
{
	GENERATED_BODY()

public:
	AIPGrid3DActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
		UIPOperationTransformMultiply* IPOperationTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
		UIPOperationGrid3D* IPOperationGrid3D;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
		UIPOperationRandomTransform* IPOperationRandomTransform;
#endif
};
