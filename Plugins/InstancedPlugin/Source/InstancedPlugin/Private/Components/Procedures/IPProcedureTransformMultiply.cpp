// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureTransformMultiply.h"

UIPProcedureTransformMultiply::UIPProcedureTransformMultiply()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
	MultiplyTransform = FTransform();
#endif
}

#if WITH_EDITOR
void UIPProcedureTransformMultiply::RunProcedure(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		ResultTransforms.Add(Transf * MultiplyTransform);
	}

	Transforms = ResultTransforms;
}

FTransform UIPProcedureTransformMultiply::Operation(FTransform& A, FTransform& B)
{
	return FTransform();
}
#endif