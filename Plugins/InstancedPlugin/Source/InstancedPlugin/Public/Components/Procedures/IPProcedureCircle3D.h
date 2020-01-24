// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPProcedureInstanceSpaceBase.h"
#include "IPProcedureCircle3D.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPProcedureCircle3D : public UIPProcedureInstanceSpaceBase
{
	GENERATED_BODY()

public:
	UIPProcedureCircle3D();

#if WITH_EDITOR
	virtual void RunProcedure(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Number of instances to create */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (ShowOnlyInnerProperties))
		FIntVector InstancesNum3D;

	/** Angle to place instances in */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		float PlacementAngle;

	/** Should instances be oriented to central axis? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bOrientToCentralAxis;

	/** Should make odd/even rows in checker pattern? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bCheckerOddEven;

	/** Should flip odd/even rows? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bFlipOddEven;
#endif
};