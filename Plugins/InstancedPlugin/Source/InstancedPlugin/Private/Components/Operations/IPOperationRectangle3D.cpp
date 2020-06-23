// redbox, 2020

#include "Components/Operations/IPOperationRectangle3D.h"

UIPOperationRectangle3D::UIPOperationRectangle3D()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
	bCornersMeshes = true;
	bOrientCornersMeshesAround = false;
	bSidesMeshes = true;
	bOrientSidesMeshesOutside = false;
	bReverseSidesMeshesOrientation = false;
#endif
}

#if WITH_EDITOR
void UIPOperationRectangle3D::RunOperation(TArray<FTransform>& Transforms)
{
	Super::RunOperation(Transforms);
	TArray<FTransform> ResultTransforms;

	for (auto& Transf : Transforms)
	{
		for (int32 X = 0; X < InstancesNum3D.X; ++X)
		{
			for (int32 Y = 0; Y < InstancesNum3D.Y; ++Y)
			{
				for (int32 Z = 0; Z < InstancesNum3D.Z; ++Z)
				{
					if (X == 0 || X == InstancesNum3D.X - 1 || Y == 0 || Y == InstancesNum3D.Y - 1)
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
						const bool bCornerMeshesCond = (X == 0 && Y == 0)
							|| (X == 0 && Y == InstancesNum3D.Y - 1)
							|| (X == InstancesNum3D.X - 1 && Y == 0)
							|| (X == InstancesNum3D.X - 1 && Y == InstancesNum3D.Y - 1);

						if (bCornersMeshes && bCornerMeshesCond)
						{
							if (bOrientCornersMeshesAround)
							{
								if (X == InstancesNum3D.X - 1 && Y == 0)
								{
									Rotation = FRotator(0.f, 90.f, 0.f);
								}

								if (X == InstancesNum3D.X - 1 && Y == InstancesNum3D.Y - 1)
								{
									Rotation = FRotator(0.f, 180.f, 0.f);
								}

								if (X == 0 && Y == InstancesNum3D.Y - 1)
								{
									Rotation = FRotator(0.f, 270.f, 0.f);
								}
							}

							ResultTransforms.Add(Transf * FTransform(Rotation, Location, FVector::OneVector));
						}

						if (bSidesMeshes && !bCornerMeshesCond)
						{
							if (bOrientSidesMeshesOutside)
							{
								if (bReverseSidesMeshesOrientation)
								{
									if (X == InstancesNum3D.X - 1)
									{
										Rotation = FRotator(0.f, 180.f, 0.f);
									}

									if (Y == 0)
									{
										Rotation = FRotator(0.f, 90.f, 0.f);
									}

									if (Y == InstancesNum3D.Y - 1)
									{
										Rotation = FRotator(0.f, -90.f, 0.f);
									}
								}
								else
								{
									if (X == 0)
									{
										Rotation = FRotator(0.f, 180.f, 0.f);
									}

									if (Y == 0)
									{
										Rotation = FRotator(0.f, -90.f, 0.f);
									}

									if (Y == InstancesNum3D.Y - 1)
									{
										Rotation = FRotator(0.f, 90.f, 0.f);
									}
								}
							}

							ResultTransforms.Add(Transf * FTransform(Rotation, Location, FVector::OneVector));
						}
					}
				}
			}
		}
	}

	Transforms = ResultTransforms;
}
#endif
