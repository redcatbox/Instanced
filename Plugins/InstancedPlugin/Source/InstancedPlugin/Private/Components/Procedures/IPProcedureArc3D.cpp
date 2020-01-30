// Dmitriy Barannik aka redbox, 2020

#include "Components/Procedures/IPProcedureArc3D.h"
#include "DrawDebugHelpers.h"

UIPProcedureArc3D::UIPProcedureArc3D()
{
#if WITH_EDITORONLY_DATA
	InstancesNum3D = FIntVector(1);
	Point1 = FVector::ZeroVector;
	Point2 = FVector(500.f, 500.f, 0.f);
	Point3 = FVector(1000.f, 0.f, 0.f);
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

	FVector P12 = (Point1 - Point2);
	FVector P23 = (Point2 - Point3);
	FVector P13 = (Point1 - Point3);

	if (FVector::Parallel(P12.GetSafeNormal(), P23.GetSafeNormal()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Three arc points are collinear, can't create arc!"));
		ResultTransforms = Transforms;
	}
	else if (Point1 == Point2 || Point2 == Point3 || Point1 == Point3)
	{
		UE_LOG(LogTemp, Warning, TEXT("Two of three arc points are coincident, can't create arc!"));
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
						float Div = 2 * FMath::Pow((FVector::CrossProduct(P12, P23)).Size(), 2);
						float A = FMath::Pow(P23.Size(), 2) * FVector::DotProduct(P12, P13) / Div;
						float B = FMath::Pow(P13.Size(), 2) * FVector::DotProduct(-P12, P23) / Div;
						float C = FMath::Pow(P12.Size(), 2) * FVector::DotProduct(-P13, -P23) / Div;
						FVector ArcCenter = A * Point1 + B * Point2 + C * Point3;
						InstanceSpace.X = (Point1 - ArcCenter).Size();

						FVector P1CN = (Point1 - ArcCenter).GetSafeNormal();
						float DotFwd = FVector::DotProduct(P1CN, FVector::ForwardVector);
						float DotRt = FVector::DotProduct(P1CN, FVector::RightVector);
						float Point1Angle = FMath::RadiansToDegrees(FMath::Acos(DotFwd));

						if (DotRt < 0.f)
						{
							Point1Angle = 360.f - Point1Angle;
						}

						FVector P2CN = (Point2 - ArcCenter).GetSafeNormal();
						DotFwd = FVector::DotProduct(P2CN, FVector::ForwardVector);
						DotRt = FVector::DotProduct(P2CN, FVector::RightVector);
						float Point2Angle = FMath::RadiansToDegrees(FMath::Acos(DotFwd));

						if (DotRt < 0.f)
						{
							Point2Angle = 360.f - Point2Angle;
						}

						FVector P3CN = (Point3 - ArcCenter).GetSafeNormal();
						DotFwd = FVector::DotProduct(P3CN, FVector::ForwardVector);
						DotRt = FVector::DotProduct(P3CN, FVector::RightVector);
						float Point3Angle = FMath::RadiansToDegrees(FMath::Acos(DotFwd));

						if (DotRt < 0.f)
						{
							Point3Angle = 360.f - Point3Angle;
						}

						UE_LOG(LogTemp, Warning, TEXT("Point1Angle = %f"), Point1Angle);
						UE_LOG(LogTemp, Warning, TEXT("Point2Angle = %f"), Point2Angle);
						UE_LOG(LogTemp, Warning, TEXT("Point3Angle = %f"), Point3Angle);
						float Radius = (ArcCenter - Point1).Size();
						DrawDebugLine(this->GetWorld(), ArcCenter, ArcCenter + P1CN * Radius, FColor::Cyan, false, 1.f, 0, 5.f);
						DrawDebugLine(this->GetWorld(), ArcCenter, ArcCenter + P2CN * Radius, FColor::Cyan, false, 1.f, 0, 5.f);
						DrawDebugLine(this->GetWorld(), ArcCenter, ArcCenter + P3CN * Radius, FColor::Cyan, false, 1.f, 0, 5.f);

						float ArcAngle = Point3Angle - Point1Angle;

						//if ()
						//{
						//	ArcAngle = -ArcAngle;
						//}

						float RotYaw = 0.f;
						
						if (InstancesNum3D.X > 1)
						{
							RotYaw = ArcAngle / InstancesNum3D.X - 1;
						}

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
						FVector Location = Rotation.RotateVector(FVector(LocX, 0, LocZ)) + ArcCenter;

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