// redbox, 2022

#include "Components/Operations/IPOperationDynamicComponent.h"

UIPOperationDynamicComponent::UIPOperationDynamicComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

#if WITH_EDITORONLY_DATA
	bInstancesNumEditCondition = false;
#endif
}

void UIPOperationDynamicComponent::RunOperationDynamic()
{
	BlueprintOperationDynamic();
}
