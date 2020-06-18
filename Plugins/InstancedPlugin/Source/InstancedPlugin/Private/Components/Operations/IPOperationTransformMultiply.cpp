// redbox, 2020

#include "Components/Operations/IPOperationTransformMultiply.h"

#if WITH_EDITOR
void UIPOperationTransformMultiply::RunOperation(TArray<FTransform>& Transforms)
{
	if (OperationTransforms.Num() > 0)
	{
		Algo::Sort(OperationTransforms, FSortByInstanceId());

		for (auto& PIT : OperationTransforms)
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