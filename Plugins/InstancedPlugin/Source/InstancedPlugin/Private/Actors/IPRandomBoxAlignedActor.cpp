// Dmitriy Barannik aka redbox, 2020

#include "Actors/IPRandomBoxAlignedActor.h"

AIPRandomBoxAlignedActor::AIPRandomBoxAlignedActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(HISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->bIsEditorOnly = true;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationRandomBox = CreateDefaultSubobject<UIPOperationRandomBox>(TEXT("IPOperationRandomBox"));
	IPOperationRandomBox->SetupAttachment(HISMComponent);
	IPOperationRandomBox->Mobility = EComponentMobility::Static;
	IPOperationRandomBox->bIsEditorOnly = true;
	IPOperationRandomBox->ExecutionOrder = 1;

	IPOperationAlignByDirection = CreateDefaultSubobject<UIPOperationAlignByDirection>(TEXT("IPOperationAlignByDirection"));
	IPOperationAlignByDirection->SetupAttachment(HISMComponent);
	IPOperationAlignByDirection->Mobility = EComponentMobility::Static;
	IPOperationAlignByDirection->bIsEditorOnly = true;
	IPOperationAlignByDirection->ExecutionOrder = 2;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(HISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->bIsEditorOnly = true;
	IPOperationRandomTransform->ExecutionOrder = 3;
#endif
}