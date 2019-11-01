// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureTransformBase.h"
#include "IPProcedureTransformReplace.generated.h"

UCLASS(NotBlueprintable, ClassGroup=(Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureTransformReplace : public UIPProcedureTransformBase
{
	GENERATED_BODY()

public:
	UIPProcedureTransformReplace();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
	virtual FTransform Operation(FTransform& A, FTransform& B) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Transform to replace with */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ShowOnlyInnerProperties))
		FTransform ReplacementTransform;
#endif
};