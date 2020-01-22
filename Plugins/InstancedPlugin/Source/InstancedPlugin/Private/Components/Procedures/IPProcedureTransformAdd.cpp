// Dmitriy Barannik aka redbox, 2020

#include "Components/Procedures/IPProcedureTransformAdd.h"

UIPProcedureTransformAdd::UIPProcedureTransformAdd()
{
#if WITH_EDITORONLY_DATA
	bPerInstanceIncremental = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureTransformAdd::RunProcedure(TArray<FTransform>& Transforms)
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
					if (bPerInstanceIncremental)
					{
						FTransform IncrementalTransform = FTransform(
							PIT.NewTransform.Rotator() * i,
							PIT.NewTransform.GetLocation() * i,
							PIT.NewTransform.GetScale3D() * i
						);
						Transforms[i] = Operation(Transforms[i], IncrementalTransform);
					}
					else
					{
						Transforms[i] = Operation(Transforms[i], PIT.NewTransform);
					}
				}
			}
			else if (PIT.InstanceId < Transforms.Num())
			{
				Transforms[PIT.InstanceId] = Operation(Transforms[PIT.InstanceId], PIT.NewTransform);
			}
		}
	}
}

FTransform UIPProcedureTransformAdd::Operation(FTransform& A, FTransform& B)
{
	return FTransform(
		A.Rotator() + B.Rotator(),
		A.GetLocation() + B.GetLocation(),
		A.GetScale3D() + B.GetScale3D()
	);
}
#endif