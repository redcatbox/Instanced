// redbox, 2020

#include "Actors/IPGrid3DDynDistTransfActor.h"

AIPGrid3DDynDistTransfActor::AIPGrid3DDynDistTransfActor()
{
	PrimaryActorTick.bCanEverTick = true;
	IPOperationDynamicTransform = CreateDefaultSubobject<UIPOperationDynamicTransform>(TEXT("IPOperationDynamicTransform"));
	IPOperationDynamicTransform->SetupAttachment(HISMComponent);
}

void AIPGrid3DDynDistTransfActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	IPOperationDynamicTransform->RunOperationDynamic();
}
