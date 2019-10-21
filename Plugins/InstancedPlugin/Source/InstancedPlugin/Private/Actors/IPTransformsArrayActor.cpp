// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPTransformsArrayActor.h"

AIPTransformsArrayActor::AIPTransformsArrayActor()
{
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	IPProcedureTransformsArray = CreateDefaultSubobject<UIPProcedureTransformsArray>(TEXT("IPProcedureTransformsArray"));
	IPProcedureTransformsArray->SetupAttachment(RootComponent);
	IPProcedureTransformsArray->Mobility = EComponentMobility::Static;

	bInstancesNumEditCondition = false;
#endif
}

#if WITH_EDITOR
void AIPTransformsArrayActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	InstancesNum = IPProcedureTransformsArray->Transforms.Num();
	RunGeneration();
}
#endif