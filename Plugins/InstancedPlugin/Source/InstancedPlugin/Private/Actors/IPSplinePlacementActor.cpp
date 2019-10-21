// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPSplinePlacementActor.h"

AIPSplinePlacementActor::AIPSplinePlacementActor()
{
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
	SplineComponent->Mobility = EComponentMobility::Static;

	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(RootComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureSplinePlacement = CreateDefaultSubobject<UIPProcedureSplinePlacement>(TEXT("IPProcedureSplinePlacement"));
	IPProcedureSplinePlacement->SetupAttachment(RootComponent);
	IPProcedureSplinePlacement->Mobility = EComponentMobility::Static;
	IPProcedureSplinePlacement->SplineComponent = SplineComponent;
	IPProcedureSplinePlacement->ExecutionOrder = 1;
	IPProcedureSplinePlacement->bUseInstancesNum = true;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(RootComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->ExecutionOrder = 2;

	InstancesNum = 10;
#endif
}

#if WITH_EDITOR
void AIPSplinePlacementActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (IPProcedureSplinePlacement->bPlaceBetweenPoints)
	{
		bInstancesNumEditCondition = false;
		InstancesNum = SplineComponent->GetNumberOfSplinePoints() - 1;
	}
	else
		bInstancesNumEditCondition = true;

	RunGeneration();
}
#endif