// redbox, 2022

#include "Actors/IPTransformsArrayActor.h"

AIPTransformsArrayActor::AIPTransformsArrayActor()
{
#if WITH_EDITORONLY_DATA
	IPOperationTransformsArray = CreateDefaultSubobject<UIPOperationTransformsArray>(TEXT("IPOperationTransformsArray"));
	IPOperationTransformsArray->SetupAttachment(ISMComponent);
	IPOperationTransformsArray->Mobility = EComponentMobility::Static;
#endif
}
