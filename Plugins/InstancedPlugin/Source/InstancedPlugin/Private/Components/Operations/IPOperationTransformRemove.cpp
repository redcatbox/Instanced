// Dmitriy Barannik aka redbox, 2020

#include "Components/Operations/IPOperationTransformRemove.h"

#if WITH_EDITOR
void UIPOperationTransformRemove::RunOperation(TArray<FTransform>& Transforms)
{
	if (OperationTransforms.Num() > 0)
	{
		Algo::Sort(OperationTransforms, FSortByInstanceId());

		for (FPerInstanceTransform PIT : OperationTransforms)
		{
			if (PIT.InstanceId > -1 && PIT.InstanceId < Transforms.Num())
			{
				Transforms.RemoveAt(PIT.InstanceId);
			}
		}
	}
}
#endif