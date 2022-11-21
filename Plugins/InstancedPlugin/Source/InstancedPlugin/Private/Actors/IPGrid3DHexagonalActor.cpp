// redbox, 2022

#include "Actors/IPGrid3DHexagonalActor.h"

AIPGrid3DHexagonalActor::AIPGrid3DHexagonalActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(ISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationGrid3DHexagonal = CreateDefaultSubobject<UIPOperationGrid3DHexagonal>(TEXT("IPOperationGrid3DHexagonal"));
	IPOperationGrid3DHexagonal->SetupAttachment(ISMComponent);
	IPOperationGrid3DHexagonal->Mobility = EComponentMobility::Static;
	IPOperationGrid3DHexagonal->ExecutionOrder = 1;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(ISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->ExecutionOrder = 2;
#endif
}
