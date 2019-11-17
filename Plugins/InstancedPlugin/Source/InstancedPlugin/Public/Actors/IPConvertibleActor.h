// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IPBaseGeneratedActor.h"
#include "IPConvertibleActor.generated.h"

UCLASS(ClassGroup = (Instanced), HideCategories = (Actor, Collision, Cooking, Input, LOD, Rendering, Replication), AutoExpandCategories = (Convertation))
class INSTANCEDPLUGIN_API AIPConvertibleActor : public AActor
{
	GENERATED_BODY()

public:
	AIPConvertibleActor();

#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, CallInEditor, Category = Convertation)
		virtual void ConvertToInstances();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = Convertation)
		virtual void ConvertToStaticMeshes();
#endif

#if WITH_EDITORONLY_DATA
	/** Should remove original objects after convertation? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Convertation)
		bool bRemoveOriginal;
#endif

	UPROPERTY()
		USceneComponent* DefaultSceneRoot;
};