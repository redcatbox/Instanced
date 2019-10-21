// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureGrid3DBase.h"
#include "IPProcedureRectangle3D.generated.h"

UCLASS(Blueprintable, ClassGroup = (Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureRectangle3D : public UIPProcedureGrid3DBase
{
	GENERATED_BODY()

public:
	UIPProcedureRectangle3D();

#if WITH_EDITOR
	virtual void RunProcedure(int32 NumIterations, TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Override world axes with custom axes */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters")
		bool bNoCornerMeshes;

	/** Override world axes with custom axes */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters")
		bool bOrientOutside;

	/** Override world axes with custom axes */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters", Meta = (EditCondition = "bOrientOutside"))
		bool bReverseOrientation;
#endif
};