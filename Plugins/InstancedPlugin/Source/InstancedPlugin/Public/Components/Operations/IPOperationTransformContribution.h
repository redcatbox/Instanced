// redbox, 2022

#pragma once

#include "IPOperationRandomBase.h"
#include "IPOperationTransformContribution.generated.h"

UCLASS(Meta = (BlueprintSpawnableComponent))
class INSTANCEDPLUGIN_API UIPOperationTransformContribution : public UIPOperationRandomBase
{
	GENERATED_BODY()

public:
	UIPOperationTransformContribution();

#if WITH_EDITOR
	virtual void RunOperation(TArray<FTransform>& Transforms) override;
#endif

#if WITH_EDITORONLY_DATA
	/** Contribution of processed transforms */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
	float ContributionRangeStart;

	/** Contribution of processed transforms */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Operation | Parameters", Meta = (ClampMin = "0", UIMin = "0", ClampMax = "1", UIMax = "1"))
	float ContributionRangeEnd;
#endif
};
