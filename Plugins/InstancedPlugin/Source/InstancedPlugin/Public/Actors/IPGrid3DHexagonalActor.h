// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/Operations/IPOperationTransformMultiply.h"
#include "Components/Operations/IPOperationGrid3DHexagonal.h"
#include "Components/Operations/IPOperationRandomTransform.h"
#include "IPGrid3DHexagonalActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPGrid3DHexagonalActor : public AIPInstancedHISMActor
{
	GENERATED_BODY()

public:
	AIPGrid3DHexagonalActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = "Operations")
		UIPOperationTransformMultiply* IPOperationTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = "Operations")
		UIPOperationGrid3DHexagonal* IPOperationGrid3DHexagonal;

	UPROPERTY(VisibleDefaultsOnly, Category = "Operations")
		UIPOperationRandomTransform* IPOperationRandomTransform;
#endif
};
