// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureCircle3D.h"

UIPProcedureCircle3D::UIPProcedureCircle3D()
{
	PrimaryComponentTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	InstancesNum3D = FIntVector(1, 1, 1);
	PlacementAngle = 360.f;
	InstanceSpace = FVector(100.f, 100.f, 100.f);
	bOrientToCentralAxis = false;
	bCheckerOddEven = false;
	bFlipOddEven = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureCircle3D::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
{
	InstanceSpace = FVector(
		FMath::Clamp(InstanceSpace.X, 0.f, InstanceSpace.X),
		FMath::Clamp(InstanceSpace.Y, 0.f, InstanceSpace.Y),
		FMath::Clamp(InstanceSpace.Z, 0.f, InstanceSpace.Z));

	TArray<FTransform> ResultTransforms;

	for (int32 Index = 0; Index < NumIterations; Index++)
		for (FTransform Transf : Transforms)
			for (int32 X = 0; X < InstancesNum3D.X; ++X)
				for (int32 Y = 0; Y < InstancesNum3D.Y; ++Y)
					for (int32 Z = 0; Z < InstancesNum3D.Z; ++Z)
					{
						FVector Location;
						FRotator Rotation;

						//Rotation
						float RotYaw = PlacementAngle / InstancesNum3D.X;
						float RotYawHalf = RotYaw * 0.5f;
						RotYaw *= X;

						if (bCheckerOddEven)
						{
							if (bFlipOddEven)
							{
								if (!(Z % 2 == 0))
									RotYaw += RotYawHalf;
							}
							else
							{
								if (Z % 2 == 0)
									RotYaw += RotYawHalf;
							}
						}

						Rotation = FRotator(0, RotYaw, 0);

						//Location
						float LocX = InstanceSpace.X + InstanceSpace.Y * Y;
						float LocZ = InstanceSpace.Z * Z;
						Location = Transf.GetLocation() + FVector(LocX, 0, LocZ);
						Location = Rotation.RotateVector(Location);

						//Rotation
						if (!bOrientToCentralAxis)
							Rotation = Transf.Rotator();

						FTransform NewTransf = FTransform(Rotation, Location, Transf.GetScale3D());
						ResultTransforms.Add(NewTransf);
					}

	Transforms = ResultTransforms;
}
#endif