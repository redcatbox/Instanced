// Dmitriy Barannik aka redbox, 2020

#include "Components/Procedures/IPProcedureTransformRemove.h"

#if WITH_EDITOR
void UIPProcedureTransformRemove::RunProcedure(TArray<FTransform>& Transforms)
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