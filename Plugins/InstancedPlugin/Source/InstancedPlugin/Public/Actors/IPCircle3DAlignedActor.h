// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/Procedures/IPProcedureTransformMultiply.h"
#include "Components/Procedures/IPProcedureCircle3D.h"
#include "Components/Procedures/IPProcedureRandomTransform.h"
#include "Components/Procedures/IPProcedureAlignFromAxis.h"
#include "IPCircle3DAlignedActor.generated.h"

UCLASS(ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPCircle3DAlignedActor : public AIPInstancedHISMActor
{
	GENERATED_BODY()

public:
	AIPCircle3DAlignedActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureTransformMultiply* IPProcedureTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureCircle3D* IPProcedureCircle3D;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureRandomTransform* IPProcedureRandomTransform;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureAlignFromAxis* IPProcedureAlignFromAxis;
#endif
};
