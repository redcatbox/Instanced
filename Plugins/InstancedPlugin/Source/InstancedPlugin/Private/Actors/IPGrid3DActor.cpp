// Dmitriy Barannik aka redbox, 2020

#include "Actors/IPGrid3DActor.h"

AIPGrid3DActor::AIPGrid3DActor()
{
#if WITH_EDITORONLY_DATA
	IPProcedureTransformMultiply = CreateDefaultSubobject<UIPProcedureTransformMultiply>(TEXT("IPProcedureTransformMultiply"));
	IPProcedureTransformMultiply->SetupAttachment(HISMComponent);
	IPProcedureTransformMultiply->Mobility = EComponentMobility::Static;
	IPProcedureTransformMultiply->bIsEditorOnly = true;
	IPProcedureTransformMultiply->ExecutionOrder = 0;
	IPProcedureTransformMultiply->OperationTransforms.Add(FPerInstanceTransform(-1, FTransform()));

	IPProcedureGrid3D = CreateDefaultSubobject<UIPProcedureGrid3D>(TEXT("IPProcedureGrid3D"));
	IPProcedureGrid3D->SetupAttachment(HISMComponent);
	IPProcedureGrid3D->Mobility = EComponentMobility::Static;
	IPProcedureGrid3D->bIsEditorOnly = true;
	IPProcedureGrid3D->ExecutionOrder = 1;

	IPProcedureRandomTransform = CreateDefaultSubobject<UIPProcedureRandomTransform>(TEXT("IPProcedureRandomTransform"));
	IPProcedureRandomTransform->SetupAttachment(HISMComponent);
	IPProcedureRandomTransform->Mobility = EComponentMobility::Static;
	IPProcedureRandomTransform->bIsEditorOnly = true;
	IPProcedureRandomTransform->ExecutionOrder = 2;
#endif
}