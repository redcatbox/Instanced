// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPSplinePlacementActor.h"

AIPSplinePlacementActor::AIPSplinePlacementActor()
{
#if WITH_EDITORONLY_DATA
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
	SplineComponent->Mobility = EComponentMobility::Static;
	SplineComponent->bIsEditorOnly = true;

	HISMComponent->SetupAttachment(SplineComponent);

	IPProcedureTransformMultiply = CreateDefaultSubobject<UIPProcedureTransformMultiply>(TEXT("IPProcedureTransformMultiply"));
	IPProcedureTransformMultiply->SetupAttachment(HISMComponent);
	IPProcedureTransformMultiply->Mobility = EComponentMobility::Static;
	IPProcedureTransformMultiply->bIsEditorOnly = true;
	IPProcedureTransformMultiply->ExecutionOrder = 0;
	IPProcedureTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPProcedureSplinePlacement = CreateDefaultSubobject<UIPProcedureSplinePlacement>(TEXT("IPProcedureSplinePlacement"));
	IPProcedureSplinePlacement->SetupAttachment(HISMComponent);
	IPProcedureSplinePlacement->Mobility = EComponentMobility::Static;
	IPProcedureSplinePlacement->bIsEditorOnly = true;
	IPProcedureSplinePlacement->ExecutionOrder = 1;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(HISMComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bIsEditorOnly = true;
	IPProcedureRandomTransform->ExecutionOrder = 2;
#endif
}