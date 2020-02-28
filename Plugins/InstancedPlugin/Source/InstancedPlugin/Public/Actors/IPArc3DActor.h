// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/Operations/IPOperationTransformMultiply.h"
#include "Components/Operations/IPOperationArc3D.h"
#include "Components/Operations/IPOperationRandomTransform.h"
#include "IPArc3DActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPArc3DActor : public AIPInstancedHISMActor
{
	GENERATED_BODY()

public:
	AIPArc3DActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
		UIPOperationTransformMultiply* IPOperationTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
		UIPOperationArc3D* IPOperationArc3D;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
		UIPOperationRandomTransform* IPOperationRandomTransform;
#endif
};