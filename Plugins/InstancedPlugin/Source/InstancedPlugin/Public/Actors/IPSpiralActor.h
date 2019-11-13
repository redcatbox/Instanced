// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/Procedures/IPProcedureTransformMultiply.h"
#include "Components/Procedures/IPProcedureSpiral.h"
#include "Components/Procedures/IPProcedureRandomTransform.h"
#include "IPSpiralActor.generated.h"

UCLASS(ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPSpiralActor : public AIPInstancedHISMActor
{
	GENERATED_BODY()

public:
	AIPSpiralActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureTransformMultiply* IPProcedureTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureSpiral* IPProcedureSpiral;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureRandomTransform* IPProcedureRandomTransform;
#endif
};