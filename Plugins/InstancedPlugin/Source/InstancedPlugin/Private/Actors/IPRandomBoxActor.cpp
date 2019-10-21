// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPRandomBoxActor.h"

AIPRandomBoxActor::AIPRandomBoxActor()
{
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = true;
	InstancesNum = 100;

	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(RootComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureRandomBox = CreateDefaultSubobject<UIPProcedureRandomBox>(TEXT("IPProcedureRandomSphere"));
	IPProcedureRandomBox->SetupAttachment(RootComponent);
	IPProcedureRandomBox->Mobility = EComponentMobility::Static;
	IPProcedureRandomBox->bUseRandomStreamEditCondition = false;
	IPProcedureRandomBox->bUseRandomStreamSeedEditCondition = false;
	IPProcedureRandomBox->bUseRandomStream = bUseRandomStream;
	IPProcedureRandomBox->RandomStreamSeed = RandomStreamSeed;
	IPProcedureRandomBox->ExecutionOrder = 1;
	IPProcedureRandomBox->bUseInstancesNum = true;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(RootComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bUseRandomStreamEditCondition = false;
	IPProcedureRandomTransform->bUseRandomStream = bUseRandomStream;
	IPProcedureRandomTransform->RandomStreamSeed = RandomStreamSeed;
	IPProcedureRandomTransform->ExecutionOrder = 2;

	bUseRandomStream = false;
	RandomStreamSeed = 0;
#endif
}

#if WITH_EDITOR
void AIPRandomBoxActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	IPProcedureRandomBox->bUseRandomStreamEditCondition = false;
	IPProcedureRandomBox->bUseRandomStreamSeedEditCondition = false;
	IPProcedureRandomBox->bUseRandomStream = bUseRandomStream;
	IPProcedureRandomBox->RandomStreamSeed = RandomStreamSeed;
	IPProcedureRandomTransform->bUseRandomStream = bUseRandomStream;
	IPProcedureRandomTransform->RandomStreamSeed = RandomStreamSeed;

	RunGeneration();
}
#endif