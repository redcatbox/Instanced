// Dmitriy Barannik aka redbox, 2020

#include "Components/Operations/IPOperationTransformsArray.h"

UIPOperationTransformsArray::UIPOperationTransformsArray()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
#endif
}

#if WITH_EDITOR
void UIPOperationTransformsArray::RunOperation(TArray<FTransform>& Transforms)
{
	InstancesNum = PlacementTransforms.Num();
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		for (FTransform PTransf : PlacementTransforms)
		{
			ResultTransforms.Add(Transf * PTransf);
		}
	}

	Transforms = ResultTransforms;
}
#endif