// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureTransformMultiply.h"

#if WITH_EDITOR
void UIPProcedureTransformMultiply::RunProcedure(TArray<FTransform>& Transforms)
{
	if (OperationTransforms.Num() > 0)
	{
		Algo::Sort(OperationTransforms, FSortByInstanceId());
		TArray<FTransform> ResultTransforms = Transforms;

		for (FPerInstanceTransform PIT : OperationTransforms)
		{
			if (PIT.InstanceId <= -1)
			{
				for (int32 i = 0; i < ResultTransforms.Num(); i++)
				{
					ResultTransforms[i] = ResultTransforms[i] * PIT.NewTransform;
				}
			}
			else if (PIT.InstanceId < ResultTransforms.Num())
			{
				ResultTransforms[PIT.InstanceId] = ResultTransforms[PIT.InstanceId] * PIT.NewTransform;
			}
		}

		Transforms = ResultTransforms;
	}
}
#endif