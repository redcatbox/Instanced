// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureAlignFromAxis.h"
#include "CollisionQueryParams.h"

UIPProcedureAlignFromAxis::UIPProcedureAlignFromAxis()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;

	AlignAxisStart = FVector::ZeroVector;
	AlignAxisEnd = FVector(0.f, 0.f, 1000.f);
	AlignDistance = 1000.f;
	bReverse = false;
	bOrientToSurface = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureAlignFromAxis::RunProcedure(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		FVector Location = Transf.GetLocation();
		FRotator Rotation = Transf.Rotator();

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

		if (bOrientToSurface)
			Rotation += FRotationMatrix::MakeFromZ(TraceOutHit.Normal).Rotator();

		ResultTransforms.Add(FTransform(Rotation, Location, Transf.GetScale3D()));
	}

	Transforms = ResultTransforms;
}
#endif