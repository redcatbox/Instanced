// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureDynamicComponent.h"

UIPProcedureDynamicComponent::UIPProcedureDynamicComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
#endif
}

void UIPProcedureDynamicComponent::RunProcedureDynamic()
{
	BlueprintProcedureDynamic();
}