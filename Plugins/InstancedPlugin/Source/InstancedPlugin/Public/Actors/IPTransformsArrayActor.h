// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/Procedures/IPProcedureTransformsArray.h"
#include "IPTransformsArrayActor.generated.h"

UCLASS(ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPTransformsArrayActor : public AIPInstancedHISMActor
{
	GENERATED_BODY()

public:
	AIPTransformsArrayActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureTransformsArray* IPProcedureTransformsArray;
#endif
};