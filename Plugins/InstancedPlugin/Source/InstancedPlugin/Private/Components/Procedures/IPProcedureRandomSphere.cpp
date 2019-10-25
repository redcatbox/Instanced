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
void UIPProcedureRandomSphere::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
{
	Super::RunProcedure(NumIterations, Transforms);
	BoxExtent = BoxExtent.GetAbs();
	TArray<FTransform> ResultTransforms;

	for (int32 i = 0; i < NumIterations; i++)
		for (FTransform Transf : Transforms)
		{
			UIPFunctionLibrary::MutateRandomSeed(RandomStream);
			FVector Location;
			FRotator Rotation;

			//Location
			Location = FMath::VRand() * BoxExtent;

			if (bUseRandomStream)
				Location = RandomStream.VRand() * BoxExtent;

			if (!bOnSurfaceOnly)
				Location = Location * UIPFunctionLibrary::RandomVectorInDelta(FVector(1.f, 1.f, 1.f), false, bUseRandomStream, RandomStream);

			//Rotation
			Rotation = Transf.Rotator();

			if (bOrientToCenter)
				Rotation += FRotationMatrix::MakeFromX(Location.GetSafeNormal()).Rotator();

			ResultTransforms.Add(Transf * FTransform(Rotation, Location, Transf.GetScale3D()));
		}

	Transforms = ResultTransforms;
}
#endif