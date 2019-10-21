// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPRectangle3DActor.h"

AIPRectangle3DActor::AIPRectangle3DActor()
{
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(RootComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureRectangle3D = CreateDefaultSubobject<UIPProcedureRectangle3D>(TEXT("IPProcedureRectangle3D"));
	IPProcedureRectangle3D->SetupAttachment(RootComponent);
	IPProcedureRectangle3D->Mobility = EComponentMobility::Static;
	IPProcedureRectangle3D->ExecutionOrder = 1;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(RootComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->ExecutionOrder = 2;

	bInstancesNumEditCondition = false;
#endif
}

#if WITH_EDITOR
void AIPRectangle3DActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	bInstancesNumEditCondition = false;
	InstancesNum = IPProcedureRectangle3D->InstancesNum3D.X * IPProcedureRectangle3D->InstancesNum3D.Y * IPProcedureRectangle3D->InstancesNum3D.Z;

	RunGeneration();
}
#endif