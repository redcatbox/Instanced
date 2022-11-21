// redbox, 2022

#pragma once

#include "IPBaseInstancedActor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "IPInstancedISMActor.generated.h"

UCLASS(Blueprintable)
class INSTANCEDPLUGIN_API AIPInstancedISMActor : public AIPBaseInstancedActor
{
	GENERATED_BODY()

public:
	AIPInstancedISMActor();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
	UInstancedStaticMeshComponent* ISMComponent;
};
