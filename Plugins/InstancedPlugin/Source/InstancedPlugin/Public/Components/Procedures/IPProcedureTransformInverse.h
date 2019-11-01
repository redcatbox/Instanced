// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureTransformBase.h"
#include "IPProcedureTransformInverse.generated.h"

UCLASS(NotBlueprintable, ClassGroup=(Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureTransformInverse : public UIPProcedureTransformBase
{
	GENERATED_BODY()

public:
	UIPProcedureTransformInverse();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
	virtual FTransform Operation(FTransform& A, FTransform& B) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Transform to Inverse */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ShowOnlyInnerProperties))
		FTransform AdditionalTransform;

	/** Increment by instance id */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bPerInstanceIncremental;
#endif
};