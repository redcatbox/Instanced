// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureDynamicComponent.generated.h"

UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureDynamicComponent : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureDynamicComponent();

	UFUNCTION(BlueprintCallable, Category = InstancedPlugin)
		virtual void RunProcedureDynamic();

	UFUNCTION(BlueprintImplementableEvent, Category = InstancedPlugin)
		void BlueprintProcedureDynamic();
};