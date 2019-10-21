// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureDynamicComponent.generated.h"

UCLASS(Blueprintable, ClassGroup = (Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureDynamicComponent : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureDynamicComponent();

	UFUNCTION()
		virtual void RunProcedureDynamic();
};