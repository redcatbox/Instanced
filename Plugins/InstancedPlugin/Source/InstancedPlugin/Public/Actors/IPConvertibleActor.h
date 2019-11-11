// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPBaseGeneratedActor.h"
#include "IPConvertibleActor.generated.h"

UCLASS(ClassGroup = (Instanced), HideCategories = ("Generation"))
class INSTANCEDPLUGIN_API AIPConvertibleActor : public AIPBaseGeneratedActor
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	UFUNCTION(BlueprintCallable, CallInEditor, Category = Convertation)
		virtual void ConvertToInstances();

	UFUNCTION(BlueprintCallable, CallInEditor, Category = Convertation)
		virtual void ConvertToStaticMeshes();
#endif
};