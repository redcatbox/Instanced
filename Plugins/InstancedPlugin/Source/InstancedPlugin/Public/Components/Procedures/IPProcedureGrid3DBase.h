// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureGrid3DBase.generated.h"

UCLASS(Abstract, NotBlueprintable, ClassGroup = (Procedure))
class INSTANCEDPLUGIN_API UIPProcedureGrid3DBase : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureGrid3DBase();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Number of instances to create */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ShowOnlyInnerProperties))
		FIntVector InstancesNum3D;

	/** Space of every instance from it's center */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ShowOnlyInnerProperties))
		FVector InstanceSpace;

	/** Should instances be offset on half space from it's center? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bHalfSpaceOffset;

	/** Override world axes with custom axes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bUseCustomAxes;

	/** Custom X axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true, EditCondition = "bUseCustomAxes"))
		FVector CustomAxis_X;

	/** Custom Y axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true, EditCondition = "bUseCustomAxes"))
		FVector CustomAxis_Y;

	/** Custom Z axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true, EditCondition = "bUseCustomAxes"))
		FVector CustomAxis_Z;

	/** Orient by custom axes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bUseCustomAxes"))
		bool bOrientByCustomAxes;
#endif
};