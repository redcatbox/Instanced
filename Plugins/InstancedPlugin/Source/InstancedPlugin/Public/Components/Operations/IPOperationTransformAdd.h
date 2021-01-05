// redbox, 2021

#pragma once

#include "IPOperationTransformBase.h"
#include "IPOperationTransformAdd.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationTransformAdd : public UIPOperationTransformBase
{
	GENERATED_BODY()

public:
	UIPOperationTransformAdd();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;

	UFUNCTION()
		FTransform Operation(FTransform& A, FTransform& B);
#endif

#if WITH_EDITORONLY_DATA
	/** Increment by instance id */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		bool bPerInstanceIncremental;
#endif
};
