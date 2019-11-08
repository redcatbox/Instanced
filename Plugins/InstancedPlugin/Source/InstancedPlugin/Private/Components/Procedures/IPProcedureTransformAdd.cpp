// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureTransformAdd.h"

UIPProcedureTransformAdd::UIPProcedureTransformAdd()
{
#if WITH_EDITORONLY_DATA
	bPerInstanceIncremental = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureTransformAdd::RunProcedure(TArray<FTransform>& Transforms)
{
	if (OperationTransforms.Num() > 0)
	{
		Algo::Sort(OperationTransforms, FSortByInstanceId());
		TArray<FTransform> ResultTransforms = Transforms;

		for (FPerInstanceTransform PIT : OperationTransforms)
		{
			if (PIT.InstanceId > -1)
			{
				ResultTransforms[PIT.InstanceId] = Operation(ResultTransforms[PIT.InstanceId], PIT.NewTransform);
			}
			else
			{
				for (int32 i = 0; i < ResultTransforms.Num(); i++)
				{
					if (bPerInstanceIncremental)
					{
						FTransform IncrementalTransform = FTransform(
							PIT.NewTransform.Rotator() * i,
							PIT.NewTransform.GetLocation() * i,
							PIT.NewTransform.GetScale3D() * i
						);
						ResultTransforms[i] = Operation(ResultTransforms[i], IncrementalTransform);
					}
					else
					{
						ResultTransforms[i] = Operation(ResultTransforms[i], PIT.NewTransform);
					}
				}
			}
		}

		Transforms = ResultTransforms;
	}
}

FTransform UIPProcedureTransformAdd::Operation(FTransform& A, FTransform& B)
{
	return FTransform(
		A.Rotator() + B.Rotator(),
		A.GetLocation() + B.GetLocation(),
		A.GetScale3D() + B.GetScale3D()
	);
}
#endif