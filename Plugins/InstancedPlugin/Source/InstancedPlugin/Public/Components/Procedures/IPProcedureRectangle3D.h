// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureGrid3DBase.h"
#include "IPProcedureRectangle3D.generated.h"

UCLASS(NotBlueprintable, ClassGroup = (Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureRectangle3D : public UIPProcedureGrid3DBase
{
	GENERATED_BODY()

public:
	UIPProcedureRectangle3D();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Do not create corner meshes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bNoCornerMeshes;

	/** Create only corner meshes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bOnlyCornerMeshes;

	/** Override world axes with custom axes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bOrientOutside;

	/** Override world axes with custom axes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bOrientOutside"))
		bool bReverseOrientation;
#endif
};