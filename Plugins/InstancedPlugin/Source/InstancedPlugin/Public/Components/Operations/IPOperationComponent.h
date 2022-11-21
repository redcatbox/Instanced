// redbox, 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "IPOperationComponent.generated.h"

UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent), AutoExpandCategories = ("Operation | Execution", "Operation | Parameters"), AutoCollapseCategories=("Utilities | Transformation"), HideCategories = (Collision, Rendering, "Utilities | Transformation"))
class INSTANCEDPLUGIN_API UIPOperationComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UIPOperationComponent();

#if WITH_EDITOR
	UFUNCTION()
	virtual void RunOperation(TArray<FTransform>& Transforms);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UFUNCTION(BlueprintImplementableEvent, Category = InstancedPlugin)
	TArray<FTransform> BlueprintOperation(const TArray<FTransform>& Transforms);

	UFUNCTION(BlueprintCallable, Category = InstancedPlugin)
	virtual class UInstancedStaticMeshComponent* GetParentISMComponent();

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	bool bInstancesNumEditCondition;

	/** Number of instances to create */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bInstancesNumEditCondition", ClampMin = "1", UIMin = "1"))
	int32 InstancesNum;

	/** Process this operation or not */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Execution")
	bool bEnabled;
#endif

	/** Order in operations execution chain */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Execution")
	int32 ExecutionOrder;
};

USTRUCT()
struct FSortByExecutionOrder
{
	GENERATED_BODY()

	FSortByExecutionOrder() {}

	bool operator()(const UIPOperationComponent* A, const UIPOperationComponent* B) const
	{
		const int32 ExecutionOrderA = A->ExecutionOrder;
		const int32 ExecutionOrderB = B->ExecutionOrder;
		return ExecutionOrderA < ExecutionOrderB;
	}
};
