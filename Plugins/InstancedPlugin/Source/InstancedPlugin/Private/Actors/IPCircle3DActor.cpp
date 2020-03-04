// Dmitriy Barannik aka redbox, 2020

#include "Actors/IPCircle3DActor.h"

AIPCircle3DActor::AIPCircle3DActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(HISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->bIsEditorOnly = true;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationCircle3D = CreateDefaultSubobject<UIPOperationCircle3D>(TEXT("IPOperationCircle3D"));
	IPOperationCircle3D->SetupAttachment(HISMComponent);
	IPOperationCircle3D->Mobility = EComponentMobility::Static;
	IPOperationCircle3D->bIsEditorOnly = true;
	IPOperationCircle3D->ExecutionOrder = 1;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(HISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->bIsEditorOnly = true;
	IPOperationRandomTransform->ExecutionOrder = 2;
#endif
}