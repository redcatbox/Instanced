// Dmitriy Barannik aka redbox, 2020

#include "Actors/IPRandomBoxAlignedActor.h"

AIPRandomBoxAlignedActor::AIPRandomBoxAlignedActor()
{
#if WITH_EDITORONLY_DATA
	IPProcedureTransformMultiply = CreateDefaultSubobject<UIPProcedureTransformMultiply>(TEXT("IPProcedureTransformMultiply"));
	IPProcedureTransformMultiply->SetupAttachment(HISMComponent);
	IPProcedureTransformMultiply->Mobility = EComponentMobility::Static;
	IPProcedureTransformMultiply->bIsEditorOnly = true;
	IPProcedureTransformMultiply->ExecutionOrder = 0;
	IPProcedureTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPProcedureRandomBox = CreateDefaultSubobject<UIPProcedureRandomBox>(TEXT("IPProcedureRandomBox"));
	IPProcedureRandomBox->SetupAttachment(HISMComponent);
	IPProcedureRandomBox->Mobility = EComponentMobility::Static;
	IPProcedureRandomBox->bIsEditorOnly = true;
	IPProcedureRandomBox->ExecutionOrder = 1;

	IPProcedureAlignByDirection = CreateDefaultSubobject<UIPProcedureAlignByDirection>(TEXT("IPProcedureAlignByDirection"));
	IPProcedureAlignByDirection->SetupAttachment(HISMComponent);
	IPProcedureAlignByDirection->Mobility = EComponentMobility::Static;
	IPProcedureAlignByDirection->bIsEditorOnly = true;
	IPProcedureAlignByDirection->ExecutionOrder = 2;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(HISMComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bIsEditorOnly = true;
	IPProcedureRandomTransform->ExecutionOrder = 3;
#endif
}