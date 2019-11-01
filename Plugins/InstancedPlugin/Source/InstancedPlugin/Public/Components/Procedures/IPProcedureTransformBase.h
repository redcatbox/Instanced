// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureTransformBase.generated.h"

USTRUCT(BlueprintType)
struct FPerInstanceTransform
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		int32 InstanceId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ShowOnlyInnerProperties, MakeEditWidget = true))
		FTransform NewTransform;

	FPerInstanceTransform()
	{
		InstanceId = -1;
		NewTransform = FTransform();
	}
};

UCLASS(Abstract, NotBlueprintable, ClassGroup=(Procedure))
class INSTANCEDPLUGIN_API UIPProcedureTransformBase : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureTransformBase();

#if WITH_EDITOR
	UFUNCTION()
		virtual FTransform Operation(FTransform& A, FTransform& B);
#endif

#if WITH_EDITORONLY_DATA
	/** Transform */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ShowOnlyInnerProperties))
		TArray<FPerInstanceTransform> InstancesTransforms;

	/** Apply to location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bApplyToLocation;

	/** Apply to rotation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bApplyToRotation;

	/** Apply to location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bApplyToScale;
#endif
};