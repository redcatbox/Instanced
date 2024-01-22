// redbox, 2022

#pragma once

#include "IPOperationRandomBase.h"
#include "IPOperationRandomTransform.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationRandomTransform : public UIPOperationRandomBase
{
	GENERATED_BODY()

public:
	UIPOperationRandomTransform();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
	bool bRandomLocation;

	/** Min random location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bRandomLocation"))
	FVector RandomLocationMin;

	/** Max random location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bRandomLocation"))
	FVector RandomLocationMax;

	/** Should rotation be randomized? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
	bool bRandomRotation;

	/** Min random rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bRandomRotation"))
	FRotator RandomRotationMin;

	/** Max random rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bRandomRotation"))
	FRotator RandomRotationMax;

	/** Should rotation be randomized by fixed rotator steps? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bRandomRotation"))
	bool bRandomRotationByFixedRotatorSteps;

	UPROPERTY()
	bool bRandomRotationByFixedRotatorStepsEditCond;

	/** Fixed rotator */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bRandomRotationByFixedRotatorStepsEditCond"))
	FRotator FixedRotator;

	/** Min number of steps */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bRandomRotationByFixedRotatorStepsEditCond"))
	int32 StepsMin;

	/** Max number of steps */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bRandomRotationByFixedRotatorStepsEditCond"))
	int32 StepsMax;

	/** Should scale be randomized? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
	bool bRandomScale;

	/** Should scale be randomized uniformly (take only X value)? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bRandomScale"))
	bool bRandomizeScaleUniformly;

	/** Min random scale*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bRandomScale"))
	FVector RandomScaleMin;

	/** Max random scale */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bRandomScale"))
	FVector RandomScaleMax;
#endif
};
