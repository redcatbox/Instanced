// redbox, 2022

#pragma once

#include "IPOperationComponent.h"
#include "IPOperationInstanceSpaceBase.generated.h"

UCLASS(Abstract)
class INSTANCEDPLUGIN_API UIPOperationInstanceSpaceBase : public UIPOperationComponent
{
	GENERATED_BODY()

public:
	UIPOperationInstanceSpaceBase();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Space of every instance from it's center */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bInstanceSpaceEditCond"))
	FVector InstanceSpace;

	/** Should set instance space from mesh bounds? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
	bool bInstanceSpaceFromMeshBounds;

	/** Should instance space include current scale? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bInstanceSpaceFromMeshBounds"))
	bool bInstanceSpaceFromMeshBoundsWithCurrentScale;

	UPROPERTY()
	bool bHalfSpaceOffsetEditCond;

	/** Should instances be offset on half space from it's center? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bHalfSpaceOffsetEditCond"))
	bool bHalfSpaceOffset;
#endif

protected:
	UPROPERTY()
	bool bInstanceSpaceEditCond;
};
