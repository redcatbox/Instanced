// Fill out your copyright notice in the Description page of Project Settings.

// This actor trying to get procedure components added in editor, and process them.
#include "Actors/IPInstancedActor.h"

AIPInstancedActor::AIPInstancedActor()
{
	PrimaryActorTick.bCanEverTick = false;

	ISMComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISMComponent"));
	ISMComponent->SetupAttachment(RootComponent);
	ISMComponent->Mobility = EComponentMobility::Static;
	ISMComponent->CreationMethod = EComponentCreationMethod::Native;
}

#if WITH_EDITOR
void AIPInstancedActor::RunGeneration()
{
	Super::RunGeneration();
}

void AIPInstancedActor::UpdateInstances(TArray<FTransform>& Transforms, UInstancedStaticMeshComponent* ISMComponentRef)
{
	UHierarchicalInstancedStaticMeshComponent* HISMComponentRef = Cast<UHierarchicalInstancedStaticMeshComponent>(ISMComponentRef);
	if (HISMComponentRef)
	{
		HISMComponentRef->bAutoRebuildTreeOnInstanceChanges = false;
		HISMComponentRef->ClearInstances();

		for (FTransform Transf : Transforms)
			HISMComponentRef->AddInstance(Transf);

		HISMComponentRef->bAutoRebuildTreeOnInstanceChanges = true;
		HISMComponentRef->BuildTreeIfOutdated(true, true);
		HISMComponentRef->Modify();
	}
}

void AIPInstancedActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	RunGeneration();
}
#endif