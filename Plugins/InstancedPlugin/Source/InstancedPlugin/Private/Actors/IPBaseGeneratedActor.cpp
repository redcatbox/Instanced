// redbox, 2022

#include "Actors/IPBaseGeneratedActor.h"
#include "Components/SceneComponent.h"
#include "Objects/IPFunctionLibrary.h"

AIPBaseGeneratedActor::AIPBaseGeneratedActor()
{
	PrimaryActorTick.bCanEverTick = false;

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

void AIPBaseGeneratedActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	RunGeneration();
}
#endif
