// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPInstancedActor.h"
#include "Components/Procedures/IPProcedureInitialTransform.h"
#include "Components/Procedures/IPProcedureRandomBox.h"
#include "Components/Procedures/IPProcedureRandomTransform.h"
#include "IPRandomBoxActor.generated.h"

UCLASS(ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPRandomBoxActor : public AIPInstancedActor
{
	GENERATED_BODY()

public:
	AIPRandomBoxActor();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Should random stream be used for randomization? */
	UPROPERTY(EditAnywhere, Category = Generation)
		bool bUseRandomStream;

	/** Random stream seed value */
	UPROPERTY(EditAnywhere, Category = Generation, Meta = (EditCondition = "bUseRandomStream"))
		int32 RandomStreamSeed;

	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureInitialTransform* IPProcedureInitialTransform;

	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureRandomBox* IPProcedureRandomBox;

	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureRandomTransform* IPProcedureRandomTransform;
#endif
};
