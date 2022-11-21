// redbox, 2022

#include "Actors/IPRandomSphereAlignedActor.h"

AIPRandomSphereAlignedActor::AIPRandomSphereAlignedActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformMultiply = CreateDefaultSubobject<UIPOperationTransformMultiply>(TEXT("IPOperationTransformMultiply"));
	IPOperationTransformMultiply->SetupAttachment(ISMComponent);
	IPOperationTransformMultiply->Mobility = EComponentMobility::Static;
	IPOperationTransformMultiply->ExecutionOrder = 0;
	IPOperationTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPOperationRandomSphere = CreateDefaultSubobject<UIPOperationRandomSphere>(TEXT("IPOperationRandomSphere"));
	IPOperationRandomSphere->SetupAttachment(ISMComponent);
	IPOperationRandomSphere->Mobility = EComponentMobility::Static;
	IPOperationRandomSphere->ExecutionOrder = 1;

	IPOperationAlignFromPoint = CreateDefaultSubobject<UIPOperationAlignFromPoint>(TEXT("IPOperationAlignFromPoint"));
	IPOperationAlignFromPoint->SetupAttachment(ISMComponent);
	IPOperationAlignFromPoint->Mobility = EComponentMobility::Static;
	IPOperationAlignFromPoint->ExecutionOrder = 2;

	IPOperationRandomTransform = CreateDefaultSubobject<UIPOperationRandomTransform>(TEXT("IPOperationRandomTransform"));
	IPOperationRandomTransform->SetupAttachment(ISMComponent);
	IPOperationRandomTransform->Mobility = EComponentMobility::Static;
	IPOperationRandomTransform->ExecutionOrder = 3;
#endif
}
