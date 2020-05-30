// Dmitriy Barannik aka redbox, 2020

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
	//UE_LOG(IPLog, Log, TEXT("RunGeneration()"));
	this->Modify();
}

void AIPBaseGeneratedActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	RunGeneration();
}
#endif