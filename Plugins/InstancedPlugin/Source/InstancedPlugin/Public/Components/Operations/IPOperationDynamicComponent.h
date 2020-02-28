// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPOperationComponent.h"
#include "IPOperationDynamicComponent.generated.h"

UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationDynamicComponent : public UIPOperationComponent
{
	GENERATED_BODY()

public:
	UIPOperationDynamicComponent();

	UFUNCTION(BlueprintCallable, Category = InstancedPlugin)
		virtual void RunOperationDynamic();

	UFUNCTION(BlueprintImplementableEvent, Category = InstancedPlugin)
		void BlueprintOperationDynamic();
};