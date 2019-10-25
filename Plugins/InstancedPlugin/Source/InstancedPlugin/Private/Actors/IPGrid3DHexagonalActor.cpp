// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPGrid3DHexagonalActor.h"

AIPGrid3DHexagonalActor::AIPGrid3DHexagonalActor()
{
#if WITH_EDITORONLY_DATA
	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(HISMComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureGrid3DHexagonal = CreateDefaultSubobject<UIPProcedureGrid3DHexagonal>(TEXT("IPProcedureGrid3DHexagonal"));
	IPProcedureGrid3DHexagonal->SetupAttachment(HISMComponent);
	IPProcedureGrid3DHexagonal->Mobility = EComponentMobility::Static;
	IPProcedureGrid3DHexagonal->ExecutionOrder = 1;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(HISMComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->ExecutionOrder = 2;
#endif
}