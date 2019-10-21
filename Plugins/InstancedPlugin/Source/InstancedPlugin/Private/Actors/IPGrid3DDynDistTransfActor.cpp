// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPGrid3DDynDistTransfActor.h"

AIPGrid3DDynDistTransfActor::AIPGrid3DDynDistTransfActor()
{
	PrimaryActorTick.bCanEverTick = true;

	IPProcedureDynamicTransform = CreateDefaultSubobject<UIPProcedureDynamicTransform>(TEXT("IPProcedureDynamicTransform"));
	IPProcedureDynamicTransform->SetupAttachment(RootComponent);
}

void AIPGrid3DDynDistTransfActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	IPProcedureDynamicTransform->RunProcedureDynamic();
}