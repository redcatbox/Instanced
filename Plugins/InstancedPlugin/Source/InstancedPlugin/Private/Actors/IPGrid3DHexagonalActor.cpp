// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPGrid3DHexagonalActor.h"

AIPGrid3DHexagonalActor::AIPGrid3DHexagonalActor()
{
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(RootComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureGrid3DHexagonal = CreateDefaultSubobject<UIPProcedureGrid3DHexagonal>(TEXT("IPProcedureGrid3DHexagonal"));
	IPProcedureGrid3DHexagonal->SetupAttachment(RootComponent);
	IPProcedureGrid3DHexagonal->Mobility = EComponentMobility::Static;
	IPProcedureGrid3DHexagonal->ExecutionOrder = 1;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(RootComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->ExecutionOrder = 2;

	bInstancesNumEditCondition = false;
#endif
}

#if WITH_EDITOR
void AIPGrid3DHexagonalActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	bInstancesNumEditCondition = false;
	InstancesNum = IPProcedureGrid3DHexagonal->InstancesNum3D.X * IPProcedureGrid3DHexagonal->InstancesNum3D.Y * IPProcedureGrid3DHexagonal->InstancesNum3D.Z;

	RunGeneration();
}
#endif