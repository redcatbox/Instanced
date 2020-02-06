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

	/** Angle to place instances from */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		float StartAngle;

	/** Angle to place instances to */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		float EndAngle;

	/** Should offset instances to align with the end of placement angle? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bAlignWithAngleEnd;

	/** Should instances be oriented to central axis? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bOrientToCentralAxis;

	/** Should make odd/even rows in checker pattern? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters")
		bool bCheckerOddEven;

	/** Should flip odd/even of Y rows? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bCheckerOddEven"))
		bool bFlipOddEven_Y;

	/** Should flip odd/even of Z rows? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bCheckerOddEven"))
		bool bFlipOddEven_Z;

	/** Should flip odd/even rows? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Procedure | Parameters", Meta = (EditCondition = "bCheckerOddEven"))
		bool bSymmetricalEven;
#endif
};