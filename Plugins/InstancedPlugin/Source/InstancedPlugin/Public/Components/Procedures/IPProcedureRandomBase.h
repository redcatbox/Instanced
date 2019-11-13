// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureRandomBase.generated.h"

UCLASS(Abstract)
class INSTANCEDPLUGIN_API UIPProcedureRandomBase : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureRandomBase();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Should random stream be used for randomization? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bUseRandomStream;

	/** Random stream seed value */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bUseRandomStream"))
		int32 RandomStreamSeed;

	UPROPERTY()
		FRandomStream RandomStream;
#endif
};