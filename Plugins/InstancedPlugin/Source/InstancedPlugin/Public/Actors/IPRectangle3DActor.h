// redbox, 2022

#pragma once

#include "IPInstancedISMActor.h"
#include "Components/Operations/IPOperationTransformMultiply.h"
#include "Components/Operations/IPOperationRectangle3D.h"
#include "Components/Operations/IPOperationRandomTransform.h"
#include "IPRectangle3DActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPRectangle3DActor : public AIPInstancedISMActor
{
	GENERATED_BODY()

public:
	AIPRectangle3DActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationTransformMultiply* IPOperationTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationRectangle3D* IPOperationRectangle3D;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
	UIPOperationRandomTransform* IPOperationRandomTransform;
#endif
};
