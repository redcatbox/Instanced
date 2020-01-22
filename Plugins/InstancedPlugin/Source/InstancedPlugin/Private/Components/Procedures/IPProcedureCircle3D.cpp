// Dmitriy Barannik aka redbox, 2020

#include "Components/Procedures/IPProcedureCircle3D.h"

UIPProcedureCircle3D::UIPProcedureCircle3D()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;

	InstancesNum3D = FIntVector(1, 1, 1);
	PlacementAngle = 360.f;
	InstanceSpace = FVector(100.f, 100.f, 100.f);
	bOrientToCentralAxis = false;
	bCheckerOddEven = false;
	bFlipOddEven = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureCircle3D::RunProcedure(TArray<FTransform>& Transforms)
{
	InstancesNum3D = FIntVector(
		FMath::Clamp(InstancesNum3D.X, 1, InstancesNum3D.X),
		FMath::Clamp(InstancesNum3D.Y, 1, InstancesNum3D.Y),
		FMath::Clamp(InstancesNum3D.Z, 1, InstancesNum3D.Z));

	InstancesNum = InstancesNum3D.X * InstancesNum3D.Y * InstancesNum3D.Z;
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		for (int32 X = 0; X < InstancesNum3D.X; ++X)
		{
			for (int32 Y = 0; Y < InstancesNum3D.Y; ++Y)
			{
				for (int32 Z = 0; Z < InstancesNum3D.Z; ++Z)
				{
					float RotYaw = PlacementAngle / InstancesNum3D.X;
					float RotYawHalf = RotYaw * 0.5f;
					RotYaw *= X;

					if (bCheckerOddEven)
					{
						if (bFlipOddEven)
						{
							if (Z % 2 == 0)
							{
								RotYaw += RotYawHalf;
							}
						}
						else
						{
							if (!(Z % 2 == 0))
							{
								RotYaw += RotYawHalf;
							}
						}
					}

					FRotator Rotation = FRotator(0, RotYaw, 0);
					float LocX = InstanceSpace.X + InstanceSpace.Y * Y;
					float LocZ = InstanceSpace.Z * Z;
					FVector Location = Rotation.RotateVector(FVector(LocX, 0, LocZ));

					if (!bOrientToCentralAxis)
					{
						Rotation = FRotator::ZeroRotator;
					}

					ResultTransforms.Add(Transf * FTransform(Rotation, Location, FVector::OneVector));
				}
			}
		}
	}

	Transforms = ResultTransforms;
}
#endif