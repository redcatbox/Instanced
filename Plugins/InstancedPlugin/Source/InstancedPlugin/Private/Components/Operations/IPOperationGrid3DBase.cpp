// Dmitriy Barannik aka redbox, 2020

#include "Components/Operations/IPOperationGrid3DBase.h"

UIPOperationGrid3DBase::UIPOperationGrid3DBase()
{
#if WITH_EDITORONLY_DATA
	InstancesNum3D = FIntVector(1);
	bUseCustomAxes = false;
	CustomAxis_X = FVector(100.f, 0.f, 0.f);
	CustomAxis_Y = FVector(0.f, 100.f, 0.f);
	CustomAxis_Z = FVector(0.f, 0.f, 100.f);
	bOrientByCustomAxes = false;
#endif
}

#if WITH_EDITOR
void UIPOperationGrid3DBase::RunOperation(TArray<FTransform>& Transforms)
{
	Super::RunOperation(Transforms);

	InstancesNum3D = FIntVector(
		FMath::Clamp(InstancesNum3D.X, 1, InstancesNum3D.X),
		FMath::Clamp(InstancesNum3D.Y, 1, InstancesNum3D.Y),
		FMath::Clamp(InstancesNum3D.Z, 1, InstancesNum3D.Z));

	InstancesNum = InstancesNum3D.X * InstancesNum3D.Y * InstancesNum3D.Z;
}
#endif