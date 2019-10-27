// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureInitialTransform.h"

UIPProcedureInitialTransform::UIPProcedureInitialTransform()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
	InitialTransform = FTransform();
#endif
}

#if WITH_EDITOR
void UIPProcedureInitialTransform::RunProcedure(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
		ResultTransforms.Add(Transf * InitialTransform);

	Transforms = ResultTransforms;
}
#endif