// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureTransformsArray.h"

UIPProcedureTransformsArray::UIPProcedureTransformsArray()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#if WITH_EDITOR
void UIPProcedureTransformsArray::RunProcedure(int32 NumIterations, TArray<FTransform>& InTransforms)
{
	TArray<FTransform> ResultTransforms;

	for (int32 Index = 0; Index < NumIterations; Index++)
		for (FTransform Transf : Transforms)
			for (FTransform InTransf : InTransforms)
			{
				FTransform NewTransf = InTransf * Transf;
				ResultTransforms.Add(NewTransf);
			}

	InTransforms = ResultTransforms;
}
#endif