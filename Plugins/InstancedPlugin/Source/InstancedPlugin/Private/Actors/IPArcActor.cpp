// redbox, 2022

#include "Actors/IPArcActor.h"

AIPArcActor::AIPArcActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(ISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationArc = CreateDefaultSubobject<UIPOperationArc>(TEXT("IPOperationArc"));
	IPOperationArc->SetupAttachment(ISMComponent);
	IPOperationArc->Mobility = EComponentMobility::Static;
	IPOperationArc->ExecutionOrder = 1;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(ISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->ExecutionOrder = 2;
#endif
}
