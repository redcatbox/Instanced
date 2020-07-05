// redbox, 2020

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/SplineComponent.h"
#include "Components/Operations/IPOperationTransformMultiply.h"
#include "Components/Operations/IPOperationSplinePlacement.h"
#include "Components/Operations/IPOperationRandomTransform.h"
#include "IPSplinePlacementActor.generated.h"

UCLASS()
class INSTANCEDPLUGIN_API AIPSplinePlacementActor : public AIPInstancedHISMActor
{
	GENERATED_BODY()

public:
	AIPSplinePlacementActor();
	virtual void OnConstruction(const FTransform& Transform) override;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Components)
		USplineComponent* SplineComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
		UIPOperationTransformMultiply* IPOperationTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
		UIPOperationSplinePlacement* IPOperationSplinePlacement;

	UPROPERTY(VisibleDefaultsOnly, Category = Operations)
		UIPOperationRandomTransform* IPOperationRandomTransform;
#endif
};
