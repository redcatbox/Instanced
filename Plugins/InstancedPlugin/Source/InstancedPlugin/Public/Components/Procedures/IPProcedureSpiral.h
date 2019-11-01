// Fill out your copyright notice in the Description page of Project Settings.

/** https://en.wikipedia.org/wiki/Archimedean_spiral */

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureSpiral.generated.h"

UCLASS(NotBlueprintable, ClassGroup = (Procedure), Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureSpiral : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureSpiral();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Initial spiral velocity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		FVector InitialLinearVelocity;

	/** Linear acceleration */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		FVector LinearAcceleration;

	/** Angular velocity */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		FVector AngularVelocity;

	/** Time */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		float Time;

	/** Should instances be oriented to central axis? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bOrientToCentralAxis;

	/** Should instances be placed evenly along spiral? */
	//UPROPERTY(EditAnywhere, Category = "Procedure | Parameters")
	//	bool bPlaceEvenly;
#endif
};