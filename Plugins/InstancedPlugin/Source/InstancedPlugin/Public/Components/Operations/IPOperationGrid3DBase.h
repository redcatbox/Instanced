// redbox, 2020

#pragma once

#include "IPOperationInstanceSpaceBase.h"
#include "IPOperationGrid3DBase.generated.h"

UCLASS(Abstract)
class INSTANCEDPLUGIN_API UIPOperationGrid3DBase : public UIPOperationInstanceSpaceBase
{
	GENERATED_BODY()

public:
	UIPOperationGrid3DBase();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Number of instances to create */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (ShowOnlyInnerProperties))
		FIntVector InstancesNum3D;

	UPROPERTY()
		bool bRemoveInnerInstancesEditCond;

	/** Remove inner instances */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bRemoveInnerInstancesEditCond"))
		bool bRemoveInnerInstances;

	/** Override world axes with custom axes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		bool bUseCustomAxes;

	/** Custom X axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (MakeEditWidget = true, EditCondition = "bUseCustomAxes"))
		FVector CustomAxis_X;

	/** Custom Y axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (MakeEditWidget = true, EditCondition = "bUseCustomAxes"))
		FVector CustomAxis_Y;

	/** Custom Z axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (MakeEditWidget = true, EditCondition = "bUseCustomAxes"))
		FVector CustomAxis_Z;

	/** Orient by custom axes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bUseCustomAxes"))
		bool bOrientByCustomAxes;
#endif
};