// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureAlignByDirection.generated.h"

UCLASS(Blueprintable, ClassGroup = (Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureAlignByDirection : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureAlignByDirection();

#if WITH_EDITOR
	virtual void RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Direction to align */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true))
		FVector AlignDirection;

	/** Should orient to surface? */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters")
		bool bOrientToSurface;
#endif
};