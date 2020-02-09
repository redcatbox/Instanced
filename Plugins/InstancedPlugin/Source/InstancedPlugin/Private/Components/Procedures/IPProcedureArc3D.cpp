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

						FVector P1C = Point1 - ArcCenter;
						FVector P1CN = P1C.GetSafeNormal();
						float DotFwd = FVector::DotProduct(P1CN, FVector::ForwardVector);
						float P1Angle = FMath::RadiansToDegrees(FMath::Acos(DotFwd));
						float DotRt = FVector::DotProduct(P1CN, FVector::RightVector);

						if (DotRt < 0.f)
						{
							P1Angle = 360.f - P1Angle;
						}

						FVector P2C = Point2 - ArcCenter;
						FVector P2CN = P2C.GetSafeNormal();
						DotFwd = FVector::DotProduct(P2CN, FVector::ForwardVector);
						float P2Angle = FMath::RadiansToDegrees(FMath::Acos(DotFwd));
						DotRt = FVector::DotProduct(P2CN, FVector::RightVector);

						if (DotRt < 0.f)
						{
							P2Angle = 360.f - P2Angle;
						}

						FVector P3C = Point3 - ArcCenter;
						FVector P3CN = P3C.GetSafeNormal();
						DotFwd = FVector::DotProduct(P3CN, FVector::ForwardVector);
						float P3Angle = FMath::RadiansToDegrees(FMath::Acos(DotFwd));
						DotRt = FVector::DotProduct(P3CN, FVector::RightVector);

						if (DotRt < 0.f)
						{
							P3Angle = 360.f - P3Angle;
						}

						float P12Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(P1CN, P2CN)));
						float P23Angle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(P2CN, P3CN)));

						FVector UpN = FVector::CrossProduct(P1CN, P2CN);

						UE_LOG(LogTemp, Warning, TEXT("P1Angle = %f"), P1Angle);
						UE_LOG(LogTemp, Warning, TEXT("P2Angle = %f"), P2Angle);
						UE_LOG(LogTemp, Warning, TEXT("P3Angle = %f"), P3Angle);
						DrawDebugLine(this->GetWorld(), GetOwner()->GetActorLocation() + ArcCenter, GetOwner()->GetActorLocation() + ArcCenter + P1C, FColor::Cyan, false, 1.f, 0, 5.f);
						DrawDebugLine(this->GetWorld(), GetOwner()->GetActorLocation() + ArcCenter, GetOwner()->GetActorLocation() + ArcCenter + P2C, FColor::Cyan, false, 1.f, 0, 5.f);
						DrawDebugLine(this->GetWorld(), GetOwner()->GetActorLocation() + ArcCenter, GetOwner()->GetActorLocation() + ArcCenter + P3C, FColor::Cyan, false, 1.f, 0, 5.f);
						DrawDebugLine(this->GetWorld(), GetOwner()->GetActorLocation() + ArcCenter, GetOwner()->GetActorLocation() + ArcCenter + UpN * 1000.f, FColor::Yellow, false, 5.f, 0, 5.f);

						float ArcAngle = P3Angle - P1Angle;

						//if (((Point3.X - Point1.X)*(Point2.Y - Point1.Y) - (Point3.Y - Point1.Y)*(Point2.X - Point1.X)) < 0)
						//{
						//	ArcAngle = -ArcAngle;
						//}

						float RotYaw = 0.f;
						
						if (InstancesNum3D.X > 1)
						{
							RotYaw = ArcAngle / (InstancesNum3D.X - 1);
						}

						RotYaw *= X;

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