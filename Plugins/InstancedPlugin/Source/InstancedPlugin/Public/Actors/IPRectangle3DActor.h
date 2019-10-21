// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPInstancedActor.h"
#include "Components/Procedures/IPProcedureInitialTransform.h"
#include "Components/Procedures/IPProcedureRectangle3D.h"
#include "Components/Procedures/IPProcedureRandomTransform.h"
#include "IPRectangle3DActor.generated.h"

UCLASS(ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPRectangle3DActor : public AIPInstancedActor
{
	GENERATED_BODY()

public:
	AIPRectangle3DActor();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureInitialTransform* IPProcedureInitialTransform;

	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureRectangle3D* IPProcedureRectangle3D;

	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureRandomTransform* IPProcedureRandomTransform;
#endif
};
