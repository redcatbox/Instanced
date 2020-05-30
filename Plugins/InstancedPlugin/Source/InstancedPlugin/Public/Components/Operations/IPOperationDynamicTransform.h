// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPOperationDynamicComponent.h"
#include "IPOperationDynamicTransform.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationDynamicTransform : public UIPOperationDynamicComponent
{
	GENERATED_BODY()

public:
	UIPOperationDynamicTransform();
	virtual void BeginPlay() override;
	virtual void RunOperationDynamic() override;

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

	UPROPERTY()
		UInstancedStaticMeshComponent* ParentISMComp;

	/** Dynamic transformation amount */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamicTransform")
		FTransform DynamicTransformDelta;

	/** Max distance to apply dynamic transformation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamicTransform", Meta = (ClampMin = "0", UIMin = "0"))
		float DynamicDistance;

	/** Near factor for dynamic transformation distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamicTransform", Meta = (ClampMin = "0", UIMin = "0"))
		float DynamicNearFactor;

	/** Far factor for dynamic transformation distance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DynamicTransform", Meta = (ClampMin = "0", UIMin = "0"))
		float DynamicFarFactor;

	UPROPERTY()
		TArray<FTransform> InstancesTransformsOld;

	UPROPERTY()
		TArray<FTransform> InstancesTransformsNew;
};