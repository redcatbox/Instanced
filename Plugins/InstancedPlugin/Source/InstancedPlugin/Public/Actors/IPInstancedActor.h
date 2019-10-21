// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPBaseInstancedActor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "IPInstancedActor.generated.h"

UCLASS(ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPInstancedActor : public AIPBaseInstancedActor
{
	GENERATED_BODY()

public:
	AIPInstancedActor();

#if WITH_EDITOR
	virtual void RunGeneration() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void UpdateInstances(TArray<FTransform>& Transforms, UInstancedStaticMeshComponent* ISMComponentRef) override;
#endif
};
