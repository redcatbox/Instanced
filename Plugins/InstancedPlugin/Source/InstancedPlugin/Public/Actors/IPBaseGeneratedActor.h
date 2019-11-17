// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objects/IPFunctionLibrary.h"
#include "Components/SceneComponent.h"
#include "IPBaseGeneratedActor.generated.h"

UCLASS(Abstract, ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPBaseGeneratedActor : public AActor
{
	GENERATED_BODY()

public:
	AIPBaseGeneratedActor();

#if WITH_EDITOR
	UFUNCTION(CallInEditor, Category = InstancedPlugin)
		virtual void RunGeneration();

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UPROPERTY()
		USceneComponent* DefaultSceneRoot;
};