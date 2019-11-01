// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureComponent.h"
#include "Components/SplineComponent.h"
#include "IPProcedureSplinePlacement.generated.h"

UCLASS(NotBlueprintable, ClassGroup = (Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureSplinePlacement : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureSplinePlacement();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = "Procedure | Parameters")
		USplineComponent* SplineComponent;

	UPROPERTY()
		bool bOrientBySplineEditCondition;

	UPROPERTY()
		bool bPlaceBetweenPointsEditCondition;

	/** Should instances be oriented by spline? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bOrientBySplineEditCondition"))
		bool bOrientBySpline;

	/** Should instances be placed between spline points? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bPlaceBetweenPointsEditCondition"))
		bool bPlaceBetweenPoints;

	/** Should instances be oriented from point to point? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bPlaceBetweenPoints"))
		bool bOrientByPoints;

	/** Should instances be scaled between points? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bPlaceBetweenPoints"))
		bool bScaleBetweenPoints;

	/** Size of instance on X axis to scale between points */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bPlaceBetweenPoints"))
		float XSizeToScale;
#endif
};