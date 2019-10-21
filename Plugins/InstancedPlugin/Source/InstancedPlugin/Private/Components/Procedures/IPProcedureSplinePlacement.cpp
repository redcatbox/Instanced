// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureSplinePlacement.h"

UIPProcedureSplinePlacement::UIPProcedureSplinePlacement()
{
	PrimaryComponentTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	bOrientBySplineEditCondition = true;
	bPlaceBetweenPointsEditCondition = true;

	bOrientBySpline = false;
	bPlaceBetweenPoints = false;
	bOrientByPoints = false;
	bScaleBetweenPoints = false;
	XSizeToScale = 100.f;

	bUseInstancesNum = true;
#endif
}

#if WITH_EDITOR
void UIPProcedureSplinePlacement::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
{
	if (bOrientBySpline)
	{
		bPlaceBetweenPointsEditCondition = false;
		bPlaceBetweenPoints = false;
	}
	else
		bPlaceBetweenPointsEditCondition = true;

	if (bPlaceBetweenPoints)
	{
		bOrientBySplineEditCondition = false;
		bOrientBySpline = false;
	}
	else
		bOrientBySplineEditCondition = true;

	XSizeToScale = FMath::Clamp(XSizeToScale, 0.f, 1000000.f);

	TArray<FTransform> ResultTransforms;
	bool bLoop = SplineComponent->IsClosedLoop();

	if (bPlaceBetweenPoints)
	{
		NumIterations = SplineComponent->GetNumberOfSplinePoints() - 1;

		if (bLoop)
			NumIterations++;
	}

	for (int32 Index = 0; Index < NumIterations; Index++)
		for (FTransform Transf : Transforms)
		{
			FVector Location;
			FRotator Rotation;
			FVector Scale;

			//Location
			float Distance = SplineComponent->GetSplineLength() * Index / (NumIterations - 1);
			Location = SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);

			FVector CurrentLocation;
			FVector NextLocation;

			if (bPlaceBetweenPoints)
			{
				CurrentLocation = SplineComponent->GetLocationAtSplinePoint(Index, ESplineCoordinateSpace::Local);
				NextLocation = SplineComponent->GetLocationAtSplinePoint(Index + 1, ESplineCoordinateSpace::Local);

				if (bLoop)
				{
					if (Index != NumIterations)
						NextLocation = SplineComponent->GetLocationAtSplinePoint(Index + 1, ESplineCoordinateSpace::Local);
					else
						NextLocation = SplineComponent->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Local);
				}

				Location = (CurrentLocation + NextLocation) * 0.5;
			}

			Location += Transf.GetLocation();

			//Rotation
			Rotation = Transf.Rotator();

			if (bOrientBySpline && !bPlaceBetweenPoints)
				Rotation += SplineComponent->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Local);
			else
			{
				if (bPlaceBetweenPoints && bOrientByPoints)
					Rotation += FRotationMatrix::MakeFromX((NextLocation - CurrentLocation).GetSafeNormal()).Rotator();
			}

			//Scale
			Scale = Transf.GetScale3D();

			if (bPlaceBetweenPoints && bOrientByPoints && bScaleBetweenPoints)
				Scale.X = Scale.X * (NextLocation - CurrentLocation).Size() / XSizeToScale;

			FTransform NewTransf = FTransform(Rotation, Location, Scale);
			ResultTransforms.Add(NewTransf);
		}

	Transforms = ResultTransforms;
}
#endif