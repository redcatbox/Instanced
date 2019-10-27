// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureRandomBase.h"
#include "IPProcedureRandomSphere.generated.h"

UCLASS(Blueprintable, ClassGroup = (Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureRandomSphere : public UIPProcedureRandomBase
{
	GENERATED_BODY()

public:
	UIPProcedureRandomSphere();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Should location be randomized? */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true))
		FVector BoxExtent;

	/** Should instances be generated on sphere surface only? */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters")
		bool bOnSurfaceOnly;

	/** Should instances be oriented to sphere center? */
	UPROPERTY(EditAnywhere, Category = "Procedure | Parameters")
		bool bOrientToCenter;
#endif
};