// redbox, 2022

#include "Actors/IPGrid3DActor.h"

AIPGrid3DActor::AIPGrid3DActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(ISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationGrid3D = CreateDefaultSubobject<UIPOperationGrid3D>(TEXT("IPOperationGrid3D"));
	IPOperationGrid3D->SetupAttachment(ISMComponent);
	IPOperationGrid3D->Mobility = EComponentMobility::Static;
	IPOperationGrid3D->ExecutionOrder = 1;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(ISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->ExecutionOrder = 2;
#endif
}
