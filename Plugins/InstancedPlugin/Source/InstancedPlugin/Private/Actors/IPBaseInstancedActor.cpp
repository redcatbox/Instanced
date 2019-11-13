// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPBaseInstancedActor.h"

AIPBaseInstancedActor::AIPBaseInstancedActor()
{
	//#if WITH_EDITORONLY_DATA
	//	bUseInstancingRandomSeed = false;
	//	InstancingRandomSeed = 0;
	//#endif
}

#if WITH_EDITOR
void AIPBaseInstancedActor::RunGeneration()
{
	Super::RunGeneration();
	TArray<UActorComponent*> ACompISMCs = GetComponentsByClass(UInstancedStaticMeshComponent::StaticClass());

	if (ACompISMCs.Num() > 0)
	{
		for (UActorComponent* ACompISM : ACompISMCs)
		{
			if (UInstancedStaticMeshComponent* ISMComp = Cast<UInstancedStaticMeshComponent>(ACompISM))
			{
				TArray<FTransform> Transforms;
				TArray<USceneComponent*> ISMCompChildren;
				ISMComp->GetChildrenComponents(false, ISMCompChildren);

				if (ISMCompChildren.Num() > 0)
				{
					TArray<UIPProcedureComponent*> PComps;

					for (USceneComponent* SComp : ISMCompChildren)
					{
						if (UIPProcedureComponent* PComp = Cast<UIPProcedureComponent>(SComp))
						{
							if (PComp->bEnabled)
							{
								PComps.AddUnique(PComp);
							}
						}
					}

					if (PComps.Num() > 0)
					{
						Algo::Sort(PComps, FSortByExecutionOrder());
						Transforms.Add(FTransform());

						for (UIPProcedureComponent* PComp : PComps)
						{
							PComp->RunProcedure(Transforms);
						}
					}
				}

				UpdateInstances(Transforms, ISMComp);
			}
		}
	}
}

void AIPBaseInstancedActor::UpdateInstances(TArray<FTransform>& Transforms, UInstancedStaticMeshComponent* ISMComponentRef)
{
	UHierarchicalInstancedStaticMeshComponent* HISMComponentRef = Cast<UHierarchicalInstancedStaticMeshComponent>(ISMComponentRef);

	if (HISMComponentRef)
	{
		HISMComponentRef->bAutoRebuildTreeOnInstanceChanges = false;
	}

	ISMComponentRef->ClearInstances();

	for (FTransform Transf : Transforms)
	{
		ISMComponentRef->AddInstance(Transf);
	}

	if (HISMComponentRef)
	{
		HISMComponentRef->bAutoRebuildTreeOnInstanceChanges = true;
		HISMComponentRef->BuildTreeIfOutdated(true, true);
	}

	ISMComponentRef->Modify();
}
#endif