// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPBaseInstancedActor.h"

AIPBaseInstancedActor::AIPBaseInstancedActor()
{
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = true;
	InstancesNum = 10;
	bUseInstancingRandomSeed = false;
	InstancingRandomSeed = 0;
#endif
}

#if WITH_EDITOR
void AIPBaseInstancedActor::RunGeneration()
{
	Super::RunGeneration();

	TArray<FTransform> Transforms;
	TArray<UActorComponent*> AComponents = GetComponentsByClass(UIPProcedureComponent::StaticClass());

	if (AComponents.Num() > 0)
	{
		ProcedureComponents.Empty();

		for (UActorComponent* AComp : AComponents)
			if (UIPProcedureComponent* PComp = Cast<UIPProcedureComponent>(AComp))
			{
				if (PComp->bEnabled)
					ProcedureComponents.AddUnique(PComp);

				PComp->bIsEditorOnly = true;
			}

		if (ProcedureComponents.Num() > 0)
		{
			Algo::Sort(ProcedureComponents, FSortByExecutionOrder());
			Transforms.Add(FTransform());

			for (UIPProcedureComponent* PComp : ProcedureComponents)
				if (PComp->bUseInstancesNum)
					PComp->RunProcedure(InstancesNum, Transforms);
				else
					PComp->RunProcedure(1, Transforms);
		}
	}

	UpdateInstances(Transforms, ISMComponent);
}

void AIPBaseInstancedActor::UpdateInstances(TArray<FTransform>& Transforms, UInstancedStaticMeshComponent* ISMComponentRef)
{
	ISMComponentRef->ClearInstances();

	for (FTransform Transf : Transforms)
		ISMComponentRef->AddInstance(Transf);

	ISMComponentRef->Modify();
}

void AIPBaseInstancedActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (bUseInstancingRandomSeed)
	{
		ISMComponent->InstancingRandomSeed = InstancingRandomSeed;
		ISMComponent->Modify();
	}

	RunGeneration();
}
#endif