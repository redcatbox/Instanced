// redbox, 2022

#include "Actors/IPSpiralActor.h"

AIPSpiralActor::AIPSpiralActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(ISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationSpiral = CreateDefaultSubobject<UIPOperationSpiral>(TEXT("IPOperationSpiral"));
	IPOperationSpiral->SetupAttachment(ISMComponent);
	IPOperationSpiral->Mobility = EComponentMobility::Static;
	IPOperationSpiral->ExecutionOrder = 1;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(ISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->ExecutionOrder = 2;
#endif
}
