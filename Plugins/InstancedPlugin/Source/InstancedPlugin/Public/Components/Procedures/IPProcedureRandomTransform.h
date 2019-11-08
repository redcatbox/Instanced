// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureRandomBase.h"
#include "IPProcedureRandomTransform.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureRandomTransform : public UIPProcedureRandomBase
{
	GENERATED_BODY()

public:
	UIPProcedureRandomTransform();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;

	UFUNCTION()
		FVector RandomizeLocation(FVector Location);

	UFUNCTION()
		FRotator RandomizeRotation(FRotator Rotation);

	UFUNCTION()
		FRotator RandomizeRotationByFixedRotatorSteps(FRotator Rotation);

	UFUNCTION()
		FVector RandomizeScale(FVector Scale);
#endif

#if WITH_EDITORONLY_DATA
	/** Should location be randomized? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bRandomLocation;

	/** Min random location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bRandomLocation"))
		FVector RandomLocationMin;

	/** Max random location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bRandomLocation"))
		FVector RandomLocationMax;

	/** Should rotation be randomized? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bRandomRotation;

	/** Min random rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bRandomRotation"))
		FRotator RandomRotationMin;

	/** Max random rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bRandomRotation"))
		FRotator RandomRotationMax;

	/** Should rotation be randomized by fixed rotator steps? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bRandomRotation"))
		bool bRandomRotationByFixedRotatorSteps;

	UPROPERTY()
		bool bRandomRotationByFixedRotatorStepsEditCondition;

	/** Fixed rotator */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bRandomRotationByFixedRotatorStepsEditCondition"))
		FRotator FixedRotator;

	/** Min number of steps */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bRandomRotationByFixedRotatorStepsEditCondition"))
		int32 StepsMin;

	/** Max number of steps */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bRandomRotationByFixedRotatorStepsEditCondition"))
		int32 StepsMax;

	/** Should scale be randomized? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bRandomScale;

	/** Should scale be randomized uniformly (take only X value)? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bRandomScale"))
		bool bRandomizeScaleUniformly;

	/** Min random scale*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bRandomScale"))
		FVector RandomScaleMin;

	/** Max random scale */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bRandomScale"))
		FVector RandomScaleMax;
#endif
};