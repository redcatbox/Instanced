// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPInstancedHISMActor.h"

AIPInstancedHISMActor::AIPInstancedHISMActor()
{
	HISMComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISMComponent"));
	HISMComponent->SetupAttachment(RootComponent);
	HISMComponent->Mobility = EComponentMobility::Static;
	HISMComponent->CreationMethod = EComponentCreationMethod::Native;
}