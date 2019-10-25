// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureGrid3DBase.h"
#include "IPProcedureGrid3D.generated.h"

UCLASS(Blueprintable, ClassGroup = (Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureGrid3D : public UIPProcedureGrid3DBase
{
	GENERATED_BODY()

public:
	//UIPProcedureGrid3D();

#if WITH_EDITOR
	virtual void RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms) override;
#endif
};