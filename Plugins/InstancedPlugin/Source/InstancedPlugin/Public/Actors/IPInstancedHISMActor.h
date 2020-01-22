// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPBaseInstancedActor.h"
#include "IPInstancedHISMActor.generated.h"

UCLASS(Blueprintable, ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPInstancedHISMActor : public AIPBaseInstancedActor
{
	GENERATED_BODY()

public:
	AIPInstancedHISMActor();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
		UHierarchicalInstancedStaticMeshComponent* HISMComponent;
};
