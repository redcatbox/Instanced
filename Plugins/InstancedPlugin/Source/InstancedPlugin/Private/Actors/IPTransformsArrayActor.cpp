// Dmitriy Barannik aka redbox, 2020

#include "Actors/IPTransformsArrayActor.h"

AIPTransformsArrayActor::AIPTransformsArrayActor()
{
#if WITH_EDITORONLY_DATA
	IPProcedureTransformsArray = CreateDefaultSubobject<UIPProcedureTransformsArray>(TEXT("IPProcedureTransformsArray"));
	IPProcedureTransformsArray->SetupAttachment(HISMComponent);
	IPProcedureTransformsArray->Mobility = EComponentMobility::Static;
	IPProcedureTransformsArray->bIsEditorOnly = true;
#endif
}