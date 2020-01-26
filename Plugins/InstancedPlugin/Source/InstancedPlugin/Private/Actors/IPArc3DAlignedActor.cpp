// Dmitriy Barannik aka redbox, 2020

#include "Actors/IPArc3DAlignedActor.h"

AIPArc3DAlignedActor::AIPArc3DAlignedActor()
{
#if WITH_EDITORONLY_DATA
	IPProcedureTransformMultiply = CreateDefaultSubobject<UIPProcedureTransformMultiply>(TEXT("IPProcedureTransformMultiply"));
	IPProcedureTransformMultiply->SetupAttachment(HISMComponent);
	IPProcedureTransformMultiply->Mobility = EComponentMobility::Static;
	IPProcedureTransformMultiply->bIsEditorOnly = true;
	IPProcedureTransformMultiply->ExecutionOrder = 0;
	IPProcedureTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPProcedureArc3D = CreateDefaultSubobject<UIPProcedureArc3D>(TEXT("IPProcedureArc3D"));
	IPProcedureArc3D->SetupAttachment(HISMComponent);
	IPProcedureArc3D->Mobility = EComponentMobility::Static;
	IPProcedureArc3D->bIsEditorOnly = true;
	IPProcedureArc3D->ExecutionOrder = 1;

	IPProcedureAlignFromAxis = CreateDefaultSubobject<UIPProcedureAlignFromAxis>(TEXT("IPProcedureAlignFromAxis"));
	IPProcedureAlignFromAxis->SetupAttachment(HISMComponent);
	IPProcedureAlignFromAxis->Mobility = EComponentMobility::Static;
	IPProcedureAlignFromAxis->bIsEditorOnly = true;
	IPProcedureAlignFromAxis->ExecutionOrder = 2;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(HISMComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bIsEditorOnly = true;
	IPProcedureRandomTransform->ExecutionOrder = 3;
#endif
}