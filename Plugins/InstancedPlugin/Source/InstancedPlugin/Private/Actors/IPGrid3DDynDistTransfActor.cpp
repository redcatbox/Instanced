// redbox, 2022

#include "Actors/IPGrid3DDynDistTransfActor.h"

AIPGrid3DDynDistTransfActor::AIPGrid3DDynDistTransfActor()
{
	PrimaryActorTick.bCanEverTick = true;
	IPOperationDynamicTransform = CreateDefaultSubobject<UIPOperationDynamicTransform>(TEXT("IPOperationDynamicTransform"));
	IPOperationDynamicTransform->SetupAttachment(ISMComponent);
}

void AIPGrid3DDynDistTransfActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	IPOperationDynamicTransform->RunOperationDynamic();
}
