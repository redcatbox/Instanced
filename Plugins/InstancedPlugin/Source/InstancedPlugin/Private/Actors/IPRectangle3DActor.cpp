// Dmitriy Barannik aka redbox, 2020

#include "Actors/IPRectangle3DActor.h"

AIPRectangle3DActor::AIPRectangle3DActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(HISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->bIsEditorOnly = true;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationRectangle3D = CreateDefaultSubobject<UIPOperationRectangle3D>(TEXT("IPOperationRectangle3D"));
	IPOperationRectangle3D->SetupAttachment(HISMComponent);
	IPOperationRectangle3D->Mobility = EComponentMobility::Static;
	IPOperationRectangle3D->bIsEditorOnly = true;
	IPOperationRectangle3D->ExecutionOrder = 1;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(HISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->bIsEditorOnly = true;
	IPOperationRandomTransform->ExecutionOrder = 2;
#endif
}