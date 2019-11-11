// Fill out your copyright notice in the Description page of Project Settings.

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

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly)
		USplineComponent* SplineComponent;

	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureTransformMultiply* IPProcedureTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureSplinePlacement* IPProcedureSplinePlacement;

	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureRandomTransform* IPProcedureRandomTransform;
#endif
};
