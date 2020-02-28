// Dmitriy Barannik aka redbox, 2020

#include "Components/Operations/IPOperationSplinePlacement.h"

UIPOperationSplinePlacement::UIPOperationSplinePlacement()
{
#if WITH_EDITORONLY_DATA
	bOrientBySplineEditCondition = true;
	bPlaceBetweenPointsEditCondition = true;
	bOrientBySpline = false;
	bPlaceBetweenPoints = false;
	bOrientByPoints = false;
	bScaleBetweenPoints = false;
	XSizeToScale = 100.f;
#endif
}

#if WITH_EDITOR
void UIPOperationSplinePlacement::RunOperation(TArray<FTransform>& Transforms)
{
	USplineComponent* SplineComponent = GetParentSplineComponent();

	if (SplineComponent)
	{
		if (bPlaceBetweenPoints)
		{
			bInstancesNumEditCondition = false;
			InstancesNum = SplineComponent->GetNumberOfSplinePoints() - 1;
		}
		else
		{
			bInstancesNumEditCondition = true;
		}

		if (bOrientBySpline)
		{
			bPlaceBetweenPointsEditCondition = false;
			bPlaceBetweenPoints = false;
		}
		else
		{
			bPlaceBetweenPointsEditCondition = true;
		}

		if (bPlaceBetweenPoints)
		{
			bOrientBySplineEditCondition = false;
			bOrientBySpline = false;
		}
		else
		{
			bOrientBySplineEditCondition = true;
		}

		XSizeToScale = FMath::Clamp(XSizeToScale, 0.f, 1000000.f);

		TArray<FTransform> ResultTransforms;
		bool bLoop = SplineComponent->IsClosedLoop();

		if (bPlaceBetweenPoints)
		{
			InstancesNum = SplineComponent->GetNumberOfSplinePoints() - 1;

			if (bLoop)
			{
				InstancesNum++;
			}
		}

		for (FTransform Transf : Transforms)
		{
			for (int32 i = 0; i < InstancesNum; i++)
			{
				FVector Location;
				FRotator Rotation;
				FVector Scale;

				//Location
				float Distance = SplineComponent->GetSplineLength() * i / (InstancesNum - 1);
				Location = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);

				FVector CurrentLocation;
				FVector NextLocation;

				if (bPlaceBetweenPoints)
				{
					CurrentLocation = SplineComponent->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Local);
					NextLocation = SplineComponent->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);

					if (bLoop)
					{
						if (i != InstancesNum)
						{
							NextLocation = SplineComponent->GetLocationAtSplinePoint(i + 1, ESplineCoordinateSpace::Local);
						}
						else
						{
							NextLocation = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Local);
						}
					}

					Location = (CurrentLocation + NextLocation) * 0.5;
				}

				Location += Transf.GetLocation();

				//Rotation
				Rotation = Transf.Rotator();

				if (bOrientBySpline && !bPlaceBetweenPoints)
				{
					Rotation += SplineComponent->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
				}
				else
				{
					if (bPlaceBetweenPoints && bOrientByPoints)
					{
						Rotation += FRotationMatrix::MakeFromX((NextLocation - CurrentLocation).GetSafeNormal()).Rotator();
					}
				}

				//Scale
				Scale = Transf.GetScale3D();

				if (bPlaceBetweenPoints && bOrientByPoints && bScaleBetweenPoints)
				{
					Scale.X = Scale.X * (NextLocation - CurrentLocation).Size() / XSizeToScale;
				}

				FTransform NewTransf = FTransform(Rotation, Location, Scale);
				ResultTransforms.Add(NewTransf);
			}
		}

		Transforms = ResultTransforms;
	}
}
#endif

USplineComponent* UIPOperationSplinePlacement::GetParentSplineComponent()
{
	TArray<USceneComponent*> ParentComps;
	GetParentComponents(ParentComps);

	if (ParentComps.Num() > 0)
	{
		for (USceneComponent* SComp : ParentComps)
		{
			if (USplineComponent* ParentSplineComponent = Cast<USplineComponent>(SComp))
			{
				return ParentSplineComponent;
			}
		}
	}

	return nullptr;
}