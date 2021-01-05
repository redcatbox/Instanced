// redbox, 2021

#include "Actors/IPArcActor.h"

AIPArcActor::AIPArcActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(HISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->bIsEditorOnly = true;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationArc = CreateDefaultSubobject<UIPOperationArc>(TEXT("IPOperationArc"));
	IPOperationArc->SetupAttachment(HISMComponent);
	IPOperationArc->Mobility = EComponentMobility::Static;
	IPOperationArc->bIsEditorOnly = true;
	IPOperationArc->ExecutionOrder = 1;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(HISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->bIsEditorOnly = true;
	IPOperationRandomTransform->ExecutionOrder = 2;
#endif
}
