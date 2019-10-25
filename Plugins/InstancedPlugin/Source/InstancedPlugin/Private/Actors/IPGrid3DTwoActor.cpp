// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPGrid3DTwoActor.h"

AIPGrid3DTwoActor::AIPGrid3DTwoActor()
{
#if WITH_EDITORONLY_DATA
	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(RootComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->bIsEditorOnly = true;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureGrid3D = CreateDefaultSubobject<UIPProcedureGrid3D>(TEXT("IPProcedureGrid3D"));
	IPProcedureGrid3D->SetupAttachment(RootComponent);
	IPProcedureGrid3D->Mobility = EComponentMobility::Static;
	IPProcedureGrid3D->bIsEditorOnly = true;
	IPProcedureGrid3D->ExecutionOrder = 1;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(RootComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bIsEditorOnly = true;
	IPProcedureRandomTransform->ExecutionOrder = 2;
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
	UpdateInstances(Transforms1, HISMComponent1);
	UpdateInstances(Transforms2, HISMComponent2);
}
#endif