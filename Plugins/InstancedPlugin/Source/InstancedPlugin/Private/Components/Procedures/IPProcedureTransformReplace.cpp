// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureTransformReplace.h"

UIPProcedureTransformReplace::UIPProcedureTransformReplace()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
	ReplacementTransform = FTransform();
#endif
}

#if WITH_EDITOR
void UIPProcedureTransformReplace::RunProcedure(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		ResultTransforms.Add(ReplacementTransform);
	}

	Transforms = ResultTransforms;
}

FTransform UIPProcedureTransformReplace::Operation(FTransform& A, FTransform& B)
{
	return FTransform();
}
#endif