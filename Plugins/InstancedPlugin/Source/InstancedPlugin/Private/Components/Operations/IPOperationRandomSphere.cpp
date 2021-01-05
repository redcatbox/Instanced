// redbox, 2021

#include "Components/Operations/IPOperationRandomSphere.h"

UIPOperationRandomSphere::UIPOperationRandomSphere()
{
#if WITH_EDITORONLY_DATA
	BoxExtent = FVector(500.f);
	bOnSurfaceOnly = false;
	bOrientToCenter = false;
#endif
}

#if WITH_EDITOR
void UIPOperationRandomSphere::RunOperation(TArray<FTransform>& Transforms)
{
	Super::RunOperation(Transforms);
	BoxExtent = BoxExtent.GetAbs();
	TArray<FTransform> ResultTransforms;

	for (auto& Transf : Transforms)
	{
		for (int32 i = 0; i < InstancesNum; i++)
		{
			UIPFunctionLibrary::MutateRandomSeed(RandomStream);
			FVector Location = FMath::VRand() * BoxExtent;
			FRotator Rotation = Transf.Rotator();

			if (bUseRandomStream)
			{
				Location = RandomStream.VRand() * BoxExtent;
			}

			if (!bOnSurfaceOnly)
			{
				Location = Location * UIPFunctionLibrary::RandomVectorInDelta(FVector::OneVector, false, bUseRandomStream, RandomStream);
			}

			if (bOrientToCenter)
			{
				Rotation += FRotationMatrix::MakeFromX(Location.GetSafeNormal()).Rotator();
			}

			ResultTransforms.Add(Transf * FTransform(Rotation, Location, FVector::OneVector));
		}
	}

	Transforms = ResultTransforms;
}
#endif
