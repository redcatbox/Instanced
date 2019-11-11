// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPInstancedHISMActor.h"
#include "Components/Procedures/IPProcedureTransformMultiply.h"
#include "Components/Procedures/IPProcedureRandomBox.h"
#include "Components/Procedures/IPProcedureAlignByDirection.h"
#include "Components/Procedures/IPProcedureRandomTransform.h"
#include "IPRandomBoxAlignedActor.generated.h"

UCLASS(ClassGroup = (Instanced))
class INSTANCEDPLUGIN_API AIPRandomBoxAlignedActor : public AIPInstancedHISMActor
{
	GENERATED_BODY()

public:
	AIPRandomBoxAlignedActor();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Should random stream be used for randomization? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Generation)
		bool bUseRandomStream;

	/** Random stream seed value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Generation, Meta = (EditCondition = "bUseRandomStream"))
		int32 RandomStreamSeed;

	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureTransformMultiply* IPProcedureTransformMultiply;

	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureRandomBox* IPProcedureRandomBox;

	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureAlignByDirection* IPProcedureAlignByDirection;

	UPROPERTY(VisibleDefaultsOnly)
		UIPProcedureRandomTransform* IPProcedureRandomTransform;
#endif
};
