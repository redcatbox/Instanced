// redbox, 2020

#include "Actors/IPTransformsArrayActor.h"

AIPTransformsArrayActor::AIPTransformsArrayActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformsArray = CreateDefaultSubobject<UIPOperationTransformsArray>(TEXT("IPOperationTransformsArray"));
	IPOperationTransformsArray->SetupAttachment(HISMComponent);
	IPOperationTransformsArray->Mobility = EComponentMobility::Static;
	IPOperationTransformsArray->bIsEditorOnly = true;
#endif
}