// redbox, 2020

#include "Actors/IPBaseInstancedActor.h"

#if WITH_EDITOR
void AIPBaseInstancedActor::RunGeneration()
{
	Super::RunGeneration();
	TArray<UActorComponent*> ACompISMCs;
	GetComponents(UInstancedStaticMeshComponent::StaticClass(), ACompISMCs);

	if (ACompISMCs.Num() > 0)
	{
		for (auto& ACompISM : ACompISMCs)
		{
			if (UInstancedStaticMeshComponent* ISMComp = Cast<UInstancedStaticMeshComponent>(ACompISM))
			{
				TArray<FTransform> Transforms;
				TArray<USceneComponent*> ISMCompChildren;
				ISMComp->GetChildrenComponents(false, ISMCompChildren);

				if (ISMCompChildren.Num() > 0)
				{
					TArray<UIPOperationComponent*> PComps;

					for (auto& SComp : ISMCompChildren)
					{
						if (UIPOperationComponent* PComp = Cast<UIPOperationComponent>(SComp))
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

						for (auto& PComp : PComps)
						{
							PComp->RunOperation(Transforms);
						}
					}
				}
				else return;

				UHierarchicalInstancedStaticMeshComponent* HISMComp = Cast<UHierarchicalInstancedStaticMeshComponent>(ISMComp);
				if (HISMComp)
				{
					HISMComp->bAutoRebuildTreeOnInstanceChanges = false;
				}

				//if (ISMComp->GetInstanceCount() != Transforms.Num()) // causes editor crash on copy/paste or duplicate!
				//{

				ISMComp->ClearInstances();

				for (auto& Transf : Transforms)
				{
					ISMComp->AddInstance(Transf);
				}

				//}
				//else
				//{
				//	for (int32 i = 0; i < Transforms.Num(); i++)
				//	{
				//		ISMComp->UpdateInstanceTransform(i, Transforms[i], false, false, false);
				//	}
				//}

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
