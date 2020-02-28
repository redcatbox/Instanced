// Dmitriy Barannik aka redbox, 2020

#include "Actors/IPGrid3DActor.h"

AIPGrid3DActor::AIPGrid3DActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(HISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->bIsEditorOnly = true;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationGrid3D = CreateDefaultSubobject<UIPOperationGrid3D>(TEXT("IPOperationGrid3D"));
	IPOperationGrid3D->SetupAttachment(HISMComponent);
	IPOperationGrid3D->Mobility = EComponentMobility::Static;
	IPOperationGrid3D->bIsEditorOnly = true;
	IPOperationGrid3D->ExecutionOrder = 1;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(HISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->bIsEditorOnly = true;
	IPOperationRandomTransform->ExecutionOrder = 2;
#endif
}