// Dmitriy Barannik aka redbox, 2020

#include "Components/Procedures/IPProcedureCircle3D.h"

UIPProcedureCircle3D::UIPProcedureCircle3D()
{
#if WITH_EDITORONLY_DATA
	InstancesNum3D = FIntVector(1);
	StartAngle = 0.f;
	EndAngle = 360.f;
	bAlignWithAngleEnd = false;
	bOrientToCentralAxis = false;
	bCheckerOddEven = false;
	bFlipOddEven_Y = false;
	bFlipOddEven_Z = false;
	bSymmetricalEven = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureCircle3D::RunProcedure(TArray<FTransform>& Transforms)
{
	Super::RunProcedure(Transforms);

	InstancesNum3D = FIntVector(
		FMath::Clamp(InstancesNum3D.X, 1, InstancesNum3D.X),
		FMath::Clamp(InstancesNum3D.Y, 1, InstancesNum3D.Y),
		FMath::Clamp(InstancesNum3D.Z, 1, InstancesNum3D.Z));

	InstancesNum = InstancesNum3D.X * InstancesNum3D.Y * InstancesNum3D.Z;
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		int32 LastIndex_X = InstancesNum3D.X;

		if (bCheckerOddEven && bSymmetricalEven)
		{
			if (bFlipOddEven_Y)
			{
				if (X % 2 == 0)
				{
					LastIndex_X++;
				}
			}
			else
			{
				if (!(X % 2 == 0))
				{
					LastIndex_X++;
				}
			}
		}

		for (int32 X = 0; X < LastIndex_X; ++X)
		{
			for (int32 Y = 0; Y < InstancesNum3D.Y; ++Y)
			{
				for (int32 Z = 0; Z < InstancesNum3D.Z; ++Z)
				{
					float PlacementAngle = EndAngle - StartAngle;
					float RotYaw = PlacementAngle / InstancesNum3D.X;

					if (bAlignWithAngleEnd)
					{
						if (InstancesNum3D.X > 1)
						{
							RotYaw = PlacementAngle / (InstancesNum3D.X - 1);
						}
					}

					float RotYawHalf = RotYaw * 0.5f;
					RotYaw *= X;

					if (bCheckerOddEven)
					{
						if (bFlipOddEven_Z)
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

					FRotator Rotation = FRotator(0, RotYaw + StartAngle, 0);
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