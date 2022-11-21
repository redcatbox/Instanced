// redbox, 2022

#include "Actors/IPRandomBoxAlignedActor.h"

AIPRandomBoxAlignedActor::AIPRandomBoxAlignedActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(ISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationRandomBox = CreateDefaultSubobject<UIPOperationRandomBox>(TEXT("IPOperationRandomBox"));
	IPOperationRandomBox->SetupAttachment(ISMComponent);
	IPOperationRandomBox->Mobility = EComponentMobility::Static;
	IPOperationRandomBox->ExecutionOrder = 1;

	IPOperationAlignByDirection = CreateDefaultSubobject<UIPOperationAlignByDirection>(TEXT("IPOperationAlignByDirection"));
	IPOperationAlignByDirection->SetupAttachment(ISMComponent);
	IPOperationAlignByDirection->Mobility = EComponentMobility::Static;
	IPOperationAlignByDirection->ExecutionOrder = 2;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(ISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->ExecutionOrder = 3;
#endif
}
