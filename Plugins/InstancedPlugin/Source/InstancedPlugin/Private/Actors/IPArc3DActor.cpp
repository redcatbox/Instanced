// Dmitriy Barannik aka redbox, 2020

#include "Actors/IPArc3DActor.h"

AIPArc3DActor::AIPArc3DActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(HISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->bIsEditorOnly = true;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationArc3D = CreateDefaultSubobject<UIPOperationArc3D>(TEXT("IPOperationArc3D"));
	IPOperationArc3D->SetupAttachment(HISMComponent);
	IPOperationArc3D->Mobility = EComponentMobility::Static;
	IPOperationArc3D->bIsEditorOnly = true;
	IPOperationArc3D->ExecutionOrder = 1;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(HISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->bIsEditorOnly = true;
	IPOperationRandomTransform->ExecutionOrder = 3;
#endif
}