// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureRandomBox.h"

UIPProcedureRandomBox::UIPProcedureRandomBox()
{
#if WITH_EDITORONLY_DATA
	BoxExtent = FVector(500.f, 500.f, 500.f);
	bOnSurfaceOnly = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureRandomBox::RunProcedure(TArray<FTransform>& Transforms)
{
	Super::RunProcedure(Transforms);
	BoxExtent = BoxExtent.GetAbs();
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
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