// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPInstancedActor.h"
#include "Components/Procedures/IPProcedureInitialTransform.h"
#include "Components/Procedures/IPProcedureGrid3D.h"
#include "Components/Procedures/IPProcedureRandomTransform.h"
#include "IPGrid3DActor.generated.h"

UCLASS(ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPGrid3DActor : public AIPInstancedActor
{
	GENERATED_BODY()

public:
	AIPGrid3DActor();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureInitialTransform* IPProcedureInitialTransform;

	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureGrid3D* IPProcedureGrid3D;

	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureRandomTransform* IPProcedureRandomTransform;
#endif
};
