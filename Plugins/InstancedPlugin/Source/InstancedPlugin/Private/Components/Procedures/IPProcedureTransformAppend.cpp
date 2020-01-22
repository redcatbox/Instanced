// Dmitriy Barannik aka redbox, 2020

#include "Components/Procedures/IPProcedureTransformAppend.h"

#if WITH_EDITOR
void UIPProcedureTransformAppend::RunProcedure(TArray<FTransform>& Transforms)
{
	if (OperationTransforms.Num() > 0)
	{
		Algo::Sort(OperationTransforms, FSortByInstanceId());

		for (int32 i = 0; i < OperationTransforms.Num(); i++)
		{
			OperationTransforms[i].bInstanceIdEditCond = false;
			Transforms.Add(OperationTransforms[i].NewTransform);
			OperationTransforms[i].InstanceId = Transforms.Num();
		}
	}
}
#endif