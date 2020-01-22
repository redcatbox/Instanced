// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Objects/IPFunctionLibrary.h"
#include "IPProcedureComponent.generated.h"

UCLASS(Blueprintable, ClassGroup = (InstancingProcedure), Meta = (BlueprintSpawnableComponent), AutoExpandCategories = ("Procedure | Execution", "Procedure | Parameters"))
class INSTANCEDPLUGIN_API UIPProcedureComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UIPProcedureComponent();

#if WITH_EDITOR
	UFUNCTION()
		virtual void RunProcedure(TArray<FTransform>& Transforms);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UFUNCTION(BlueprintImplementableEvent, Category = InstancedPlugin)
		TArray<FTransform> BlueprintProcedure(const TArray<FTransform>& Transforms);

	UFUNCTION(BlueprintCallable, Category = InstancedPlugin)
		virtual UInstancedStaticMeshComponent* GetParentISMComponent();

#if WITH_EDITORONLY_DATA
	UPROPERTY()
		bool bInstancesNumEditCondition;

	/** Number of instances to create */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bInstancesNumEditCondition", ClampMin = "1", UIMin = "1"))
		int32 InstancesNum;

	/** Process this procedure or not */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Execution")
		bool bEnabled;
#endif

	/** Order in procedures execution chain */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Execution")
		int32 ExecutionOrder;
};