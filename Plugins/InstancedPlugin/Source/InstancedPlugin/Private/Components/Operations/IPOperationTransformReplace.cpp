// redbox, 2020

#include "Components/Operations/IPOperationTransformReplace.h"

#if WITH_EDITOR
void UIPOperationTransformReplace::RunOperation(TArray<FTransform>& Transforms)
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
