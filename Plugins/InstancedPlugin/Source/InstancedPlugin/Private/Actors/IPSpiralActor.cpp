// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPSpiralActor.h"

AIPSpiralActor::AIPSpiralActor()
{
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(RootComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureSpiral = CreateDefaultSubobject<UIPProcedureSpiral>(TEXT("IPProcedureSpiral"));
	IPProcedureSpiral->SetupAttachment(RootComponent);
	IPProcedureSpiral->Mobility = EComponentMobility::Static;
	IPProcedureSpiral->ExecutionOrder = 1;
	IPProcedureSpiral->bUseInstancesNum = true;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(RootComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->ExecutionOrder = 2;

	InstancesNum = 10;
#endif
}

#if WITH_EDITOR
void AIPSpiralActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	RunGeneration();
}
#endif