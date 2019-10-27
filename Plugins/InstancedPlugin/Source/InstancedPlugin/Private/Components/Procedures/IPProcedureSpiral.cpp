// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureSpiral.h"

UIPProcedureSpiral::UIPProcedureSpiral()
{
#if WITH_EDITORONLY_DATA
	InitialLinearVelocity = FVector(100.f, 0.f, 0.f);
	LinearAcceleration = FVector(0.f, 0.f, 0.f);
	AngularVelocity = FVector(0.f, 0.f, 360.f);
	Time = 1.f;
	bOrientToCentralAxis = false;
	//bPlaceEvenly = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureSpiral::RunProcedure(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
		for (int32 i = 0; i < InstancesNum; i++)
		{
			//if (bPlaceEvenly)
			//	float SpiralLength = (InitialLinearVelocity * Time + LinearAcceleration * Time * Time / 2 + AngularVelocity * Time).Size();

			int32 Intervals = InstancesNum - 1;
			float IntervalFactor = (float)i / Intervals;
			float SpiralAngle = (AngularVelocity * Time).Size();
			float RotYaw = SpiralAngle * IntervalFactor;
			FRotator Rotation = FRotator(0, RotYaw, 0);
			FVector LinearVelocity = InitialLinearVelocity + LinearAcceleration * Time;
			FVector Location = LinearVelocity * Time * IntervalFactor;
			Location = Rotation.RotateVector(Location);

			if (!bOrientToCentralAxis)
				Rotation = FRotator::ZeroRotator;

			ResultTransforms.Add(Transf * FTransform(Rotation, Location, FVector::OneVector));
		}

	Transforms = ResultTransforms;
}
#endif