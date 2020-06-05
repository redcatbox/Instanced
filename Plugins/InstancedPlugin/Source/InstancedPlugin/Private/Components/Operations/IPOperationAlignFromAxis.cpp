// redbox, 2020

#include "Components/Operations/IPOperationAlignFromAxis.h"

UIPOperationAlignFromAxis::UIPOperationAlignFromAxis()
{
#if WITH_EDITORONLY_DATA
	AlignAxisStart = FVector::ZeroVector;
	AlignAxisEnd = FVector(0.f, 0.f, 1000.f);
	AlignDistance = 1000.f;
#endif
}

#if WITH_EDITOR
void UIPOperationAlignFromAxis::RunOperation(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (FTransform Transf : Transforms)
	{
		FVector Location = Transf.GetLocation();
		FQuat Rotation = Transf.GetRotation();

		if (UInstancedStaticMeshComponent* ParentISMComp = GetParentISMComponent())
		{
			FVector TraceStart = ParentISMComp->GetComponentTransform().TransformPosition(Location);
			FVector TraceDirection = AlignAxisStart - AlignAxisEnd;
			TraceDirection = -((Location ^ TraceDirection) ^ TraceDirection).GetSafeNormal();
			TraceDirection = ParentISMComp->GetComponentTransform().TransformVector(TraceDirection);

			if (bReverse)
			{
				TraceDirection = -TraceDirection;
			}

			FVector TraceEnd = TraceStart + TraceDirection * AlignDistance;
			FHitResult TraceOutHit(ForceInit);
			bool bHit = UKismetSystemLibrary::LineTraceSingle(GetOwner(), TraceStart, TraceEnd, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, TraceOutHit, bIgnoreSelf, FLinearColor::Red, FLinearColor::Green, DrawTime);

			if (bHit)
			{
				Location = TraceOutHit.Location + TraceDirection * OffsetInTraceDirection;
				Location = ParentISMComp->GetComponentTransform().InverseTransformPosition(Location);
			}

			if (bAlignToSurface)
			{
				Rotation = FRotationMatrix::MakeFromZ(ParentISMComp->GetComponentTransform().InverseTransformVectorNoScale(TraceOutHit.Normal)).ToQuat();
			}
		}

		ResultTransforms.Add(FTransform(Rotation, Location, Transf.GetScale3D()));
	}

	Transforms = ResultTransforms;
}
#endif