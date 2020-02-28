// Dmitriy Barannik aka redbox, 2020

#include "Components/Operations/IPOperationGrid3D.h"

#if WITH_EDITOR
void UIPOperationGrid3D::RunOperation(TArray<FTransform>& Transforms)
{
	Super::RunOperation(Transforms);
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		for (int32 X = 0; X < InstancesNum3D.X; ++X)
		{
			for (int32 Y = 0; Y < InstancesNum3D.Y; ++Y)
			{
				for (int32 Z = 0; Z < InstancesNum3D.Z; ++Z)
				{
					FVector Location = InstanceSpace * FVector(X, Y, Z);

					if (bHalfSpaceOffset)
					{
						Location += InstanceSpace * 0.5;
					}

					if (bUseCustomAxes)
					{
						Location = Location.X * CustomAxis_X.GetSafeNormal() + Location.Y * CustomAxis_Y.GetSafeNormal() + Location.Z * CustomAxis_Z.GetSafeNormal();
					}

					FRotator Rotation = FRotator::ZeroRotator;

					if (bOrientByCustomAxes)
					{
						Rotation = FRotationMatrix::MakeFromX((X * CustomAxis_X.GetSafeNormal() + Y * CustomAxis_Y.GetSafeNormal() + Z * CustomAxis_Z.GetSafeNormal()).GetSafeNormal()).Rotator();
					}

					ResultTransforms.Add(Transf * FTransform(Rotation, Location, FVector::OneVector));
				}
			}
		}
	}

	Transforms = ResultTransforms;
}
#endif