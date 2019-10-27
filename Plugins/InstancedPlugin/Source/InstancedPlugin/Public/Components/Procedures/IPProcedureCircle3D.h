// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureCircle3D.generated.h"

UCLASS(Blueprintable, ClassGroup = (Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureCircle3D : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureCircle3D();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Number of instances to create */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters", Meta = (ShowOnlyInnerProperties))
		FIntVector InstancesNum3D;

	/** Angle to place instances in */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters")
		float PlacementAngle;

	/** Space of every instance from it's center */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters")
		FVector InstanceSpace;

	/** Should instances be oriented to central axis? */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters")
		bool bOrientToCentralAxis;

	/** Should make odd/even rows in checker pattern? */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters")
		bool bCheckerOddEven;

	/** Should flip odd/even rows? */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters")
		bool bFlipOddEven;
#endif
};