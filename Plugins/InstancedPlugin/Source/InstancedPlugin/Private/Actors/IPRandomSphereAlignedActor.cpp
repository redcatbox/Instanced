// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPRandomSphereAlignedActor.h"

AIPRandomSphereAlignedActor::AIPRandomSphereAlignedActor()
{
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(HISMComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureRandomSphere = CreateDefaultSubobject<UIPProcedureRandomSphere>(TEXT("IPProcedureRandomSphere"));
	IPProcedureRandomSphere->SetupAttachment(HISMComponent);
	IPProcedureRandomSphere->Mobility = EComponentMobility::Static;
	IPProcedureRandomSphere->bUseRandomStreamEditCondition = false;
	IPProcedureRandomSphere->bUseRandomStreamSeedEditCondition = false;
	IPProcedureRandomSphere->bUseRandomStream = bUseRandomStream;
	IPProcedureRandomSphere->RandomStreamSeed = RandomStreamSeed;
	IPProcedureRandomSphere->ExecutionOrder = 1;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(HISMComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bUseRandomStreamEditCondition = false;
	IPProcedureRandomTransform->bUseRandomStream = bUseRandomStream;
	IPProcedureRandomTransform->RandomStreamSeed = RandomStreamSeed;
	IPProcedureRandomTransform->ExecutionOrder = 2;

	IPProcedureAlignFromPoint = CreateDefaultSubobject<UIPProcedureAlignFromPoint>(TEXT("IPProcedureAlignFromPoint"));
	IPProcedureAlignFromPoint->SetupAttachment(HISMComponent);
	IPProcedureAlignFromPoint->Mobility = EComponentMobility::Static;
	IPProcedureAlignFromPoint->ExecutionOrder = 3;

	bUseRandomStream = false;
	RandomStreamSeed = 0;
#endif
}

#if WITH_EDITOR
void AIPRandomSphereAlignedActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	IPProcedureRandomSphere->bUseRandomStreamEditCondition = false;
	IPProcedureRandomSphere->bUseRandomStreamSeedEditCondition = false;
	IPProcedureRandomSphere->bUseRandomStream = bUseRandomStream;
	IPProcedureRandomSphere->RandomStreamSeed = RandomStreamSeed;
	IPProcedureRandomTransform->bUseRandomStream = bUseRandomStream;
	IPProcedureRandomTransform->RandomStreamSeed = RandomStreamSeed;

	RunGeneration();
}
#endif