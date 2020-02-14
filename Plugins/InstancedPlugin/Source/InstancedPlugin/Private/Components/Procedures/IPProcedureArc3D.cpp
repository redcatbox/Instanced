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
	bOrientToCenter = false;
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

						FVector P1C = Point1 - ArcCenter;
						FVector P1CN = P1C.GetSafeNormal();
						FVector P2CN = (Point2 - ArcCenter).GetSafeNormal();
						FVector P3CN = (Point3 - ArcCenter).GetSafeNormal();
						FVector UpN = FVector::CrossProduct(P1CN, P2CN);
						float DotFwd = FVector::DotProduct(P1CN, FVector::ForwardVector);
						float P1Angle = FMath::RadiansToDegrees(FMath::Acos(DotFwd));
						float DotRt = FVector::DotProduct(P1CN, FVector::RightVector);

						if (DotRt < 0.f)
						{
							P1Angle = 360.f - P1Angle;
						}

						float P12Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(P1CN, P2CN)));
						float P23Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(P2CN, P3CN)));
						float ArcAngle = P12Angle + P23Angle;

						if (((Point3.X - Point1.X)*(Point2.Y - Point1.Y) - (Point3.Y - Point1.Y)*(Point2.X - Point1.X)) < 0)
						{
							ArcAngle = -ArcAngle;
						}

						float RotYaw = 0.f;
						
						if (InstancesNum3D.X > 1)
						{
							RotYaw = ArcAngle * X / (InstancesNum3D.X - 1);
						}

						FQuat Rotation = FRotationMatrix::MakeFromZ(UpN).ToQuat() * FQuat(FRotator(0, RotYaw + P1Angle, 0));
						InstanceSpace.X = P1C.Size();
						float LocX = InstanceSpace.X + InstanceSpace.Y * Y;
						float LocZ = InstanceSpace.Z * Z;
						FVector Location = ArcCenter + Rotation.RotateVector(FVector(LocX, 0, LocZ));
						
						if (!bOrientToCenter)
						{
							Rotation = FRotator::ZeroRotator.Quaternion();
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