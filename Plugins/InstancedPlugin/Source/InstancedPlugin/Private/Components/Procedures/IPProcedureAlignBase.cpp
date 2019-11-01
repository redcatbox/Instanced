// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureAlignBase.h"

UIPProcedureAlignBase::UIPProcedureAlignBase()
{
#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
	bAlignToSurface = false;
	bReverse = false;
	bTraceComplex = false;
	bIgnoreSelf = true;
	DrawTime = 5.f;
#endif
}

#if WITH_EDITOR
void UIPProcedureAlignBase::RunProcedure(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		FVector Location = Transf.GetLocation();
		FQuat Rotation = Transf.GetRotation();

		//Trace
		FVector TraceStart = Location + GetOwner()->GetActorLocation();
		FVector TraceDirection = Location.GetSafeNormal();

		if (bReverse)
		{
			TraceDirection = -TraceDirection;
		}

		FVector TraceEnd = TraceStart + TraceDirection;
		FHitResult TraceOutHit(ForceInit);
		bool bHit = UKismetSystemLibrary::LineTraceSingle(GetOwner(), TraceStart, TraceEnd, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, TraceOutHit, bIgnoreSelf, FLinearColor::Red, FLinearColor::Green, DrawTime);

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