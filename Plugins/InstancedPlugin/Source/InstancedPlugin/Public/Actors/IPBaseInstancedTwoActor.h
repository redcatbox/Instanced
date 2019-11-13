// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Actors/IPBaseInstancedActor.h"
#include "Components/Procedures/IPProcedureRandomBase.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "IPBaseInstancedTwoActor.generated.h"

UCLASS(Abstract, ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPBaseInstancedTwoActor : public AIPBaseInstancedActor
{
	GENERATED_BODY()

public:
	AIPBaseInstancedTwoActor();

#if WITH_EDITOR
	virtual void RunGeneration() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	UFUNCTION()
		virtual void DistributeToTwoTransforms(TArray<FTransform>& Transforms, TArray<FTransform>& Transforms1, TArray<FTransform>& Transforms2);
#endif

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
		UInstancedStaticMeshComponent* HISMComponent1;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Components)
		UInstancedStaticMeshComponent* HISMComponent2;

#if WITH_EDITORONLY_DATA
	/** Distribution between first and second instances */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Generation, Meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
		float Distribution;

	/** First instance contribution */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Generation, Meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
		float Contribution1;

	/** Second instance contribution */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Generation, Meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
		float Contribution2;

	/** Should randomize instances? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Generation)
		bool bRandomizeInstances;

	/** Should random stream be used for randomization? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Generation, Meta = (EditCondition = "bRandomizeInstances"))
		bool bUseRandomStream;

	/** Random stream seed value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Generation, Meta = (EditCondition = "bUseRandomStream"))
		int32 RandomStreamSeed;

	UPROPERTY()
		FRandomStream RandomStream;

protected:
	UPROPERTY()
		int32 InstancesNum1;

	UPROPERTY()
		int32 InstancesNum2;
#endif
};
