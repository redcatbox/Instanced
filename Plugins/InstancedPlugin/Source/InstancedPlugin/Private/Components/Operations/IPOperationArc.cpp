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
	float L12 = P12.Size();
	float L23 = P23.Size();
	float L13 = P13.Size();

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
		// Get center
		float Div = 2 * FMath::Pow((P12 ^ P23).Size(), 2);
		float A = (L23 * L23) * (P12 | P13) / Div;
		float B = (L13 * L13) * (-P12 | P23) / Div;
		float C = (L12 * L12) * (-P13 | -P23) / Div;
		FVector ArcCenter = A * Point1 + B * Point2 + C * Point3;

		DrawDebugSphere(GetWorld(), ArcCenter, 25.f, 4, FColor::White, false, 3.f, 0, 2.f);

		// Get vectors
		FVector P1C = Point1 - ArcCenter;
		float Radius = P1C.Size();
		FVector P1CN = P1C.GetSafeNormal();
		FVector P2CN = (Point2 - ArcCenter).GetSafeNormal();
		FVector P3CN = (Point3 - ArcCenter).GetSafeNormal();
		FVector UpN = P12.GetSafeNormal() ^ P13.GetSafeNormal();

		DrawDebugLine(GetWorld(), ArcCenter, ArcCenter + P1CN * Radius, FColor::Cyan, false, 3.f, 0, 5.f);
		DrawDebugLine(GetWorld(), ArcCenter, ArcCenter + P2CN * Radius, FColor::Yellow, false, 3.f, 0, 5.f);
		DrawDebugLine(GetWorld(), ArcCenter, ArcCenter + P3CN * Radius, FColor::Magenta, false, 3.f, 0, 5.f);
		DrawDebugLine(GetWorld(), ArcCenter, ArcCenter + UpN * Radius, FColor::Blue, false, 3.f, 0, 5.f);

		// Get angles
		float Dot12 = P1CN | P2CN;
		float P12Angle = FMath::RadiansToDegrees(FMath::Acos(Dot12));
		float Dot23 = P2CN | P3CN;
		float P23Angle = FMath::RadiansToDegrees(FMath::Acos(Dot23));

		DrawDebugLine(GetWorld(), ArcCenter, ArcCenter + (P1CN ^ UpN) * Radius, FColor::Red, false, 3.f, 0, 5.f);
		DrawDebugLine(GetWorld(), ArcCenter, ArcCenter + (P2CN ^ UpN) * Radius, FColor::Green, false, 3.f, 0, 5.f);

		if ((P2CN | (P1CN ^ UpN)) > 0.f)
		{
			P12Angle = 360.f - P12Angle;
		}
		UE_LOG(IPLog, Warning, TEXT("P12Angle = %f"), P12Angle);

		if ((P3CN | (P2CN ^ UpN)) > 0.f)
		{
			P23Angle = 360.f - P23Angle;
		}
		UE_LOG(IPLog, Warning, TEXT("P23Angle = %f"), P23Angle);

		float ArcAngle = P12Angle + P23Angle;

		for (FTransform Transf : Transforms)
		{
			for (int32 i = 0; i < InstancesNum; i++)
			{
				float RotYaw = 0.f;

				if (InstancesNum > 1)
				{
					RotYaw = ArcAngle * i / (InstancesNum - 1);
				}

				FQuat Rotation = FRotationMatrix::MakeFromXZ(P1CN, UpN).ToQuat() * FQuat(FRotator(0.f, RotYaw, 0.f));
				FVector Location = ArcCenter + Rotation.RotateVector(FVector::ForwardVector * Radius);

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