// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureRandomBase.h"
#include "IPProcedureTransformsContribution.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureTransformsContribution : public UIPProcedureRandomBase
{
	GENERATED_BODY()

public:
	UIPProcedureTransformsContribution();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Contribution of processed transforms */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
		float ContributionRangeStart;

	/** Contribution of processed transforms */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
		float ContributionRangeEnd;
#endif
};