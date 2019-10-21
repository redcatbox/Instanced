// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureAdditionalTransformPI.h"

UIPProcedureAdditionalTransformPI::UIPProcedureAdditionalTransformPI()
{
	PrimaryComponentTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	AdditionalTransform = FTransform();
	AdditionalTransform.SetScale3D(FVector::ZeroVector);
#endif
}

#if WITH_EDITOR
void UIPProcedureAdditionalTransformPI::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
{
	// This is additional transform for every input transform
	TArray<FTransform> ResultTransforms;

	for (int32 Index = 0; Index < NumIterations; Index++)
		for (int32 i = 0; i < Transforms.Num(); i++)
		{
			FTransform NewTransf = FTransform();
			NewTransf.SetLocation(Transforms[i].GetLocation() + AdditionalTransform.GetLocation() * i);
			NewTransf.SetRotation((Transforms[i].Rotator() + (AdditionalTransform.Rotator() * i)).Quaternion());
			NewTransf.SetScale3D(Transforms[i].GetScale3D() + (AdditionalTransform.GetScale3D() * i));
			ResultTransforms.Add(NewTransf);
		}

	Transforms = ResultTransforms;
}
#endif