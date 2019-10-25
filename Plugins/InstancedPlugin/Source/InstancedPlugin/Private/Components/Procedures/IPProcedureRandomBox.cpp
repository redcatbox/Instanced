// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureRandomBox.h"

UIPProcedureRandomBox::UIPProcedureRandomBox()
{
#if WITH_EDITORONLY_DATA
	BoxExtent = FVector(500.f, 500.f, 500.f);
	bOnSurfaceOnly = false;

	bUseRandomStreamEditCondition = true;
	bUseRandomStream = false;
	bUseRandomStreamSeedEditCondition = false;
	RandomStreamSeed = 0;
#endif
}

#if WITH_EDITOR
void UIPProcedureRandomBox::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
{
	Super::RunProcedure(NumIterations, Transforms);
	BoxExtent = BoxExtent.GetAbs();
	TArray<FTransform> ResultTransforms;

	for (int32 i = 0; i < NumIterations; i++)
		for (FTransform Transf : Transforms)
		{
			UIPFunctionLibrary::MutateRandomSeed(RandomStream);
			FVector Location = UIPFunctionLibrary::RandomVectorInDelta(BoxExtent, false, bUseRandomStream, RandomStream);

			if (bOnSurfaceOnly)
			{
				Location = Location.GetSafeNormal() * BoxExtent * 2.f;
				Location = UIPFunctionLibrary::ClampVector(Location, -BoxExtent, BoxExtent);
			}

			ResultTransforms.Add(Transf * FTransform(Transf.Rotator(), Location, Transf.GetScale3D()));
		}

	Transforms = ResultTransforms;
}
#endif