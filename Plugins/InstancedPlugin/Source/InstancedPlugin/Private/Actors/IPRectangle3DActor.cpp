// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPRectangle3DActor.h"

AIPRectangle3DActor::AIPRectangle3DActor()
{
#if WITH_EDITORONLY_DATA
	IPProcedureInitialTransform = CreateDefaultSubobject<UIPProcedureInitialTransform>(TEXT("IPProcedureInitialTransform"));
	IPProcedureInitialTransform->SetupAttachment(HISMComponent);
	IPProcedureInitialTransform->Mobility = EComponentMobility::Static;
	IPProcedureInitialTransform->bIsEditorOnly = true;
	IPProcedureInitialTransform->ExecutionOrder = 0;

	IPProcedureRectangle3D = CreateDefaultSubobject<UIPProcedureRectangle3D>(TEXT("IPProcedureRectangle3D"));
	IPProcedureRectangle3D->SetupAttachment(HISMComponent);
	IPProcedureRectangle3D->Mobility = EComponentMobility::Static;
	IPProcedureRectangle3D->bIsEditorOnly = true;
	IPProcedureRectangle3D->ExecutionOrder = 1;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(HISMComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bIsEditorOnly = true;
	IPProcedureRandomTransform->ExecutionOrder = 2;
#endif
}