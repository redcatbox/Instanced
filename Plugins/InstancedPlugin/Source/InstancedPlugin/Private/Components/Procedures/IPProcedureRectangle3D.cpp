// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureRectangle3D.h"

UIPProcedureRectangle3D::UIPProcedureRectangle3D()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;

	bNoCornerMeshes = false;
	bOrientOutside = false;
	bReverseOrientation = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureRectangle3D::RunProcedure(TArray<FTransform>& Transforms)
{
	Super::RunProcedure(Transforms);
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
		for (int32 X = 0; X < InstancesNum3D.X; ++X)
			for (int32 Y = 0; Y < InstancesNum3D.Y; ++Y)
				for (int32 Z = 0; Z < InstancesNum3D.Z; ++Z)
					if ((X == 0) || (X == InstancesNum3D.X - 1) || (Y == 0) || (Y == InstancesNum3D.Y - 1))
					{
						FVector Location = InstanceSpace * FVector(X, Y, Z);

						if (bHalfSpaceOffset)
							Location += InstanceSpace * 0.5;

						if (bUseCustomAxes)
							Location = Location.X * CustomAxis_X.GetSafeNormal() + Location.Y * CustomAxis_Y.GetSafeNormal() + Location.Z * CustomAxis_Z.GetSafeNormal();

						FRotator Rotation = FRotator::ZeroRotator;

						if (bOrientOutside)
						{
							if (X == 0)
								Rotation = FRotator(0.f, 0.f, 180.f);

							if (X == InstancesNum3D.X - 1)
								Rotation = FRotator(0.f, 0.f, 0.f);

							if (Y == 0)
								Rotation = FRotator(0.f, 0.f, -90.f);

							if (Y == InstancesNum3D.Y - 1)
								Rotation = FRotator(0.f, 0.f, 90.f);

							if (bReverseOrientation)
								Rotation = Rotation.GetInverse();
						}

						ResultTransforms.Add(Transf * FTransform(Rotation, Location, FVector::OneVector));
					}

	Transforms = ResultTransforms;
}
#endif