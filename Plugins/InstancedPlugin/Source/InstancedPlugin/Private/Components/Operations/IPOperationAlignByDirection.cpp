// redbox, 2021

#include "Components/Operations/IPOperationAlignByDirection.h"
#include "CollisionQueryParams.h"

UIPOperationAlignByDirection::UIPOperationAlignByDirection()
{
#if WITH_EDITORONLY_DATA
	AlignDirection = FVector(0.f, 0.f, -1000.f);
#endif
}

#if WITH_EDITOR
void UIPOperationAlignByDirection::RunOperation(TArray<FTransform>& Transforms)
{
	TArray<FTransform> ResultTransforms;

	for (auto& Transf : Transforms)
	{
		FVector Location = Transf.GetLocation();
		FQuat Rotation = Transf.GetRotation();

		if (UInstancedStaticMeshComponent* ParentISMComp = GetParentISMComponent())
		{
			const FVector TraceStart = ParentISMComp->GetComponentTransform().TransformPosition(Location);
			FVector TraceDirection = ParentISMComp->GetComponentTransform().TransformVector(AlignDirection.GetSafeNormal());

			if (bReverse)
			{
				TraceDirection = -TraceDirection;
			}

			const float TraceDistance = AlignDirection.Size();
			const FVector TraceEnd = TraceStart + TraceDirection * TraceDistance;
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
