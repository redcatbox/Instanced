// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureRandomSphere.h"

UIPProcedureRandomSphere::UIPProcedureRandomSphere()
{
#if WITH_EDITORONLY_DATA
	BoxExtent = FVector(500.f, 500.f, 500.f);
	bOnSurfaceOnly = false;
	bOrientToCenter = false;

	bUseRandomStreamEditCondition = true;
	bUseRandomStream = false;
	bUseRandomStreamSeedEditCondition = false;
	RandomStreamSeed = 0;
#endif
}

#if WITH_EDITOR
void UIPProcedureRandomSphere::RunProcedure(TArray<FTransform>& Transforms)
{
	Super::RunProcedure(Transforms);
	BoxExtent = BoxExtent.GetAbs();
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
		for (int32 i = 0; i < InstancesNum; i++)
		{
			UIPFunctionLibrary::MutateRandomSeed(RandomStream);
			FVector Location = FMath::VRand() * BoxExtent;
			FRotator Rotation = Transf.Rotator();

			if (bUseRandomStream)
				Location = RandomStream.VRand() * BoxExtent;

			if (!bOnSurfaceOnly)
				Location = Location * UIPFunctionLibrary::RandomVectorInDelta(FVector(1.f, 1.f, 1.f), false, bUseRandomStream, RandomStream);

			if (bOrientToCenter)
				Rotation += FRotationMatrix::MakeFromX(Location.GetSafeNormal()).Rotator();

			ResultTransforms.Add(Transf * FTransform(Rotation, Location, FVector::OneVector));
		}

	Transforms = ResultTransforms;
}
#endif