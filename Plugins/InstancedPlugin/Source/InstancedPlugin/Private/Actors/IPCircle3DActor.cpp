// redbox, 2022

#include "Actors/IPCircle3DActor.h"

AIPCircle3DActor::AIPCircle3DActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(ISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationCircle3D = CreateDefaultSubobject<UIPOperationCircle3D>(TEXT("IPOperationCircle3D"));
	IPOperationCircle3D->SetupAttachment(ISMComponent);
	IPOperationCircle3D->Mobility = EComponentMobility::Static;
	IPOperationCircle3D->ExecutionOrder = 1;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(ISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->ExecutionOrder = 2;
#endif
}
