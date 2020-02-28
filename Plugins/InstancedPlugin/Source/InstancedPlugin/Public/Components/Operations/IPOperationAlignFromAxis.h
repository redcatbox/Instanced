// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPOperationAlignBase.h"
#include "IPOperationAlignFromAxis.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationAlignFromAxis : public UIPOperationAlignBase
{
	GENERATED_BODY()

public:
	UIPOperationAlignFromAxis();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Axis start */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (MakeEditWidget = true))
		FVector AlignAxisStart;

	/** Axis end */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (MakeEditWidget = true))
		FVector AlignAxisEnd;

	/** Distance to align at */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (ClampMin = "0", UIMin = "0"))
		float AlignDistance;
#endif
};