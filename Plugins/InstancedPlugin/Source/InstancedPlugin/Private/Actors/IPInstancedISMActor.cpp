// redbox, 2022

#include "Actors/IPInstancedISMActor.h"

AIPInstancedISMActor::AIPInstancedISMActor()
{
	ISMComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("ISMComponent"));
	ISMComponent->SetupAttachment(RootComponent);
	ISMComponent->Mobility = EComponentMobility::Static;
	ISMComponent->CreationMethod = EComponentCreationMethod::Native;
}
