// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureRandomBase.generated.h"

UCLASS(Abstract, ClassGroup = (Procedure))
class INSTANCEDPLUGIN_API UIPProcedureRandomBase : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureRandomBase();

#if WITH_EDITOR
	virtual void RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	UPROPERTY()
		bool bUseRandomStreamEditCondition;

	UPROPERTY()
		bool bUseRandomStreamSeedEditCondition;

	/** Should random stream be used for randomization? */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters", Meta = (EditCondition = "bUseRandomStreamEditCondition"))
		bool bUseRandomStream;

	/** Random stream seed value */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters", Meta = (EditCondition = "bUseRandomStreamSeedEditCondition"))
		int32 RandomStreamSeed;

	UPROPERTY()
		FRandomStream RandomStream;
#endif
};