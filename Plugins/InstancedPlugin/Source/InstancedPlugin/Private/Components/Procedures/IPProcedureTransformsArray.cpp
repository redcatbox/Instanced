// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureTransformsArray.h"

UIPProcedureTransformsArray::UIPProcedureTransformsArray()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureTransformsArray::RunProcedure(TArray<FTransform>& Transforms)
{
	InstancesNum = PlacementTransforms.Num();
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
		for (FTransform PTransf : PlacementTransforms)
			ResultTransforms.Add(Transf * PTransf);

	Transforms = ResultTransforms;
}
#endif