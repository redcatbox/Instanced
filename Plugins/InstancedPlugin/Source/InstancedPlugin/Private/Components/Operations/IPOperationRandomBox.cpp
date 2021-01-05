// redbox, 2021

#include "Components/Operations/IPOperationRandomBox.h"

UIPOperationRandomBox::UIPOperationRandomBox()
{
#if WITH_EDITORONLY_DATA
	BoxExtent = FVector(500.f);
	bOnSurfaceOnly = false;
#endif
}

#if WITH_EDITOR
void UIPOperationRandomBox::RunOperation(TArray<FTransform>& Transforms)
{
	Super::RunOperation(Transforms);
	BoxExtent = BoxExtent.GetAbs();
	TArray<FTransform> ResultTransforms;

	for (auto& Transf : Transforms)
	{
		for (int32 i = 0; i < InstancesNum; i++)
		{
			UIPFunctionLibrary::MutateRandomSeed(RandomStream);
			FVector Location = UIPFunctionLibrary::RandomVectorInDelta(BoxExtent, false, bUseRandomStream, RandomStream);

			if (bOnSurfaceOnly)
			{
				Location = Location.GetSafeNormal() * BoxExtent * 2.f;
				Location = UIPFunctionLibrary::ClampVector(Location, -BoxExtent, BoxExtent);
			}

			ResultTransforms.Add(Transf * FTransform(Transf.Rotator(), Location, FVector::OneVector));
		}
	}

	Transforms = ResultTransforms;
}
#endif
