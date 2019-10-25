// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureGrid3DHexagonal.h"

UIPProcedureGrid3DHexagonal::UIPProcedureGrid3DHexagonal()
{
	PrimaryComponentTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	bFlipOddEven_X = false;
	bSymmetrical_Y = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureGrid3DHexagonal::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
{
	Super::RunProcedure(NumIterations, Transforms);
	TArray<FTransform> ResultTransforms;

	for (int32 Index = 0; Index < NumIterations; Index++)
		for (FTransform Transf : Transforms)
			for (int32 X = 0; X < InstancesNum3D.X; ++X)
			{
				int32 LastIndex_Y;

				if (bSymmetrical_Y)
				{
					if (bFlipOddEven_X)
					{
						if (!(X % 2 == 0))
							LastIndex_Y = InstancesNum3D.Y;
						else
							LastIndex_Y = InstancesNum3D.Y - 1;
					}
					else
					{
						if (X % 2 == 0)
							LastIndex_Y = InstancesNum3D.Y;
						else
							LastIndex_Y = InstancesNum3D.Y - 1;
					}
				}
				else
					LastIndex_Y = InstancesNum3D.Y;

				for (int32 Y = 0; Y < LastIndex_Y; ++Y)
					for (int32 Z = 0; Z < InstancesNum3D.Z; ++Z)
					{
						//Hexagon space X/Y = 115.5/100
						 FVector Location = FVector(InstanceSpace.X * 0.75 * X, InstanceSpace.Y * Y, InstanceSpace.Z * Z);

						if (bFlipOddEven_X)
						{
							if (!(X % 2 == 0))
								Location = Location;
							else
								Location.Y += InstanceSpace.Y * 0.5;
						}
						else
						{
							if (X % 2 == 0)
								Location = Location;
							else
								Location.Y += InstanceSpace.Y * 0.5;
						}

						if (bHalfSpaceOffset)
							Location = Location + InstanceSpace * 0.5;

						ResultTransforms.Add(Transf * FTransform(Transf.Rotator(), Location, Transf.GetScale3D()));
					}
			}

	Transforms = ResultTransforms;
}
#endif