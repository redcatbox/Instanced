// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureTransformsArray.generated.h"

UCLASS(Blueprintable, ClassGroup = (Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureTransformsArray : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureTransformsArray();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Array of transforms for instances */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true))
		TArray<FTransform> PlacementTransforms;
#endif
};