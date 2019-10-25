// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPSpiralActor.h"

AIPSpiralActor::AIPSpiralActor()
{
#if WITH_EDITORONLY_DATA
	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(HISMComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->bIsEditorOnly = true;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureSpiral = CreateDefaultSubobject<UIPProcedureSpiral>(TEXT("IPProcedureSpiral"));
	IPProcedureSpiral->SetupAttachment(HISMComponent);
	IPProcedureSpiral->Mobility = EComponentMobility::Static;
	IPProcedureSpiral->bIsEditorOnly = true;
	IPProcedureSpiral->ExecutionOrder = 1;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(HISMComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bIsEditorOnly = true;
	IPProcedureRandomTransform->ExecutionOrder = 2;
#endif
}