// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureTransformReplace.h"

#if WITH_EDITOR
void UIPProcedureTransformReplace::RunProcedure(TArray<FTransform>& Transforms)
{
	if (OperationTransforms.Num() > 0)
	{
		Algo::Sort(OperationTransforms, FSortByInstanceId());

		for (FPerInstanceTransform PIT : OperationTransforms)
		{
			if (PIT.InstanceId <= -1)
			{
				for (int32 i = 0; i < Transforms.Num(); i++)
				{
					Transforms[i] = PIT.NewTransform;
				}
			}
			else if (PIT.InstanceId < Transforms.Num())
			{
				Transforms[PIT.InstanceId] = PIT.NewTransform;
			}
		}
	}
}
#endif