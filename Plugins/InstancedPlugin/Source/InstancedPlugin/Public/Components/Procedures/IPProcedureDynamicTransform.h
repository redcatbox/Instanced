// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureDynamicComponent.h"
#include "IPProcedureDynamicTransform.generated.h"

UCLASS(Blueprintable, ClassGroup = (Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureDynamicTransform : public UIPProcedureDynamicComponent
{
	GENERATED_BODY()

public:
	UIPProcedureDynamicTransform();
	virtual void RunProcedureDynamic() override;

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

	UPROPERTY()
		UInstancedStaticMeshComponent* ISMParentComp;

	/** Dynamic transformation amount */
	UPROPERTY(EditAnywhere, Category = DynamicTransform)
		FTransform DynamicTransformDelta;

	/** Max distance to aIPly dynamic transformation */
	UPROPERTY(EditAnywhere, Category = DynamicTransform, Meta = (ClampMin = "0", UIMin = "0"))
		float DynamicDistance;

	/** Near factor for dynamic transformation distance */
	UPROPERTY(EditAnywhere, Category = DynamicTransform, Meta = (ClampMin = "0", UIMin = "0"))
		float DynamicNearFactor;

	/** Far factor for dynamic transformation distance */
	UPROPERTY(EditAnywhere, Category = DynamicTransform, Meta = (ClampMin = "0", UIMin = "0"))
		float DynamicFarFactor;

	UPROPERTY()
		TArray<FTransform> InstancesTransformsOld;

	UPROPERTY()
		TArray<FTransform> InstancesTransformsNew;
};