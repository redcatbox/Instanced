// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureAlignFromAxis.generated.h"

UCLASS(Blueprintable, ClassGroup = (Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureAlignFromAxis : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureAlignFromAxis();

#if WITH_EDITOR
	virtual void RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Axis start */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true))
		FVector AlignAxisStart;

	/** Axis end */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true))
		FVector AlignAxisEnd;

	/** Distance to align at */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters", Meta = (ClampMin = "0", UIMin = "0"))
		float AlignDistance;

	/** Should reverse alignment? */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters")
		bool bReverse;

	/** Should orient to surface? */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters")
		bool bOrientToSurface;
#endif
};