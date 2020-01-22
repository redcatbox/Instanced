// Dmitriy Barannik aka redbox, 2020

#include "Actors/IPRectangle3DActor.h"

AIPRectangle3DActor::AIPRectangle3DActor()
{
#if WITH_EDITORONLY_DATA
	IPProcedureTransformMultiply = CreateDefaultSubobject<UIPProcedureTransformMultiply>(TEXT("IPProcedureTransformMultiply"));
	IPProcedureTransformMultiply->SetupAttachment(HISMComponent);
	IPProcedureTransformMultiply->Mobility = EComponentMobility::Static;
	IPProcedureTransformMultiply->bIsEditorOnly = true;
	IPProcedureTransformMultiply->ExecutionOrder = 0;
	IPProcedureTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPProcedureRectangle3D = CreateDefaultSubobject<UIPProcedureRectangle3D>(TEXT("IPProcedureRectangle3D"));
	IPProcedureRectangle3D->SetupAttachment(HISMComponent);
	IPProcedureRectangle3D->Mobility = EComponentMobility::Static;
	IPProcedureRectangle3D->bIsEditorOnly = true;
	IPProcedureRectangle3D->ExecutionOrder = 1;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(HISMComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bIsEditorOnly = true;
	IPProcedureRandomTransform->ExecutionOrder = 2;
#endif
}