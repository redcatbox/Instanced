// Dmitriy Barannik aka redbox, 2020

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
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		FVector Location = Transf.GetLocation();
		FVector TraceStart = GetParentISMComponent()->GetComponentTransform().TransformPosition(Location);
		FVector TraceDirection = GetParentISMComponent()->GetComponentTransform().TransformVector(AlignDirection.GetSafeNormal());

		if (bReverse)
		{
			TraceDirection = -TraceDirection;
		}

		float TraceDistance = AlignDirection.Size();
		FVector TraceEnd = TraceStart + TraceDirection * TraceDistance;

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