// redbox, 2020

#include "Actors/IPSplinePlacementActor.h"

AIPSplinePlacementActor::AIPSplinePlacementActor()
{
#if WITH_EDITORONLY_DATA
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
	SplineComponent->Mobility = EComponentMobility::Static;
	SplineComponent->bIsEditorOnly = true;

	HISMComponent->SetupAttachment(SplineComponent);

	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(HISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->bIsEditorOnly = true;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationSplinePlacement = CreateDefaultSubobject<UIPOperationSplinePlacement>(TEXT("IPOperationSplinePlacement"));
	IPOperationSplinePlacement->SetupAttachment(HISMComponent);
	IPOperationSplinePlacement->Mobility = EComponentMobility::Static;
	IPOperationSplinePlacement->bIsEditorOnly = true;
	IPOperationSplinePlacement->ExecutionOrder = 1;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(HISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->bIsEditorOnly = true;
	IPOperationRandomTransform->ExecutionOrder = 2;
#endif
}

void AIPSplinePlacementActor::OnConstruction(const FTransform& Transform)
{
#if WITH_EDITOR
	RunGeneration();
#endif
}
