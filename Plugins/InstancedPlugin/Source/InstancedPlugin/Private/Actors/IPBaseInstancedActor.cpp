// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/IPBaseInstancedActor.h"

#if WITH_EDITOR
void AIPBaseInstancedActor::RunGeneration()
{
	Super::RunGeneration();
	TArray<UActorComponent*> ACompISMCs;
	GetComponents(UInstancedStaticMeshComponent::StaticClass(), ACompISMCs);

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

				UHierarchicalInstancedStaticMeshComponent* HISMComp = Cast<UHierarchicalInstancedStaticMeshComponent>(ISMComp);

				if (HISMComp)
				{
					HISMComp->bAutoRebuildTreeOnInstanceChanges = false;
				}

				ISMComp->ClearInstances();

				for (FTransform Transf : Transforms)
				{
					ISMComp->AddInstance(Transf);
				}

				if (HISMComp)
				{
					HISMComp->bAutoRebuildTreeOnInstanceChanges = true;
					HISMComp->BuildTreeIfOutdated(true, true);
				}

				ISMComp->Modify();
			}
		}
	}
}
#endif