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
void UIPProcedureAdditionalTransformPI::RunProcedure(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (int32 i = 0; i < Transforms.Num(); i++)
		ResultTransforms.Add(FTransform((Transforms[i].Rotator() + (AdditionalTransform.Rotator() * i)),
			Transforms[i].GetLocation() + AdditionalTransform.GetLocation() * i,
			Transforms[i].GetScale3D() + (AdditionalTransform.GetScale3D() * i)));

	Transforms = ResultTransforms;
}
#endif