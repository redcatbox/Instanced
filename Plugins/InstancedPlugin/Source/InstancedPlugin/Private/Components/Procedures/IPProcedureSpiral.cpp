// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureSpiral.h"

UIPProcedureSpiral::UIPProcedureSpiral()
{
	PrimaryComponentTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	InitialLinearVelocity = FVector(100.f, 0.f, 0.f);
	LinearAcceleration = FVector(0.f, 0.f, 0.f);
	AngularVelocity = FVector(0.f, 0.f, 360.f);
	Time = 1.f;
	bOrientToCentralAxis = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureSpiral::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (int32 Index = 0; Index < NumIterations; Index++)
		for (FTransform Transf : Transforms)
		{
			FVector Location;
			FRotator Rotation;

			int32 Intervals = NumIterations - 1;
			float IntervalFactor = (float) Index / Intervals;
			float SpiralAngle = (AngularVelocity * Time).Size();
			float RotYaw = SpiralAngle * IntervalFactor;
			Rotation = FRotator(0, RotYaw, 0);

			//Location
			FVector LinearVelocity = InitialLinearVelocity + LinearAcceleration * Time;
			Location = Transf.GetLocation() + LinearVelocity * Time * IntervalFactor;
			Location = Rotation.RotateVector(Location);

			//Rotation
			if (!bOrientToCentralAxis)
				Rotation = Transf.Rotator();

			ResultTransforms.Add(FTransform(Rotation, Location, Transf.GetScale3D()));
		}

	Transforms = ResultTransforms;
}
#endif