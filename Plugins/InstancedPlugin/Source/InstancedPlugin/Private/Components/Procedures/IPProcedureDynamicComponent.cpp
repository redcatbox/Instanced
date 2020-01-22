// Dmitriy Barannik aka redbox, 2020

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