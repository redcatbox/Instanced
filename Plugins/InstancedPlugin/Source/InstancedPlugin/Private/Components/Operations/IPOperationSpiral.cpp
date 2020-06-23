// redbox, 2020

#include "Components/Operations/IPOperationSpiral.h"

UIPOperationSpiral::UIPOperationSpiral()
{
#if WITH_EDITORONLY_DATA
	InitialLinearVelocity = FVector(100.f, 0.f, 0.f);
	LinearAcceleration = FVector(0.f);
	AngularVelocity = FVector(0.f, 0.f, 360.f);
	Time = 1.f;
	bOrientToCentralAxis = false;
	//bPlaceEvenly = false;
#endif
}

#if WITH_EDITOR
void UIPOperationSpiral::RunOperation(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (auto& Transf : Transforms)
	{
		for (int32 i = 0; i < InstancesNum; i++)
		{
			const int32 Intervals = InstancesNum - 1;
			const float IntervalFactor = (float)i / Intervals;
			const float SpiralAngle = (AngularVelocity * Time).Size();
			const float RotYaw = SpiralAngle * IntervalFactor;
			FRotator Rotation = FRotator(0, RotYaw, 0);
			FVector LinearVelocity = InitialLinearVelocity + LinearAcceleration * Time;
			FVector Location = LinearVelocity * Time * IntervalFactor;
			Location = Rotation.RotateVector(Location);

			if (!bOrientToCentralAxis)
			{
				Rotation = FRotator::ZeroRotator;
			}

			ResultTransforms.Add(Transf * FTransform(Rotation, Location, FVector::OneVector));
		}
	}

	Transforms = ResultTransforms;
}
#endif
