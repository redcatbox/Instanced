// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPBaseGeneratedActor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/Procedures/IPProcedureComponent.h"
#include "IPBaseInstancedActor.generated.h"

#if WITH_EDITOR
struct FSortByExecutionOrder
{
	FSortByExecutionOrder() {}

	bool operator()(const UIPProcedureComponent* A, const UIPProcedureComponent* B) const
	{
		int32 ExecutionOrderA = A->ExecutionOrder;
		int32 ExecutionOrderB = B->ExecutionOrder;
		return ExecutionOrderA < ExecutionOrderB;
	}
};
#endif

UCLASS(Abstract, ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPBaseInstancedActor : public AIPBaseGeneratedActor
{
	GENERATED_BODY()

public:
	AIPBaseInstancedActor();

#if WITH_EDITOR
	virtual void RunGeneration() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UFUNCTION()
		virtual void UpdateInstances(TArray<FTransform>& Transforms, UInstancedStaticMeshComponent* ISMComponentRef);
#endif

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UInstancedStaticMeshComponent* ISMComponent;

#if WITH_EDITORONLY_DATA
	UPROPERTY()
		bool bInstancesNumEditCondition;

	/** Number of instances to create */
	UPROPERTY(EditAnywhere, Category = Generation, Meta = (EditCondition = "bInstancesNumEditCondition", ClampMin = "1", UIMin = "1"))
		int32 InstancesNum;

	/** Should random seed be used? */
	UPROPERTY(EditAnywhere, Category = Generation)
		bool bUseInstancingRandomSeed;

	/** Random seed value */
	UPROPERTY(EditAnywhere, Category = Generation, Meta = (EditCondition = "bUseInstancingRandomSeed"))
		int32 InstancingRandomSeed;

	UPROPERTY()
		TArray<UIPProcedureComponent*> ProcedureComponents;
#endif
};
