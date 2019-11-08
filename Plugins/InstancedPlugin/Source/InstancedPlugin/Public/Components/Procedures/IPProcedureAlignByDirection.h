// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureAlignBase.h"
#include "IPProcedureAlignByDirection.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureAlignByDirection : public UIPProcedureAlignBase
{
	GENERATED_BODY()

public:
	UIPProcedureAlignByDirection();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Direction to align */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true))
		FVector AlignDirection;
#endif
};