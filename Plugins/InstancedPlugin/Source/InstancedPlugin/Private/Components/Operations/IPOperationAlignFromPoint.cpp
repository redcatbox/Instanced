// redbox, 2021

#include "Components/Operations/IPOperationAlignFromPoint.h"
#include "CollisionQueryParams.h"

UIPOperationAlignFromPoint::UIPOperationAlignFromPoint()
{
#if WITH_EDITORONLY_DATA
	AlignPoint = FVector::ZeroVector;
	AlignDistance = 1000.f;
#endif
}

#if WITH_EDITOR
void UIPOperationAlignFromPoint::RunOperation(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (auto& Transf : Transforms)
	{
		FVector Location = Transf.GetLocation();
		FQuat Rotation = Transf.GetRotation();

		if (UInstancedStaticMeshComponent* ParentISMComp = GetParentISMComponent())
		{
			const FVector TraceStart = ParentISMComp->GetComponentTransform().TransformPosition(Location);
			FVector TraceDirection = ParentISMComp->GetComponentTransform().TransformVector((Location - AlignPoint).GetSafeNormal());

			if (bReverse)
			{
				TraceDirection = -TraceDirection;
			}

			const FVector TraceEnd = TraceStart + TraceDirection * AlignDistance;

			FHitResult TraceOutHit(ForceInit);
			const bool bHit = UKismetSystemLibrary::LineTraceSingle(GetOwner(), TraceStart, TraceEnd, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, TraceOutHit, bIgnoreSelf, FLinearColor::Red, FLinearColor::Green, DrawTime);

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
