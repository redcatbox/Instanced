// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureAlignFromPoint.h"
#include "CollisionQueryParams.h"

UIPProcedureAlignFromPoint::UIPProcedureAlignFromPoint()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;

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

	for (FTransform Transf : Transforms)
	{
		FVector Location = Transf.GetLocation();
		FRotator Rotation = Transf.Rotator();

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

		if (bOrientToSurface)
			Rotation += FRotationMatrix::MakeFromZ(TraceOutHit.Normal).Rotator();

		FTransform NewTransf = FTransform(Rotation, Location, Transf.GetScale3D());
		ResultTransforms.Add(NewTransf);
	}

	Transforms = ResultTransforms;
}
#endif