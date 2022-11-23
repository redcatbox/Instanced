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

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = InstancedPlugin)
	TSubclassOf<UInstancedStaticMeshComponent> InstancedStaticMeshComponentClass;
#endif

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
