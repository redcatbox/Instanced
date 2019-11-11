// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPRandomSphereAlignedActor.h"

AIPRandomSphereAlignedActor::AIPRandomSphereAlignedActor()
{
#if WITH_EDITORONLY_DATA
	IPProcedureTransformMultiply = CreateDefaultSubobject<UIPProcedureTransformMultiply>(TEXT("IPProcedureTransformMultiply"));
	IPProcedureTransformMultiply->SetupAttachment(HISMComponent);
	IPProcedureTransformMultiply->Mobility = EComponentMobility::Static;
	IPProcedureTransformMultiply->bIsEditorOnly = true;
	IPProcedureTransformMultiply->ExecutionOrder = 0;
	IPProcedureTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPProcedureRandomSphere = CreateDefaultSubobject<UIPProcedureRandomSphere>(TEXT("IPProcedureRandomSphere"));
	IPProcedureRandomSphere->SetupAttachment(HISMComponent);
	IPProcedureRandomSphere->Mobility = EComponentMobility::Static;
	IPProcedureRandomSphere->bIsEditorOnly = true;
	IPProcedureRandomSphere->bUseRandomStreamEditCondition = false;
	IPProcedureRandomSphere->bUseRandomStreamSeedEditCondition = false;
	IPProcedureRandomSphere->bUseRandomStream = bUseRandomStream;
	IPProcedureRandomSphere->RandomStreamSeed = RandomStreamSeed;
	IPProcedureRandomSphere->ExecutionOrder = 1;

	IPProcedureAlignFromPoint = CreateDefaultSubobject<UIPProcedureAlignFromPoint>(TEXT("IPProcedureAlignFromPoint"));
	IPProcedureAlignFromPoint->SetupAttachment(HISMComponent);
	IPProcedureAlignFromPoint->Mobility = EComponentMobility::Static;
	IPProcedureAlignFromPoint->bIsEditorOnly = true;
	IPProcedureAlignFromPoint->ExecutionOrder = 2;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(HISMComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bIsEditorOnly = true;
	IPProcedureRandomTransform->bUseRandomStreamEditCondition = false;
	IPProcedureRandomTransform->bUseRandomStream = bUseRandomStream;
	IPProcedureRandomTransform->RandomStreamSeed = RandomStreamSeed;
	IPProcedureRandomTransform->ExecutionOrder = 3;

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