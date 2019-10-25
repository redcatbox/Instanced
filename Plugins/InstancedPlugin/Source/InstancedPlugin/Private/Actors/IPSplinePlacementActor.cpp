// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPSplinePlacementActor.h"

AIPSplinePlacementActor::AIPSplinePlacementActor()
{
#if WITH_EDITORONLY_DATA
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
	SplineComponent->Mobility = EComponentMobility::Static;
	SplineComponent->bIsEditorOnly = true;

	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(HISMComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->bIsEditorOnly = true;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureSplinePlacement = CreateDefaultSubobject<UIPProcedureSplinePlacement>(TEXT("IPProcedureSplinePlacement"));
	IPProcedureSplinePlacement->SetupAttachment(HISMComponent);
	IPProcedureSplinePlacement->Mobility = EComponentMobility::Static;
	IPProcedureSplinePlacement->SplineComponent = SplineComponent;
	IPProcedureSplinePlacement->bIsEditorOnly = true;
	IPProcedureSplinePlacement->ExecutionOrder = 1;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(HISMComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bIsEditorOnly = true;
	IPProcedureRandomTransform->ExecutionOrder = 2;
#endif
}