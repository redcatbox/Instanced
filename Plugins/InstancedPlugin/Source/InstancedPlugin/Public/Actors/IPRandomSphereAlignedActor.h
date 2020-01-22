// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/Procedures/IPProcedureTransformMultiply.h"
#include "Components/Procedures/IPProcedureRandomSphere.h"
#include "Components/Procedures/IPProcedureRandomTransform.h"
#include "Components/Procedures/IPProcedureAlignFromPoint.h"
#include "IPRandomSphereAlignedActor.generated.h"

UCLASS(ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPRandomSphereAlignedActor : public AIPInstancedHISMActor
{
	GENERATED_BODY()

public:
	AIPRandomSphereAlignedActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureTransformMultiply* IPProcedureTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureRandomSphere* IPProcedureRandomSphere;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureRandomTransform* IPProcedureRandomTransform;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureAlignFromPoint* IPProcedureAlignFromPoint;
#endif
};
