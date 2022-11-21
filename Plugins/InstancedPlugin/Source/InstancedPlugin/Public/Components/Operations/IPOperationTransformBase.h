// redbox, 2022

#pragma once

#include "IPOperationComponent.h"
#include "IPOperationTransformBase.generated.h"

USTRUCT(BlueprintType)
struct FPerInstanceTransform
{
	GENERATED_BODY()

	UPROPERTY()
		bool bInstanceIdEditCond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (ClampMin = "-1", UIMin = "-1", EditCondition = "bInstanceIdEditCond"))
		int32 InstanceId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (ShowOnlyInnerProperties, MakeEditWidget = true))
		FTransform NewTransform;

	FPerInstanceTransform()
	{
		bInstanceIdEditCond = true;
		InstanceId = 0;
		NewTransform = FTransform();
	}

	FPerInstanceTransform(int32 InstId, FTransform NewTransf)
	{
		bInstanceIdEditCond = true;
		InstanceId = InstId;
		NewTransform = NewTransf;
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

UCLASS(Abstract)
class INSTANCEDPLUGIN_API UIPOperationTransformBase : public UIPOperationComponent
{
	GENERATED_BODY()

public:
	UIPOperationTransformBase();

#if WITH_EDITOR
	/** Copy existing instances transforms to operation transforms array.
	This operation will replace existing OperationTransforms data.
	This operation will not update instances automatically. */
	UFUNCTION(BlueprintCallable, CallInEditor, Category = Operation)
	virtual void CopyTransforms();
#endif

#if WITH_EDITORONLY_DATA
	/** Transforms to use in operation. If contains any with InstanceId = -1, that one will be applied to all instances. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (ShowOnlyInnerProperties))
	TArray<FPerInstanceTransform> OperationTransforms;
#endif
};
