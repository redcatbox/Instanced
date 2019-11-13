// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/Procedures/IPProcedureTransformMultiply.h"
#include "Components/Procedures/IPProcedureGrid3DHexagonal.h"
#include "Components/Procedures/IPProcedureRandomTransform.h"
#include "IPGrid3DHexagonalActor.generated.h"

UCLASS(ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPGrid3DHexagonalActor : public AIPInstancedHISMActor
{
	GENERATED_BODY()

public:
	AIPGrid3DHexagonalActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureTransformMultiply* IPProcedureTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureGrid3DHexagonal* IPProcedureGrid3DHexagonal;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureRandomTransform* IPProcedureRandomTransform;
#endif
};
