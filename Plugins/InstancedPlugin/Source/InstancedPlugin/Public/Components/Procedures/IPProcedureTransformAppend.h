// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureTransformBase.h"
#include "IPProcedureTransformAppend.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureTransformAppend : public UIPProcedureTransformBase
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif
};