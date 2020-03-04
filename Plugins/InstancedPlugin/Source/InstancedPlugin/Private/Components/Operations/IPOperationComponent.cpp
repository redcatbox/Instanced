// Dmitriy Barannik aka redbox, 2020

#include "Components/Operations/IPOperationComponent.h"
#include "Actors/IPBaseGeneratedActor.h"

UIPOperationComponent::UIPOperationComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = true;
	InstancesNum = 1;
	bEnabled = true;
	ExecutionOrder = 0;
#endif
}

#if WITH_EDITOR
void UIPOperationComponent::RunOperation(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms = BlueprintOperation(Transforms);

	if (ResultTransforms.Num() > 0)
	{
		Transforms = ResultTransforms;
	}

	//for (FTransform Transf : Transforms)
	//{
	//	for (int32 i = 0; i < InstancesNum; i++)
	//	{
	//		FTransform ProcTransf = FTransform();
	//		ResultTransforms.Add(Transf * ProcTransf);
	//	}
	//}
	//Transforms = ResultTransforms;
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
		for (USceneComponent* SComp : ParentComps)
		{
			if (UInstancedStaticMeshComponent* ParentISMComp = Cast<UInstancedStaticMeshComponent>(SComp))
			{
				return ParentISMComp;
			}
		}
	}

	return nullptr;
}