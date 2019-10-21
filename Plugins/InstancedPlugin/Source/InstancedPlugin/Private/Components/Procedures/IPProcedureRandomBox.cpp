// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureRandomBox.h"

UIPProcedureRandomBox::UIPProcedureRandomBox()
{
	PrimaryComponentTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	BoxExtent = FVector(500.f, 500.f, 500.f);
	bOnSurfaceOnly = false;

	bUseRandomStreamEditCondition = true;
	bUseRandomStream = false;
	bUseRandomStreamSeedEditCondition = false;
	RandomStreamSeed = 0;

	bUseInstancesNum = true;
#endif
}

#if WITH_EDITOR
void UIPProcedureRandomBox::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
{
	Super::RunProcedure(NumIterations, Transforms);
	BoxExtent = BoxExtent.GetAbs();
	TArray<FTransform> ResultTransforms;

	for (int32 Index = 0; Index < NumIterations; Index++)
		for (FTransform Transf : Transforms)
		{
			UIPFunctionLibrary::MutateRandomSeed(RandomStream);
			FVector Location;
			FRotator Rotation;
			FVector Scale;

			//Location
			Location = UIPFunctionLibrary::RandomVectorInDelta(BoxExtent, false, bUseRandomStream, RandomStream);

			if (bOnSurfaceOnly)
			{
				Location = Location.GetSafeNormal() * BoxExtent * 2.f;
				Location = UIPFunctionLibrary::ClampVector(Location, -BoxExtent, BoxExtent);
			}

			//Rotation
			Rotation = Transf.Rotator();

			//Scale
			Scale = Transf.GetScale3D();

			FTransform NewTransf = Transf * FTransform(Rotation, Location, Scale);
			ResultTransforms.Add(NewTransf);
		}

	Transforms = ResultTransforms;
}
#endif