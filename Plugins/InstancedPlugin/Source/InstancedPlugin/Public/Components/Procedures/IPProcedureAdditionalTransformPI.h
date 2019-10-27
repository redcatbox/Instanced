// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureAdditionalTransformPI.generated.h"

UCLASS(Blueprintable, ClassGroup=(Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureAdditionalTransformPI : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureAdditionalTransformPI();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Initial instances transform. AIPlied to all instances! */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ShowOnlyInnerProperties))
		FTransform AdditionalTransform;
#endif
};