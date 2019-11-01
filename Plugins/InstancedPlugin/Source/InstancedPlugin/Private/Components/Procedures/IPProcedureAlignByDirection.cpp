// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureAlignByDirection.h"
#include "CollisionQueryParams.h"

UIPProcedureAlignByDirection::UIPProcedureAlignByDirection()
{
#if WITH_EDITORONLY_DATA
	AlignDirection = FVector(0.f, 0.f, -1000.f);
#endif
}

#if WITH_EDITOR
void UIPProcedureAlignByDirection::RunProcedure(TArray<FTransform>& Transforms)
{
	Super::RunProcedure(Transforms);

	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		FVector Location = Transf.GetLocation();
		FQuat Rotation = Transf.GetRotation();

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
		{
			Location = TraceOutHit.Location - GetOwner()->GetActorLocation();
		}

		if (bAlignToSurface)
		{
			Rotation *= GetParentISMComponent()->GetComponentTransform().InverseTransformRotation(FRotationMatrix::MakeFromZ(TraceOutHit.Normal).ToQuat());
		}

		ResultTransforms.Add(FTransform(Rotation, Location, Transf.GetScale3D()));
	}

	Transforms = ResultTransforms;
}
#endif