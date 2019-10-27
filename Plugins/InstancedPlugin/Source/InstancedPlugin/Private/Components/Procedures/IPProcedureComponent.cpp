// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureComponent.h"
#include "Actors/IPBaseGeneratedActor.h"

UIPProcedureComponent::UIPProcedureComponent()
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
void UIPProcedureComponent::RunProcedure(TArray<FTransform>& Transforms)
{
	Transforms = BlueprintProcedure(Transforms);

	//TArray<FTransform> ResultTransforms;

	//for (FTransform Transf : Transforms)
	//	for (int32 i = 0; i < InstancesNum; i++)
	//	{
	//		FTransform ProcTransf = FTransform();
	//		ResultTransforms.Add(Transf * ProcTransf);
	//	}

	//Transforms = ResultTransforms;
}

void UIPProcedureComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (AIPBaseGeneratedActor* BaseGeneratedActor = Cast<AIPBaseGeneratedActor>(GetOwner()))
		BaseGeneratedActor->RunGeneration();
}
#endif