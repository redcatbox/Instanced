// redbox, 2022

#include "Actors/IPSplinePlacementActor.h"

AIPSplinePlacementActor::AIPSplinePlacementActor()
{
#if WITH_EDITORONLY_DATA
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SplineComponent->SetupAttachment(RootComponent);
	SplineComponent->Mobility = EComponentMobility::Static;

	ISMComponent->SetupAttachment(SplineComponent);

	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(ISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationSplinePlacement = CreateDefaultSubobject<UIPOperationSplinePlacement>(TEXT("IPOperationSplinePlacement"));
	IPOperationSplinePlacement->SetupAttachment(ISMComponent);
	IPOperationSplinePlacement->Mobility = EComponentMobility::Static;
	IPOperationSplinePlacement->ExecutionOrder = 1;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(ISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->ExecutionOrder = 2;
#endif
}

void AIPSplinePlacementActor::OnConstruction(const FTransform& Transform)
{
#if WITH_EDITOR
	RunGeneration();
#endif
}
