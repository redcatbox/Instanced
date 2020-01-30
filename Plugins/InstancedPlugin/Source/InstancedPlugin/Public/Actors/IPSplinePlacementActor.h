// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/SplineComponent.h"
#include "Components/Procedures/IPProcedureTransformMultiply.h"
#include "Components/Procedures/IPProcedureSplinePlacement.h"
#include "Components/Procedures/IPProcedureRandomTransform.h"
#include "IPSplinePlacementActor.generated.h"

UCLASS(ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPSplinePlacementActor : public AIPInstancedHISMActor
{
	GENERATED_BODY()

public:
	AIPSplinePlacementActor();
	virtual void OnConstruction(const FTransform& Transform) override;

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Components)
		USplineComponent* SplineComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureTransformMultiply* IPProcedureTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureSplinePlacement* IPProcedureSplinePlacement;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureRandomTransform* IPProcedureRandomTransform;
#endif
};
