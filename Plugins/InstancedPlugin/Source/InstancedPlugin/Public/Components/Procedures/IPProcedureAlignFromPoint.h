// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureAlignBase.h"
#include "IPProcedureAlignFromPoint.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureAlignFromPoint : public UIPProcedureAlignBase
{
	GENERATED_BODY()

public:
	UIPProcedureAlignFromPoint();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Center to align from */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true))
		FVector AlignPoint;

	/** Distance to align at */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ClampMin = "0", UIMin = "0"))
		float AlignDistance;
#endif
};