// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPProcedureInstanceSpaceBase.h"
#include "IPProcedureGrid3DBase.generated.h"

UCLASS(Abstract)
class INSTANCEDPLUGIN_API UIPProcedureGrid3DBase : public UIPProcedureInstanceSpaceBase
{
	GENERATED_BODY()

public:
	UIPProcedureGrid3DBase();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Number of instances to create */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ShowOnlyInnerProperties))
		FIntVector InstancesNum3D;

	/** Override world axes with custom axes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bUseCustomAxes;

	/** Custom X axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true, EditCondition = "bUseCustomAxes"))
		FVector CustomAxis_X;

	/** Custom Y axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true, EditCondition = "bUseCustomAxes"))
		FVector CustomAxis_Y;

	/** Custom Z axis */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (MakeEditWidget = true, EditCondition = "bUseCustomAxes"))
		FVector CustomAxis_Z;

	/** Orient by custom axes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bUseCustomAxes"))
		bool bOrientByCustomAxes;
#endif
};