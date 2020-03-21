// Dmitriy Barannik aka redbox, 2020

#include "Components/Operations/IPOperationArc.h"
#include "InstancedPlugin.h"
#include "DrawDebugHelpers.h"

UIPOperationArc::UIPOperationArc()
{
#if WITH_EDITORONLY_DATA
	Point1 = FVector::ZeroVector;
	Point2 = FVector(500.f, 500.f, 0.f);
	Point3 = FVector(1000.f, 0.f, 0.f);
	bOrientToCenter = false;
#endif
}

#if WITH_EDITOR
void UIPOperationArc::RunOperation(TArray<FTransform>& Transforms)
{
	Super::RunOperation(Transforms);
	TArray<FTransform> ResultTransforms;

	FVector P12 = (Point1 - Point2);
	FVector P23 = (Point2 - Point3);
	FVector P13 = (Point1 - Point3);

	if (FVector::Parallel(P12.GetSafeNormal(), P23.GetSafeNormal()))
	{
		UE_LOG(IPLog, Warning, TEXT("Three arc points are collinear, can't create arc!"));
		ResultTransforms = Transforms;
	}
	else if (Point1.Equals(Point2, 1.f) || Point2.Equals(Point3, 1.f) || Point1.Equals(Point3, 1.f))
	{
		UE_LOG(IPLog, Warning, TEXT("Two of three arc points are coincident, can't create arc!"));
		ResultTransforms = Transforms;
	}
	else
	{
		float Div = 2 * FMath::Pow((FVector::CrossProduct(P12, P23)).Size(), 2);
		float A = FMath::Pow(P23.Size(), 2) * FVector::DotProduct(P12, P13) / Div;
		float B = FMath::Pow(P13.Size(), 2) * FVector::DotProduct(-P12, P23) / Div;
		float C = FMath::Pow(P12.Size(), 2) * FVector::DotProduct(-P13, -P23) / Div;
		FVector ArcCenter = A * Point1 + B * Point2 + C * Point3;

		DrawDebugSphere(GetWorld(), ArcCenter, 10.f, 8, FColor::Cyan, false, 2.f, 0, 1.f);
		DrawDebugLine(GetWorld(), ArcCenter, Point1, FColor::White, false, 2.f, 0, 5.f);
		DrawDebugLine(GetWorld(), ArcCenter, Point2, FColor::White, false, 2.f, 0, 5.f);
		DrawDebugLine(GetWorld(), ArcCenter, Point3, FColor::White, false, 2.f, 0, 5.f);

		FVector P1C = Point1 - ArcCenter;
		FVector P1CN = P1C.GetSafeNormal();
		float Radius = P1C.Size();
		FVector P2CN = (Point2 - ArcCenter).GetSafeNormal();
		FVector P3CN = (Point3 - ArcCenter).GetSafeNormal();

		FVector UpN = FVector::CrossProduct(P1CN, P2CN);
		if (FVector::DotProduct(UpN, FVector::UpVector) < 0)
		{
			UpN = -UpN;
		}

		//float DotFwd = FVector::DotProduct(P1CN, FVector::ForwardVector);
		//float P1Angle = 0.f;//FMath::RadiansToDegrees(FMath::Acos(DotFwd));
		//float DotRt = FVector::DotProduct(P1CN, FVector::RightVector);

		//if (DotRt < 0.f)
		//{
		//	P1Angle = 360.f - P1Angle;
		//}

		//FVector InitialLocation = Point1;//FVector(Radius, 0.f, 0.f);
		//InitialLocation = FRotator(0.f, P1Angle, 0.f).RotateVector(InitialLocation);

		//DrawDebugLine(GetWorld(), ArcCenter, FRotator(0.f, P1Angle, 0.f).RotateVector(FVector::ForwardVector) * Radius, FColor::Red, false, 2.f, 0, 5.f);
		//UE_LOG(IPLog, Warning, TEXT("P1Angle = %f"), P1Angle);

		float Dot12 = FVector::DotProduct(P1CN, P2CN);
		float P12Angle = FMath::RadiansToDegrees(FMath::Acos(Dot12));

		//DrawDebugLine(GetWorld(), ArcCenter, FRotator(0.f, P12Angle, 0.f).RotateVector(FVector::ForwardVector) * Radius, FColor::Green, false, 2.f, 0, 5.f);
		//UE_LOG(IPLog, Warning, TEXT("P12Angle = %f"), P12Angle);

		float Dot23 = FVector::DotProduct(P2CN, P3CN);
		float P23Angle = FMath::RadiansToDegrees(FMath::Acos(Dot23));

		//DrawDebugLine(GetWorld(), ArcCenter, FRotator(0.f, P1Angle + P12Angle + P23Angle, 0.f).RotateVector(FVector::ForwardVector) * Radius, FColor::Blue, false, 2.f, 0, 5.f);
		//UE_LOG(IPLog, Warning, TEXT("P23Angle = %f"), P23Angle);

		float ArcAngle = P12Angle + P23Angle;

		//if (((Point3.X - Point1.X)*(Point2.Y - Point1.Y) - (Point3.Y - Point1.Y)*(Point2.X - Point1.X)) < 0)
		//{
		//	ArcAngle = -ArcAngle;
		//}

		for (FTransform Transf : Transforms)
		{
			for (int32 i = 0; i < InstancesNum; i++)
			{
				float RotYaw = 0.f;

				if (InstancesNum > 1)
				{
					RotYaw = ArcAngle * i / (InstancesNum - 1);
				}

				FRotator Rot = FRotationMatrix::MakeFromZ(UpN).Rotator();
				Rot.Yaw = 0.f;
				FQuat Rotation = Rot.Quaternion() * FQuat(FRotator(0, RotYaw, 0));

				FVector Location = ArcCenter + Rotation.RotateVector(P1C);

				if (!bOrientToCenter)
				{
					Rotation = FRotator::ZeroRotator.Quaternion();
				}

				ResultTransforms.Add(Transf * FTransform(Rotation, Location, FVector::OneVector));
			}
		}
	}

	Transforms = ResultTransforms;
}
#endif