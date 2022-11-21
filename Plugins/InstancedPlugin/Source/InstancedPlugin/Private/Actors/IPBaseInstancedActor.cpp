// redbox, 2022

#include "Actors/IPBaseInstancedActor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/Operations/IPOperationComponent.h"

#if WITH_EDITOR
void AIPBaseInstancedActor::RunGeneration()
{
	Super::RunGeneration();

	TArray<UActorComponent*> ACompISMs;
	GetComponents(UInstancedStaticMeshComponent::StaticClass(), ACompISMs);

	if (ACompISMs.Num() > 0)
	{
		for (auto& ACompISM : ACompISMs)
		{
			if (UInstancedStaticMeshComponent* ISMComp = Cast<UInstancedStaticMeshComponent>(ACompISM))
			{
				TArray<FTransform> Transforms;
				TArray<USceneComponent*> ISMCompChildren;
				ISMComp->GetChildrenComponents(true, ISMCompChildren);

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
				else continue;

				UHierarchicalInstancedStaticMeshComponent* HISMComp = Cast<UHierarchicalInstancedStaticMeshComponent>(ISMComp);
				if (HISMComp)
				{
					HISMComp->bAutoRebuildTreeOnInstanceChanges = false;
				}

				ISMComp->ClearInstances();

				for (auto& Transf : Transforms)
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
