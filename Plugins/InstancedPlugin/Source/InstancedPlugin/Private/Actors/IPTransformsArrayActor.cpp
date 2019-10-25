// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPTransformsArrayActor.h"

AIPTransformsArrayActor::AIPTransformsArrayActor()
{
#if WITH_EDITORONLY_DATA
	IPProcedureTransformsArray = CreateDefaultSubobject<UIPProcedureTransformsArray>(TEXT("IPProcedureTransformsArray"));
	IPProcedureTransformsArray->SetupAttachment(HISMComponent);
	IPProcedureTransformsArray->Mobility = EComponentMobility::Static;
	IPProcedureTransformsArray->bIsEditorOnly = true;
#endif
}