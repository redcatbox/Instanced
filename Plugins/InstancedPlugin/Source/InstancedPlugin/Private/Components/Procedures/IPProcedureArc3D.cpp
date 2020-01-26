// Dmitriy Barannik aka redbox, 2020

#include "Components/Procedures/IPProcedureArc3D.h"

UIPProcedureArc3D::UIPProcedureArc3D()
{
#if WITH_EDITORONLY_DATA

	InstancesNum3D = FIntVector(1);
	ArcFirstPoint = FVector::ZeroVector;
	ArcSecondPoint = FVector(500.f, 500.f, 0.f);
	ArcThirdPoint = FVector(1000.f, 0.f, 0.f);
	bOrientToCentralAxis = false;
	bCheckerOddEven = false;
	bFlipOddEven = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureArc3D::RunProcedure(TArray<FTransform>& Transforms)
{
	Super::RunProcedure(Transforms);

	InstancesNum3D = FIntVector(
		FMath::Clamp(InstancesNum3D.X, 1, InstancesNum3D.X),
		FMath::Clamp(InstancesNum3D.Y, 1, InstancesNum3D.Y),
		FMath::Clamp(InstancesNum3D.Z, 1, InstancesNum3D.Z));

	InstancesNum = InstancesNum3D.X * InstancesNum3D.Y * InstancesNum3D.Z;
	TArray<FTransform> ResultTransforms;

	FVector FirstSecond = (ArcSecondPoint - ArcFirstPoint).GetSafeNormal();
	FVector SecondThird = (ArcThirdPoint - ArcSecondPoint).GetSafeNormal();
	FVector FirstThird = (ArcThirdPoint - ArcFirstPoint).GetSafeNormal();

	if (FVector::Parallel(FirstSecond, SecondThird))
	{
		UE_LOG(LogTemp, Warning, TEXT("Three arc points are collinear!"));
		ResultTransforms = Transforms;
	}
	else if (ArcFirstPoint == ArcSecondPoint || ArcSecondPoint == ArcThirdPoint || ArcFirstPoint == ArcThirdPoint)
	{
		UE_LOG(LogTemp, Warning, TEXT("Two of three arc points are coincident!"));
		ResultTransforms = Transforms;
	}
	else
	{
		for (FTransform Transf : Transforms)
		{
			for (int32 X = 0; X < InstancesNum3D.X; ++X)
			{
				for (int32 Y = 0; Y < InstancesNum3D.Y; ++Y)
				{
					for (int32 Z = 0; Z < InstancesNum3D.Z; ++Z)
					{
						float ArcAngle = FMath::Acos(FVector::DotProduct(-ArcFirstPoint.GetSafeNormal(), (ArcFirstPoint - ArcFirstPoint).GetSafeNormal()));
						ArcAngle = FMath::RadiansToDegrees(ArcAngle);
						UE_LOG(LogTemp, Warning, TEXT("ArcAngle = %f"), ArcAngle);
						float RotYaw = ArcAngle / InstancesNum3D.X;
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
						FVector Location = Rotation.RotateVector(FVector(LocX, 0, LocZ) + ArcFirstPoint);

						if (!bOrientToCentralAxis)
						{
							Rotation = FRotator::ZeroRotator;
						}

						ResultTransforms.Add(Transf * FTransform(Rotation, Location, FVector::OneVector));
					}
				}
			}
		}
	}

	Transforms = ResultTransforms;
}
#endif