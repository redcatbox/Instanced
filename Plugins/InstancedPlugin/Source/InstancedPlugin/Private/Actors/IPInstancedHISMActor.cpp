// redbox, 2022

#include "Actors/IPInstancedHISMActor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

AIPInstancedHISMActor::AIPInstancedHISMActor()
{
	ISMComponent = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("HISMComponent"));
	ISMComponent->SetupAttachment(RootComponent);
	ISMComponent->Mobility = EComponentMobility::Static;
	ISMComponent->CreationMethod = EComponentCreationMethod::Native;
}
