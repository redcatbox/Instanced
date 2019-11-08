// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureAlignFromPoint.h"
#include "CollisionQueryParams.h"

UIPProcedureAlignFromPoint::UIPProcedureAlignFromPoint()
{
#if WITH_EDITORONLY_DATA
	AlignPoint = FVector::ZeroVector;
	AlignDistance = 1000.f;
#endif
}

#if WITH_EDITOR
void UIPProcedureAlignFromPoint::RunProcedure(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		FVector Location = Transf.GetLocation();
		FVector TraceStart = GetParentISMComponent()->GetComponentTransform().TransformPosition(Location);
		FVector TraceDirection = GetParentISMComponent()->GetComponentTransform().TransformVector((Location - AlignPoint).GetSafeNormal());
		
		if (bReverse)
		{
			TraceDirection = -TraceDirection;
		}

		FVector TraceEnd = TraceStart + TraceDirection * AlignDistance;

		FHitResult TraceOutHit(ForceInit);
		bool bHit = UKismetSystemLibrary::LineTraceSingle(GetOwner(), TraceStart, TraceEnd, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, TraceOutHit, bIgnoreSelf, FLinearColor::Red, FLinearColor::Green, DrawTime);

		if (bHit)
		{
			Location = GetParentISMComponent()->GetComponentTransform().InverseTransformPosition(TraceOutHit.Location);
		}

		FQuat Rotation = Transf.GetRotation();

		if (bAlignToSurface)
		{
			Rotation = FRotationMatrix::MakeFromZ(GetParentISMComponent()->GetComponentTransform().InverseTransformVectorNoScale(TraceOutHit.Normal)).ToQuat();
		}

		ResultTransforms.Add(FTransform(Rotation, Location, Transf.GetScale3D()));
	}

	Transforms = ResultTransforms;
}
#endif