// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureTransformsArray.h"

UIPProcedureTransformsArray::UIPProcedureTransformsArray()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureTransformsArray::RunProcedure(int32 NumIterations, TArray<FTransform>& InTransforms)
{
	TArray<FTransform> ResultTransforms;
	InstancesNum = Transforms.Num();

	for (FTransform Transf : Transforms)
		for (FTransform InTransf : InTransforms)
			ResultTransforms.Add(InTransf * Transf);

	InTransforms = ResultTransforms;
}
#endif