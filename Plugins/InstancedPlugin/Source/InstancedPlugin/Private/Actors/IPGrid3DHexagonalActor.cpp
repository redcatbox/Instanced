// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPGrid3DHexagonalActor.h"

AIPGrid3DHexagonalActor::AIPGrid3DHexagonalActor()
{
#if WITH_EDITORONLY_DATA
	IPProcedureTransformMultiply = CreateDefaultSubobject<UIPProcedureTransformMultiply>(TEXT("IPProcedureTransformMultiply"));
	IPProcedureTransformMultiply->SetupAttachment(HISMComponent);
	IPProcedureTransformMultiply->Mobility = EComponentMobility::Static;
	IPProcedureTransformMultiply->bIsEditorOnly = true;
	IPProcedureTransformMultiply->ExecutionOrder = 0;
	IPProcedureTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPProcedureGrid3DHexagonal = CreateDefaultSubobject<UIPProcedureGrid3DHexagonal>(TEXT("IPProcedureGrid3DHexagonal"));
	IPProcedureGrid3DHexagonal->SetupAttachment(HISMComponent);
	IPProcedureGrid3DHexagonal->Mobility = EComponentMobility::Static;
	IPProcedureGrid3DHexagonal->bIsEditorOnly = true;
	IPProcedureGrid3DHexagonal->ExecutionOrder = 1;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(HISMComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bIsEditorOnly = true;
	IPProcedureRandomTransform->ExecutionOrder = 2;
#endif
}