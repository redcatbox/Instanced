// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureTransformBase.h"
#include "IPProcedureTransformMultiply.generated.h"

UCLASS(NotBlueprintable, ClassGroup=(Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureTransformMultiply : public UIPProcedureTransformBase
{
	GENERATED_BODY()

public:
	UIPProcedureTransformMultiply();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
	virtual FTransform Operation(FTransform& A, FTransform& B) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Transform to multiply on */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ShowOnlyInnerProperties))
		FTransform MultiplyTransform;
#endif
};