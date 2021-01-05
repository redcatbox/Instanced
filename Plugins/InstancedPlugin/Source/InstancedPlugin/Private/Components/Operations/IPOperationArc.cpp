// redbox, 2021

#include "Components/Operations/IPOperationArc.h"
#include "InstancedPlugin.h"

UIPOperationArc::UIPOperationArc()
{
#if WITH_EDITORONLY_DATA
	Point1 = FVector::ZeroVector;
	Point2 = FVector(500.f, 500.f, 0.f);
	Point3 = FVector(1000.f, 0.f, 0.f);
	bOrientToCenter = false;
	bInvertVertical = false;
#endif
}

// TO DO - this one have an issues when angles between points radiuses is larger than 180 degrees.
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
		const float Div = 2 * FMath::Pow((P12 ^ P23).Size(), 2);
		const float A = L23 * L23 * (P12 | P13) / Div;
		const float B = L13 * L13 * (-P12 | P23) / Div;
		const float C = L12 * L12 * (-P13 | -P23) / Div;
		const FVector ArcCenter = A * Point1 + B * Point2 + C * Point3;

		// Get vectors
		const FVector P1C = Point1 - ArcCenter;
		const float Radius = P1C.Size();
		const FVector P1CN = P1C.GetSafeNormal();
		const FVector P2CN = (Point2 - ArcCenter).GetSafeNormal();
		const FVector P3CN = (Point3 - ArcCenter).GetSafeNormal();
		const FVector UpN = P12.GetSafeNormal() ^ P13.GetSafeNormal();

		// Get angles
		const float Dot12 = P1CN | P2CN;
		float P12Angle = FMath::RadiansToDegrees(FMath::Acos(Dot12));
		const float Dot23 = P2CN | P3CN;
		float P23Angle = FMath::RadiansToDegrees(FMath::Acos(Dot23));

		if ((P2CN | (P1CN ^ UpN)) > 0.f)
		{
			P12Angle = 360.f - P12Angle;
		}

		if ((P3CN | (P2CN ^ UpN)) > 0.f)
		{
			P23Angle = 360.f - P23Angle;
		}

		const float ArcAngle = P12Angle + P23Angle;

		for (auto& Transf : Transforms)
		{
			for (int32 i = 0; i < InstancesNum; i++)
			{
				const float RotYaw = InstancesNum > 1
					? 0.f
					: ArcAngle * i / (InstancesNum - 1);

				FQuat Rot = FRotationMatrix::MakeFromXZ(P1CN, UpN).ToQuat() * FQuat(FRotator(0.f, RotYaw, 0.f));
				FRotator Rotation = Rot.Rotator();
				FVector Location = ArcCenter + Rotation.RotateVector(FVector::ForwardVector * Radius);

				if (!bOrientToCenter)
				{
					Rotation = FRotator::ZeroRotator;
				}

				if (bInvertVertical)
				{
					Rotation = (Rotation.Quaternion() * FRotator(180.f, 0.f, 0.f).Quaternion()).Rotator();
				}

				ResultTransforms.Add(Transf * FTransform(Rotation, Location, FVector::OneVector));
			}
		}
	}

	Transforms = ResultTransforms;
}
#endif
