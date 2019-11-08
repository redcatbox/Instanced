// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureTransformReplace.h"

#if WITH_EDITOR
void UIPProcedureTransformReplace::RunProcedure(TArray<FTransform>& Transforms)
{
	if (OperationTransforms.Num() > 0)
	{
		Algo::Sort(OperationTransforms, FSortByInstanceId());
		TArray<FTransform> ResultTransforms = Transforms;

		for (FPerInstanceTransform PIT : OperationTransforms)
		{
			if (PIT.InstanceId > -1)
			{
				ResultTransforms[PIT.InstanceId] = PIT.NewTransform;
			}
			else
			{
				for (int32 i = 0; i < ResultTransforms.Num(); i++)
				{
					ResultTransforms[i] = PIT.NewTransform;
				}
			}
		}

		Transforms = ResultTransforms;
	}
}
#endif