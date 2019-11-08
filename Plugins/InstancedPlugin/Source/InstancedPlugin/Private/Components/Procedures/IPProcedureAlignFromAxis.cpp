// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureAlignFromAxis.h"

UIPProcedureAlignFromAxis::UIPProcedureAlignFromAxis()
{
#if WITH_EDITORONLY_DATA
	AlignAxisStart = FVector::ZeroVector;
	AlignAxisEnd = FVector(0.f, 0.f, 1000.f);
	AlignDistance = 1000.f;
#endif
}

#if WITH_EDITOR
void UIPProcedureAlignFromAxis::RunProcedure(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		FVector Location = Transf.GetLocation();
		FVector TraceStart = GetParentISMComponent()->GetComponentTransform().TransformPosition(Location);
		FVector TraceDirection = AlignAxisStart - AlignAxisEnd;
		TraceDirection = -FVector::CrossProduct(FVector::CrossProduct(Location, TraceDirection), TraceDirection).GetSafeNormal();
		TraceDirection = GetParentISMComponent()->GetComponentTransform().TransformVector(TraceDirection);

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