// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureAlignByDirection.h"
#include "CollisionQueryParams.h"

UIPProcedureAlignByDirection::UIPProcedureAlignByDirection()
{
	PrimaryComponentTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	AlignDirection = FVector(0.f, 0.f, -1000.f);
	bOrientToSurface = false;
#endif
}

#if WITH_EDITOR
void UIPProcedureAlignByDirection::RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (int32 Index = 0; Index < NumIterations; Index++)
	{
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
			FVector TraceEnd = TraceStart + AlignDirection;
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
	}

	Transforms = ResultTransforms;
}
#endif