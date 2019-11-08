// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IPProcedureComponent.h"
#include "IPProcedureTransformBase.generated.h"

#if WITH_EDITOR
USTRUCT(BlueprintType)
struct FPerInstanceTransform
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ClampMin = "-1", UIMin = "-1"))
		int32 InstanceId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ShowOnlyInnerProperties, MakeEditWidget = true))
		FTransform NewTransform;

	FPerInstanceTransform()
	{
		InstanceId = 0;
		NewTransform = FTransform();
	}
};

USTRUCT()
struct FSortByInstanceId
{
	GENERATED_BODY()

	FSortByInstanceId() {}

	bool operator()(const FPerInstanceTransform& A, const FPerInstanceTransform& B) const
	{
		return A.InstanceId < B.InstanceId;
	}
};
#endif

UCLASS(Abstract)
class INSTANCEDPLUGIN_API UIPProcedureTransformBase : public UIPProcedureComponent
{
	GENERATED_BODY()

public:
	UIPProcedureTransformBase();

#if WITH_EDITORONLY_DATA
	/** Transforms to use in operation. If contains any with InstanceId = -1, that one will be applied to all instances. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ShowOnlyInnerProperties))
		TArray<FPerInstanceTransform> OperationTransforms;
#endif
};