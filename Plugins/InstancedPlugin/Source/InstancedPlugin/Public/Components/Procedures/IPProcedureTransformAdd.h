// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureTransformBase.h"
#include "IPProcedureTransformAdd.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureTransformAdd : public UIPProcedureTransformBase
{
	GENERATED_BODY()

public:
	UIPProcedureTransformAdd();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;

	UFUNCTION()
		FTransform Operation(FTransform& A, FTransform& B);
#endif

#if WITH_EDITORONLY_DATA
	/** Increment by instance id */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bPerInstanceIncremental;
#endif
};