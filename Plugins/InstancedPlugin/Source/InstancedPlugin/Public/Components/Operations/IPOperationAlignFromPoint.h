// Dmitriy Barannik aka redbox, 2020

#pragma once

#include "IPOperationAlignBase.h"
#include "IPOperationAlignFromPoint.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationAlignFromPoint : public UIPOperationAlignBase
{
	GENERATED_BODY()

public:
	UIPOperationAlignFromPoint();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Center to align from */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (MakeEditWidget = true))
		FVector AlignPoint;

	/** Distance to align at */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (ClampMin = "0", UIMin = "0"))
		float AlignDistance;
#endif
};