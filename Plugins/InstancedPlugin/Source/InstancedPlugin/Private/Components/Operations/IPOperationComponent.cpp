// redbox, 2022

#include "Components/Operations/IPOperationComponent.h"
#include "Actors/IPBaseGeneratedActor.h"
#include "Components/InstancedStaticMeshComponent.h"

UIPOperationComponent::UIPOperationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	bInstancesNumEditCond = true;
	InstancesNum = 1;
	bEnabled = true;
	ExecutionOrder = 0;
#endif
}

#if WITH_EDITOR
void UIPOperationComponent::RunOperation(TArray<FTransform>& Transforms)
{
	const TArray<FTransform> ResultTransforms = BlueprintOperation(Transforms);

	if (ResultTransforms.Num() > 0)
	{
		Transforms = ResultTransforms;
	}
}

void UIPOperationComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (AIPBaseGeneratedActor* BaseGeneratedActor = Cast<AIPBaseGeneratedActor>(GetOwner()))
	{
		BaseGeneratedActor->RunGeneration();
	}
}
#endif

UInstancedStaticMeshComponent* UIPOperationComponent::GetParentISMComponent()
{
	TArray<USceneComponent*> ParentComps;
	GetParentComponents(ParentComps);

	if (ParentComps.Num() > 0)
	{
		for (auto& SComp : ParentComps)
		{
			if (UInstancedStaticMeshComponent* ParentISMComp = Cast<UInstancedStaticMeshComponent>(SComp))
			{
				return ParentISMComp;
			}
		}
	}

	return nullptr;
}
