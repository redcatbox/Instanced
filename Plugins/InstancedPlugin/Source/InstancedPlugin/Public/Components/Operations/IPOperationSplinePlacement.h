// redbox, 2022

#pragma once

#include "IPOperationComponent.h"
#include "Components/SplineComponent.h"
#include "IPOperationSplinePlacement.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationSplinePlacement : public UIPOperationComponent
{
	GENERATED_BODY()

public:
	UIPOperationSplinePlacement();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

	UFUNCTION(BlueprintCallable, Category = InstancedPlugin)
	virtual USplineComponent* GetParentSplineComponent();

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	bool bOrientBySplineEditCond;

	UPROPERTY()
	bool bPlaceBetweenPointsEditCond;

	/** Should instances be oriented by spline? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCond = "bOrientBySplineEditCond"))
	bool bOrientBySpline;

	/** Should instances be placed between spline points? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCond = "bPlaceBetweenPointsEditCond"))
	bool bPlaceBetweenPoints;

	/** Should instances be oriented from point to point? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCond = "bPlaceBetweenPoints"))
	bool bOrientByPoints;

	/** Should instances be scaled between points? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCond = "bPlaceBetweenPoints"))
	bool bScaleBetweenPoints;

	/** Size of instance on X axis to scale between points */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCond = "bPlaceBetweenPoints"))
	float XSizeToScale;
#endif
};
