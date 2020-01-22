// Dmitriy Barannik aka redbox, 2020

#include "Components/Procedures/IPProcedureTransformMultiply.h"

#if WITH_EDITOR
void UIPProcedureTransformMultiply::RunProcedure(TArray<FTransform>& Transforms)
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
					Transforms[i] = Transforms[i] * PIT.NewTransform;
				}
			}
			else if (PIT.InstanceId < Transforms.Num())
			{
				Transforms[PIT.InstanceId] = Transforms[PIT.InstanceId] * PIT.NewTransform;
			}
		}
	}
}
#endif