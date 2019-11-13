// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureGrid3DBase.h"
#include "IPProcedureRectangle3D.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureRectangle3D : public UIPProcedureGrid3DBase
{
	GENERATED_BODY()

public:
	UIPProcedureRectangle3D();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Create corner meshes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bCornersMeshes;

	/** Orient corner meshes around the object */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bOrientCornersMeshesAround;

	/** Create sides meshes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bSidesMeshes;

	/** Orient sides meshes outside */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bOrientSidesMeshesOutside;

	/** Orient sides meshes inside */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bOrientSidesMeshesOutside"))
		bool bReverseSidesMeshesOrientation;
#endif
};