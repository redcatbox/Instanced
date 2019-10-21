// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPGrid3DTwoActor.h"

AIPGrid3DTwoActor::AIPGrid3DTwoActor()
{
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(RootComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureGrid3D = CreateDefaultSubobject<UIPProcedureGrid3D>(TEXT("IPProcedureGrid3D"));
	IPProcedureGrid3D->SetupAttachment(RootComponent);
	IPProcedureGrid3D->Mobility = EComponentMobility::Static;
	IPProcedureGrid3D->ExecutionOrder = 1;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(RootComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->ExecutionOrder = 2;

	bInstancesNumEditCondition = false;
#endif
}

#if WITH_EDITOR
void AIPGrid3DTwoActor::RunGeneration()
{
	Super::RunGeneration();

	TArray<FTransform> Transforms;
	Transforms.Add(FTransform());

	IPProcedureInitialTransform->RunProcedure(1, Transforms);
	IPProcedureGrid3D->RunProcedure(1, Transforms);
	IPProcedureRandomTransform->RunProcedure(1, Transforms);

	TArray<FTransform> Transforms1;
	TArray<FTransform> Transforms2;
	DistributeToTwoTransforms(Transforms, Transforms1, Transforms2);
	UpdateInstances(Transforms1, ISMComponent);
	UpdateInstances(Transforms2, ISMComponent2);
}

void AIPGrid3DTwoActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	bInstancesNumEditCondition = false;
	InstancesNum = IPProcedureGrid3D->InstancesNum3D.X * IPProcedureGrid3D->InstancesNum3D.Y * IPProcedureGrid3D->InstancesNum3D.Z;

	RunGeneration();
}
#endif