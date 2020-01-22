// Dmitriy Barannik aka redbox, 2020

#include "Components/Procedures/IPProcedureTransformsArray.h"

UIPProcedureTransformsArray::UIPProcedureTransformsArray()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureTransformsArray::RunProcedure(TArray<FTransform>& Transforms)
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