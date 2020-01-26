// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/Procedures/IPProcedureTransformMultiply.h"
#include "Components/Procedures/IPProcedureArc3D.h"
#include "Components/Procedures/IPProcedureAlignFromAxis.h"
#include "Components/Procedures/IPProcedureRandomTransform.h"
#include "IPArc3DAlignedActor.generated.h"

UCLASS(ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPArc3DAlignedActor : public AIPInstancedHISMActor
{
	GENERATED_BODY()

public:
	AIPArc3DAlignedActor();

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureTransformMultiply* IPProcedureTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureArc3D* IPProcedureArc3D;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureAlignFromAxis* IPProcedureAlignFromAxis;

	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureRandomTransform* IPProcedureRandomTransform;
#endif
};