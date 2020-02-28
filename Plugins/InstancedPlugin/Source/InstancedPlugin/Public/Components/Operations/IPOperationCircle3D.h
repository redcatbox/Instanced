// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPOperationInstanceSpaceBase.h"
#include "IPOperationCircle3D.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationCircle3D : public UIPOperationInstanceSpaceBase
{
	GENERATED_BODY()

public:
	UIPOperationCircle3D();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Number of instances to create */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (ShowOnlyInnerProperties))
		FIntVector InstancesNum3D;

	/** Angle to place instances from */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		float StartAngle;

	/** Angle to place instances to */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		float EndAngle;

	/** Should offset instances to align with the end of placement angle? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		bool bAlignWithAngleEnd;

	/** Should instances be oriented to central axis? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		bool bOrientToCentralAxis;

	/** Should make odd/even rows by Z in checker pattern? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		bool bCheckerOddEven_Z;

	/** Should flip odd/even of Z rows? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bCheckerOddEven_Z"))
		bool bFlipOddEven_Z;

	/** Should flip odd/even rows? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (EditCondition = "bCheckerOddEven_Z"))
		bool bSymmetricalEven_Z;
#endif
};