// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPCircle3DAlignedActor.h"

AIPCircle3DAlignedActor::AIPCircle3DAlignedActor()
{
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(RootComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureCircle3D = CreateDefaultSubobject<UIPProcedureCircle3D>(TEXT("IPProcedureCircle3D"));
	IPProcedureCircle3D->SetupAttachment(RootComponent);
	IPProcedureCircle3D->Mobility = EComponentMobility::Static;
	IPProcedureCircle3D->ExecutionOrder = 1;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(RootComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->ExecutionOrder = 2;

	IPProcedureAlignFromAxis = CreateDefaultSubobject<UIPProcedureAlignFromAxis>(TEXT("IPProcedureAlignFromAxis"));
	IPProcedureAlignFromAxis->SetupAttachment(RootComponent);
	IPProcedureAlignFromAxis->Mobility = EComponentMobility::Static;
	IPProcedureAlignFromAxis->ExecutionOrder = 3;

	bInstancesNumEditCondition = false;
#endif
}

#if WITH_EDITOR
void AIPCircle3DAlignedActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	bInstancesNumEditCondition = false;
	InstancesNum = IPProcedureCircle3D->InstancesNum3D.X * IPProcedureCircle3D->InstancesNum3D.Y * IPProcedureCircle3D->InstancesNum3D.Z;

	RunGeneration();
}
#endif