// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Procedures/IPProcedureDynamicComponent.h"

UIPProcedureDynamicComponent::UIPProcedureDynamicComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UIPProcedureDynamicComponent::RunProcedureDynamic()
{
	BlueprintProcedureDynamic();
}