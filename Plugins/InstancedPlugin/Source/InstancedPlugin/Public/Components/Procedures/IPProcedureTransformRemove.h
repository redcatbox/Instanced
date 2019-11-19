// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureTransformBase.h"
#include "IPProcedureTransformRemove.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureTransformRemove : public UIPProcedureTransformBase
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif
};