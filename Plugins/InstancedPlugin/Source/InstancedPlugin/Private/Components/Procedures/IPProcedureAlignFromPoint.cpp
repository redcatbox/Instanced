// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureAlignFromPoint.h"
#include "CollisionQueryParams.h"

UIPProcedureAlignFromPoint::UIPProcedureAlignFromPoint()
{
	PrimaryComponentTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	AlignPoint = FVector::ZeroVector;
	AlignDistance = 1000.f;
	bReverse = false;
	bOrientToSurface = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureAlignFromPoint::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
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
			FVector TraceDirection = (Location - AlignPoint).GetSafeNormal();
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