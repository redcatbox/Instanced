// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureGrid3DBase.h"
#include "IPProcedureGrid3DHexagonal.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureGrid3DHexagonal : public UIPProcedureGrid3DBase
{
	GENERATED_BODY()

public:
	UIPProcedureGrid3DHexagonal();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Should odd and even rows be fliIPed along X axis? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bFlipOddEven_X;

	/** Should grid be symmetrical along Y axiz? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bSymmetrical_Y;
#endif
};