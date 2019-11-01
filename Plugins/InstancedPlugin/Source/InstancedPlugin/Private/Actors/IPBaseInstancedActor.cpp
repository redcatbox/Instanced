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

	if (ISMComponentRef->GetInstanceCount() != Transforms.Num())
	{
		ISMComponentRef->ClearInstances();

		for (FTransform Transf : Transforms)
		{
			ISMComponentRef->AddInstance(Transf);
		}
	}
	else
	{
		for (int32 i = 0; i < Transforms.Num(); i++)
		{
			ISMComponentRef->UpdateInstanceTransform(i, Transforms[i], false, false, false);
		}
	}

	if (HISMComponentRef)
	{
		HISMComponentRef->bAutoRebuildTreeOnInstanceChanges = true;
		HISMComponentRef->BuildTreeIfOutdated(true, true);
	}

	ISMComponentRef->Modify();
}

void AIPBaseInstancedActor::DrawDebugInfo()
{
	TArray<UActorComponent*> ACompISMCs = GetComponentsByClass(UInstancedStaticMeshComponent::StaticClass());

	if (ACompISMCs.Num() > 0)
	{
		for (UActorComponent* ACompISM : ACompISMCs)
		{
			if (UInstancedStaticMeshComponent* ISMComp = Cast<UInstancedStaticMeshComponent>(ACompISM))
			{
				for (int32 i = 0; i < ISMComp->GetInstanceCount(); i++)
				{
					FTransform Transf;
					ISMComp->GetInstanceTransform(i, Transf, true);
					DrawDebugString(GetWorld(), Transf.GetLocation(), FString::FromInt(i), this, FColor::White, 0.f, false, 1.f);
				}
			}
		}
	}
}

void AIPBaseInstancedActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//if (bUseInstancingRandomSeed)
	//{
	//	ISMComponent->InstancingRandomSeed = InstancingRandomSeed;
	//	ISMComponent->Modify();
	//}

	RunGeneration();
}
#endif