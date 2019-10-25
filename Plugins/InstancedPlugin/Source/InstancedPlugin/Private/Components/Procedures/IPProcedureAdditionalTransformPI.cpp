// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureAdditionalTransformPI.h"

UIPProcedureAdditionalTransformPI::UIPProcedureAdditionalTransformPI()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;

	AdditionalTransform = FTransform();
	AdditionalTransform.SetScale3D(FVector::ZeroVector);
#endif
}

#if WITH_EDITOR
void UIPProcedureAdditionalTransformPI::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (int32 t = 0; t < Transforms.Num(); t++)
		ResultTransforms.Add(FTransform((Transforms[t].Rotator() + (AdditionalTransform.Rotator() * t)),
			Transforms[t].GetLocation() + AdditionalTransform.GetLocation() * t,
			Transforms[t].GetScale3D() + (AdditionalTransform.GetScale3D() * t)));

	Transforms = ResultTransforms;
}
#endif