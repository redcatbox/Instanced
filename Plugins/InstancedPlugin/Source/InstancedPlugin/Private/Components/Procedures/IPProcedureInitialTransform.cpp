// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureInitialTransform.h"

UIPProcedureInitialTransform::UIPProcedureInitialTransform()
{
	PrimaryComponentTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	InitialTransform = FTransform();
#endif
}

#if WITH_EDITOR
void UIPProcedureInitialTransform::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
{
	// Idea is to always use it with only 1 iteration, because anyway this is only 1 initial transform for all instances.
	TArray<FTransform> ResultTransforms;

	for (int32 Index = 0; Index < NumIterations; Index++)
		for (FTransform Transf : Transforms)
			ResultTransforms.Add(Transf * InitialTransform);

	Transforms = ResultTransforms;
}
#endif