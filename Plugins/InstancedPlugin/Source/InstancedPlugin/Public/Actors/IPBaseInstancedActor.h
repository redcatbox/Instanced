// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPBaseGeneratedActor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Components/Procedures/IPProcedureDynamicComponent.h"
#include "IPBaseInstancedActor.generated.h"

#if WITH_EDITOR
USTRUCT()
struct FSortByExecutionOrder
{
	GENERATED_BODY()

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
	virtual void DrawDebugInfo() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UFUNCTION()
		virtual void UpdateInstances(TArray<FTransform>& Transforms, UInstancedStaticMeshComponent* ISMComponentRef);
#endif

//#if WITH_EDITORONLY_DATA
	///** Should random seed be used? */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Generation)
	//	bool bUseInstancingRandomSeed;

	///** Random seed value */
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Generation, Meta = (EditCondition = "bUseInstancingRandomSeed"))
	//	int32 InstancingRandomSeed;
//#endif
};