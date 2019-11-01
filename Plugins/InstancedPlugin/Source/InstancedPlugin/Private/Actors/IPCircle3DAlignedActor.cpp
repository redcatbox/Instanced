// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPCircle3DAlignedActor.h"

AIPCircle3DAlignedActor::AIPCircle3DAlignedActor()
{
#if WITH_EDITORONLY_DATA
	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(HISMComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->bIsEditorOnly = true;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureCircle3D = CreateDefaultSubobject<UIPProcedureCircle3D>(TEXT("IPProcedureCircle3D"));
	IPProcedureCircle3D->SetupAttachment(HISMComponent);
	IPProcedureCircle3D->Mobility = EComponentMobility::Static;
	IPProcedureCircle3D->bIsEditorOnly = true;
	IPProcedureCircle3D->ExecutionOrder = 1;

	IPProcedureAlignFromAxis = CreateDefaultSubobject<UIPProcedureAlignFromAxis>(TEXT("IPProcedureAlignFromAxis"));
	IPProcedureAlignFromAxis->SetupAttachment(HISMComponent);
	IPProcedureAlignFromAxis->Mobility = EComponentMobility::Static;
	IPProcedureAlignFromAxis->bIsEditorOnly = true;
	IPProcedureAlignFromAxis->ExecutionOrder = 2;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(HISMComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bIsEditorOnly = true;
	IPProcedureRandomTransform->ExecutionOrder = 3;
#endif
}