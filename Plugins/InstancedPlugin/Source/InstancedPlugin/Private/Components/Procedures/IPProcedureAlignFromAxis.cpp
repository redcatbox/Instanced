// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureAlignFromAxis.h"
#include "CollisionQueryParams.h"

UIPProcedureAlignFromAxis::UIPProcedureAlignFromAxis()
{
	PrimaryComponentTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	AlignAxisStart = FVector::ZeroVector;
	AlignAxisEnd = FVector(0.f, 0.f, 1000.f);
	AlignDistance = 1000.f;
	bReverse = false;
	bOrientToSurface = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureAlignFromAxis::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (int32 Index = 0; Index < NumIterations; Index++)
		for (FTransform Transf : Transforms)
		{
			FVector Location;
			FRotator Rotation;

			//Location
			Location = Transf.GetLocation();

			//Trace
			FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("Trace")), true, GetOwner());
			TraceParams.bReturnPhysicalMaterial = false;
			FHitResult TraceOutHit(ForceInit);
			FVector TraceStart = Location + GetOwner()->GetActorLocation();
			FVector TraceDirection = AlignAxisStart - AlignAxisEnd;
			TraceDirection = -FVector::CrossProduct(FVector::CrossProduct(Location, TraceDirection), TraceDirection).GetSafeNormal();

			if (bReverse)
				TraceDirection = -TraceDirection;

			FVector TraceEnd = TraceStart + TraceDirection * AlignDistance;
			bool bHit = GetWorld()->LineTraceSingleByChannel(
				TraceOutHit,
				TraceStart,
				TraceEnd,
				ECC_Visibility,
				TraceParams
			);

			if (bHit)
				Location = TraceOutHit.Location - GetOwner()->GetActorLocation();

			//Rotation
			Rotation = Transf.Rotator();

			if (bOrientToSurface)
				Rotation += FRotationMatrix::MakeFromZ(TraceOutHit.Normal).Rotator();

			FTransform NewTransf = FTransform(Rotation, Location, Transf.GetScale3D());
			ResultTransforms.Add(NewTransf);
		}

	Transforms = ResultTransforms;
}
#endif