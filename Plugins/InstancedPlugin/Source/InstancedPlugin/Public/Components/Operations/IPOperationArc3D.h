// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPOperationInstanceSpaceBase.h"
#include "IPOperationArc3D.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationArc3D : public UIPOperationInstanceSpaceBase
{
	GENERATED_BODY()

public:
	UIPOperationArc3D();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Number of instances to create */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (ShowOnlyInnerProperties))
		FIntVector InstancesNum3D;

	/** Arc 1st point */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (MakeEditWidget = true))
		FVector Point1;

	/** Arc 2nd point */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (MakeEditWidget = true))
		FVector Point2;

	/** Arc 3rd point */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (MakeEditWidget = true))
		FVector Point3;

	/** Should instances be oriented to central axis? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters")
		bool bOrientToCenter;
#endif
};