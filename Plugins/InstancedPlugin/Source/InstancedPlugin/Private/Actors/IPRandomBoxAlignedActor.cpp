// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPRandomBoxAlignedActor.h"

AIPRandomBoxAlignedActor::AIPRandomBoxAlignedActor()
{
#if WITH_EDITORONLY_DATA
	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(HISMComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureRandomBox = CreateDefaultSubobject<UIPProcedureRandomBox>(TEXT("IPProcedureRandomBox"));
	IPProcedureRandomBox->SetupAttachment(HISMComponent);
	IPProcedureRandomBox->Mobility = EComponentMobility::Static;
	IPProcedureRandomBox->bUseRandomStreamEditCondition = false;
	IPProcedureRandomBox->bUseRandomStreamSeedEditCondition = false;
	IPProcedureRandomBox->bUseRandomStream = bUseRandomStream;
	IPProcedureRandomBox->RandomStreamSeed = RandomStreamSeed;
	IPProcedureRandomBox->ExecutionOrder = 1;

	IPProcedureAlignByDirection = CreateDefaultSubobject<UIPProcedureAlignByDirection>(TEXT("IPProcedureAlignByDirection"));
	IPProcedureAlignByDirection->SetupAttachment(HISMComponent);
	IPProcedureAlignByDirection->Mobility = EComponentMobility::Static;
	IPProcedureAlignByDirection->ExecutionOrder = 2;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(HISMComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bUseRandomStreamEditCondition = false;
	IPProcedureRandomTransform->bUseRandomStream = bUseRandomStream;
	IPProcedureRandomTransform->RandomStreamSeed = RandomStreamSeed;
	IPProcedureRandomTransform->ExecutionOrder = 3;

	bUseRandomStream = false;
	RandomStreamSeed = 0;
#endif
}

#if WITH_EDITOR
void AIPRandomBoxAlignedActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	IPProcedureRandomBox->bUseRandomStreamEditCondition = false;
	IPProcedureRandomBox->bUseRandomStreamSeedEditCondition = false;

	RunGeneration();
}
#endif