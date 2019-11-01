// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPBaseGeneratedActor.h"

AIPBaseGeneratedActor::AIPBaseGeneratedActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Default root
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	DefaultSceneRoot->Mobility = EComponentMobility::Static;

#if WITH_EDITORONLY_DATA
	DefaultSceneRoot->bVisualizeComponent = true;
#endif
}

#if WITH_EDITOR
void AIPBaseGeneratedActor::RunGeneration()
{
	this->Modify();
}

void AIPBaseGeneratedActor::DrawDebugInfo() {}

void AIPBaseGeneratedActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	RunGeneration();
}
#endif