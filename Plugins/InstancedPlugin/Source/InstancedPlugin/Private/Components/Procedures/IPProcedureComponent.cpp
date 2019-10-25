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
void UIPProcedureComponent::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
{
	Transforms = BlueprintProcedure(NumIterations, Transforms);

//TArray<FTransform> ResultTransforms;
//for (int32 Index = 0; Index < NumIterations; Index++)
//	for (FTransform Transf : Transforms)
//	{
//		FTransform ProcTransf;
//		FTransform NewTransf = Transf * ProcTransf;
//		ResultTransforms.Add(NewTransf);
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