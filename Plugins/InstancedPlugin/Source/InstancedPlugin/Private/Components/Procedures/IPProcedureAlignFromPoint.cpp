// Dmitriy Barannik aka redbox, 2020

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
		FQuat Rotation = Transf.GetRotation();

		if (UInstancedStaticMeshComponent* ParentISMComp = GetParentISMComponent())
		{
			FVector TraceStart = ParentISMComp->GetComponentTransform().TransformPosition(Location);
			FVector TraceDirection = ParentISMComp->GetComponentTransform().TransformVector((Location - AlignPoint).GetSafeNormal());

			if (bReverse)
			{
				TraceDirection = -TraceDirection;
			}

			FVector TraceEnd = TraceStart + TraceDirection * AlignDistance;

			FHitResult TraceOutHit(ForceInit);
			bool bHit = UKismetSystemLibrary::LineTraceSingle(GetOwner(), TraceStart, TraceEnd, TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType, TraceOutHit, bIgnoreSelf, FLinearColor::Red, FLinearColor::Green, DrawTime);

			if (bHit)
			{
				Location = ParentISMComp->GetComponentTransform().InverseTransformPosition(TraceOutHit.Location);
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