// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureTransformInverse.h"

UIPProcedureTransformInverse::UIPProcedureTransformInverse()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
	bPerInstanceIncremental = false;
	AdditionalTransform = FTransform();
	AdditionalTransform.SetScale3D(FVector::ZeroVector);
#endif
}

#if WITH_EDITOR
void UIPProcedureTransformInverse::RunProcedure(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (int32 i = 0; i < Transforms.Num(); i++)
	{
		if (bPerInstanceIncremental)
		{
			ResultTransforms.Add(FTransform((Transforms[i].Rotator() + (AdditionalTransform.Rotator() * i)),
				Transforms[i].GetLocation() + AdditionalTransform.GetLocation() * i,
				Transforms[i].GetScale3D() + (AdditionalTransform.GetScale3D() * i)));
		}
		else
		{
			ResultTransforms.Add(FTransform((Transforms[i].Rotator() + (AdditionalTransform.Rotator())),
				Transforms[i].GetLocation() + AdditionalTransform.GetLocation(),
				Transforms[i].GetScale3D() + (AdditionalTransform.GetScale3D())));
		}
	}

	Transforms = ResultTransforms;
}

FTransform UIPProcedureTransformInverse::Operation(FTransform& A, FTransform& B)
{
	return FTransform();
}
#endif