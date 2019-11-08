// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPBaseInstancedActor.h"
#include "IPInstancedHISMActor.generated.h"

UCLASS(Blueprintable, ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPInstancedHISMActor : public AIPBaseInstancedActor
{
	GENERATED_BODY()

public:
	AIPInstancedHISMActor();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UHierarchicalInstancedStaticMeshComponent* HISMComponent;
};
