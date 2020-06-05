// redbox, 2020

#include "Components/Operations/IPOperationGrid3DHexagonal.h"

UIPOperationGrid3DHexagonal::UIPOperationGrid3DHexagonal()
{
#if WITH_EDITORONLY_DATA
	bFlipOddEven_X = false;
	bSymmetrical_Y = false;
#endif
}

#if WITH_EDITOR
void UIPOperationGrid3DHexagonal::RunOperation(TArray<FTransform>& Transforms)
{
	Super::RunOperation(Transforms);
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		for (int32 X = 0; X < InstancesNum3D.X; ++X)
		{
			int32 LastIndex_Y = InstancesNum3D.Y;

			if (bSymmetrical_Y)
			{
				if (bFlipOddEven_X)
				{
					if (X % 2 == 0)
					{
						LastIndex_Y--;
					}
				}
				else
				{
					if (!(X % 2 == 0))
					{
						LastIndex_Y--;
					}
				}
			}

			for (int32 Y = 0; Y < LastIndex_Y; ++Y)
			{
				for (int32 Z = 0; Z < InstancesNum3D.Z; ++Z)
				{
					//Hexagon space X/Y = 115.5/100
					FVector Location = FVector(InstanceSpace.X * 0.75 * X, InstanceSpace.Y * Y, InstanceSpace.Z * Z);

					if (bFlipOddEven_X)
					{
						if (!(X % 2 == 0))
						{
							Location = Location;
						}
						else
						{
							Location.Y += InstanceSpace.Y * 0.5;
						}
					}
					else
					{
						if (X % 2 == 0)
						{
							Location = Location;
						}
						else
						{
							Location.Y += InstanceSpace.Y * 0.5;
						}
					}

					if (bHalfSpaceOffset)
					{
						Location = Location + InstanceSpace * 0.5;
					}

					ResultTransforms.Add(Transf * FTransform(Transf.Rotator(), Location, FVector::OneVector));
				}
			}
		}
	}

	Transforms = ResultTransforms;
}
#endif