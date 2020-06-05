// redbox, 2020

#include "Actors/IPRandomSphereAlignedActor.h"

AIPRandomSphereAlignedActor::AIPRandomSphereAlignedActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(HISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->bIsEditorOnly = true;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationRandomSphere = CreateDefaultSubobject<UIPOperationRandomSphere>(TEXT("IPOperationRandomSphere"));
	IPOperationRandomSphere->SetupAttachment(HISMComponent);
	IPOperationRandomSphere->Mobility = EComponentMobility::Static;
	IPOperationRandomSphere->bIsEditorOnly = true;
	IPOperationRandomSphere->ExecutionOrder = 1;

	IPOperationAlignFromPoint = CreateDefaultSubobject<UIPOperationAlignFromPoint>(TEXT("IPOperationAlignFromPoint"));
	IPOperationAlignFromPoint->SetupAttachment(HISMComponent);
	IPOperationAlignFromPoint->Mobility = EComponentMobility::Static;
	IPOperationAlignFromPoint->bIsEditorOnly = true;
	IPOperationAlignFromPoint->ExecutionOrder = 2;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(HISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->bIsEditorOnly = true;
	IPOperationRandomTransform->ExecutionOrder = 3;
#endif
}