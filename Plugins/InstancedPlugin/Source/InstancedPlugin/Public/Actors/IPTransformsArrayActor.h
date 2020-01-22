// Dmitriy Barannik aka redbox, 2020

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
	UPROPERTY(VisibleDefaultsOnly, Category = Procedures)
		UIPProcedureTransformsArray* IPProcedureTransformsArray;
#endif
};